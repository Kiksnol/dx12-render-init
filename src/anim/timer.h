/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : timer.h
  * PURPOSE     : T51DX12 project.
  *               Timer system declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _timer_h_
#define _timer_h_

#include "../def.h"

namespace nidx
{
  /* Timer class */
  class timer
  {
  private:
    /* Timer data */
    UINT64
      StartTime,    /* Start program time */
      OldTime,      /* Previous frame time */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */
  public:
    DBL
      GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frame per second */
    BOOL IsPause;                  /* Pause flag */

    /* Timer initializing function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    timer( VOID ) :  GlobalTime(0), GlobalDeltaTime(0), DeltaTime(0), Time(0), FPS(0), IsPause(FALSE)
    {
      LARGE_INTEGER t;
    
      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
      FrameCounter = 0;
      IsPause = FALSE;
      FPS = 30.0;
      PauseTime = 0;
    } /* End of 'TimerInit' function */
    
    /* Timer interframe response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID TimerResponse( VOID )
    {
      LARGE_INTEGER t;
    
      QueryPerformanceCounter(&t);
      /* Global time */
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      /* FPS */
      FrameCounter++;
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    } /* End of 'TimerResponse' function */
  }; /* end of 'timer' class */
} /* end of 'nidx' spacename */
#endif // !_timer_h_

/* END OF 'timer.h' FILE */ 
