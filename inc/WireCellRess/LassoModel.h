#ifndef WIRECELLRESS_LASSOMODEL_H
#define WIRECELLRESS_LASSOMODEL_H

#include "WireCellRess/LinearModel.h"

namespace WireCell {

class LassoModel: public LinearModel {
public:
    LassoModel(double lambda=1., int max_iter=100000, double TOL=1e-3, bool non_negtive=true);
    ~LassoModel();

    double lambda; // regularization parameter
    int max_iter; // maximum iteration
    double TOL;
    bool non_negtive;

    void Fit();

private:
    double _soft_thresholding(double x, double lambda_);
};

}

#endif