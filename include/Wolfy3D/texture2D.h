/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_TEXTURE2D_H__
#define __WOLFY3D_TEXTURE2D_H__ 1

#include "Wolfy3D/globals.h"
#include <DirectXMath.h>

namespace W3D {

// Texture2D class.
class Texture2D {

 public:


/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Texture2D();
  /// Default class destructor
  ~Texture2D();
  /// copy constructor.
  Texture2D(const Texture2D& copy);
  /// operator of assignment.
  Texture2D& operator=(const Texture2D& copy);

/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   ID id();
  ///
  /// @brief  Texture2D id getter.
  /// @returns  Texture2D id.
  ///--------------------------------------------------------------------------
  ID id();

/*******************************************************************************
***                              Initializers                                ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void initFromFile(const char* texture_path);
  ///
  /// @brief  Loads a texture froma a file.
  ///--------------------------------------------------------------------------
  void initFromFile(const char* texture_path);


/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/

private:


  /// Core Geo class id.
  ID id_;


}; /* Texture2D */

}; /* W3D */

#endif
