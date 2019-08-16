//
//  driver.hpp
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2015-11-10.
//  Copyright (c) 2015 Ronald Aranha. All rights reserved.
//

#ifndef drives_hpp
#define drives_hpp

#include "dgfeSolver.hpp"
#include "input.hpp"
#include "derivedShapeFunction.hpp"
//#include "gaussianQuadrature.hpp"


namespace solver
{
    class drives : public derivedShapeFunction, public input {
        private:
	    int myNumElementInMesh;
            int myNumElementsInJacobiMatrix;

            std::vector<float> myShapeElement4;
            std::vector<float> myShapeElement8;
            std::vector<float> myGaussianPositions;
            std::vector<float> myGaussianWeights;
            std::vector<Point2f> myDerivative;
            std::vector<Point2f> myCoord;    
            std::vector<float>   myAreaWeight;
            std::vector<Point2f> myShapeFunctionDeriv;
       	    std::vector<Point2f> myShapeFunctionDerivLinear;



            float **myJacobiInv;
            float **myJacobi;
            float **myLocalToGlobal;
	 

        public:

	    drives();
            ~drives();
    };
}
#endif 
