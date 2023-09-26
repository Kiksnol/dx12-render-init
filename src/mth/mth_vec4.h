/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : mth_vec4.h
  * PURPOSE     : T51DX12 project.
  *               Vector 4 declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _mth_vec4_h_
#define _mth_vec4_h_

#include "mthdef.h"
#include "mth_vec3.h"

namespace mth
{
  template<class Type>
  class vec4
  {
  private:
    Type X, Y, Z, W;
  public:
    /* Vector init function
     * ARGUMENTS: None.
     * RETURNS:
     * (vec4) vector.
     */
    explicit vec4( VOID ) : X(0), Y(0), Z(0), W(0)
    {
    } /* End of 'vec4' function */
    
    /* Vector init function
     * ARGUMENTS:
     *   - number
     *      Type a;
     * RETURNS:
     * (vec4) vector.
     */
    explicit vec4( Type a ) : X(a), Y(a), Z(a), W(a)
    {
    } /* End of 'vec4' function */

    /* Vector init function
     * ARGUMENTS:
     *   - numbers
     *      Type a, b, c, d;
     * RETURNS:
     * (vec4) vector.
     */
    explicit vec4( Type a, Type b, Type c, Type d ) : X(a), Y(b), Z(c), W(d)
    {
    } /* End of 'vec4' function */

    /* Vector init function
     * ARGUMENTS:
     *   - numbers
     *      Type a, b, c, d;
     * RETURNS:
     * (vec4) vector.
     */
    explicit vec4( vec3<Type> a, Type d ) : X(a.X), Y(a.Y), Z(a.Z), W(d)
    {
    } /* End of 'vec4' function */

    /* Sqrt from vector function
     * ARGUMENTS: None.
     * RETURNS:
     * (DBL) number.
     */
    DBL operator!( VOID ) const
    {
      return sqrt(X * X + Y * Y + Z * Z + W * W);
    } /* End of 'operator!' function */

    /* Add vectors function
     * ARGUMENTS:
     *   - vector to add
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator+( const vec4 & v ) const
    {
      return vec4(v.X + X, v.Y + Y, v.Z + Z, v.W + W);
    } /* End of 'operator+' function */

    /* Sub vectors function
     * ARGUMENTS:
     *   - vector to SUB
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator-( const vec4 & v ) const
    {
      return vec4(X - v.X, Y - v.Y, Z - v.Z, W - v.W);
    } /* End of 'operator-' function */

    /* Change all vector numbers sign function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator-( VOID ) const
    {
      return vec4(-X, -Y, -Z, -W);
    } /* End of 'operator-' function */

    /* Dot vectors function
     * ARGUMENTS:
     *   - vector to dot
     *      vec4 v;
     * RETURNS:
     *   (Type) result number.
     */
    Type operator&( const vec4 & v ) const
    {
      return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
    } /* End of 'operator&' function */

    /* Mull vectors components to other vector components function
     * ARGUMENTS:
     *   - vector
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator*( const vec4& v ) const
    {
      return vec4(X * v.X, Y * v.Y, Z * v.Z, W * v.W);
    } /* End of 'operator*' function */
    
    /* Mull vectors components to num function
     * ARGUMENTS:
     *   - number
     *      DBL a;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator*( const DBL a ) const
    {
      return vec4(X * a, Y * a, Z * a, W * a);
    } /* End of 'operator*' function */

    /* Mull vectors components to num function
     * ARGUMENTS:
     *   - number
     *      DBL a;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator/( const DBL a ) const
    {
      return vec4(X / a, Y / a, Z / a, W / a);
    } /* End of 'operator/' function */
    
    /* Add to vector other function
     * ARGUMENTS:
     *   - vector
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 & operator+=( const vec4 & v )
    {
      X += v.X;
      Y += v.Y;
      Z += v.Z;
      W += v.W;
      
      return *this;
    } /* End of 'operator+=' function */

    /* Sub vector to other function
     * ARGUMENTS:
     *   - vector
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 & operator-=( const vec4 & v )
    {
      X -= v.X;
      Y -= v.Y;
      Z -= v.Z;
      W -= v.W;

      return *this;
    } /* End of 'operator-=' function */

    /* Mul vector to other function
     * ARGUMENTS:
     *   - vector
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 & operator*=( const vec4 & v )
    {
      X *= v.X;
      Y *= v.Y;
      Z *= v.Z;
      W *= v.W;
      
      return *this;
    } /* End of 'operator*=' function */

    /* Add to vector other function
     * ARGUMENTS:
     *   - vector
     *      DBL a;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 & operator/=( const DBL a )
    {
      X /= a;
      Y /= a;
      Z /= a;
      W /= a;

      return *this;
    } /* End of 'operator/=' function */

    /* Get vector equal to other function
     * ARGUMENTS:
     *   - vector
     *      vec4 v;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 & operator=( const vec4& v )
    {
      X = v.X;
      Y = v.Y;
      Z = v.Z;
      W = v.W;

      return *this;
    }  /* End of 'operator=' function */

    /* Get normal of vector function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Normalize( VOID )  
    {
      *this /= !*this;
    } /* End of 'Normalize' function */

    /* Get normalizing vector function
     * ARGUMENTS: None.
     * RETURNS: 
     *   (vec4) result vector;
     */
    vec4 & Normalizing( VOID )
    {
      return *this /= !*this;
    } /* End of 'Normalizing' function */

    /* Get vector sqr length function
     * ARGUMENTS: None.
     * RETURNS:
     *   (DBL) sqr length.
     */
    DBL Length2( VOID )
    {
      return X * X + Y * Y + Z * Z + W * W;
    } /* End of 'Length2' function */

    /* Get zero vector component function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) vector.
     */
    vec4 & Zero( VOID )
    {
      X = 0; 
      Y = 0; 
      Z = 0;
      W = 0;

      return *this;
    } /* End of 'Zero' function */

    /* Get vector components function
     * ARGUMENTS:
     *   - Comoponents number:
     *       DBL a; 
     * RETURNS:
     *   (Type) component.
     */
    Type operator[]( const DBL a ) const
    {
      if (a == 0)
        return X;
      else if (a == 1)
        return Y;
      else if (a == 2)
        return Z;
      else
        return W;
    } /* End of 'operator[]' function */
    
    /* Get value of first vector component function
     * ARGUMENTS: None.
     * RETURNS:
     *   (operator const Type*) value.
     */
    operator const Type* ( VOID ) const
    {
      return &X;
    } /* End of 'type*' function */
  }; /* End of 'vec4' class */
} /* End of 'mth' spacename */

#endif // !_mth_vec4_h_

/* END OF 'mth_vec4.h' FILE */
