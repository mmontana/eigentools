#ifndef SPECTRALF_H
#define SPECTRALF_H

#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace Eigen;

//TODO generalize for static size matrices

template<typename M> M spectralf(const M& matrix, double tol){

    JacobiSVD<M> svd(matrix, ComputeThinU | ComputeThinV);
	Matrix<double ,Dynamic,1> vals = svd.singularValues();

    int cut_idx;
    for(int i = 0; i < vals.size(); i++){
        if(vals(i) >= tol) cut_idx = i; 
    }
	if(cut_idx == vals.size()-1){
    std::cout << "reverted back to original rank" << std::endl;
    return matrix;
    }

    return svd.matrixU().leftCols(cut_idx+1) * vals.head(cut_idx+1).asDiagonal() *
    svd.matrixV().leftCols(cut_idx+1).transpose();
}

template<typename M> M spectralf(const M& matrix, int rank){

    JacobiSVD<M> svd(matrix, ComputeThinU | ComputeThinV);
	Matrix<double,Dynamic,1> vals = svd.singularValues();
    
    int svdrank = vals.size();

    //TODO: rank truncation

    return matrix;
}

#endif //SPECTRALF_H
