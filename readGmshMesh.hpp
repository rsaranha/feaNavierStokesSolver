//
//  ReadGmshMesh.h
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2016-01-27.
//  Copyright (c) 2016 Ronald Aranha. All rights reserved.
//

#ifndef readGmshMesh_hpp
#define readGmshMesh_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <vector>
#include <string>
#include "dgfeSolver.hpp"

using namespace std;
namespace solver{
    
    class readGmshMesh{
        
    public:
        
        readGmshMesh();
        
        ~readGmshMesh();
        
        char ch_cap ( char ch );
        bool ch_eqi ( char ch1, char ch2 );
        int  ch_to_digit ( char ch );
        void gmsh_data_read (string gmsh_filename, int node_dim, int node_num,
                             Dim2d &globalCoordinates, int element_order, int element_num, Dim2id &element_node );
        void gmsh_size_read (string gmsh_filename, int &node_num, int &node_dim,
                             int &element_num, int &element_order );

        void   i4mat_write ( string output_filename, int m, int n, int table[] );
        double r8_max ( double x, double y );
        double r8_min ( double x, double y );
        void   r8mat_write ( string output_filename, int m, int n, double table[] );
        bool   s_begin ( string s1, string s2 );
        int    s_len_trim ( string s );
        int    s_to_i4 ( string s, int &last, bool &error );
        double s_to_r8 ( string s, int &lchar, bool &error );
        void   timestamp ( );
        
      
    };
    
}

#endif 
