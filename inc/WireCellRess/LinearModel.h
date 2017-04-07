#ifndef WIRECELLRESS_LINEARMODEL_H
#define WIRECELLRESS_LINEARMODEL_H

#include <Eigen/Dense>

namespace WireCell {

class LinearModel {
public:
    LinearModel();
    virtual ~LinearModel();

    Eigen::VectorXd& y() { return _y; }
    Eigen::MatrixXd& X() { return _X; }
    Eigen::VectorXd& beta() { return _beta; }

    void SetData(Eigen::MatrixXd& X, Eigen::VectorXd& y);
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