#include "userstab.h"
#include <iostream>
#include <string>
#include <numeric>
#include <functional>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "csv.h"
#include "../components/globals.h"


namespace fs = std::filesystem;
using std::cout,std::endl,std::vector,std::string;






void renderUsersTab(){
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
}
