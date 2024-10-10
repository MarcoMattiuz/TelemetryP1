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
          ImGui::MenuItem(("role: "+getRole(glb::role)).c_str());
          if(ImGui::MenuItem("LOGOUT")){
            logout();
          }
          if(glb::role == Admin){
            if(ImGui::MenuItem("CREATE NEW USER")){
              cout << "ADMIN";
              ImGui::OpenPopup("CREATEUSER");
              createUser(window);
            }
           
          }
          ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
      }
      
      

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
                //user tab - logout 
                //TODO *optional: see all users available (without password, obviously)
                if(ImGui::BeginTabItem("User")){

                  
                  ImGui::EndTabItem();
                }



                ImGui::EndTabBar();
        }



 
  
  ImGui::End();
}
