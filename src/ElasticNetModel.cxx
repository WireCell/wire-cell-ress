#include "WireCellRess/ElasticNetModel.h"

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
using namespace std;

/* Minimize the following problem:
 * 1/(2N) * ||Y - beta * X||_2^2 + lambda * (
 *   alpha * ||beta||_1 + 0.5 * (1-alpha) * ||beta||_2^2
 * )
 * To control L1 and L2 separately, this is equivaletnt to a * L1 + b * L2,
 * where lambda = a + b and alpha = a / (a + b)
 */

WireCell::ElasticNetModel::ElasticNetModel(double lambda, double alpha, int max_iter, double TOL, bool non_negtive)
: lambda(lambda), alpha(alpha), max_iter(max_iter), TOL(TOL), non_negtive(non_negtive)
{
    // cout << "Model constructed" << endl;
}

WireCell::ElasticNetModel::~ElasticNetModel()
{}

void WireCell::ElasticNetModel::Fit()
{
    // cooridate decsent
    int nbeta = _beta.size();
    int ny = _y.size();
    VectorXd norm(nbeta);
    for (int j=0; j<nbeta; j++) {
        norm(j) = _X.col(j).dot(_X.col(j));
        if (norm(j) < 1e-6) {norm(j) = 1;}
    }
    double tol2 = TOL*TOL;

    for (int i=0; i<max_iter; i++) {
        VectorXd _betalast = _beta;
        for (int j=0; j<nbeta; j++) {
            VectorXd X_j = _X.col(j);
            VectorXd r_j = (_y - _X * _beta) + X_j * _beta(j);
            double delta_j = X_j.dot(r_j);
            _beta(j) = _soft_thresholding(delta_j, lambda*ny) / norm(j);
            // if (j==0) cout << _beta(j) << ", " << arg1 << endl;
        }
        VectorXd diff = _beta - _betalast;
        if (diff.squaredNorm()<tol2) {
            // cout << "found minimum at iteration: " << i << endl;
            // cout << diff << endl;
            break;
        }
    }

}

double WireCell::ElasticNetModel::_soft_thresholding(double delta, double lambda_)
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