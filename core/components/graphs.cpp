#include <vector>
#include <string>
#include <iostream>

#include "graphs.h"
#include "csv.h"
#include "implot/implot.h"
using std::vector,std::cout,std::endl;

// struct Acceleration{
//   vector<double> time;
//   vector<double> throttle;
//   vector<double> brake;
//   vector<double> speed;
//   vector<double> x;
//   vector<double> y;
// };


void loadAccelerationCSV(Acceleration& acc) {
    
    io::CSVReader<6> in("../csv_samples/acceleration.csv");
    in.read_header(io::ignore_missing_column, "time","throttle","brake","speed","x","y");
    double time,throttle,brake,speed,x,y ;
    while(in.read_row(time,throttle,brake,speed,x,y)){
        acc.time.push_back(time);
        acc.throttle.push_back(throttle);
        acc.brake.push_back(brake);
        acc.speed.push_back(speed);
        acc.x.push_back(x);
        acc.y.push_back(y);

    }

   
}

void PlotAcceleration(const Acceleration& data) {
    if (ImPlot::BeginPlot("Acceleration Data",ImVec2(0,0))) {
        if(!data.time.empty() && !data.throttle.empty() && !data.brake.empty() && !data.speed.empty() ){
            data.throttle.at(0);
            ImPlot::PlotLine("throttle", data.time.data(), data.throttle.data(), data.time.size());
            ImPlot::PlotLine("Brake", data.time.data(), data.brake.data(), data.time.size());
            ImPlot::PlotLine("Speed", data.time.data(), data.speed.data(), data.time.size());
        }else{
            cout << "wait";
        }
            
       
        ImPlot::EndPlot();
    }
}

void InitAcceleration(Acceleration& acc){
     acc.time.push_back(0);
        acc.throttle.clear();
        acc.brake.clear();
        acc.speed.clear();
        acc.x.clear();
        acc.y.clear();
}



