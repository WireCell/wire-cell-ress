#include "WireCellRess/LassoModel.h"

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    // std::srand((unsigned int) time(0));

    const int N_CELL = 16;
    const int N_ZERO = 10;
    const int N_WIRE = int(N_CELL * 0.8);

    // initialize C vector: NCELL cells with NZERO zeros. (true charge in each cell)
    VectorXd C = VectorXd::Random(N_CELL)*50 + VectorXd::Constant(N_CELL, 150);
    VectorXd r = N_CELL / 2 * (VectorXd::Random(N_ZERO)+VectorXd::Constant(N_ZERO, 1));
    for (int i=0; i<N_ZERO; i++) {
        C( int(r(i)) ) = 0;
    }

    // initialize G matrix: N_WIRE rows and N_CELL columns. (geometry matrix)
    MatrixXd G = MatrixXd::Zero(N_WIRE, N_CELL);
    for (int i=0; i<N_WIRE; i++) {
        VectorXd t = VectorXd::Random(N_CELL);
        for (int j=0; j<N_CELL; j++) {
            G(i, j) = int(t(j)+1);
        }
    }

    // W vector is the measured charge on wires.
    VectorXd W = G * C;

    // cout << W << endl << endl;
    // cout << G << endl << endl;
    // cout << C << endl << endl;

    WireCell::LassoModel m(0.5, 100000, 1e-4);
    // LassoModel m(0.5, int(1000));
    m.SetData(G, W);
    m.Fit();
    VectorXd beta = m.Getbeta();

    cout << "geometry matrix:" << endl;
    cout << G << endl << endl;

    cout << "true charge of each cell:" << endl;
    cout << C.transpose() << endl << endl;

    cout << "fitted charge of each cell:" << endl;
    cout << beta.transpose() << endl << endl;

    cout << "measured charge on each wire:" << endl;
    cout << W.transpose() << endl << endl;

    cout << "predicted charge on each wire:" << endl;
    cout << m.Predict().transpose() << endl << endl;

    cout << "residual distance:" << (m.Predict() - W).norm() << endl;

    return 0;
}