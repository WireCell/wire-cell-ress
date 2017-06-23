#include "WireCellRess/LassoModel.h"

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
using namespace std;

/* Minimize the following problem:
 * 1/(2) * ||Y - beta * X||_2^2 + N * lambda * ||beta||_1
 */

WireCell::LassoModel::LassoModel(double lambda, int max_iter, double TOL, bool non_negtive)
: ElasticNetModel(lambda, 1., max_iter, TOL, non_negtive)
{
    name = "Lasso";
}

WireCell::LassoModel::~LassoModel()
{}

double WireCell::LassoModel::chi2_l1()
{
    return lambda * Getbeta().lpNorm<1>();
}

