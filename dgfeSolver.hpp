//
//  dgFeaSolver.h
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2016-02-27.
//  Copyright (c) 2016 Ronald Aranha. All rights reserved.
//

#ifndef dgfeSolver_dgfeSolver_hpp
#define dgfeSolver_dgfeSolver_hpp

#include <vector>
#include <math.h>

typedef struct{
	float x, y;

} Point2f ;

typedef std::vector<Point2f> Dim2 ;
typedef std::vector<Dim2>    Dim3 ;
typedef std::vector<Dim3>    Dim4 ;


typedef std::vector<float>  Dim1d ;
typedef std::vector<Dim1d>  Dim2d ;
typedef std::vector<Dim2d>  Dim3d ;

typedef std::vector<int>     Dim1id ;
typedef std::vector<Dim1id>  Dim2id ;

typedef std::vector<double> Dim1dd;
typedef std::vector<Dim1dd> Dim2dd;

#endif
