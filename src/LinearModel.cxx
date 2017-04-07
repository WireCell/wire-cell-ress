#include "WireCellRess/LinearModel.h"

#include <Eigen/Dense>
using namespace Eigen;

WireCell::LinearModel::LinearModel()
{}

WireCell::LinearModel::~LinearModel()
{}

void WireCell::LinearModel::SetData(Eigen::MatrixXd& X, Eigen::VectorXd& y)
{
    _X = X;
    _y = y;
    _beta = VectorXd::Zero(_X.cols()); // initialize solution to zero.
}


VectorXd WireCell::LinearModel::Predict()
{
    return _X * _beta;
}
