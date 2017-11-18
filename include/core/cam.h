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
  void setupPerspective(const float field_of_view,
                        const float aspect_ratio,
                        const float z_near,
                        const float z_far);


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
  void setupOrthographic(const float left,
                         const float right_vector,
                         const float bottom,
                         const float top,
                         const float z_near,
                         const float z_far);

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
  /// @fn   void update();
  ///
  /// @brief Update the camera data when movement is active
  ///--------------------------------------------------------------------------
  void update();



  /*******************************************************************************
  ***                            Setters & Getters                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   set_position(const float x, const float y, const float z)
  ///
  /// @brief Sets the position of the camera.
  ///
  /// @param X position in the world X axis.
  /// @param Y position in the world Y axis.
  /// @param Z position in the world Z axis.
  ///--------------------------------------------------------------------------
  void set_position(const float x, const float y, const float z);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMVECTOR position);
  ///
  /// @brief  Transform position setter.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMVECTOR position);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMFLOAT3 position);
  ///
  /// @brief  Transform position setter.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMFLOAT3 position);

  ///--------------------------------------------------------------------------
  /// @fn   set_target(const float x, const float y, const float z)
  ///
  /// @brief Sets the target of the camera.
  ///
  /// @param X target position in the world X axis.
  /// @param Y target position in the world Y axis.
  /// @param Z target position in the world Z axis.
  ///--------------------------------------------------------------------------
  void set_target(const float x, const float y, const float z);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMVECTOR target);
  ///
  /// @brief  Transform target setter.
  ///--------------------------------------------------------------------------
  void set_target(const DirectX::XMVECTOR target_vector);

  ///--------------------------------------------------------------------------
  /// @fn   void set_target(const DirectX::XMFLOAT3 target);
  ///
  /// @brief  Transform target setter.
  ///--------------------------------------------------------------------------
  void set_target(const DirectX::XMFLOAT3 target_vector);

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
  /// @fn   DirectX::XMMATRIX projectionMatrix()
  ///
  /// @brief Projection Matrix getter.
  ///
  /// @return Projection Matrix
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX projectionMatrix();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMMATRIX viewMatrix()
  ///
  /// @brief View Matrix getter.
  ///
  /// @return View Matrix
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX viewMatrix();

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// Aspect Ratio (window width / window height)
  float aspect_;
  /// Field of View.
  float fovy_;
  /// ZNear
  float z_near_;
  /// ZFar
  float z_far_;
  
  /// Camera movement speed.
  float movement_speed_;
  /// Camera rotation speed.
  float rotation_speed_;
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


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

  Cam(const Cam& copy);
  Cam& operator=(const Cam& copy);

  ///--------------------------------------------------------------------------
  /// @fn   void translate();
  ///
  /// @brief Update the camera position when movement is active
  ///--------------------------------------------------------------------------
  bool translate();

  ///--------------------------------------------------------------------------
  /// @fn   void rotate();
  ///
  /// @brief Update the camera rotation when movement is active
  ///--------------------------------------------------------------------------
  bool rotate();

}; /* Cam */

}; /* W3D */

#endif
