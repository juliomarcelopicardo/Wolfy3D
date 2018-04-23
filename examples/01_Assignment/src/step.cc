/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "step.h"


namespace W3D {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

StepsInfo::StepsInfo() {
  mode = kMode_Rotation;
  step_timers.clear();
  step_values.clear();
  num_steps = 0;
  origin = { 0.0f, 0.0f, 0.0f, 1.0f };
  destiny = { 0.0f, 0.0f, 0.0f, 1.0f };
  alpha = 0.0f;
  timer = 0.0f;
  timer_limit = 0.0f;
  step_destiny = 0;
}

StepsInfo::~StepsInfo() {}

StepsInfo::StepsInfo(const StepsInfo& copy) {
  mode = copy.mode;
  step_timers = copy.step_timers;
  step_values = copy.step_values;
  num_steps = copy.num_steps;
  origin = copy.origin;
  destiny = copy.destiny;
  alpha = copy.alpha;
  timer = copy.timer;
  timer_limit = copy.timer_limit;
  step_destiny = copy.step_destiny;
}

StepsInfo& StepsInfo::operator=(const StepsInfo& copy) {
  mode = copy.mode;
  step_timers = copy.step_timers;
  step_values = copy.step_values;
  num_steps = copy.num_steps;
  origin = copy.origin;
  destiny = copy.destiny;
  alpha = copy.alpha;
  timer = copy.timer;
  timer_limit = copy.timer_limit;
  step_destiny = copy.step_destiny;
  return *this;
}


/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/


DirectX::XMVECTOR StepsInfo::update(const float32& delta_time) {
  timer += delta_time;

  // Sets the alpha to apply the interpolations.
  alpha = timer / timer_limit; // values between 0 and 1 to interpole

  // As timer > timer_limit
  if (alpha > 1.0f) {
    startNextStep();
  }

  // Returns the transformation.
  switch (mode) {
    case StepsInfo::kMode_Rotation: { return Math::QuaternionLerpVector(origin, destiny, alpha); } break;
    case StepsInfo::kMode_Translation: { return Math::LerpVector(origin, destiny, alpha); } break;
  }

  MessageBox(NULL, "Error StepsInfo Mode not set", "ERROR", MB_OK);
  return DirectX::XMVECTOR();
}


void StepsInfo::start(const bool apply_blending,
                      const DirectX::XMFLOAT4 origin_value, 
                      const float32 blending_duration) {
  step_destiny = 0;
  alpha = 0.0f;
  timer = 0.0f;
  destiny = step_values[step_destiny];
  if (apply_blending) {
    timer_limit = blending_duration;
    origin = origin_value;
  }
  else {
    timer_limit = step_timers[step_destiny];
    origin = step_values[0];
  }
}



/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void StepsInfo::startNextStep() {
  // Not to waste any millisecond, accumulate the resting time to the next step.
  timer = timer - timer_limit;
  step_destiny += 1;
  if (step_destiny == num_steps) {
    step_destiny = 0;
  }
  timer_limit = step_timers[step_destiny];
  origin = destiny;
  destiny = step_values[step_destiny];
  alpha = 0.0f;
}





}; /* W3D */