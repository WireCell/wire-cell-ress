#include "WireCellRess/LassoModel.h"

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
using namespace std;

WireCell::LassoModel::LassoModel(double lambda, int max_iter, double TOL, bool non_negtive)
: ElasticNetModel(lambda, 1., max_iter, TOL, non_negtive)
{
}

WireCell::LassoModel::~LassoModel()
{}
