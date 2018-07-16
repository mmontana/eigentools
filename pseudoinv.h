#ifndef PSEUDOINV_H
#define PSEUDOINV_H

#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace Eigen;

template<typename M> M pseudoinv(const M& matrix, const double tol = 10e-6) {
	
	JacobiSVD<M> svd(matrix, ComputeThinU | ComputeThinV);
	Matrix<float,Dynamic,1> vals = svd.singularValues();
	int rank = vals.size();

	for(int i = 0; i < rank; i++ ){
		vals(i) = (vals(i) < tol) ? 0.0 : (1.0/vals(i)); 	
	}
	return svd.matrixV().leftCols(rank) * vals.head(rank).asDiagonal() * svd.matrixU().leftCols(rank).transpose() ;
}


template<typename M> M pseudoinv(const M& matrix, int rank, const double tol = 10e-6) {
	
	JacobiSVD<M> svd(matrix, ComputeThinU | ComputeThinV);
	Matrix<float,Dynamic,1> vals = svd.singularValues();

	//rank truncation
	if( rank<= 0 || rank > vals.size() ){
	rank = vals.size();
	std::cout << "revert to full rank. matrix rank: " << rank << std::endl;
	}
	
	for(int i = 0; i < rank; i++ ){
		vals(i) = (vals(i) < tol) ? 0.0 : (1.0/vals(i)); 	
	}
	return svd.matrixV().leftCols(rank) * vals.head(rank).asDiagonal() * svd.matrixU().leftCols(rank).transpose() ;
}
#endif //PSEUDOINV_H
