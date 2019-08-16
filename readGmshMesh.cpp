//
//  Input.cpp
//  dgFeaSolver
//
//  Created by Ronald Aranha on 2016-01-27.
//  Copyright (c) 2016 Ronald Aranha. All rights reserved.
//

#include "readGmshMesh.hpp"
#include "dgfeSolver.hpp"

namespace solver{
    
    readGmshMesh::readGmshMesh(){
        
        std::cout<< "readGmshMesh constructor "<< std::endl ;
        
    }
    
    readGmshMesh::~readGmshMesh(){
        
        
    }
    

char readGmshMesh::ch_cap ( char ch )
{
  if ( 97 <= ch && ch <= 122 ) 
  {
    ch = ch - 32;
  }   

  return ch;
}

bool readGmshMesh::ch_eqi ( char ch1, char ch2 )
{
  if ( 97 <= ch1 && ch1 <= 122 ) 
  {
    ch1 = ch1 - 32;
  } 
  if ( 97 <= ch2 && ch2 <= 122 ) 
  {
    ch2 = ch2 - 32;
  }     

  return ( ch1 == ch2 );
}

int  readGmshMesh::  ch_to_digit ( char ch )
{
  int digit;

  if ( '0' <= ch && ch <= '9' )
  {
    digit = ch - '0';
  }
  else if ( ch == ' ' )
  {
    digit = 0;
  }
  else
  {
    digit = -1;
  }

  return digit;
}

void  readGmshMesh:: gmsh_data_read ( string gmsh_filename, int node_dim, int node_num, 
  Dim2d &node_x, int element_order, int element_num, Dim2id &element_node )
{
  int i;
  int i4_dummy;
  bool ierror;
  int indx;
  ifstream input;
  int j;
  int k;
  int length;
  int level;
  string text;
  double x;
  double y;
  double z;

  input.open ( gmsh_filename.c_str ( ) );

  if ( ! input )
  {
    cerr << "\n";
    cerr << "GMSH_DATA_READ - Fatal error!\n";
    cerr << "  Could not open input file \"" << gmsh_filename << "\"\n";
    exit ( 1 );
  }

  level = 0;
 
  for ( ; ; )
  {
    getline ( input, text );

    if ( input.eof ( ) )
    {
      break;
    }

    if ( level == 0 )
    {
      if ( s_begin ( text, "$Nodes" ) )
      {
        level = 1;
      }
    }
    else if ( level == 1 )
    {
      i4_dummy = s_to_i4 ( text, length, ierror );
      level = 2;
      j = 0;
    }
    else if ( level == 2 )
    {
      if ( s_begin ( text, "$EndNodes" ) )
      {
        break;
      }
      else
      {
        i4_dummy = s_to_i4 ( text, length, ierror );
        text.erase ( 0, length );
        for ( i = 0; i < 3; i++ )
        {
          x = s_to_r8 ( text, length, ierror );
          node_x[i4_dummy-1][i] = (float) x ;
          text.erase ( 0, length );
          //node_x[i+j*node_dim] = x;
        }
        j = j + 1;
      }
    }
  }
//
//  Now read element information.
//
  level = 0;
  for ( ; ; )
  {
    getline ( input, text );

    if ( input.eof ( ) )
    {
      break;
    }

    if ( level == 0 )
    {
      if ( s_begin ( text, "$Elements" ) )
      {
        level = 1;
      }
    }
    else if ( level == 1 )
    {
      i4_dummy = s_to_i4 ( text, length, ierror );
      level = 2;
      j = 0;
    }
    else if ( level == 2 )
    {
      if ( s_begin ( text, "$EndElements" ) )
      {
        break;
      }
      else
      {
        int ielem ; 
         
        for ( k = 1; k <= 14; k++ )
        {
          i4_dummy = s_to_i4 ( text, length, ierror );

          if (k == 1)
	     ielem = i4_dummy ;      	  

          if (k >= 7)            
             element_node[ielem-1][k-7] = i4_dummy;
 
          text.erase ( 0, length );
        }
        //printf("element_order = %d \n", element_order);
        //fflush(stdout);
        for ( i = 0; i < element_order; i++ )
        {
          k = s_to_i4 ( text, length, ierror );
          text.erase ( 0, length );
          //element_node[i+j*element_order] = k;
          //printf("element vals = %d  elements = %d\n", i, k);
          //fflush(stdout);
        }
        j = j + 1;
      }
    }
  }

  input.close ( );

  return;
}

void  readGmshMesh::gmsh_size_read(string gmsh_filename, int &node_num, int &node_dim,
  int &element_num, int &element_order)
{
  bool ierror;
  int indx;
  ifstream input;
  int k;
  int length;
  int level;
  const double r8_big = 1.0E+30;
  string text;
  double x;
  double x_max;
  double x_min;
  double y;
  double y_max;
  double y_min;
  double z;
  double z_max;
  double z_min;

  node_num = 0;
  node_dim = 0;

  x_max = - r8_big;
  x_min = + r8_big;
  y_max = - r8_big;
  y_min = + r8_big;
  z_max = - r8_big;
  z_min = + r8_big;

  input.open ( gmsh_filename.c_str ( ) );

  if ( ! input )
  {
    cerr << "\n";
    cerr << "GMSH_SIZE_READ - Fatal error!\n";
    cerr << "  Could not open input file \"" << gmsh_filename << "\"\n";
    exit ( 1 );
  }

  level = 0;
 
  for ( ; ; )
  {
    getline ( input, text );

    if ( input.eof ( ) )
    {
      break;
    }

    if ( level == 0 )
    {
      if ( s_begin ( text, "$Nodes" ) )
      {
        level = 1;
      }
    }
    else if ( level == 1 )
    {
      node_num = s_to_i4 ( text, length, ierror );
      level = 2;
    }
    else if ( level == 2 )
    {
      if ( s_begin ( text, "$EndNodes" ) )
      {
        break;
      }
      else
      {
        indx = s_to_i4 ( text, length, ierror );
        text.erase ( 0, length );

        x = s_to_r8 ( text, length, ierror );
        x_min = r8_min ( x_min, x );
        x_max = r8_max ( x_max, x );
        text.erase ( 0, length );

        y = s_to_r8 ( text, length, ierror );
        y_min = r8_min ( y_min, y );
        y_max = r8_max ( y_max, y );
        text.erase ( 0, length );

        z = s_to_r8 ( text, length, ierror);
        z_min = r8_min ( z_min, z );
        z_max = r8_max ( z_max, z );
        text.erase ( 0, length );
      }
    }
  }
//
//  Make a very simple guess as to the dimensionality of the data.
//
  node_dim = 3;
  if ( z_max == z_min )
  {
    node_dim = 2;
    if ( y_max == y_min )
    {
      node_dim = 1;
    }
  }
//
//  Now read element information.
//
  level = 0;

  for ( ; ; )
  {
    getline ( input, text );

    if ( input.eof ( ) )
    {
      break;
    }

    if ( level == 0 )
    {
      if ( s_begin ( text, "$Elements" ) )
      {
        level = 1;
      }
    }
    else if ( level == 1 )
    {
      element_num = s_to_i4 ( text, length, ierror );
      level = 2;
    }
    else if ( level == 2 )
    {
      if ( s_begin ( text, "$EndElements" ) )
      {
        break;
      }
      else
      {
        k = 0;
        for ( ; ; )
        {
          indx = s_to_i4 ( text, length, ierror );
          text.erase ( 0, length );
          if ( ierror != 0 )
          {
            break;
          }
          k = k + 1;
        }
        //cout << "element_order " << k << endl ;  
        element_order = k - 5;
        break;
      }
    }
  }

  input.close ( );

  return;
}

void  readGmshMesh::i4mat_write ( string output_filename, int m, int n, int table[] )
{
  int i;
  int j;
  ofstream output;
//
//  Open the file.
//
  output.open ( output_filename.c_str ( ) );

  if ( !output )
  {
    cerr << "\n";
    cerr << "I4MAT_WRITE - Fatal error!\n";
    cerr << "  Could not open the output file.\n";
    exit ( 1 );
  }
//
//  Write the data.
//
  for ( j = 0; j < n; j++ )
  {
    for ( i = 0; i < m; i++ )
    {
      output << "  " << table[i+j*m];
    }
    output << "\n";
  }
//
//  Close the file.
//
  output.close ( );

  return;
}

double readGmshMesh::r8_max ( double x, double y )
{
  double value;

  if ( y < x )
  {
    value = x;
  }
  else
  {
    value = y;
  }
  return value;
}

double readGmshMesh::r8_min ( double x, double y )
{
  double value;

  if ( y < x )
  {
    value = y;
  }
  else
  {
    value = x;
  }
  return value;
}

void readGmshMesh::r8mat_write ( string output_filename, int m, int n, double table[] )
{
  int i;
  int j;
  ofstream output;
//
//  Open the file.
//
  output.open ( output_filename.c_str ( ) );

  if ( !output )
  {
    cerr << "\n";
    cerr << "R8MAT_WRITE - Fatal error!\n";
    cerr << "  Could not open the output file.\n";
    exit ( 1 );
  }
//
//  Write the data.
//
  for ( j = 0; j < n; j++ )
  {
    for ( i = 0; i < m; i++ )
    {
      output << "  " << table[i+j*m];
    }
    output << "\n";
  }
//
//  Close the file.
//
  output.close ( );

  return;
}

bool readGmshMesh::s_begin ( string s1, string s2 )
{
  int i;
  int n1;
  int n2;

  n1 = s1.length ( );
  n2 = s2.length ( );

  if ( n1 < n2 )
  {
    return false;
  }

  for ( i = 0; i < n2; i++ )
  {
    if ( ch_cap ( s1[i] ) != ch_cap ( s2[i] ) )
    {
      return false;
    }
  }
  return true;
}

int readGmshMesh::s_len_trim ( string s )
{
  int n;

  n = s.length ( );

  while ( 0 < n ) 
  {
    if ( s[n-1] != ' ' && s[n-1] != '\n' )
    {
      return n;
    }
    n = n - 1;
  }

  return n;
}

int readGmshMesh::s_to_i4 ( string s, int &last, bool &error )
{
  char c;
  int i;
  int isgn;
  int istate;
  int ival;

  error = false;
  istate = 0;
  isgn = 1;
  i = 0;
  ival = 0;

  for ( ; ; ) 
  {
    c = s[i];
    i = i + 1;
//
//  Haven't read anything.
//
    if ( istate == 0 )
    {
      if ( c == ' ' )
      {
      }
      else if ( c == '-' )
      {
        istate = 1;
        isgn = -1;
      }
      else if ( c == '+' )
      {
        istate = 1;
        isgn = + 1;
      }
      else if ( '0' <= c && c <= '9' )
      {
        istate = 2;
        ival = c - '0';
      }
      else
      {
        error = true;
        return ival;
      }
    }
//
//  Have read the sign, expecting digits.
//
    else if ( istate == 1 )
    {
      if ( c == ' ' )
      {
      }
      else if ( '0' <= c && c <= '9' )
      {
        istate = 2;
        ival = c - '0';
      }
      else
      {
        error = true;
        return ival;
      }
    }
//
//  Have read at least one digit, expecting more.
//
    else if ( istate == 2 )
    {
      if ( '0' <= c && c <= '9' )
      {
        ival = 10 * ival + c - '0';
      }
      else
      {
        ival = isgn * ival;
        last = i - 1;
        return ival;
      }

    }
  }
//
//  If we read all the characters in the string, see if we're OK.
//
  if ( istate == 2 )
  {
    ival = isgn * ival;
    last = s_len_trim ( s );
  }
  else
  {
    error = true;
    last = 0;
  }

  return ival;
}

double readGmshMesh::s_to_r8 ( string s, int &lchar, bool &error )
{
  char c;
  int ihave;
  int isgn;
  int iterm;
  int jbot;
  int jsgn;
  int jtop;
  int nchar;
  int ndig;
  double r;
  double rbot;
  double rexp;
  double rtop;
  char TAB = 9;

  nchar = s_len_trim ( s );
  error = false;
  r = 0.0;
  lchar = -1;
  isgn = 1;
  rtop = 0.0;
  rbot = 1.0;
  jsgn = 1;
  jtop = 0;
  jbot = 1;
  ihave = 1;
  iterm = 0;

  for ( ; ; )
  {
    c = s[lchar+1];
    lchar = lchar + 1;
//
//  Blank or TAB character.
//
    if ( c == ' ' || c == TAB )
    {
      if ( ihave == 2 )
      {
      }
      else if ( ihave == 6 || ihave == 7 )
      {
        iterm = 1;
      }
      else if ( 1 < ihave )
      {
        ihave = 11;
      }
    }
//
//  Comma.
//
    else if ( c == ',' || c == ';' )
    {
      if ( ihave != 1 )
      {
        iterm = 1;
        ihave = 12;
        lchar = lchar + 1;
      }
    }
//
//  Minus sign.
//
    else if ( c == '-' )
    {
      if ( ihave == 1 )
      {
        ihave = 2;
        isgn = -1;
      }
      else if ( ihave == 6 )
      {
        ihave = 7;
        jsgn = -1;
      }
      else
      {
        iterm = 1;
      }
    }
//
//  Plus sign.
//
    else if ( c == '+' )
    {
      if ( ihave == 1 )
      {
        ihave = 2;
      }
      else if ( ihave == 6 )
      {
        ihave = 7;
      }
      else
      {
        iterm = 1;
      }
    }
//
//  Decimal point.
//
    else if ( c == '.' )
    {
      if ( ihave < 4 )
      {
        ihave = 4;
      }
      else if ( 6 <= ihave && ihave <= 8 )
      {
        ihave = 9;
      }
      else
      {
        iterm = 1;
      }
    }
//
//  Exponent marker.
//
    else if ( ch_eqi ( c, 'E' ) || ch_eqi ( c, 'D' ) )
    {
      if ( ihave < 6 )
      {
        ihave = 6;
      }
      else
      {
        iterm = 1;
      }
    }
//
//  Digit.
//
    else if ( ihave < 11 && '0' <= c && c <= '9' )
    {
      if ( ihave <= 2 )
      {
        ihave = 3;
      }
      else if ( ihave == 4 )
      {
        ihave = 5;
      }
      else if ( ihave == 6 || ihave == 7 )
      {
        ihave = 8;
      }
      else if ( ihave == 9 )
      {
        ihave = 10;
      }

      ndig = ch_to_digit ( c );

      if ( ihave == 3 )
      {
        rtop = 10.0 * rtop + ( double ) ndig;
      }
      else if ( ihave == 5 )
      {
        rtop = 10.0 * rtop + ( double ) ndig;
        rbot = 10.0 * rbot;
      }
      else if ( ihave == 8 )
      {
        jtop = 10 * jtop + ndig;
      }
      else if ( ihave == 10 )
      {
        jtop = 10 * jtop + ndig;
        jbot = 10 * jbot;
      }

    }
//
//  Anything else is regarded as a terminator.
//
    else
    {
      iterm = 1;
    }
//
//  If we haven't seen a terminator, and we haven't examined the
//  entire string, go get the next character.
//
    if ( iterm == 1 || nchar <= lchar + 1 )
    {
      break;
    }

  }
//
//  If we haven't seen a terminator, and we have examined the
//  entire string, then we're done, and LCHAR is equal to NCHAR.
//
  if ( iterm != 1 && lchar + 1 == nchar )
  {
    lchar = nchar;
  }
//
//  Number seems to have terminated.  Have we got a legal number?
//  Not if we terminated in states 1, 2, 6 or 7!
//
  if ( ihave == 1 || ihave == 2 || ihave == 6 || ihave == 7 )
  {
    error = true;
    return r;
  }
//
//  Number seems OK.  Form it.
//
  if ( jtop == 0 )
  {
    rexp = 1.0;
  }
  else
  {
    if ( jbot == 1 )
    {
      rexp = pow ( 10.0, jsgn * jtop );
    }
    else
    {
      rexp = jsgn * jtop;
      rexp = rexp / jbot;
      rexp = pow ( 10.0, rexp );
    }

  }

  r = isgn * rexp * rtop / rbot;

  return r;
}

void  readGmshMesh:: timestamp ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}

    
    
        
        
    
    
}
