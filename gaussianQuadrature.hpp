//
//  gaussianQuadrature.hpp
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2019-05-03.
//  Copyright (c) 2019 Ronald Aranha. All rights reserved.
//

#ifndef gaussianQuadrature_hpp
#define gaussianQuadrature_hpp

#include <vector>
using namespace std ;

namespace solver {

   // class for 3-point Gauss-Legendre quadrature
   class gaussianQuadrature{

	std::vector<float>myGaussianPositions ;
        std::vector<float>myGaussianWeights;

	public:

           gaussianQuadrature(int numGauss);
           ~gaussianQuadrature(); 

           void setGaussianPosition();
           void setGaussianWeights();
           
           std::vector <float> getGaussianPosition();
           std::vector <float> getGaussianWeights();        



   }; 


}

#endif
