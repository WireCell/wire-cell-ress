#ifndef WIRECELLRESS_LASSOMODEL_H
#define WIRECELLRESS_LASSOMODEL_H

#include "WireCellRess/ElasticNetModel.h"

namespace WireCell {

class LassoModel: public ElasticNetModel {
public:
    LassoModel(double lambda=1., int max_iter=100000, double TOL=1e-3, bool non_negtive=true);
    ~LassoModel();

};

}

#endif