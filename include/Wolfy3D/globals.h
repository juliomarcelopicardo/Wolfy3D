/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_GLOBALS_H__
#define __WOLFY3D_GLOBALS_H__ 1

#include <stdint.h>

namespace W3D {

  /*******************************************************************************
  ***                                 TYPES                                    ***
  *******************************************************************************/

  /// char
  typedef char char8;
  typedef char16_t char16;
  typedef char32_t char32;

  /// unsigned char
  typedef unsigned char uchar8;

  /// integer
  typedef int8_t int8;
  typedef int16_t int16;
  typedef int32_t int32;
  typedef int64_t int64;

  /// unsigned integer
  typedef uint8_t uint8;
  typedef uint16_t uint16;
  typedef uint32_t uint32;
  typedef uint64_t uint64;

  /// precision
  typedef float float32;
  typedef double float64;

  // MAIN DECLARATION
  int32 main();

  /*******************************************************************************
  ***                              CONST VALUES                                ***
  *******************************************************************************/

  const int32 ejemplo = 69;
  const float SCREEN_DEPTH = 1000.0f;
  const float SCREEN_NEAR = 0.1f;
  const bool VSYNC_ENABLED = false;
  const bool FULLSCREEN = false;

  /*******************************************************************************
  ***                                 ENUMS                                    ***
  *******************************************************************************/

  enum ComponentType {
    kComponentType_None,
    kComponentType_Transform,
    kComponentType_Render
  };


}; /* W3D */

#endif
