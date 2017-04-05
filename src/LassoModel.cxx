#include "WireCellRess/LassoModel.h"

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
using namespace std;

WireCell::LassoModel::LassoModel(double lambda_, int max_iter_, double TOL_, bool non_negtive_)
{
    lambda = lambda_;
    max_iter = max_iter_;

    TOL = TOL_;
    non_negtive = non_negtive_;
    // cout << "Model constructed" << endl;
}

WireCell::LassoModel::~LassoModel()
{}

void WireCell::LassoModel::Fit()
{
    // cooridate decsent
    int nbeta = beta_.size();
    int ny = y_.size();
    VectorXd norm(nbeta);
    for (int j=0; j<nbeta; j++) {
        norm(j) = X_.col(j).dot(X_.col(j));
        if (norm(j) < 1e-6) {norm(j) = 1;}
    }
    double tol2 = TOL*TOL;

    for (int i=0; i<max_iter; i++) {
        VectorXd beta_last = beta_;
        for (int j=0; j<nbeta; j++) {
            VectorXd X_j = X_.col(j);
            VectorXd r_j = (y_ - X_ * beta_) + X_j * beta_(j);
            double delta_j = X_j.dot(r_j);
            beta_(j) = _soft_thresholding(delta_j, lambda*ny) / norm(j);
            // if (j==0) cout << beta_(j) << ", " << arg1 << endl;
        }
        VectorXd diff = beta_ - beta_last;
        if (diff.squaredNorm()<tol2) {
            // cout << "found minimum at iteration: " << i << endl;
            // cout << diff << endl;
            break;
        }
    }

}

double WireCell::LassoModel::_soft_thresholding(double delta, double lambda_)
{
    if (delta > lambda_) {
        return delta - lambda_;
    }
    else {
        if (non_negtive) {
            return 0;
        }
        else {
            if (delta < -lambda_) {
                return delta + lambda_;
            }
            else {
                return 0;
            }
        }
    }
}