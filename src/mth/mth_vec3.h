/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : mth_vec3.h
  * PURPOSE     : T51DX12 project.
  *               Vector 3 declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _mth_vec3_h_
#define _mth_vec3_h_

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* Vec3 handle class */
  template <typename Type>
  class vec3
  {
  private:
    Type X, Y, Z;
  public:
    /* Vector construction function.
     * ARGUMENTS:
     *   - None.
    */
    vec3( VOID ) : X(0), Y(0), Z(0)
    {
    } /* End of 'vec3 constructor' function */

    /* Vector construction function.
     * ARGUMENTS:
     *   - 3 coords:
     *       Type A, B, C;
    */
    vec3( Type A, Type B, Type C ) : X(A), Y(B), Z(C)
    {
    } /* End of 'vec3 constructor' function */

    /* Vector construction function.
     * ARGUMENTS:
     *   - 1 coord for all:
     *       Type A;
    */
    vec3( Type A ) : X(A), Y(A), Z(A)
    {
    } /* End of 'vec3 constructor' function */

    /* Operator + redefinition function.
     * ARGUMENTS:
     *   - Vector to add:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator +( const vec3 &val )
    {
      return vec3(this->X + val.X, this->Y + val.Y, this->Z + val.Z);
    } /* End of 'operator +' function */

    /* Operator - redefinition function.
     * ARGUMENTS:
     *   - Vector to sub:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator -( const vec3 &val )
    {
      return vec3(X - val.X, Y - val.Y, Z - val.Z);
    } /* End of 'operator -' function */

    /* Operator & redefinition function.
     * ARGUMENTS:
     *   - Vector to dot:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    Type operator &( const vec3 &val )
    {
      return X * val.X + Y * val.Y + Z * val.Z;
    } /* End of 'operator &' function */

    /* Operator % redefinition function.
     * ARGUMENTS:
     *   - Vector to cross:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator %( const vec3 &val )
    {
      return vec3(Y * val.Z - Z * val.Y, Z * val.X - X * val.Z, X * val.Y - Y * val.X);
    } /* End of 'operator %' function */

    /* Operator - redefinition function. Negative.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator -( void )
    {
      return vec3(-X, -Y, -Z);
    } /* End of 'operator -' function */

    /* Operator ! redefinition function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (DBL) vector length;
    */
    DBL operator !( VOID )
    {
      return sqrt(X * X + Y * Y + Z * Z);
    } /* End of 'operator !' function */

    /* Operator * redefinition function.
     * ARGUMENTS:
     *   - Number to multiply:
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator *( const Type N )
    {
      return vec3(X * N, Y * N, Z * N);
    } /* End of 'operator *' function */

    /* Operator / redefinition function.
     * ARGUMENTS:
     *   - Number to divide:
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator /( const Type N )
    {
      return vec3(X / N, Y / N, Z / N);
    } /* End of 'operator /' function */

    /* Operator += redefinition function.
     * ARGUMENTS:
     *   - Vector to add:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator +=( const vec3 &val )
    {
      X += val.X;
      Y += val.Y;
      Z += val.Z;

      return *this;
    } /* End of 'operator +=' function */

    /* Operator -= redefinition function.
     * ARGUMENTS:
     *   - Vector to sub:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator -=( const vec3 &val )
    {
      X -= val.X;
      Y -= val.Y;
      Z -= val.Z;

      return *this;
    } /* End of 'operator -=' function */

    /* Operator *= redefinition function.
     * ARGUMENTS:
     *   - Number to multiply:
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator *=( const Type N )
    {
      X *= N;
      Y *= N;
      Z *= N;

      return *this;
    } /* End of 'operator *=' function */

    /* Operator /= redefinition function.
     * ARGUMENTS:
     *   - Number to divide:
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator /=( const Type N )
    {
      X /= N;
      Y /= N;
      Z /= N;

      return *this;
    } /* End of 'operator /=' function */

    /* Squared length function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (Type) vector length;
    */
    Type Length2( VOID )
    {
      return X * X + Y * Y + Z * Z;
    } /* End of 'Length2' function */

    /* Distance finder function.
     * ARGUMENTS:
     *   - Vector to find dist:
     *       const vec3 &val;
     * RETURNS:
     *   (DBL) distance;
    */
    DBL Distance( const vec3 &val )
    {
      return sqrt((X - val.X) * (X - val.X) + (Y - val.Y) * (Y - val.Y) + (Z - val.Z) * (Z - val.Z));
    } /* End of 'Distance' function */

    /* Operator * redefinition function.
     * ARGUMENTS:
     *   - Vector to mul:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator *( const vec3 &val )
    {
      return vec3(X * val.X, Y * val.Y, Z * val.Z);
    } /* End of 'operator *' function */

    /* Operator *= redefinition function.
     * ARGUMENTS:
     *   - Vector to mul:
     *       const vec3 &val;
     * RETURNS:
     *   (vec3) result vector;
    */
    vec3 operator *=( const vec3 &val )
    {
      X *= val.X;
      Y *= val.Y;
      Z *= val.Z;

      return *this;
    } /* End of 'operator *=' function */

    vec3 operator ~( VOID )
    {
      return *this / !*this;
    }

    /* Normalize function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   None.
    */
    VOID Normalize( VOID )
    {
      *this /= !*this;
    } /* End of 'Normalize' function */

    /* Normalize function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (vec3 &) normalized vector.
    */
    vec3 Normalizing( VOID )
    {
      return *this / !*this;
    } /* End of 'Normalizing' function */

    /* Zero vector function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (vec3) zero vector.
    */
    vec3 Zero( VOID )
    {
      return vec3(0);
    } /* End of 'Zero' function */

    /* Operator [] redefinition function.
     * ARGUMENTS:
     *   - Element number:
     *       INT i;
     * RETURNS:
     *   (Type &) element.
    */
    Type & operator []( INT i )
    {
      switch(i)
      {
      case 0:
        return this->X;
      case 1:
        return this->Y;
      case 2:
        return this->Z;
      default:
        if (i < 0)
          return this->X;
        else
          return this->Z;
      }
    } /* End of 'operator []' function */

    template <typename Type1>
    friend class matr;
    template <typename Type2>
    friend class vec4;
  }; /* End of 'vec3' class */
} /* End of 'mth' namespace */

#endif // !_mth_vec3_h_

/* END OF 'mth_vec3.h' FILE */
