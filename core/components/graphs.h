#ifndef GRAPHS_H
#define GRAPHS_H

#include <vector>
#include <string>
#include <iostream>

#include "csv.h"
#include "implot/implot.h"

using std::vector;

struct csvformat {
    vector<double> time;
    vector<double> throttle;
    vector<double> brake;
    vector<double> speed;
    vector<double> x;
    vector<double> y;
};




void loadCsvformat(csvformat& acc,std::string filepath);
void InitCsvformat(csvformat& acc);
void plotThrottle(csvformat& csv);
void plotBrake(csvformat& csv);
void plotSpeed(csvformat& csv);

#endif 