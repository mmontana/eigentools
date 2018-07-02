#ifndef CSV_H
#define CSV_H

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <stdlib.h>
#include<eigen3/Eigen/Dense>

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
			}//endif
		} //endwhile
		row += 1;
		if(counter != col ){
		std::cerr << "incompatible input format \n";
		std::exit(1);
		} //endif
	} //endwhile
		
	Map<Matrix<typename T::Scalar,T::RowsAtCompileTime,T::ColsAtCompileTime,RowMajor>,RowMajor> matrix(val.data(),row,col);	

	return matrix;
};
	
#endif //CSV_H
