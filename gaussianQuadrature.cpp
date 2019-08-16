#include "gaussianQuadrature.hpp"
using namespace std;

namespace solver{
  

  gaussianQuadrature:: gaussianQuadrature(int numGauss){
    myGaussianPositions.resize(numGauss,0) ;
    myGaussianWeights.resize(numGauss,0);

    setGaussianPosition(); 	
    setGaussianWeights() ; 
    
  }       	

  gaussianQuadrature::~gaussianQuadrature(){ 	
    //std::cout << "gaussianQuadrature destructed " << std::endl ;	
  }

  void gaussianQuadrature::setGaussianPosition(){
    // 3-point Positions
    myGaussianPositions[0] = 0.7745966692;
    myGaussianPositions[1] = 0. ;
    myGaussianPositions[2] = -0.7745966692 ;
    
  }

  void gaussianQuadrature::setGaussianWeights(){
    
    // 3-point Weights
    myGaussianWeights[0] = 0.55555;
    myGaussianWeights[1] = 0.88888;
    myGaussianWeights[2] = 0.55555;

  }
 
  std::vector <float> gaussianQuadrature::getGaussianPosition(){
    return myGaussianPositions;   
  }


  std::vector <float> gaussianQuadrature::getGaussianWeights(){
    return myGaussianWeights;
  } 
  
}


