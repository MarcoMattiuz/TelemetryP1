#include <iostream>

#include "graphs.h"
#include "app.h"
#include "csv.h";
char username[100] = "";
char password[100] = "";
using std::cout,std::endl,std::vector;





  
void app_render(Acceleration acc) {

  


  

  ImGui::ShowDemoWindow();
  ImPlot::ShowDemoWindow();
  ImGui::Begin("Project 1");
  ImGui::Text("Project 1");
  ImVec4 redColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
  ImGui::InputText("username",username,sizeof(username));
  ImGui::InputText("password",password,sizeof(password), ImGuiInputTextFlags_Password);
  PlotAcceleration(acc);
  ImGui::End();
}
