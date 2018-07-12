#ifndef CSV_H
#define CSV_H

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <stdlib.h>
#include<eigen3/Eigen/Dense>
#include<type_traits>

using namespace Eigen;

template<typename T> T read_csv( const char path[], const char sep = ','){
	
	int row = 0;
	int col = 0;
	int counter;
	std::vector<typename T::Scalar> val;

	std::ifstream infile(path);
	
	std::string line;
	
	while(std::getline(infile,line)){
		counter = 0;
				
		std::stringstream linestream(line);
		std::string cell;
		while(std::getline(linestream,cell,sep)){
			counter += 1;		
			
			val.push_back(atof(cell.c_str()));
				
			if(row == 0 ){
				col += 1;
			}
		} 
		row += 1;
		if(counter != col ){
		std::cerr << "incompatible input format \n";
		std::exit(1);
		} 
	} 
		
	Map<Matrix<typename T::Scalar,T::RowsAtCompileTime,T::ColsAtCompileTime,RowMajor>,RowMajor> matrix(val.data(),row,col);	

	return matrix;
	}

	template<typename T> void to_csv(const T& matrix, const IOFormat form, const char name[]){
		//static_assert(std::is_base_of<MatrixBase,T>::value,"Not a matrix object");
		std::ofstream out(name);
		out << matrix.format(form);
	}

	
	
#endif //CSV_H
