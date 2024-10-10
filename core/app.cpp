#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>
// #include "imgui/backends/imgui_impl_glfw.h"
// #include "imgui/backends/imgui_impl_opengl2.h"
#include "graphs.h"
#include "app.h"
#include "csv.h";
#include "globals.h";

using std::cout,std::endl,std::vector,std::string;
Acceleration acc;
bool dataLoaded = false;  
bool showLoginPopup = true;
bool showPassword = false;

char usernameBuffer[256];
char passwordBuffer[256];
string passwordHash;


bool pswOK = false;


string stringToHash(string str){
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(str);
    std::ostringstream oss;
    oss << hash;  
    std::string hash_string = oss.str();
    cout << hash_string;
    return hash_string;
}



void app_render(GLFWwindow *window) {

    
  int windowWidth, windowHeight;
  glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
  const ImVec2 popupSize(500, 400); 
  


  if (glb::role == None) {
        ImGui::OpenPopup("Login");
    }

    // Definisci il pop-up modale per il login
    if (ImGui::BeginPopupModal("Login", nullptr, ImGuiWindowFlags_NoResize)) {

        ImGui::SetWindowSize(popupSize);
        
        

       
        ImGui::InputText("Input", usernameBuffer, sizeof(usernameBuffer));
      
         // Input per password
        if (showPassword) {
            ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_None); // Mostra la password
        } else {
            ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password); // Nasconde la password
        }
        
        // Pulsante per mostrare/nascondere la password
        if (ImGui::Button(showPassword ? "Hide" : "Show")) {
            showPassword = !showPassword; // Cambia il flag
        }
        
        if(ImGui::Button("LOG-IN",ImVec2(50,20))){
          passwordHash = stringToHash(passwordBuffer);

          io::CSVReader<3> in("../core/logins.csv");
          in.read_header(io::ignore_missing_column, "username","password","role");
          string username,filepassword;
          int role;
          while(in.read_row(username,filepassword,role)){
              if(username == usernameBuffer){
                glb::username = usernameBuffer;
              }
              if(filepassword==passwordHash){
                pswOK = true;
                setRole(role);
              }
          }
          if(!glb::username.empty()){
            if(pswOK){
              ImGui::CloseCurrentPopup();
            }
          }

          

        }



        ImGui::SameLine(ImGui::GetWindowWidth() - 50); // Posiziona la X a destra
        if (ImGui::Button("X", ImVec2(30, 30))) {
            glb::role = Admin;
            ImGui::CloseCurrentPopup(); // Chiude il pop-up
        }

        ImGui::EndPopup();
    }
  
  
  
  
  

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight));

    //Main window 
    ImGui::Begin("Telemetry P1",nullptr, 
    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
  

  
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

            if(ImGui::BeginTabItem("User")){
              ImGui::Text(glb::username.c_str());
              ImGui::Text(getRole(glb::role).c_str());
              ImGui::EndTabItem();
            }



            ImGui::EndTabBar();
        }



 
  
  ImGui::End();
}
