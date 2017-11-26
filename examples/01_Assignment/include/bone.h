/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __BONE_H__
#define __BONE_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "core/texture.h"
#include "core/geo.h"
#include "core/core.h"
#include "core/entity.h"
#include "step.h"
#include "tinyxml2/tinyxml2.h"

namespace W3D {
  
class Bone {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Bone();
  /// Default class destructor
	~Bone();
  /// copy constructor.
  Bone(const Bone& copy);
  /// operator of assignment.
  Bone& operator=(const Bone& copy);

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void setup(tinyxml2::XMLDocument& doc);
  ///
  /// @brief Setup all the info (rotation and traslation) from a xml file.
  /// @param doc XML file to parse.
  ///--------------------------------------------------------------------------
  void setup(tinyxml2::XMLDocument& doc);

  ///--------------------------------------------------------------------------
  /// @fn   void start(const bool apply_blending,
  ///                  const DirectX::XMFLOAT4 rot_origin = { 0.0f, 0.0f, 0.0f, 0.0f }, 
  ///                  const DirectX::XMFLOAT4 traslation_origin = { 0.0f, 0.0f, 0.0f, 0.0f },
  ///                  const float32 blending_duration = 0.0f);
  ///
  /// @brief Starts the animation from the first step applying a smooth blending.
  /// @param apply_blending If true will apply a interpolation to the next step.
  /// @param rot_origin Origin quaternion value. Current rotation.
  /// @param traslation_origin Origin position value. Current position.
  /// @param blending_duration Time to interpole to the next animation.
  ///--------------------------------------------------------------------------
  void start(const bool apply_blending = false,
             const DirectX::XMFLOAT4 rot_origin = { 0.0f, 0.0f, 0.0f, 0.0f },
             const DirectX::XMFLOAT4 traslation_value = { 0.0f, 0.0f, 0.0f, 0.0f },
             const float32 blending_duration = 0.0f);


/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/



/*******************************************************************************
***                           Public  Attributes                             ***
*******************************************************************************/

  /// Traslation steps info.
  StepsInfo translation;
  /// Rotations steps info.
  StepsInfo rotation;
  /// Name of the bone to look for in the files.
  std::string name;



private:

  enum Axis {
    kAxis_X = 0,
    kAxis_Y = 1,
    kAxis_Z = 2,
  };

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/

  /* Parsing xml */

  /// Setup the axis rotation info from a xml file.
  void setupAxisRotation(Axis axis, tinyxml2::XMLNode* root);
  /// Setup the traslation info from a xml file.
  void setupTranslation(tinyxml2::XMLNode* root);
  /// As the xml file contain euler degrees, we will convert them into quaternion.
  void convertEulerAnglesIntoQuaternion();

/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/





}; /* Bone */

}; /* W3D */

#endif