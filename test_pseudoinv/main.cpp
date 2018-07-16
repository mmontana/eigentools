#include "pseudoinv.h"
#include <iostream>

using namespace Eigen;

int main(int argc, char const *argv[])
{

    float eps = 10e-4;
    MatrixXf mat;
    mat.setRandom(3,3);
    MatrixXf matp = pseudoinv<MatrixXf>(mat);
    assert(((mat * matp * mat) -mat).norm() <eps);
    assert(((matp * mat * matp) -matp).norm() <eps);

    mat.setIdentity();
    mat(2,2) = 10e-5;
    Matrix3f matv;
    matv << 1,0,0,0,1,0,0,0,0;
    MatrixXf basechange;
    
    int rank = 2;
    matp = pseudoinv<MatrixXf>(mat,rank);
    assert(matp == matv);
    double tol = 10e-4;
    matp = pseudoinv<MatrixXf>(mat, tol);
    assert(matp == matv);

    return 0;
}
