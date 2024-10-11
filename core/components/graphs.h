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




void loadCsvformat(csvformat& acc);


// void PlotCsvformat(const csvformat& data);

void InitCsvformat(csvformat& acc);
#endif 