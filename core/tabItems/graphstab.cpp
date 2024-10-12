
#include "graphstab.h"
#include <iostream>
#include <string>
#include <numeric>
#include <functional>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "csv.h"
#include "../components/globals.h"
#include "../components/graphs.h"


namespace fs = std::filesystem;
using std::cout,std::endl,std::vector,std::string;

csvformat csv;
bool dataLoaded = false;  


vector<string> csvfiles;
string selectedFile = "None";
string showSelectedFile = "None";
string folderPath = "../csv_samples/";


static int item_selected_idx = 0; 
static bool item_highlight = false;
int item_highlighted_idx = -1; 


double findAvg(vector<double> v){
    double sum = std::accumulate(v.begin(),v.end(),0);
    return sum/v.size();
}


void RenderMapWithPoints(vector<double> xCoords,vector<double> yCoords)
{

    ImGui::BeginChild("map",ImVec2(500,500));
    double scale = 2.0f;
   
    const float mapWidth = 300.0f;
    const float mapHeight = 200.0f;

    
    ImGui::SetCursorPos(ImVec2(0, 0)); 
    ImGui::InvisibleButton("map", ImVec2(mapWidth, mapHeight)); 

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 mapPos = ImGui::GetCursorScreenPos(); 
    // drawList->AddRect(mapPos, ImVec2(mapPos.x + mapWidth, mapPos.y + mapHeight), IM_COL32(0, 255, 0, 255));

    double centerX = mapPos.x + mapWidth/2;
    double centery = mapPos.y + mapHeight/2;

  
    for (size_t i = 0; i < xCoords.size(); ++i)
    {
        float x = (centerX + xCoords[i] * scale);
        float y = (centery + yCoords[i] * scale); 

        drawList->AddCircle(ImVec2(x, y), 1.3f, IM_COL32(255, 0, 255, 255),12);
        



    }
    drawList->AddCircle(ImVec2(centerX, centery), 4.0f, IM_COL32(0, 255, 0, 255),12);
    ImGui::EndChild();
}


void renderGraphsTab(GLFWwindow *window){
    ImVec2 cursorPos = ImGui::GetCursorPos();
    int windowWidth, windowHeight;
  
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    if (ImGui::BeginTabItem("Plot files"))
    {
        //TODO: make a list of files and load them
        // *** List of files group
        
        
        
        // ImGui::BeginChild("files",ImVec2((windowWidth-100.0),windowHeight));

        if(ImGui::Button("LOAD FILES",ImVec2(100,20))){
        

            try {
                for (const auto& entry : fs::directory_iterator(folderPath)) {
                if(csvfiles.empty()){
                    csvfiles.push_back(entry.path().filename().string());
                }else{
                    auto it = std::find(csvfiles.begin(),csvfiles.end(),entry.path().filename().string());

                    if(it == csvfiles.end()){
                    csvfiles.push_back(entry.path().filename().string());
                    }
                }
                
                    
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        
        }

        ImGui::SameLine();
        
        string displaySelectedFile = "Selected File: " + showSelectedFile;
        ImGui::TextColored(ImVec4(0,1,0,1),displaySelectedFile.c_str());
        

        ImGui::SameLine();
        static bool g1=false,g2=false,g3=false,g4=false;
        if(selectedFile != "None"){
        ImGui::Checkbox("Throttle",&g1);
        ImGui::SameLine();
        ImGui::Checkbox("Brake",&g2);
        ImGui::SameLine();
        ImGui::Checkbox("Speed",&g3);
        ImGui::SameLine();
        ImGui::Checkbox("Map",&g4);
        ImGui::SameLine();
        ImGui::Checkbox("Link X", &linkx);
        ImGui::SameLine();
        ImGui::Checkbox("Link Y", &linky);
        }
        
        
       
        ImGui::Separator();
        if (ImGui::BeginListBox("##fileslist",ImVec2(200,0)))
        {
            for (int n = 0; n < csvfiles.size(); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                
                if (ImGui::Selectable(csvfiles[n].c_str())){
                    selectedFile = folderPath + csvfiles[n];
                    showSelectedFile = csvfiles[n];
                    loadCsvformat(csv,selectedFile);
                    item_selected_idx = n;
                    
                }
                    
                

                if (item_highlight && ImGui::IsItemHovered())
                    item_highlighted_idx = n;

            
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::SetCursorPos(ImVec2(cursorPos.x+210, cursorPos.y+70));
        if(ImGui::BeginChild("Graphs",ImVec2(850,700),ImGuiChildFlags_AutoResizeX)){
            ImGui::DragScalarN("Limits",ImGuiDataType_Double,&lims.X.Min,4,0.01f);
            if(g1){plotThrottle(csv);}

            if(g2){plotBrake(csv);}
            if(g3){plotSpeed(csv);}
            ImGui::EndChild();
        }


        
        
        
        ImGui::SameLine();

        ImGui::BeginChild("data",ImVec2(320,windowHeight),ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY );
        if(selectedFile != "None"){
        auto maxSpeed = std::max_element(csv.speed.begin(), csv.speed.end());
        auto maxBrake= std::max_element(csv.brake.begin(), csv.brake.end());
        double avgSpeed = findAvg(csv.speed);
        ImGui::SetWindowFontScale(1.5f);
        if(glb::role == Pilot || glb::role == Admin){
            ImGui::TextColored(ImVec4(0,1,0,1),("Max Speed: "+std::to_string(*maxSpeed*3.6)+"km/h").c_str());
            ImGui::TextColored(ImVec4(1,0,0.5,1),("Avg Speed: "+std::to_string(avgSpeed*3.6)+"km/h").c_str());
            
        }
        if(glb::role == Engineer || glb::role == Admin){
            ImGui::TextColored(ImVec4(0,1,0,1),("Max Speed: "+std::to_string(*maxSpeed)+"m/s").c_str());
            ImGui::TextColored(ImVec4(1,0,0.5,1),("Avg Speed: "+std::to_string(avgSpeed)+"m/s").c_str());
            
        }
        ImGui::TextColored(ImVec4(1,0,1,1),("Max Brake: "+std::to_string(*maxBrake)+"Bar").c_str());
        ImGui::SetWindowFontScale(1.0f);


        }
        if(selectedFile != "None" && g4){
        RenderMapWithPoints(csv.x,csv.y);
        }
        
        
        ImGui::EndChild();
        
        
        

       



        ImGui::EndTabItem();
    }
}