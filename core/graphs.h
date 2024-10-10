#ifndef ACCELERATION_H
#define ACCELERATION_H

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


// Carica i dati CSV di accelerazione nel struct Acceleration
void loadAccelerationCSV(Acceleration& acc);

// Plotta i dati di accelerazione utilizzando ImPlot
void PlotAcceleration(const Acceleration& data);

#endif // ACCELERATION_H