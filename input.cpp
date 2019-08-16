//
//  Input.cpp
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2016-01-27.
//  Copyright (c) 2016 Ronald Aranha. All rights reserved.
//

#include "input.hpp"
using namespace std ;

namespace solver{
  
  input::input(){
	    
      std::cout<< "Input constructor "<< std::endl;
      numNodes      = -1;
      numElements   = -1;
      numDim        = -1;
      numGauss      =  3;
      numElemLinear =  4;
      numElemParabolic  = 8 ;
	  
      readMeshSize(numNodes, numElements, numDim);
      
      std::cout << "Finished reading the input mesh " << std::endl ; 

      setUpInput(numElements, numGauss, numNodes, numElemLinear, numElemParabolic, numNodes); 
      
      std::cout << "Finished setting up the memory arrays " << std::endl ;   
      
   }
   

   input::~input(){
     cout << "Input destructor " << endl ;

   }
   
   void input::setUpFilename(string &gmsh_filename){
     gmsh_filename = "./sg2d_v3.msh" ;
       
   }   
   
   void input::readMeshSize(int &numNodes, int &numElements, int &numDim){
     
      // hard coded atm  
      setUpFilename(gmsh_filename);
      
      gmsh_size_read(gmsh_filename, numNodes, numDim, numElements, elementOrder);
      
      cout << "element order " << elementOrder << endl ;
      
   }
   
   void input::readConnectivityMatrix(){
     
      gmsh_data_read(gmsh_filename, numDim, numNodes, globalCoordinates, elementOrder, numElements, globalToLocalNumbering);
		
      for (int i = 0; i < numElements; i++)
	  for(int j = 0; j < numElemParabolic ; j++)
	      cout <<"i =  "<< i << " j  = " << j << " cmatrix   "<< globalToLocalNumbering[i][j]<< endl ;   


   }

    void input::setUpInput(int numElements, int numGauss, int numPoints,
		    int numElemLinear, int numElemParabolic, int numNodes){

	    // initialize the input and sizes...

	    globalDerivOfParabolicShapeFunction.resize(numElements);
	    globalDerivOfLinearShapeFunction.resize(numElements);
	    globalLinearShapeFunction.resize(numElements);
	    globalParabolicShapeFunction.resize(numElements);
	    globalAreaWeights.resize(numElements);
	    globalToLocalNumbering.resize(numElements);
	    globalCoordinates.resize(numNodes); 

	    for (int i = 0 ; i < numElements; i++) {
		    globalDerivOfLinearShapeFunction[i].resize(numGauss*numGauss);
		    globalDerivOfParabolicShapeFunction[i].resize(numGauss*numGauss);

		    for (int j= 0 ; j < numGauss*numGauss; j++) {
			    globalDerivOfLinearShapeFunction[i][j].resize(numPoints);
			    globalDerivOfParabolicShapeFunction[i][j].resize(numPoints);

			    for (int k = 0; k < numPoints; k++){
				    globalDerivOfLinearShapeFunction[i][j][k] = 0.;
				    globalDerivOfLinearShapeFunction[i][j][k] = 0.;

				    globalDerivOfParabolicShapeFunction[i][j][k] = 0.;
				    globalDerivOfParabolicShapeFunction[i][j][k] = 0.;

			    }
		    }
	    }

	    for (int i = 0; i < numElements ; i++){
		    globalLinearShapeFunction[i].resize(numGauss*numGauss);
		    globalParabolicShapeFunction[i].resize(numGauss*numGauss);

		    for(int j = 0 ; j< numGauss*numGauss; j++){
			    globalLinearShapeFunction[i][j].resize(numElemLinear);
			    globalParabolicShapeFunction[i][j].resize(numElemParabolic);

			    for (int k = 0; k < numElemLinear; k++) {
				    globalLinearShapeFunction[i][j][k] = 0.;
			    }
			    for (int k = 0; k <numElemParabolic; k++) {
				    globalParabolicShapeFunction[i][j][k] = 0.;
			    }

		    }
	    }

	    for (int i = 0 ; i < numElements; i++) {
		    globalAreaWeights[i].resize(numElements);
		    for (int j = 0; j < numGauss* numGauss ; j++){
			    //globalAreaWeights[i][j].resize(1);

			    globalAreaWeights[i][j] = 0.;

		    }
	    }

	    for (int i = 0; i < numElements; i++) {
		    globalToLocalNumbering[i].resize(numElemParabolic);
		    for (int j =0; j < numElemParabolic; j++) {
			    globalToLocalNumbering[i][j] = 0;
		    }
	    }
	    
	    for (int i = 0; i < numNodes; i++) {
		globalCoordinates[i].resize(3) ;  	
		for (int j = 0 ; j < 3 ; j++) 
		    globalCoordinates[i][j] = 0.;  
	    } 


    }






}
