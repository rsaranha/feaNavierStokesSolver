//
//  derivedShapeFunction.hpp
//  dgfesolver
//
//  Created by Ronald Aranha on 2019-05-01.
//  Copyright © 2019 Ronald Aranha. All rights reserved.
//

#ifndef derivedShapeFunction_hpp
#define derivedShapeFunction_hpp

#include <iostream>
#include "dgfeSolver.hpp"
#include "baseRectShapeFunction.hpp"

namespace solver{
    
    class derivedShapeFunction : public baseRectShapeFunction{

    private:
       int myNodePoints;
        
    public:

        
        derivedShapeFunction(int npoints);
        derivedShapeFunction();
 
        ~derivedShapeFunction();

        void ShapeFunction4(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y);
        void ShapeFunction8(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y);
        void Jacobi(float &dJacobiDeterminant, Dim2d &JacobiMatrixInv, Dim2d &dJacobiMatrix,
                    const std::vector<Point2f> &deriv, const std::vector<Point2f> &coord, const Dim2d &localToGlobal,
                    int ielem);

        
    };
    
}




#endif /* derivedShapeFunction_hpp */
