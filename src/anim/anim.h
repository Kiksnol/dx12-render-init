/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : anim.h
  * PURPOSE     : T51DX12 project.
  *               Animation system declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 02.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _anim_h_
#define _anim_h_

#include "../def.h"
#include "../win/win.h"
#include "timer.h"
#include "input.h"
#include "render/render.h"

#include <iostream>

/* DirectX namespace */
namespace nidx
{
  /* Animation class */
  class anim : public win, public timer, public input, public render
  {
  private:
    anim(HINSTANCE hInst = GetModuleHandle(nullptr)) : win(hInst), input(MouseWheel), render(win::hWnd)
    {
    }

    ~anim( VOID )
    {
    }

    static anim Instance;
  public:
    static std::string Path;

    static anim& Get(VOID)
    {
      return Instance;
    }

    static anim* GetPtr(VOID)
    {
      return &Instance;
    }

    /* Render stock of unit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      TimerResponse();
      KeyboardResponse();
      MouseResponse(win::hWnd);

    } /* End of 'Render' function */

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override
    {
    } /* End of 'Init' function */
    
    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close(VOID) override
    {
    } /* End of 'Close' function */
    
    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID ) override
    {
      this->Render();
      //this->FrameCopy();
    } /* End of 'Resize' function */
    
    /* Timer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID ) override
    {
      this->Render();
      
      CHAR Buf[30];
    
      sprintf_s(Buf, 30, "FPS: %f", FPS);
      SetWindowTextA(win::hWnd, Buf);
      
    } /* End of 'Timer' function */
    
    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Activate( VOID ) override
    {
    } /* End of 'Activate' function */
    
    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID ) override
    {
      this->Render();
    } /* End of 'Idle' function */
    
    /* Erase function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC ) override
    {
    } /* End of 'Erase' function */
    
    /* Paint function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC ) override
    {
    } /* End of 'Paint' function */

   }; /* End of 'anim' class */

} /* End of 'nidx' spacename */
#endif // !_anim_h_

/* END OF 'anim.h' FILE */
