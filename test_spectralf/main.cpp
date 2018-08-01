#include "spectralf.h"
#include <iostream>

using namespace Eigen;

int main(int argc, char const *argv[])
{
    //filter by tolerance
    MatrixXd mat(4,5);
    mat << 4,0,0,0,0,
           0,3,0,0,0,
           0,0,2,0,0,
           0,0,0,1,0;
    MatrixXd matval;
    matval = mat;
    matval(3,3) = 0.0;
    assert(spectralf(mat,0.0) == mat); 
    assert(spectralf(mat,2.0) == matval);

    //filter by rank
    assert(spectralf(mat,4) == mat);
    assert(spectralf(mat,5) == mat);
    assert(spectralf(mat,3) == matval);

    return 0;
}