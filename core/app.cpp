#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "components/graphs.h"
#include "app.h"
#include "csv.h"
#include "components/globals.h"
#include "components/login.h"

using std::cout,std::endl,std::vector,std::string;
csvformat csv;
bool dataLoaded = false;  
bool openPopupCreateUser = false;

vector<string> csvfiles;
string selectedFile = "None";
string folderPath = "../csv_samples/";

static int item_selected_idx = 0; 
static bool item_highlight = false;
int item_highlighted_idx = -1; 

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
                  //TODO: make a list of files and load them
                  // *** List of files group
                 
                  
                 
                  ImGui::BeginChild("files",ImVec2((windowWidth-100.0),windowHeight));

                  if(ImGui::Button("LOAD FILES",ImVec2(100,20))){
                    

                      try {
                          for (const auto& entry : fs::directory_iterator(folderPath)) {
                            csvfiles.push_back(entry.path().filename().string());
                              std::cout << entry.path().filename().string() << std::endl;
                          }
                      } catch (const fs::filesystem_error& e) {
                          std::cerr << "Errore: " << e.what() << std::endl;
                      }
                    
                  }

                  ImGui::SameLine();
                  string displaySelectedFile = "Selected File: " + selectedFile;
                  ImGui::TextColored(ImVec4(0,1,0,1),displaySelectedFile.c_str());
                  ImGui::Separator();
               
                  if (ImGui::BeginListBox("##fileslist",ImVec2(200, windowHeight)))
                  {
                      for (int n = 0; n < csvfiles.size(); n++)
                      {
                          const bool is_selected = (item_selected_idx == n);
                          
                          if (ImGui::Button(csvfiles[n].c_str())){
                              selectedFile = folderPath + csvfiles[n];
                          }
                              
                              // item_selected_idx = n;

                          if (item_highlight && ImGui::IsItemHovered())
                              item_highlighted_idx = n;

                          // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                          if (is_selected)
                              ImGui::SetItemDefaultFocus();
                      }
                      ImGui::EndListBox();
                  }
                  ImGui::SameLine();
                  ImPlot::BeginPlot("Plot 1",ImVec2(600,0));
                 
                  ImPlot::EndPlot();
                  


                  ImGui::EndChild();

        

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
