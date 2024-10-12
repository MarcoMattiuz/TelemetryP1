#include <vector>
#include <string>

#include <iostream>

#include "graphs.h"
#include "csv.h"
#include "implot/implot.h"
using std::vector,std::cout,std::endl;


ImPlotRect lims(0,1,0,1);
bool linkx = true, linky = true;

   



void loadCsvformat(csvformat& csv, std::string filepath) {
    InitCsvformat(csv);
    io::CSVReader<6> in(filepath);
    in.read_header(io::ignore_missing_column, "time","throttle","brake","speed","x","y");
    double time,throttle,brake,speed,x,y ;
    while(in.read_row(time,throttle,brake,speed,x,y)){
        csv.time.push_back(time);
        csv.throttle.push_back(throttle);
        csv.brake.push_back(brake);
        csv.speed.push_back(speed);
        csv.x.push_back(x);
        csv.y.push_back(y);

    }

   
}

void InitCsvformat(csvformat& csv){
    cout << "Clearing csv data..." << endl;
    csv.time.clear();
    csv.throttle.clear();
    csv.brake.clear();
    csv.speed.clear();
    csv.x.clear();
    csv.y.clear();
}

void plotThrottle(csvformat& csv){
    if(ImPlot::BeginPlot("Throttle",ImVec2(800,0))){
    ImPlot::SetupAxes("Time","%");
    ImPlot::SetupAxesLimits(0,200,0,1);
    ImPlot::SetupAxisLinks(ImAxis_X1, linkx ? &lims.X.Min : nullptr, linkx ? &lims.X.Max : nullptr);
    ImPlot::SetupAxisLinks(ImAxis_Y1, linky ? &lims.Y.Min : nullptr, linky ? &lims.Y.Max : nullptr);
    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green line
            
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
            ImPlot::PlotShaded("throttle", csv.time.data(), csv.throttle.data(), csv.time.size(), 0);
            // ImPlot::PlotShaded("brake", csv.time.data(), csv.brake.data(), csv.time.size(),0);
            ImPlot::PopStyleVar();
            

        ImPlot::PlotLine("throttle", csv.time.data(), csv.throttle.data(), csv.time.size());
    ImPlot::PopStyleColor();
    // ImPlot::PlotLine("brake", csv.time.data(), csv.brake.data(), csv.time.size());
    ImPlot::EndPlot();
    }
}

void plotBrake(csvformat& csv){
    if(ImPlot::BeginPlot("Brake",ImVec2(800,0))){
    ImPlot::SetupAxes("Time","Bar");
    ImPlot::SetupAxesLimits(0,200,0,10);
    ImPlot::SetupAxisLinks(ImAxis_X1, linkx ? &lims.X.Min : nullptr, linkx ? &lims.X.Max : nullptr);
    ImPlot::SetupAxisLinks(ImAxis_Y1, linky ? &lims.Y.Min : nullptr, linky ? &lims.Y.Max : nullptr);
 
    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(1.0f, 0.0f, 1.0f, 1.0f));
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.35f);
            // ImPlot::PlotShaded("throttle", csv.time.data(), csv.throttle.data(), csv.time.size(), 0);
            ImPlot::PlotShaded("brake", csv.time.data(), csv.brake.data(), csv.time.size(),0);
            ImPlot::PopStyleVar();
        
            
    // ImPlot::PlotLine("throttle", csv.time.data(), csv.throttle.data(), csv.time.size());
    ImPlot::PlotLine("brake", csv.time.data(), csv.brake.data(), csv.time.size());
    ImPlot::PopStyleColor();
    ImPlot::EndPlot();
    }
}


void plotSpeed(csvformat& csv){
    if(ImPlot::BeginPlot("Speed",ImVec2(800,0))){
    ImPlot::SetupAxes("Time","m/s");
    ImPlot::SetupAxesLimits(0,200,0,100);
    ImPlot::SetupAxisLinks(ImAxis_X1, linkx ? &lims.X.Min : nullptr, linkx ? &lims.X.Max : nullptr);
    ImPlot::SetupAxisLinks(ImAxis_Y1, linky ? &lims.Y.Min : nullptr, linky ? &lims.Y.Max : nullptr);
    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(1.0f, 0.5f, 0.5f, 1.0f));
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.35f);
            // ImPlot::PlotShaded("throttle", csv.time.data(), csv.throttle.data(), csv.time.size(), 0);
            ImPlot::PlotShaded("speed", csv.time.data(), csv.speed.data(), csv.time.size(),0);
            ImPlot::PopStyleVar();
        
     
 
    // ImPlot::PlotLine("throttle", csv.time.data(), csv.throttle.data(), csv.time.size());
    ImPlot::PlotLine("speed", csv.time.data(), csv.speed.data(), csv.time.size());
    ImPlot::PopStyleColor();
    ImPlot::EndPlot();
    }
}



