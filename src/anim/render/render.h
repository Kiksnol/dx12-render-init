/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : render.h
  * PURPOSE     : T51DX12 project.
  *               Render system declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _render_h_
#define _render_h_

#include "../dx/dx12.h"

#include "../../def.h"

namespace nidx
{
  class render : public core
  {
  public:

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    render( HWND &hWnd ) : core(hWnd)
    {

    } /* End of 'render' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~render( VOID )
    {
    } /* End of '~render' function */
  
    /* Init render system function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Close render system function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Render system function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
    } /* End of 'Render' function */

  };

}

#endif /* _render_h_ */

/* END OF 'render.h' FILE */