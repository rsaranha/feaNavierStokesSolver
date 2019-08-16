//
//  main.cpp
//  dgfesolver
//
//  Created by Ronald Aranha on 2019-05-01.
//  Copyright © 2019 Ronald Aranha. All rights reserved.
//

#include <iostream>
#include "dgfeSolver.hpp"
#include "input.hpp"
#include "baseRectShapeFunction.hpp"
#include "derivedShapeFunction.hpp"
#include "drives.hpp"

using namespace std ;
using namespace solver;

int main(int argc, const char * argv[]) {
    
    
    // insert code here...
    std::cout << "Discontinuous Galerkin Finite Element Solver (DGFES)" << std::endl;
    std::cout << "--------------git test------------------------------" << std::endl;

    // read the Gmsh input mesh  
    input *inptr = new input ;  
    inptr->readConnectivityMatrix(); 	
        
    drives drv;
    
    int numLinear    = 4 ;
    int numParabolic = 8 ;
    float x = 0.7745966692 ;
    float y = 0.7745966692;

    std::vector<Point2f> myShapeFunctionDeriv;
    std::vector<float>   myShapeFunction;

    myShapeFunctionDeriv.resize(numLinear);
    myShapeFunction.resize(numLinear);

    baseRectShapeFunction *ptr = new derivedShapeFunction(numParabolic);

    ptr->ShapeFunction4(myShapeFunctionDeriv, myShapeFunction, x, y);

    myShapeFunctionDeriv.resize(numParabolic);
    myShapeFunction.resize(numParabolic);

    ptr->ShapeFunction8(myShapeFunctionDeriv, myShapeFunction, x, y);
 	 
    delete inptr;
    
    return 0;
}
