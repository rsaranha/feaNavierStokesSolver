//
//  Driver.cpp
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2015-11-10.
//  Copyright (c) 2015 Ronald Aranha. All rights reserved.
//

#include "drives.hpp"
#include "gaussianQuadrature.hpp"
namespace solver
{

    drives::drives(){


	cout <<  "num of nodes " << numNodes    << endl ;    
        cout <<  "num of elem  " << numElements << endl ;

        // myName variables are local to class  

	myNumElementsInJacobiMatrix = 4;
        myNumElementInMesh          = numElements;
       
        myShapeElement4.resize(numElemLinear, 0);
        myShapeElement8.resize(numElemParabolic, 0);  	
        myGaussianPositions.resize(numGauss, 0);
        myGaussianWeights.resize(numGauss, 0);   
        myDerivative.resize(numElemParabolic);
        myCoord.resize(numElemParabolic*myNumElementInMesh);	


        /*            
        */
        int numGauss = 3; 
	myGaussianPositions.resize(numGauss);
        myGaussianWeights.resize(numGauss);   
	gaussianQuadrature *gptr = new gaussianQuadrature(numGauss);
           
	myGaussianPositions = gptr->getGaussianPosition();
        myGaussianWeights   = gptr->getGaussianWeights();

	delete gptr ;

        for (int i = 0; i < numGauss ; i++)
		cout << "gauss pos " <<i << " "<<myGaussianPositions[i] << endl ; 

        /*    	        
        myJacobiInv = new float*[2];
        myJacobi    = new float*[2];
        
        myLocalToGlobal = new float*[numElements];
        for (int i = 0; i < numElements; i++)
            myLocalToGlobal[i] = new float[numElemParabolic];
        
        for (int i = 0; i < 2 ; i++)
            myJacobi[i] = new float [2];
        
        for (int i = 0; i < 2; i++)
            myJacobiInv[i] = new float [2];
        

        myAreaWeight.resize(numGauss*numGauss);
        myShapeFunctionDeriv.resize(numElemParabolic);
        myShapeFunctionDerivLinear.resize(numElemLinear);
        */
	        
    }

    drives::~drives()
    {
    }



    
}
