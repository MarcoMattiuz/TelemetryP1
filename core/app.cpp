#include <iostream>
#include <string>
#include <numeric>
#include <functional>
#include <GLFW/glfw3.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "components/graphs.h"
#include "app.h"
#include "csv.h"
#include "components/globals.h"
#include "components/login.h"
#include "tabItems/userstab.h"
#include "tabItems/graphstab.h"

using std::cout,std::endl,std::vector,std::string;
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
            
            renderGraphsTab(window);
            renderUsersTab();

            
            ImGui::EndTabBar();
    }



 
  
  ImGui::End();
}
