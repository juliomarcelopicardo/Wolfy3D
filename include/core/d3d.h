/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __D3DFRAMEWORK_H__
#define __D3DFRAMEWORK_H__ 1

#include "silverlynx.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <Windows.h>


namespace SLX {

class DirectXFramework {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

   DirectXFramework();
  ~DirectXFramework();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  void init();
  void startRenderFrame(float r = 0.0f, float g = 0.3f, float b = 0.0f, float a = 1.0f);
  void endRenderFrame();
  void shutdown();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  D3DXMATRIX projection_matrix_;
  D3DXMATRIX world_matrix_;
  D3DXMATRIX ortho_matrix_;

/*******************************************************************************
***                           Private                                        ***
*******************************************************************************/

 private:

  // This variable is a pointer to a device. In Direct3D, a device is an object that is intended to be a virtual representation of your video adapter.
  // What this line of code means is that we will create a COM object called ID3D11Device.
  // When COM makes this object, we will ignore it, and access it only indirectly using this pointer.
  ID3D11Device *device_;
  // A device context is similar to a device, but it is responsible for managing the GPU
  // and the rendering pipeline(the device mostly handles video memory).
  // This object is used to render graphics and to determine how they will be rendered.
  ID3D11DeviceContext *device_context_;
  // the swap chain is the series of buffers which take turns being rendered on.
  IDXGISwapChain *swap_chain_;
  // Render target used to render our main window.
  ID3D11RenderTargetView *backbuffer_;
  ID3D11DepthStencilView *depth_stencil_view;

}; /* DirectXFramework */

}; /* SLX */

#endif
