#ifndef WIRECELLRESS_LINEARMODEL_H
#define WIRECELLRESS_LINEARMODEL_H

#include <Eigen/Dense>

namespace WireCell {

class LinearModel {
public:
    LinearModel();
    virtual ~LinearModel();

    Eigen::VectorXd& Gety() { return _y; }
    Eigen::MatrixXd& GetX() { return _X; }
    Eigen::VectorXd& Getbeta() { return _beta; }

    void SetData(Eigen::MatrixXd X, Eigen::VectorXd y) { _X = X; _y = y; }
    void Sety(Eigen::VectorXd y) { _y = y; }
    void SetX(Eigen::MatrixXd X) { _X = X; }
    void Setbeta(Eigen::VectorXd beta) { _beta = beta; }

    virtual void Fit() {};
    Eigen::VectorXd Predict();

protected:
    // Fit: y = X * beta
    // convention: lowercase: vector, uppercase matrix.
    Eigen::VectorXd _y;
    Eigen::MatrixXd _X;
    Eigen::VectorXd _beta;

};

}

#endif