#ifndef GRAPHS_H
#define GRAPHS_H

#include <vector>
#include <string>
#include <iostream>

#include "csv.h"
#include "implot/implot.h"

using std::vector;

struct Acceleration {
    vector<double> time;
    vector<double> throttle;
    vector<double> brake;
    vector<double> speed;
    vector<double> x;
    vector<double> y;
};



void loadAccelerationCSV(Acceleration& acc);


void PlotAcceleration(const Acceleration& data);

void InitAcceleration(Acceleration& acc);
#endif 