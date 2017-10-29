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
  ***                               Attributes                                 ***
  *******************************************************************************/

   /// Projection matrix.
   D3DXMATRIX projection_matrix_;
   /// World 3D matrix.
   D3DXMATRIX world_matrix_;
   /// Orthographic matrix for 2D rendering.
   D3DXMATRIX ortho_matrix_;
   /// Video card memory in megabytes.
   SLX::int32 video_card_memory_;
   /// Video card name.
   char video_card_description_[128];

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  /// Default class constructor.
  DirectXFramework();

  /// Default class destructor.
  ~DirectXFramework();

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   bool init();
  ///
  /// @brief  Initializes the DirectX framework.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool init();

  ///--------------------------------------------------------------------------
  /// @fn startRenderFrame(float r = 0.0f, float g = 0.3f, float b = 0.0f, float a = 1.0f);
  ///
  /// @brief  Starts rendering a new frame with the specified param clear color.
  ///
  /// @param  r red color
  /// @param  g green color
  /// @param  b blue color
  /// @param  a alpha color
  ///--------------------------------------------------------------------------
  void startRenderFrame(float32 r = 0.6f, float32 g = 0.6f, float32 b = 0.6f, float32 a = 1.0f);

  ///--------------------------------------------------------------------------
  /// @fn   endRenderFrame();
  ///
  /// @brief  Present the back buffer to the screen since rendering is complete.
  ///--------------------------------------------------------------------------
  void endRenderFrame();

  ///--------------------------------------------------------------------------
  /// @fn   shutdown();
  ///
  /// @brief  Eliminates all the resources allocated into the framework.
  ///--------------------------------------------------------------------------
  void shutdown();

  /*******************************************************************************
  ***                           Setters & Getters                              ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   ID3D11Device* device();
  ///
  /// @brief  device getter.
  /// @return pointer to the Direct3D device used.
  ///--------------------------------------------------------------------------
  ID3D11Device* device();

  ///--------------------------------------------------------------------------
  /// @fn   ID3D11DeviceContext* deviceContext();
  ///
  /// @brief  device context getter.
  /// @return pointer to the Direct3D device context used.
  ///--------------------------------------------------------------------------
  ID3D11DeviceContext* deviceContext();

  /*******************************************************************************
  ***                           Private                                        ***
  *******************************************************************************/

 private:

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// This variable is a pointer to a device. In Direct3D, a device is an object that is intended to be a virtual representation of your video adapter.
  /// What this line of code means is that we will create a COM object called ID3D11Device.
  /// When COM makes this object, we will ignore it, and access it only indirectly using this pointer.
  ID3D11Device *device_;
  /// A device context is similar to a device, but it is responsible for managing the GPU
  /// and the rendering pipeline(the device mostly handles video memory).
  /// This object is used to render graphics and to determine how they will be rendered.
  ID3D11DeviceContext *device_context_;
  /// the swap chain is the series of buffers which take turns being rendered on.
  IDXGISwapChain *swap_chain_;
  /// Render target used to render our main window.
  ID3D11RenderTargetView *render_target_view_;
  /// Depth stencil view used to view onto buffer texture.
  ID3D11DepthStencilView *depth_stencil_view_;
  /// Depth stencil buffer.
  ID3D11Texture2D* depth_stencil_buffer_;
  /// Depth stencil state controls how the depth buffer and the stencil buffer are used.
  ID3D11DepthStencilState* depth_stencil_state_;
  /// Raster state controls how the raster is used.
  ID3D11RasterizerState* raster_state_;

  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   initVideoCard();
  ///
  /// @brief  Obtains all the settings related with the hardware video graphics
  ///         adapter such as graphics name, memory, refresh rate of the monitor.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initVideoCard();

  ///--------------------------------------------------------------------------
  /// @fn   initVideoCard();
  ///
  /// @brief  The swap chain is the front and back buffer to which the graphics
  ///         will be drawn. Generally you use a single back buffer, do all your
  ///         drawing to it, and then swap it to the front buffer which then
  ///         displays on the user's screen. That is why it is called a swap chain.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initSwapChainDescription();

  ///--------------------------------------------------------------------------
  /// @fn   initBackBuffer();
  ///
  /// @brief   Get a pointer to the back buffer and then attach it to the swap chain.
  ///          We'll use the CreateRenderTargetView function to attach the back
  ///          buffer to our swap chain.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initBackBuffer();

  ///--------------------------------------------------------------------------
  /// @fn   initDepthBufferDescription();
  ///
  /// @brief   Creates a depth buffer so that our polygons can be rendered properly in 3D space.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initDepthBufferDescription();

  ///--------------------------------------------------------------------------
  /// @fn   initDepthStencilDescription();
  ///
  /// @brief  Attach a stencil buffer to our depth buffer.
  ///         The stencil buffer can be used to achieve effects such as motion blur,
  ///         volumetric shadows, and other things.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initDepthStencilDescription();

  ///--------------------------------------------------------------------------
  /// @fn   initStencilView();
  ///
  /// @brief  Creates the description of the view of the depth stencil buffer.
  ///         We do this so that Direct3D knows to use the depth buffer as a depth
  ///         stencil texture.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initStencilView();

  ///--------------------------------------------------------------------------
  /// @fn   initRaster();
  ///
  /// @brief  Creates a rasterizer state. This will give us control over how
  ///         polygons are rendered. We can do things like make our scenes render
  ///         in wireframe mode or have DirectX draw both the front and back
  ///         faces of polygons. By default DirectX already has a rasterizer state 
  ///         set up and working the exact same as the one below but you have no
  ///         control to change it unless you set up one yourself.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initRaster();

}; /* DirectXFramework */

}; /* SLX */

#endif
