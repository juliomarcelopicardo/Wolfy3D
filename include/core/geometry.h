/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__ 1

#include "silverlynx.h"
#include "D3DX11.h"
#include "D3dx9math.h"
#include <vector>

namespace SLX {

class CoreGeometry {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreGeometry();

  /// Default class destructor.
  ~CoreGeometry();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   bool init();
  ///
  /// @brief  Initializes the Geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool init();

  ///--------------------------------------------------------------------------
  /// @fn   render();
  ///
  /// @brief  renders the Geometry.
  ///--------------------------------------------------------------------------
  void render();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  /// Verices info.
  std::vector<D3DXVECTOR3> vertex_position_;
  /// Vertices buffer.
  ID3D11Buffer* vertex_buffer_;

  /// Vertices indices.
  std::vector<uint32> vertex_index_;
  /// Indices buffer.
  ID3D11Buffer* vertex_index_buffer_;

  /*
    TODO: Sacar todo esto a una clase base	
  */
  D3DXMATRIX model;
	D3DXMATRIX view;
	D3DXMATRIX projection;
/*******************************************************************************
***                           Private                                        ***
*******************************************************************************/

 private:

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/



}; /* CoreGeometry */

}; /* SLX */

#endif
