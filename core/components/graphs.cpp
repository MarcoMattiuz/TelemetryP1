#include <vector>
#include <string>
#include <iostream>

#include "graphs.h"
#include "csv.h"
#include "implot/implot.h"
using std::vector,std::cout,std::endl;




void loadCsvformat(csvformat& csv) {
    
    io::CSVReader<6> in("../csv_samples/acceleration.csv");
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

void InitCsvformat(csvformat& acc){
     acc.time.push_back(0);
        acc.throttle.clear();
        acc.brake.clear();
        acc.speed.clear();
        acc.x.clear();
        acc.y.clear();
}


// void PlotCsvformat(const csvformat& data) {
//     if (ImPlot::BeginPlot("Acceleration Data",ImVec2(0,0))) {
//         if(!data.time.empty() && !data.throttle.empty() && !data.brake.empty() && !data.speed.empty() ){
//             data.throttle.at(0);
//             ImPlot::PlotLine("throttle", data.time.data(), data.throttle.data(), data.time.size());
//             ImPlot::PlotLine("Brake", data.time.data(), data.brake.data(), data.time.size());
//             ImPlot::PlotLine("Speed", data.time.data(), data.speed.data(), data.time.size());
//         }else{
//             cout << "wait";
//         }
            
       
//         ImPlot::EndPlot();
//     }
// }




