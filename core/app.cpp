#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>

#include "components/graphs.h"
#include "app.h"
#include "csv.h"
#include "components/globals.h"
#include "components/login.h"

using std::cout,std::endl,std::vector,std::string;
Acceleration acc;
bool dataLoaded = false;  
bool openPopupCreateUser = false;





void app_render(GLFWwindow *window) {

    
  int windowWidth, windowHeight;
  glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

  
  LogIn(window);
  
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight));

    //Main window 
    ImGui::Begin("Telemetry P1",
    nullptr, 
     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar
    );

      if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("USER MENU")){
          ImGui::MenuItem(("username: " + glb::username).c_str());
          ImGui::MenuItem(("role: "+getRoleStr(glb::role)).c_str());
          if(ImGui::MenuItem("LOGOUT")){
            logout();
          }
          if(glb::role == Admin){
            if(ImGui::MenuItem("CREATE NEW USER")){
              cout << "ADMIN";
              
              openPopupCreateUser = true;
              // createUser(window);
            }
           
          }
          ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
      }
      
      if(openPopupCreateUser){
        ImGui::OpenPopup("CREATEUSER");
        openPopupCreateUser = false;
      }

      // if(ImGui::BeginPopupModal("CREATEUSER")){
      //   ImGui::Text("OK!");
      //   ImGui::EndPopup();
      // }
      createUser(window);
      

      if (ImGui::BeginTabBar("bar", ImGuiTabBarFlags_Reorderable))
            {
                
                if(glb::role == Admin){
                  //1
                  if (ImGui::BeginTabItem("Demo ImGui"))
                    {
                      ImGui::ShowDemoWindow();
                      ImGui::EndTabItem();
                    }
                  //2
                  if (ImGui::BeginTabItem("Demo ImPlot"))
                    {
                      ImPlot::ShowDemoWindow();
                      ImGui::EndTabItem();
                    }
                }
                
                if (ImGui::BeginTabItem("Plot files"))
                {
                //TODO: FIX plotting
                  if (ImGui::Button("Graph Acceleration")) {
                    
                      loadAccelerationCSV(acc);
                      cout << "caricato" << endl;
                      dataLoaded=!dataLoaded;
                  }
        
                if (dataLoaded) {
                    PlotAcceleration(acc);
                } else {
                    
                    ImGui::Text("Premi 'Carica' per visualizzare i dati.");
                    
                }

                  ImGui::EndTabItem();
                }
                
                
                if(glb::role == Admin){
                  if(ImGui::BeginTabItem("Users List")){
                    vector<string> usernames;
                    vector<string> roles;
                    io::CSVReader<2> in("../core/logins.csv");
                    in.read_header(io::ignore_extra_column, "username","role");
                    string username,filepassword;
                    int role;
                    while(in.read_row(username,role)){
                       usernames.push_back(username);
                       roles.push_back(getRoleStr(getRoleByN(role)));
                    }
                    //TODO *optional: see all users available (without password, obviously)
                    ImGui::BeginTable("Users",2,ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders,ImVec2(400,50));
                      ImGui::TableSetupColumn("username");
                      ImGui::TableSetupColumn("role");

                      // Aggiungi la riga degli header
                      ImGui::TableHeadersRow();

                      
                    for (int i = 0; i < usernames.size(); i++)
                    {ImGui::TableNextColumn();

                      ImGui::TableSetColumnIndex(0);
                      ImGui::Text(usernames[i].c_str());

                      ImGui::TableSetColumnIndex(1);
                      ImGui::Text(roles[i].c_str());

                      
                    }
                      ImGui::EndTable();
                    ImGui::EndTabItem();
                  }
                }
                



                ImGui::EndTabBar();
        }



 
  
  ImGui::End();
}
