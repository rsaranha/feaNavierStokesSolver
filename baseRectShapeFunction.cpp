//
//  baseRectShapeFunction.cpp
//  dgfesolver
//
//  Created by Ronald Aranha on 2019-05-01.
//  Copyright © 2019 Ronald Aranha. All rights reserved.
//

#include "baseRectShapeFunction.hpp"
using namespace std;

namespace solver{
    
    void baseRectShapeFunction:: ShapeFunction4(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y){
        
        cout << "inside the four element base shape function " << endl;
        
    }
    
    void baseRectShapeFunction:: ShapeFunction8(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y){
    
        cout <<"inside the eight element base shape function " << endl ;
    }
 
    void baseRectShapeFunction:: Jacobi(float &dJacobiDeterminant, Dim2d &JacobiMatrixInv, Dim2d &dJacobiMatrix,
                            	        const std::vector<Point2f> &deriv, const std::vector<Point2f> &coord, 
					const Dim2d &localToGlobal, int ielem){
	cout << "Jacobi doing nothing here " << endl;
    }
    
    
    baseRectShapeFunction::baseRectShapeFunction(){

        // std::cout << "Doing nothing much here " << std::endl ;
        //std::cout<< "Guess what I am doing this again" <<std::endl;
    }
    
    baseRectShapeFunction::~baseRectShapeFunction(){
        
        
    }
}
    
    
