/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : mth_vec2.h
  * PURPOSE     : T51DX12 project.
  *               Vector 2 declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _mth_vec2_h_
#define _mth_vec2_h_

#include "mthdef.h"

namespace mth
{
  template<class Type>
  class vec2
  {
  private:
    Type X, Y;
  public:
    /* Vector init function
     * ARGUMENTS: None.
     * RETURNS:
     * (vec2) vector.
     */
    vec2( VOID ) : X(0), Y(0)
    {
    } /* End of 'vec2' function */
    
    /* Vector init function
     * ARGUMENTS:
     *   - number
     *      Type a;
     * RETURNS:
     * (vec2) vector.
     */
    vec2( Type a ) : X(a), Y(a)
    {
    } /* End of 'vec2' function */

    /* Vector init function
     * ARGUMENTS:
     *   - numbers
     *      Type a, b;
     * RETURNS:
     * (vec2) vector.
     */
    vec2( Type a, Type b ) : X(a), Y(b)
    {
    } /* End of 'vec2' function */

    /* Sqrt from vector function
     * ARGUMENTS: None.
     * RETURNS:
     * (DBL) number.
     */
    DBL operator!( VOID ) const
    {
      return sqrt(X * X + Y * Y);
    } /* End of 'operator!' function */

    /* Add vectors function
     * ARGUMENTS:
     *   - vector to add
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator+( const vec2 & v ) const
    {
      return vec2(v.X + X, v.Y + Y);
    } /* End of 'operator+' function */

    /* Sub vectors function
     * ARGUMENTS:
     *   - vector to SUB
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator-( const vec2 & v ) const
    {
      return vec2(X - v.X, Y - v.Y);
    } /* End of 'operator-' function */

    /* Change all vector numbers sign function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator-( VOID ) const
    {
      return vec2(-X, -Y);
    } /* End of 'operator-' function */

    /* Dot vectors function
     * ARGUMENTS:
     *   - vector to dot
     *      vec2 v;
     * RETURNS:
     *   (Type) result number.
     */
    Type operator&( const vec2 & v ) const
    {
      return X * v.X + Y * v.Y;
    } /* End of 'operator&' function */

    /* Mull vectors components to other vector components function
     * ARGUMENTS:
     *   - vector
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator*( const vec2& v ) const
    {
      return vec2(X * v.X, Y * v.Y);
    } /* End of 'operator*' function */
    
    /* Mull vectors components to num function
     * ARGUMENTS:
     *   - number
     *      DBL a;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator*( const DBL a ) const
    {
      return vec2(X * a, Y * a);
    } /* End of 'operator*' function */

    /* Mull vectors components to num function
     * ARGUMENTS:
     *   - number
     *      DBL a;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator/( const DBL a ) const
    {
      return vec2(X / a, Y / a);
    } /* End of 'operator/' function */
    
    /* Add to vector other function
     * ARGUMENTS:
     *   - vector
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 & operator+=( const vec2 & v )
    {
      X += v.X;
      Y += v.Y;
      
      return *this;
    } /* End of 'operator+=' function */

    /* Sub vector to other function
     * ARGUMENTS:
     *   - vector
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 & operator-=( const vec2 & v )
    {
      X -= v.X;
      Y -= v.Y;

      return *this;
    } /* End of 'operator-=' function */

    /* Mul vector to other function
     * ARGUMENTS:
     *   - vector
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 & operator*=( const vec2 & v )
    {
      X *= v.X;
      Y *= v.Y;
      
      return *this;
    } /* End of 'operator*=' function */

    /* Add to vector other function
     * ARGUMENTS:
     *   - vector
     *      DBL a;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 & operator/=( const DBL a )
    {
      X /= a;
      Y /= a;

      return *this;
    } /* End of 'operator/=' function */

    /* Get vector equal to other function
     * ARGUMENTS:
     *   - vector
     *      vec2 v;
     * RETURNS:
     *   (vec2) result vector.
     */
    //vec2 & operator=( const vec2& v )
    //{
    //  X = v.X;
    //  Y = v.Y;
    //
    //  return *this;
    //}  /* End of 'operator=' function */

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
     *   (vec2) result vector;
     */
    vec2 & Normalizing( VOID )
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
      return X * X + Y * Y;
    } /* End of 'Length2' function */

    /* Get zero vector component function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) vector.
     */
    vec2 & Zero( VOID )
    {
      X = 0; 
      Y = 0;

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
      else
        return Y;
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
  }; /* End of 'vec2' class */
} /* End of 'mth' spacename */

#endif // !_mth_vec2_h_

/* END OF 'mth_vec2.h' FILE */

