/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : mthdef.h
  * PURPOSE     : T51DX12 project.
  *               Math definition library.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _mthdef_h_
#define _mthdef_h_

#include <cmath>
#include <commondf.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define R2D(A) ((A) * (180.0 / PI))
#define Degree2Radian(a) D2R(a)

typedef double DBL;
typedef float FLT;

namespace mth {
  template<typename Type> class vec2;
  template<typename Type> class vec3;
  template<typename Type> class vec4;
  template<typename Type> class matr;
}

namespace nidx
{
  typedef mth::vec2<FLT> vec2;
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::matr<FLT> matr;
}
#endif // !_mthdef_h_

/* END OF 'mthdef.h' FILE */
