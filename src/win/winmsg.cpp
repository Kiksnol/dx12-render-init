/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : winmsg.cpp
  * PURPOSE     : T51DX12 project.
  *               Window declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#include <nidx.h>
#include "../nidx.h"

#include <iostream> 
#include "win.h"

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL nidx::win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, 30, 100, NULL);
  return TRUE;
} /* End of 'win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID nidx::win::OnDestroy( VOID )
{
  if (IsInit)
  {
    Close();
    KillTimer(hWnd, 47);
  }
  else
    KillTimer(hWnd, 30);
  PostQuitMessage(30);
  hWnd = nullptr;
} /* End of 'win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID nidx::win::OnSize( UINT State, INT W, INT H )
{
  if (IsInit)
  {
    this->W = W;
    this->H = H;
    Resize();
  }
  else
  {
    this->W = W;
    this->H = H;
  }
} /* End of 'win::OnSize' function */

/* WM_MINMAXINFO window message handle function.
 * ARGUMENTS:
 *   - min max:
 *       MINMAXINFO *minmax;
 * RETURNS: None.
 */
VOID nidx::win::OnGetMinMaxInfo( MINMAXINFO *minmax )
{
  minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) +
    GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
} /* End of 'win::OnGetMinMaxInfo' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL nidx::win::OnEraseBackground( HDC hDC )
{
  if (IsInit)
    Erase(hDC);
  return TRUE;
} /* End of 'win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID nidx::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  if (IsInit)
    Paint(hDC);
} /* End of 'win::OnPaint' function */ 

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID nidx::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  if (IsInit)
    Activate();
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
} /* End of 'win::OnActivate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID nidx::win::OnTimer( INT Id )
{
  if (!IsInit)
  {
    KillTimer(hWnd, 30);
    SetTimer(hWnd, 47, 100, nullptr);
    IsInit = TRUE;

    Init();
    Resize();
  }
  Timer();
} /* End of 'win::OnTimer' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID nidx::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'win::OnMouseWheel' function */

/* WM_MBUTTONDOWN window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID nidx::win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{ 
} /* End of 'win::OnButtonDown' function */

/* WM_MBUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID nidx::win::OnButtonUp( INT X, INT Y, UINT Keys )
{ 
} /* End of 'win::OnButtonUp' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID nidx::win::OnKeyDown( UINT Keys )
{
  if (Keys == 'F')
    this->FlipFullScreen();
  if (Keys == 27)
    this->OnDestroy();
}

/* END OF 'win.cpp' FILE */