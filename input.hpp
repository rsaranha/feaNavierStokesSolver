//
//  Input.h
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2016-01-27.
//  Copyright (c) 2016 Ronald Aranha. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <vector>
#include "dgfeSolver.hpp"
#include "readGmshMesh.hpp"

namespace solver{
    
    class input : public readGmshMesh {


    public:
        
        int numNodes;
        int numElements;
        int numDim;
        int numGauss;
        int numElemLinear  ;
        int numElemParabolic ;
        int elementOrder;

        string gmsh_filename ;

        input();
        
        ~input();

        Dim3d globalDerivOfLinearShapeFunction;
        Dim3d globalDerivOfParabolicShapeFunction;
        Dim3d globalLinearShapeFunction;
        Dim3d globalParabolicShapeFunction;
        Dim2d globalAreaWeights;
        Dim2id globalToLocalNumbering;
        Dim2d globalCoordinates;


        void setUpFilename(string &gmsh_filename);
        void readMeshSize(int &numNodes, int &numElements, int &numDim); 
        void readConnectivityMatrix();
         
        void setUpInput(int numElements, int numGauss, int numPoints,
                        int numElemLinear, int numElemParabolic, int numNodes);
      
    };
    
}
#endif 
