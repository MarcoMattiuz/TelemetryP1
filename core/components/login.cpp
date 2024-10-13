#include <iostream>
#include <functional>
#include <fstream>
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

bool userExists = false;



string stringToHash(string );


void LogIn(GLFWwindow *window){

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    const ImVec2 popupSize(350, 200); 

    if (glb::role == None) {
        ImGui::OpenPopup("Login");
    }

 
    if (ImGui::BeginPopupModal("Login", nullptr, ImGuiWindowFlags_NoResize)) {

        ImGui::SetWindowSize(popupSize);
        ImGui::SetWindowFontScale(1.5f);  
        ImGui::Text("Login");
        ImGui::SetWindowFontScale(1.0f);   
        ImGui::Separator();
        //input username
        ImGui::TextColored(ImVec4(0,1,0,1),"Username:");
        ImGui::InputText("##username", usernameBuffer, sizeof(usernameBuffer),ImGuiInputFlags_Tooltip);
      
        //Input password
        ImGui::TextColored(ImVec4(0,1,0,1),"Password:");
        if (showPassword) {
            ImGui::InputText("##Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_None); // Mostra la password
        } else {
            ImGui::InputText("##Password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password); // Nasconde la password
        }
        ImGui::SameLine();
        // toggle password
        if (ImGui::Button(showPassword ? "Hide" : "Show")) {
            showPassword = !showPassword; 
        }
        
        //readFile
        if(ImGui::Button("LOGIN",ImVec2(50,20)) || ImGui::IsKeyPressed(ImGuiKey_Enter,false)){
            
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
            passwordHash.clear();
        }

        if(ImGui::BeginPopup("ERRORUSERNAME",ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize)){
            ImGui::TextColored(ImVec4(1,0,0,1),"Username does not exist");
            ImGui::EndPopup();
        }
        if(ImGui::BeginPopup("ERRORPASSWORD",ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize)){
            ImGui::TextColored(ImVec4(1,0,0,1),"Password is incorrect");
            ImGui::EndPopup();
        }


        

        // ImGui::SameLine(ImGui::GetWindowWidth() - 60); 
        // if (ImGui::Button("X", ImVec2(30, 30))) {
        //     glb::role = Admin;
        //     ImGui::CloseCurrentPopup(); 
        // }

        ImGui::EndPopup();
    }
  
  
}

void createUser(GLFWwindow *window){
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    const ImVec2 popupSize(350, 300); 

 
    if (ImGui::BeginPopupModal("CREATEUSER", nullptr, ImGuiWindowFlags_NoResize)) {

        ImGui::SetWindowSize(popupSize);
        ImGui::SetWindowFontScale(1.5f);  
        ImGui::Text("Create new User");
        ImGui::SetWindowFontScale(1.0f);   
        ImGui::Separator();
        //input username
        ImGui::TextColored(ImVec4(0,1,0,1),"Username:");
        ImGui::InputText("##createusername", usernameBuffer, sizeof(usernameBuffer),ImGuiInputFlags_Tooltip);
      
        //Input password
        ImGui::TextColored(ImVec4(0,1,0,1),"Password:");
        if (showPassword) {
            ImGui::InputText("##createpassword", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_None); // Mostra la password
        } else {
            ImGui::InputText("##createpassword", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password); // Nasconde la password
        }
        ImGui::SameLine();
        // toggle password
        if (ImGui::Button(showPassword ? "Hide" : "Show")) {
            showPassword = !showPassword; 
        }
        //TODO:
      

        const char* items[] = { "Admin", "Engeneer", "Pilot"};
        static int item_selected_idx = 0; 

        static bool item_highlight = false;
        int item_highlighted_idx = -1; 
        // ImGui::Checkbox("Highlight hovered item in second listbox", &item_highlight);

        if (ImGui::BeginListBox("##roleslist",ImVec2(100, 60)))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                    item_selected_idx = n;

                if (item_highlight && ImGui::IsItemHovered())
                    item_highlighted_idx = n;

                
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        
       
                    
            if(ImGui::Button("CREATE USER",ImVec2(50,20))|| ImGui::IsKeyPressed(ImGuiKey_Enter,false)){
             
                passwordHash = stringToHash(passwordBuffer);
          
                io::CSVReader<1> in("../core/logins.csv");
                in.read_header(io::ignore_extra_column, "username");
                string username;
                while(in.read_row(username)){
                    if(username == usernameBuffer){
                        userExists = true;
                    }
                }
              

                if(userExists){
                    ImGui::OpenPopup("ERRORUSERNAMEEXISTS");
                    userExists = false;
                }else{
                    if(usernameBuffer[0] != '\0' && passwordBuffer[0] != '\0'){
                        std::ofstream file("../core/logins.csv", std::ios::app);

                        
                        if (!file.is_open()) {
                            std::cerr << "Error opening file." << std::endl;
                        }else{

                   
                            std::vector<std::string> newRow = {usernameBuffer, passwordHash,std::to_string(item_selected_idx+1)};
                            for (size_t i = 0; i < newRow.size(); ++i) {
                                file << newRow[i];
                                if (i < newRow.size() - 1) {
                                    file << ",";  
                                }
                            }
                            file << "\n"; 
                            file.close();
                            passwordBuffer[0] = '\0';
                            usernameBuffer[0] = '\0';  
                            passwordHash.clear();
                            ImGui::CloseCurrentPopup();
                        }
                    }else{
                        ImGui::OpenPopup("COMPILEINPUTS");
                    }
                }


                
            }
        
        ImGui::SameLine(); 
        if (ImGui::Button("EXIT", ImVec2(50, 20))) {
            ImGui::CloseCurrentPopup(); 
        }
        


        if(ImGui::BeginPopup("ERRORUSERNAMEEXISTS",ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize)){
            ImGui::TextColored(ImVec4(1,0,0,1),"This username Already Exists");
            ImGui::EndPopup();
        }

        if(ImGui::BeginPopup("COMPILEINPUTS",ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize)){
            ImGui::TextColored(ImVec4(1,0,0,1),"compile all the fields");
            ImGui::EndPopup();
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
    return hash_string;
}