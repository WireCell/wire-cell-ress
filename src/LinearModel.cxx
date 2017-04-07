#include "WireCellRess/LinearModel.h"

#include <Eigen/Dense>
using namespace Eigen;

WireCell::LinearModel::LinearModel()
{}

WireCell::LinearModel::~LinearModel()
{}

VectorXd WireCell::LinearModel::Predict()
{
    return _X * _beta;
}
