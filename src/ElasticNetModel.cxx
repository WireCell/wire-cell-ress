#include "WireCellRess/ElasticNetModel.h"

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
using namespace std;

/* Minimize the following problem:
 * 1/(2) * ||Y - beta * X||_2^2 + N * lambda * (
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
    // initialize solution to zero
    Eigen::VectorXd beta = VectorXd::Zero(_X.cols());

    // use alias for easy notation
    Eigen::VectorXd y = Gety();
    Eigen::MatrixXd X = GetX();

    // cooridate decsent
    int nbeta = beta.size();
    int N = y.size();
    VectorXd norm(nbeta);
    for (int j=0; j<nbeta; j++) {
        norm(j) = X.col(j).squaredNorm();
        if (norm(j) < 1e-6) {
            cerr << "warning: the " << j << "th variable is not used, please consider removing it." << endl;
            norm(j) = 1;
        }
    }
    double tol2 = TOL*TOL;

    for (int i=0; i<max_iter; i++) {
        VectorXd betalast = beta;
        for (int j=0; j<nbeta; j++) {
            VectorXd X_j = X.col(j);
            VectorXd beta_tmp = beta;
            beta_tmp(j) = 0;
            VectorXd r_j = (y - X * beta_tmp);
            double delta_j = X_j.dot(r_j);
            beta(j) = _soft_thresholding(delta_j, N*lambda*alpha) / (1+lambda*(1-alpha)) / norm(j);
            // if (j==0) cout << beta(j) << ", " << arg1 << endl;
        }
        VectorXd diff = beta - betalast;
        if (diff.squaredNorm()<tol2) {
            // cout << "found minimum at iteration: " << i << endl;
            // cout << diff << endl;
            break;
        }
    }

    // save results in the model
    Setbeta(beta);
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