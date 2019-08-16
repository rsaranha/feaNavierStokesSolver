//
//  baseRectShapeFunction.hpp
//  dgfesolver
//
//  Created by Ronald Aranha on 2019-05-01.
//  Copyright © 2019 Ronald Aranha. All rights reserved.
//

#ifndef baseRectShapeFunction_hpp
#define baseRectShapeFunction_hpp

#include <iostream>
#include "dgfeSolver.hpp"

namespace solver{
    
    class baseRectShapeFunction{

    private:  
       int myNodePoints;  

        
    public:
        virtual void ShapeFunction4(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y);
        
        virtual void ShapeFunction8(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y);

        virtual void Jacobi(float &dJacobiDeterminant, Dim2d &JacobiMatrixInv, Dim2d &dJacobiMatrix,
                    	    const std::vector<Point2f> &deriv, const std::vector<Point2f> &coord, const Dim2d &localToGlobal,
                            int ielem);
  
        
        baseRectShapeFunction();
    
        ~baseRectShapeFunction();
    
    };
}

#endif /* baseRectShapeFunction_hpp */
