/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include "Wolfy3D.h"
#include "DirectXMath.h"
#include <vector>
#include "core/entity.h"

namespace W3D {
  
class Cam {

 public:

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  /// Default class constructor.
  Cam();

  /// Default class destructor.
  ~Cam();

  /*******************************************************************************
  ***                          Public setup methods                            ***
  *******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   setupPerspective(const double fovy, const double aspect, const double z_near, const double z_far);
  ///
  /// @brief Sets the projection matrix.
  ///
  ///	   f / aspect   0	   0	  0         f = cotan(fovy / 2)
  ///    0            f	   0	  0         V = (z_far + z_near) / (z_near - z_far)
  ///    0            0 	 V	  L         L = (2 * z_far*z_near) / (z_near - z_far)
  ///    0            0   -1    0
  ///
  /// @param fovy Specifies the field of view angle, in degrees, in the Y direction.
  /// @param aspect Specifies the aspect ratio that determines the field of view
  /// in the x direction.The aspect ratio is the ratio of x(width) to y(height).
  /// @param z_near Distance from the viewer to the near clipping plane(always positive).
  /// @param z_far Distance from the viewer to the far clipping plane(always positive).
  ///--------------------------------------------------------------------------
  void setupPerspective(const float32 field_of_view,
                        const float32 aspect_ratio,
                        const float32 z_near,
                        const float32 z_far);


  ///--------------------------------------------------------------------------
  /// @fn   setupOrthographic(const double left, const double right, const double bottom, const double top, const double z_near, const double z_far);
  ///
  /// @brief Generates a orthographic projection matrix for 3D rendering.
  ///
  ///	   A   0	 0	 D       A = 2/(right-left)   D = -((right+left)/(right-left))
  ///	   0   B	 0	 E       B = 2/(top-bottom)   E = -((top+bottom)/(top-bottom));
  ///	   0   0 	 C	 F       C = -2/(far-near)    F = -((far+near)/(far-near));
  ///    0   0	 0   1
  ///
  /// @param left, right Coordinates for the left and right vertical clipping planes
  /// @param top, bottom Coordinates for the bottom and top horizontal clipping planes.
  /// @param near, far Distances to the nearer and farther depth clipping planes.
  ///  These values are negative if the plane is to be behind the viewer.
  ///--------------------------------------------------------------------------
  void setupOrthographic(const float32 left,
                         const float32 right_vector,
                         const float32 bottom,
                         const float32 top,
                         const float32 z_near,
                         const float32 z_far);

  ///--------------------------------------------------------------------------
  /// @fn   setupView()
  ///
  /// @brief Sets the view matrix.
  ///
  ///	   Rx   Ry	 Rz  -Px        R = Right vector of the camera.
  ///	   Ux   Uy   Uz  -Py        U = Up vector of the camera.
  ///	   Dx   Dy   Dz  -Pz        D = Inverse direction (cam_position - target)
  ///    0    0    0    1         P = Camera position.
  ///
  /// @param fovy Specifies the field of view angle, in degrees, in the Y direction.
  /// @param aspect Specifies the aspect ratio that determines the field of view
  /// in the x direction. The aspect ratio is the ratio of x (width) to y (height).
  /// @param z_near Distance from the viewer to the near clipping plane (always positive).
  /// @param z_far Distance from the viewer to the far clipping plane (always positive).
  ///--------------------------------------------------------------------------
  void setupView();

  /*******************************************************************************
  ***                          Public methods                                  ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void render(Object* obj);
  ///
  /// @brief Renders an object into the window.
  /// @param obj object to be rendered.
  ///--------------------------------------------------------------------------
  void render(class Entity* obj);

  ///--------------------------------------------------------------------------
  /// @fn   void update(const float32& delta);
  ///
  /// @brief Update the camera data when movement is active
  /// @param delta delta_time.
  ///--------------------------------------------------------------------------
  void update(const float32& delta);

  ///--------------------------------------------------------------------------
  /// @fn   moveTo(const DirectX::XMFLOAT3& position,
  ///              const DirectX::XMFLOAT3& target,
  ///              const float32 lerping_duration = 1.0f);
  ///
  /// @brief Moves to a new position applying a linear interpolation.
  /// @param position Destiny location.
  /// @param target Destiny target.
  /// @param lerping_duration duration in seconds of the interpolation.
  ///--------------------------------------------------------------------------
  void moveTo(const DirectX::XMFLOAT3& position,
              const DirectX::XMFLOAT3& target,
              const float32 lerping_duration = 1.0f);

  /*******************************************************************************
  ***                            Setters & Getters                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void set_transform(Entity entity);
  ///
  /// @brief  Transform setter using a entity to get its position, target and up.
  ///--------------------------------------------------------------------------
  void set_transform(Entity entity);

  ///--------------------------------------------------------------------------
  /// @fn   set_position(const float32 x, const float32 y, const float32 z, const bool cancel_lerping);
  ///
  /// @brief Sets the position of the camera.
  ///
  /// @param X position in the world X axis.
  /// @param Y position in the world Y axis.
  /// @param Z position in the world Z axis.
  ///--------------------------------------------------------------------------
  void set_position(const float32 x, const float32 y, const float32 z, const bool cancel_lerping = true);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMVECTOR position, const bool cancel_lerping);
  ///
  /// @brief  Transform position setter.
  /// @param  Position to set.
  /// @param  cancel_lerping will cancel the interpolation if its active.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMVECTOR position, const bool cancel_lerping = true);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMFLOAT3 position, const bool cancel_lerping);
  ///
  /// @brief  Transform position setter.
  /// @param  Position to set.
  /// @param  cancel_lerping will cancel the interpolation if its active.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMFLOAT3 position, const bool cancel_lerping = true);

  ///--------------------------------------------------------------------------
  /// @fn   set_target(const float32 x, const float32 y, const float32 z, const bool cancel_lerping)
  ///
  /// @brief Sets the target of the camera.
  ///
  /// @param X target position in the world X axis.
  /// @param Y target position in the world Y axis.
  /// @param Z target position in the world Z axis.
  /// @param  cancel_lerping will cancel the interpolation if its active.
  ///--------------------------------------------------------------------------
  void set_target(const float32 x, const float32 y, const float32 z, const bool cancel_lerping = true);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMVECTOR target, const bool cancel_lerping);
  ///
  /// @brief  Transform target setter.
  /// @param  target Target to set.
  /// @param  cancel_lerping will cancel the interpolation if its active.
  ///--------------------------------------------------------------------------
  void set_target(const DirectX::XMVECTOR target, const bool cancel_lerping = true);

  ///--------------------------------------------------------------------------
  /// @fn   void set_target(const DirectX::XMFLOAT3 target, const bool cancel_lerping);
  ///
  /// @brief  Transform target setter.  
  /// @param  target Target to set.
  /// @param  cancel_lerping will cancel the interpolation if its active.
  ///--------------------------------------------------------------------------
  void set_target(const DirectX::XMFLOAT3 target, const bool cancel_lerping = true);

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR position_vector()
  ///
  /// @brief Position getter.
  ///
  /// @return a XMVECTOR with the camera position in the world
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR position_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 position_float3()
  ///
  /// @brief Position getter.
  ///
  /// @return a XMFLOAT3 with the camera position in the world
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 position_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR target_vector()
  ///
  /// @brief Target getter.
  ///
  /// @return a XMVECTOR with the position of the camera target in the world
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR target_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 target_float3()
  ///
  /// @brief Target getter.
  ///
  /// @return a XMFLOAT3 with the position of the camera target in the world
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 target_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR up_vector()
  ///
  /// @brief Vector Up getter.
  ///
  /// @return a XMVECTOR with the global up vector of the camera
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR up_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 up_float3()
  ///
  /// @brief Vector Up getter.
  ///
  /// @return a XMFLOAT3 with the global up vector of the camera
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 up_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR forward_vector()
  ///
  /// @brief Vector Forward getter.
  ///
  /// @return a XMVECTOR with the global forward vector of the camera
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR forward_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 forward_float3()
  ///
  /// @brief Vector Forward getter.
  ///
  /// @return a XMFLOAT3 with the global forward float3 of the camera
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 forward_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR right_vector()
  ///
  /// @brief Vector Right getter.
  ///
  /// @return a XMVECTOR with the global right vector of the camera
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR right_vector();
  
  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 right_float3()
  ///
  /// @brief Vector Right getter.
  ///
  /// @return a XMFLOAT3 with the global right float3 of the camera
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 right_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMMATRIX projection_matrix()
  ///
  /// @brief Projection Matrix getter.
  ///
  /// @return Projection Matrix
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX projection_matrix();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT4X4 projection_float4x4()
  ///
  /// @brief Projection Matrix getter.
  ///
  /// @return Projection Matrix
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT4X4 projection_float4x4();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMMATRIX view_matrix()
  ///
  /// @brief View Matrix getter.
  ///
  /// @return View Matrix
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX view_matrix();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT4X4 view_float4x4()
  ///
  /// @brief View Matrix getter.
  ///
  /// @return View Matrix
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT4X4 view_float4x4();

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// Aspect Ratio (window width / window height)
  float32 aspect_;
  /// Field of View.
  float32 fovy_;
  /// ZNear
  float32 z_near_;
  /// ZFar
  float32 z_far_;
  
  /// Camera movement speed.
  float32 movement_speed_;
  /// Camera rotation speed.
  float32 rotation_speed_;
  /// Sets if the navigation is enabled (translation and rotation).
  bool is_navigation_enabled_;

  /*******************************************************************************
  ***                           Private                                        ***
  *******************************************************************************/

 private:

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// Position
  DirectX::XMFLOAT3 position_;
  /// Target
  DirectX::XMFLOAT3 target_;
  /// Projection Matrix
  DirectX::XMFLOAT4X4 projection_matrix_;
  /// View Matrix
  DirectX::XMFLOAT4X4 view_matrix_;
  /// Mouse position in the previous frame.
  DirectX::XMFLOAT2 last_mouse_position_;
  
  /* Lerp */

  /// Origin position of the lerp.
  DirectX::XMFLOAT3 origin_position_;
  /// Origin target of the lerp.
  DirectX::XMFLOAT3 origin_target_;
  /// Destiny position of the lerp.
  DirectX::XMFLOAT3 destiny_position_;
  /// Destiny target of the lerp.
  DirectX::XMFLOAT3 destiny_target_;
  /// Sets if the camera is blending or lerping between transforms.
  bool is_lerping_;
  /// Timer for the lerping in seconds.
  float32 timer_;
  /// Timer limit in seconds.
  float32 timer_limit_;

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

  Cam(const Cam& copy);
  Cam& operator=(const Cam& copy);

  ///--------------------------------------------------------------------------
  /// @fn   void translate(const float32& delta);
  ///
  /// @brief Update the camera position when movement is active.
  /// @param delta delta_time.
  ///--------------------------------------------------------------------------
  bool translate(const float32& delta);

  ///--------------------------------------------------------------------------
  /// @fn   void rotate(const float32& delta);
  ///
  /// @brief Update the camera rotation when movement is active.
  /// @param delta delta_time.
  ///--------------------------------------------------------------------------
  bool rotate(const float32& delta);

  ///--------------------------------------------------------------------------
  /// @fn   void updateLerping(const float32& delta);
  ///
  /// @brief Updates de lerping values and the transformation if needed.
  /// @param delta delta seconds.
  ///--------------------------------------------------------------------------
  void updateLerping(const float32& delta);

}; /* Cam */

}; /* W3D */

#endif
