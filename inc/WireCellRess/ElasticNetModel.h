#ifndef WIRECELLRESS_ELASTICNETMODEL_H
#define WIRECELLRESS_ELASTICNETMODEL_H

#include "WireCellRess/LinearModel.h"

namespace WireCell {

class ElasticNetModel: public LinearModel {
public:
    ElasticNetModel(double lambda=1., double alpha=1., int max_iter=100000, double TOL=1e-3, bool non_negtive=true);
    ~ElasticNetModel();

    double lambda; // regularization parameter
    double alpha; // L1 ratio (L2 ratio = 1 - alpha)
    int max_iter; // maximum iteration
    double TOL;
    bool non_negtive;

    void Fit();

private:
    double _soft_thresholding(double x, double lambda_);
};

}

#endif