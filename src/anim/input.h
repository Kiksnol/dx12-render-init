/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : input.h
  * PURPOSE     : T51DX12 project.
  *               Input system declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _input_h_
#define _input_h_

#include "../def.h"
#include "../win/win.h"

#define GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)

namespace nidx
{
  /* Timer class */
  class input
  {
  private:
    INT &Wheel;
  public:
    /* keyboard responsing */
    BYTE Keys[256];                /* state of keys on the current frame */
    BYTE KeysClick[256];           /* signs of a single click of the keyboard */
    BYTE KeysOld[256];             /* state of keys on the current frame */

    /* mouse responsing */
    INT MouseX, MouseY, MouseZ,    /* mouse coordinates */
        MouseDX, MouseDY, MouseDZ;
    /* joystick responsing */
    BYTE
      JBut[32], JButOld[32], JButClick[32]; /* joystick button states */
    INT JPov;                               /* joystick point-of-view control [-1, 0..7] */
    DBL
      JX, JY, JZ, JR;               /* joystick axes */

    input( INT &WheelRef ) : Wheel(WheelRef)
    {
      /* Mouse */
      MouseX = 0;
      MouseY = 0;
      MouseZ = 0;
      MouseDX = 0;
      MouseDY = 0;
      MouseDZ = 0;
      /* Joystick */
      JX = 0;
      JY = 0;
      JZ = 0;
      JR = 0;
      /* Keyboard */
      ZeroMemory(Keys, 256);
      ZeroMemory(KeysClick, 256);
      ZeroMemory(KeysOld, 256);
      /* Joystick */
      ZeroMemory(JBut, 32);
      ZeroMemory(JButClick, 32);
      ZeroMemory(JButOld, 32);
    }
    
    /* Animation input keyboard response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID KeyboardResponse( VOID )
    {    
      if (GetKeyboardState(Keys))
      {
        for (INT i = 0; i < 256; i++)
        {
          Keys[i] >>= 7;
          KeysClick[i] = Keys[i] && !KeysOld[i];
        }
        memcpy(KeysOld, Keys, 256);
      }
    } /* End of 'KeyboardResponse' function */

    /* Animation input mouse response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID MouseResponse( HWND hWnd )
    {
      POINT pt;
    
      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);
    
      /* transform coordinates on the screen */
      MouseDX = pt.x - MouseX;
      MouseDY = pt.y - MouseY;
      MouseDZ = Wheel;
      /* absolute val */
      MouseX = pt.x;
      MouseY = pt.y;
      MouseZ += Wheel;
    
      Wheel = 0;
    } /* End of 'MouseResponse' function */ 

    /* Animation joystick response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID JoystickResponse( VOID )
    {
      /* Joystick */
      if (joyGetNumDevs() > 0)
      {
        JOYCAPS jc;


        /* Get joystick info */
        if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
        {
          JOYINFOEX ji;


          ji.dwSize = sizeof(JOYINFOEX);
          ji.dwFlags = JOY_RETURNALL;
          if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
          {
            /* Buttons */
            for (INT i = 0; i < 32; i++)
            {
              JBut[i] = (ji.dwButtons >> i) & 1;
              JButClick[i] = JBut[i] && !JButOld[i];
              JButOld[i] =JBut[i];
            }
            /* Axes */
            JX = GET_JOYSTIC_AXIS(X);
            JY = GET_JOYSTIC_AXIS(Y);
            JZ = GET_JOYSTIC_AXIS(Z);
            JR = GET_JOYSTIC_AXIS(R);
            /* Point of view */
            JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
          }
        }
      }
    } /* End of 'JoystickResponse' function */
  }; /* end of 'input' class */
} /* end of 'nidx' spacename */
#endif // !_input_h_

/* END OF 'input.h' FILE */
