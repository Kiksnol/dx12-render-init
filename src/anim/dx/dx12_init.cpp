/***************************************************************
 * Copyright (C) 2020-2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

 /* FILE NAME   : dx12_init.cpp
  * PURPOSE     : T51DX12 project.
  *               Direct X 12 initialization module.
  * PROGRAMMER  : ND4.
  * LAST UPDATE : 07.10.2021
  * NOTE        : None.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#include <nidx.h>
#include "../../nidx.h"

#include "dx12.h"

#include <vector>
#include <string>

/* Show adapter output display modes in log function.
 * ARGUMENTS:
 *   - DirectX Graphics Infrastructure output:
 *       IDXGIOutput* output;
 *   - DirectX Graphics Infrastructure format:
 *       DXGI_FORMAT format;
 * RETURNS:
 *   (VOID) None.
*/
VOID LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
  UINT count = 0;
  UINT flags = 0;
  // Call with nullptr to get list count.
  output->GetDisplayModeList(format, flags, &count, nullptr);
  std::vector<DXGI_MODE_DESC> modeList(count);
  output->GetDisplayModeList(format, flags, &count, &modeList[0]);
  for(auto& x : modeList)
  {
    UINT n = x.RefreshRate.Numerator;
    UINT d = x.RefreshRate.Denominator;
    std::wstring text =
    L"Width = " + std::to_wstring(x.Width) + L" " + L"Height = " + std::to_wstring(x.Height) + L" " + L"Refresh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) + L"\n";
    ::OutputDebugString(text.c_str());
  }
} /* End of 'LogOutputDisplayModes' function */

/* Show adapter outputs in log function.
 * ARGUMENTS:
 *   - DirectX Graphics Infrastructure adapter:
 *       IDXGIAdapter* adapter;
 * RETURNS:
 *   (VOID) None.
*/
VOID LogAdapterOutputs( IDXGIAdapter* adapter )
{
  UINT i = 0;
  IDXGIOutput* output = nullptr;
  while(adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
  {
    DXGI_OUTPUT_DESC desc;
    output->GetDesc(&desc);
    std::wstring text = L"***Output: ";
    text += desc.DeviceName;
    text += L"\n";
    OutputDebugString(text.c_str());
    LogOutputDisplayModes(output, DXGI_FORMAT_B8G8R8A8_UNORM);
    output->Release();
    ++i;
  }
} /* End of 'LogAdapterOutputs' function */

/* Core class initialization.
 * ARGUMENTS:
 *   - Window:
 *       HWND &hWnd;
 * RETURNS: None.
*/
nidx::core::core( HWND &hWnd )
{
  // Retrive window size data
  RECT rect;
  GetWindowRect(hWnd, &rect);
  Width = rect.right - rect.left;
  Height = rect.bottom - rect.top;

  CreateDXGIFactory(IID_PPV_ARGS(&Factory));

#ifdef _DEBUG
  D3D12GetDebugInterface(IID_PPV_ARGS(&Debug));
  Debug->EnableDebugLayer();
#endif /* _DEBUG */

  IDXGIAdapter* TmpAdapter, * BestAdapter = nullptr;
  DXGI_ADAPTER_DESC AdapterDesc;
  DXGI_ADAPTER_DESC BestAdapterDesc = {};
  int i = 0;

  while (Factory->EnumAdapters(i++, &TmpAdapter) == S_OK)
  {
    TmpAdapter->GetDesc(&AdapterDesc);

    if (BestAdapter == nullptr)
    {
      BestAdapter = TmpAdapter;
      BestAdapterDesc = AdapterDesc;
    }
    else if (AdapterDesc.DedicatedVideoMemory > BestAdapterDesc.DedicatedVideoMemory)
    {
      BestAdapterDesc = AdapterDesc;
      BestAdapter->Release();
      BestAdapter = TmpAdapter;
    }
    else
      TmpAdapter->Release();
  }

  // Create D3D device
  D3D12CreateDevice(BestAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&Device));
  BestAdapter->Release();

  // Create D3D command queue
  D3D12_COMMAND_QUEUE_DESC CQDesc{};
  CQDesc.NodeMask = 0;
  CQDesc.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
  CQDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  CQDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

  Device->CreateCommandQueue(&CQDesc, IID_PPV_ARGS(&ComQueue));

  // Create DXGI swap chain
  DXGI_SWAP_CHAIN_DESC1 SCD{};
  SCD.Width = Width;
  SCD.Height = Height;
  SCD.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
  SCD.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
  SCD.Scaling = DXGI_SCALING_STRETCH;
  SCD.SampleDesc.Count = 1;
  SCD.SampleDesc.Quality = 0;
  SCD.BufferCount = NumOfBuffers;
  SCD.Stereo = FALSE;
  SCD.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  SCD.Flags = 0;

  IDXGISwapChain1* SwapChain1{};
  Factory->CreateSwapChainForHwnd(ComQueue, hWnd, &SCD, nullptr, nullptr, &SwapChain1);

  SwapChain1->QueryInterface(IID_PPV_ARGS(&SwapChain));
  SwapChain1->Release();
  for (INT i = 0; i < NumOfBuffers; i++)
    SwapChain->GetBuffer(i, IID_PPV_ARGS(&BackBuffers[i]));

  // Obtain heap descriptors
  D3D12_DESCRIPTOR_HEAP_DESC DHD{};
  DHD.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  DHD.NodeMask = 0;
  DHD.NumDescriptors = 2 /* frame buffers */ + 1 /* render target */;
  DHD.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  Device->CreateDescriptorHeap(&DHD, IID_PPV_ARGS(&RTVHeap));

  // Depth-stencil
  DHD.NumDescriptors = 1 /* frame buffers */ + 1 /* render target */;
  DHD.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  Device->CreateDescriptorHeap(&DHD, IID_PPV_ARGS(&DSVHeap));

  // Constant/shaders
  DHD.NumDescriptors = 2 /* ??? */;
  DHD.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  DHD.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  Device->CreateDescriptorHeap(&DHD, IID_PPV_ARGS(&SRVHeap));

  for (UINT i = 0; i < NumOfBuffers; i++)
  {
    D3D12_CPU_DESCRIPTOR_HANDLE CDH;

    CDH.ptr =
      RTVHeap->GetCPUDescriptorHandleForHeapStart().ptr +
      i * Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    Device->CreateRenderTargetView(BackBuffers[i], nullptr, CDH);
  }
  Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&ComAllocator));
  Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, ComAllocator, nullptr, IID_PPV_ARGS(&ComList));

  Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence));
  RTVDescSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  DSVDescSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
  SRVDescSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);


  /*UINT k = 0;
  IDXGIAdapter* adapter = nullptr;
  std::vector<IDXGIAdapter*> adapterList;
  while(Factory->EnumAdapters(k, &adapter) != DXGI_ERROR_NOT_FOUND)
  {
    DXGI_ADAPTER_DESC desc;
    adapter->GetDesc(&desc);
    std::wstring text = L"***Adapter: ";
    text += desc.Description;
    text += L"\n";
    OutputDebugString(text.c_str());
    adapterList.push_back(adapter);
    ++k;
  }
  for(size_t k = 0; k < adapterList.size(); ++k)
  {
    LogAdapterOutputs(adapterList[k]);
    adapterList[k]->Release();
  }*/

} /* End of 'nidx::core::core' function */

/* Main class destructor */
nidx::core::~core( VOID )
{
  ComAllocator->Release();
  ComList->Release();
  ComQueue->Release();
  for (INT i = 0; i < NumOfBuffers; i++)
    BackBuffers[i]->Release();
  RTVHeap->Release();
  DSVHeap->Release();
  SRVHeap->Release();

  SwapChain->Release();
  Device->Release();
  Factory->Release();

#ifdef _DEBUG
  Debug->Release();
#endif
} /* End of 'nidx::core::~core' function */


/* END OF 'dx12_init.cpp' FILE */