/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : dx12.h
  * PURPOSE     : T51DX12 project.
  *               Direct X 12 declaration module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef _dx12_h_
#define _dx12_h_

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <d3d12sdklayers.h>
#include <dxgidebug.h>

#include "../../def.h"

/* Direct X namespace */
namespace nidx
{
  /* Main DirectX class */
  class core
  {
  private:
    INT Width = 0, Height = 0;
    // Direct3D12 interfaces
    static const INT NumOfBuffers = 2;
    IDXGIFactory5* Factory{};
    ID3D12Device5* Device{};
    IDXGISwapChain4* SwapChain{};
    ID3D12Resource* BackBuffers[NumOfBuffers];

    ID3D12DescriptorHeap* RTVHeap{};
    ID3D12DescriptorHeap* SRVHeap{};
    ID3D12DescriptorHeap* DSVHeap{};

    UINT RTVDescSize;
    UINT SRVDescSize;
    UINT DSVDescSize;

    ID3D12CommandQueue* ComQueue{};
    ID3D12CommandAllocator* ComAllocator{};
    ID3D12GraphicsCommandList* ComList{};

    ID3D12Resource* ConstantBuffer{};
    HANDLE Event{};

    ID3D12Fence* Fence{};
    UINT64 FenceValue{};
#ifdef _DEBUG
    ID3D12Debug3* Debug{};
#endif /* _DEBUG */

    static const UINT BufferCount = 3;

  public:
    /* Class main constructor */
    core( HWND &hWnd );

    /* Class main destructor */
    ~core( VOID );

  }; /* End of 'core' class */

} /* end of 'nidx' spacename */
#endif // !_dx12_h_

/* END OF 'dx12.h' FILE */ 