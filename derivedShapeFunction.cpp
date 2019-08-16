//
//  derivedShapeFunction.cpp
//  dgfesolver
//
//  Created by Ronald Aranha on 2019-05-01.
//  Copyright © 2019 Ronald Aranha. All rights reserved.
//

#include "derivedShapeFunction.hpp"
using namespace std;

namespace solver{
    
    void derivedShapeFunction::ShapeFunction4(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y){
        
        cout << " inside the derived four element shape function " << myNodePoints <<  endl;

        float xy = x * y;
        
        shape[0] = (1. - x - y - xy) * 0.25 ;
        shape[1] = (1. + x - y - xy) * 0.25 ;
        shape[2] = (1. + x + y + xy) * 0.25 ;
        shape[3] = (1. - x + y - xy) * 0.25 ;
        
        
        deriv[0].x = (-1. + y) * 0.25;
        deriv[1].x = ( 1. - y) * 0.25;
        deriv[2].x = ( 1. + y) * 0.25;
        deriv[3].x = (-1. - y) * 0.25;
        
        deriv[0].y = (-1. + x) * 0.25;
        deriv[1].y = ( 1. - x) * 0.25;
        deriv[2].y = ( 1. + x) * 0.25;
        deriv[3].y = (-1. - x) * 0.25;

    }
    
    void derivedShapeFunction::ShapeFunction8(std::vector<Point2f>& deriv, std::vector<float> &shape, float x, float y){
        
        cout << " inside the derived eight element shape function " << myNodePoints << endl;

	float xy, xx, yy, x2, y2, xy2, xxy, xyy ;
    
        xy  = x * y;
        xx  = x * x;
        yy  = y * y;
        
        x2  = x * 2. ;
        y2  = y * 2. ;
        xy2 = xy * 2. ;
        
        xxy = xx * y;
        xyy = x * yy;
    
        shape[0] = (-1.0 + xy + xx + yy - xxy - xyy ) * 0.25;
        shape[1] = ( 1.0 - y  - xx + xxy) * 0.5;
        shape[2] = (-1.0 - xy + xx + yy - xxy + xyy ) * 0.25;
        shape[3] = ( 1.0 + x  - yy - xyy) * 0.5;
        shape[4] = (-1.0 + xy + xx + yy + xxy + xyy ) * 0.25;
        shape[5] = ( 1.0 + y  - xx - xxy) * 0.5;
        shape[6] = (-1.0 - xy + xx + yy + xxy - xyy ) * 0.25;
        shape[7] = ( 1.0 - x  - yy + xyy) * 0.5;
        
        deriv[0].x = ( y + x2 - xy2 - yy) * 0.25;
        deriv[1].x = (-x + xy);
        deriv[2].x = (-y + x2 - xy2 + yy) * 0.25;
        deriv[3].x = (1.0 - yy) * 0.5;
        deriv[4].x = ( y + x2 + xy2 + yy) * 0.25;
        deriv[5].x = (-x - xy);
        deriv[6].x = (-y + x2 + xy2 - yy) * 0.25;
        deriv[7].x = (- 1.0 + yy) * 0.5;
        
        deriv[0].y = ( x + y2 - xx - xy2) * 0.25;
        deriv[1].y = (-1.0 + xx) * 0.5;
        deriv[2].y = (-x + y2 - xx + xy2) * 0.25;
        deriv[3].y = (-y - xy);
        deriv[4].y = ( x + y2 + xx + xy2) * 0.25;
        deriv[5].y = (1.0 - xx) * 0.5;
        deriv[6].y = (-x + y2 + xx - xy2) * 0.25;
        deriv[7].y = (-y + xy);

        
    }

    void derivedShapeFunction:: Jacobi(float &dJacobiDeterminant, Dim2d &dJacobiMatrixInv, Dim2d &dJacobiMatrix,
                                       const std::vector<Point2f> &deriv, const std::vector<Point2f> &coord, 
				       const Dim2d &localToGlobal, int ielem)
    {
        
        float tempy = 0.;
        float kpoin1, tmp, tmp1 ;
        int   kpoin;
        
        for (int i = 0 ; i < 2; i++){
            for (int j = 0; j < 2; j++){
                for(int inodp = 0; inodp < myNodePoints ; inodp++){
                    kpoin1 = fabs(localToGlobal[ielem][inodp]);
                    kpoin  = (int)kpoin1;
                    //std::cout << "value of coord "<<kpoin<< " "<<coord[kpoin].x << " "<<coord[kpoin].y << std::endl;
                    tmp    = ( j == 0 ) ? coord[kpoin].x : coord[kpoin].y ;
                    tmp1   = ( i == 0 ) ? deriv[inodp].x : deriv[inodp].y ;
                    tempy += tmp1 * tmp ;
                }
                dJacobiMatrix[i][j] = tempy;
            }
        }
        
        dJacobiDeterminant = dJacobiMatrix[0][0] * dJacobiMatrix[1][1] - dJacobiMatrix[1][0] * dJacobiMatrix[0][1];
        
        //compute the inverse of the jacobian matrix
        dJacobiMatrixInv[0][0] =  dJacobiMatrix[1][1]/dJacobiDeterminant;
        dJacobiMatrixInv[1][1] =  dJacobiMatrix[0][0]/dJacobiDeterminant;
        dJacobiMatrixInv[0][1] = -dJacobiMatrix[0][1]/dJacobiDeterminant;
        dJacobiMatrixInv[1][0] = -dJacobiMatrix[1][0]/dJacobiDeterminant;

    }
    
    // constructor     
    derivedShapeFunction::derivedShapeFunction(int npoints):myNodePoints(-1){

        myNodePoints = npoints;    
            
    }
    derivedShapeFunction::derivedShapeFunction(){



    }    
    derivedShapeFunction::~derivedShapeFunction(){
            
            
    }
        
    
    
    
    
}
