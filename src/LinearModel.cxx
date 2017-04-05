#include "WireCellRess/LinearModel.h"

#include <Eigen/Dense>
using namespace Eigen;

WireCell::LinearModel::LinearModel()
{}

WireCell::LinearModel::~LinearModel()
{}

void WireCell::LinearModel::SetData(Eigen::MatrixXd& X, Eigen::VectorXd& y)
{
    X_ = X;
    y_ = y;
    beta_ = VectorXd::Zero(X_.cols()); // initialize solution to zero.
}


VectorXd WireCell::LinearModel::Predict()
{
    return X_ * beta_;
}
