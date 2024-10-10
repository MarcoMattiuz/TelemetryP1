#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>
#include "../app.h"
#include "csv.h"
#include "globals.h"
#include "login.h"
using std::string,std::cout,std::endl;

bool showLoginPopup = true;
bool showPassword = false;

char usernameBuffer[256];
char passwordBuffer[256];
string passwordHash;


bool pswOK = false;



string stringToHash(string );


void LogIn(GLFWwindow *window){

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    const ImVec2 popupSize(500, 400); 

    if (glb::role == None) {
        ImGui::OpenPopup("Login");
    }

 
    if (ImGui::BeginPopupModal("Login", nullptr, ImGuiWindowFlags_NoResize)) {

        ImGui::SetWindowSize(popupSize);

        //input username
        ImGui::InputText("Input", usernameBuffer, sizeof(usernameBuffer));
      
        //Input password
        if (showPassword) {
            ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_None); // Mostra la password
        } else {
            ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password); // Nasconde la password
        }
        
        // toggle password
        if (ImGui::Button(showPassword ? "Hide" : "Show")) {
            showPassword = !showPassword; 
        }
        
        //readFile
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

        //check
        if(!glb::username.empty()){
            if(pswOK){
                
                ImGui::CloseCurrentPopup();
            }else{
                ImGui::OpenPopup("ERRORPASSWORD");    
            }
        }else{
            ImGui::OpenPopup("ERRORUSERNAME");
        }
        passwordBuffer[0] = '\0';
        usernameBuffer[0] = '\0';  
        }
        if(ImGui::BeginPopup("ERRORUSERNAME",ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize)){
            ImGui::TextColored(ImVec4(1,0,0,1),"Username does not exist");
            ImGui::EndPopup();
        }
        if(ImGui::BeginPopup("ERRORPASSWORD",ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize)){
            ImGui::TextColored(ImVec4(1,0,0,1),"Password is incorrect");
            ImGui::EndPopup();
        }


        

        ImGui::SameLine(ImGui::GetWindowWidth() - 50); // Posiziona la X a destra
        if (ImGui::Button("X", ImVec2(30, 30))) {
            glb::role = Admin;
            ImGui::CloseCurrentPopup(); // Chiude il pop-up
        }

        ImGui::EndPopup();
    }
  
  
}

void createUser(GLFWwindow *window){
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    const ImVec2 popupSize(500, 400); 

  

 
    if (ImGui::BeginPopupModal("CREATEUSER", nullptr, ImGuiWindowFlags_NoResize)) {

        ImGui::SetWindowSize(popupSize);

        //input username
        ImGui::InputText("Input", usernameBuffer, sizeof(usernameBuffer));
      
        //Input password
        if (showPassword) {
            ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_None); // Mostra la password
        } else {
            ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password); // Nasconde la password
        }
        //TODO list of roles
        // toggle password
        if (ImGui::Button(showPassword ? "Hide" : "Show")) {
            showPassword = !showPassword; 
        }
    
    ImGui::EndPopup();
    }
}


string stringToHash(string str){
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(str);
    std::ostringstream oss;
    oss << hash;  
    std::string hash_string = oss.str();
    cout << hash_string;
    return hash_string;
}