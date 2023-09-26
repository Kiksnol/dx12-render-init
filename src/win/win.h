/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : win.h
  * PURPOSE     : T51DX12 project.
  *               Window declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _win_h_
#define _win_h_

#include "../def.h"

#define WND_CLASS_NAME "DirectX12 proj"

namespace nidx
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle

  private:    
    /* Window handle function.
     * ARGUMENTS:
     *   - window handle:
     *      HWND hWnd;
     *   - message type (see WM_***):
     *      UINT Msg;
     *   - message 'word' parameter:
     *      WPARAM wParam;
     *   - message 'long' parameter:
     *      LPARAM lParam;
     * RETURNS:
     *   (LRESULT) message depende return value.
     */
    static LRESULT CALLBACK WindowFunc( HWND hWnd, UINT Msg,
                                        WPARAM wParam, LPARAM lParam )
    {
      win *Win = nullptr;
      HDC hDC;
      PAINTSTRUCT ps;
      
      switch (Msg)
      {
      case WM_GETMINMAXINFO:
        if (Win != nullptr)
          Win->OnGetMinMaxInfo((MINMAXINFO*)lParam);
        return 0;
      case WM_LBUTTONDOWN:
      {
        SetCapture(hWnd);
        return 0;
      }
      case WM_LBUTTONUP:
      {
        ReleaseCapture();
        return 0;
      }
      case WM_CREATE:
        SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
      default:
        Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));
        if (Win != nullptr)
          switch (Msg)
          {
          case WM_CREATE:
            Win->hWnd = hWnd;
            return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
          case WM_SIZE:
            Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
            return 0;
          case WM_ERASEBKGND:
            return (LRESULT)Win->OnEraseBackground((HDC)wParam);
          case WM_PAINT:
            hDC = BeginPaint(hWnd, &ps);
            Win->OnPaint(hDC, &ps);
            EndPaint(hWnd, &ps);
            return 0;
          case WM_TIMER:
            Win->OnTimer((UINT)wParam);
            return 0;
          case WM_MOUSEWHEEL:
          {
            Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                              (INT)(SHORT)HIWORD(lParam),
                              (INT)(SHORT)HIWORD(wParam),
                              (UINT)(SHORT)LOWORD(wParam));
            return 0;
          }
          case WM_KEYDOWN:
          {
            Win->OnKeyDown(wParam);
            return 0;
          }
          case WM_DESTROY:
            Win->OnDestroy();
            return 0;
          }
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    } /* End of 'WindowFunc' function */

    BOOL IsFullScreen;
    RECT FullScreenSaveRect;
  public:
    BOOL IsActive;
    BOOL IsInit;
    INT MouseWheel;

    win( HINSTANCE hInst = GetModuleHandle(nullptr) ) : hInstance(hInst), MouseWheel(0), IsFullScreen(FALSE), W(0), H(0), FullScreenSaveRect(), 
                                                        IsActive(TRUE), hWnd((HWND)0), IsInit(FALSE)
    {
      WNDCLASS wc;

      wc.style = CS_VREDRAW | CS_HREDRAW;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = sizeof(win*);
      wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
      wc.hCursor = LoadCursor(nullptr, IDC_CROSS);
      wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
      wc.lpszMenuName = nullptr;
      wc.hInstance = hInstance;
      wc.lpfnWndProc = WindowFunc;
      wc.lpszClassName = L"DirectX12 proj";
      
      if (!RegisterClass(&wc))
      {
        MessageBox(NULL, L"Error register window class", L"ERROR", MB_OK);
        return;
      }

      hWnd = CreateWindow(L"DirectX12 proj", L"ND4 DirectX12 proj",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInstance, reinterpret_cast<VOID*>(this));

      /* Show window */
      ShowWindow(hWnd, SW_SHOWNORMAL);
      UpdateWindow(hWnd);

      /* Show Cursor */
      ShowCursor(TRUE);

    }

    /* Dispatch messages function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Run( VOID )
    {
      MSG msg;

      while (TRUE)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
          if (msg.message == WM_QUIT)
            break;
          DispatchMessage(&msg);
        }
        else
          if (IsInit)
            Idle();
    } /* End of 'Run' function */

    /* Flip full screen function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FlipFullScreen( VOID )
    {
      if (!IsFullScreen)
      {
        HMONITOR hMon;
        MONITORINFOEX moninfo;
        RECT rc;

        IsFullScreen = TRUE;

        /* Save old window size and position */
        GetWindowRect(hWnd, &FullScreenSaveRect);

        /* Get closest monitor */
        hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

        /* Get monitor information */
        moninfo.cbSize = sizeof(moninfo);
        GetMonitorInfo(hMon, (MONITORINFO*)&moninfo);

        rc = moninfo.rcMonitor;
        AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

        /* Expand window to full screen */
        SetWindowPos(hWnd, HWND_TOPMOST,
          rc.left, rc.top,
          rc.right - rc.left, rc.bottom - rc.top,
          SWP_NOOWNERZORDER);
      }
      else
      {
        IsFullScreen = FALSE;

        /* Restore window size and position */
        SetWindowPos(hWnd, HWND_NOTOPMOST,
          FullScreenSaveRect.left, FullScreenSaveRect.top,
          FullScreenSaveRect.right - FullScreenSaveRect.left, FullScreenSaveRect.bottom - FullScreenSaveRect.top,
          SWP_NOOWNERZORDER);
      }
    } /* End of 'FlipFullScreen' function */

  private:
    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT* CS );

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID );

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );

    /* WM_MINMAXINFO window message handle function.
     * ARGUMENTS:
     *   - min max:
     *       MINMAXINFO *minmax;
     * RETURNS: None.
     */
    VOID OnGetMinMaxInfo( MINMAXINFO *minmax );

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBackground( HDC hDC );

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT* PS );

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
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id );

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
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - keys:
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnKeyDown( UINT Keys );

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
    VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );

    /* WM_MBUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys );

        /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Timer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */
    
    /* Erase function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

  }; /* end of 'win' class */

} /* end of 'nidx' spacename */
#endif // !_win_h_

/* END OF 'win.h' FILE */