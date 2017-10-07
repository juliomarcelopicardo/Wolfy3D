/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __SILVERLYNX_TIME_H__
#define __SILVERLYNX_TIME_H__ 1

#include "SilverLynx/globals.h"

namespace SLX {

struct Chronometer {
  Chronometer() : timer(0),
                  total_average(0),
                  iterations(0) {}

  void start();
  void restart();
  uint64 end();
  uint64 average();

  uint64 timer;
  uint64 total_average;
  uint32 iterations;
};

/// @brief returns time in milliseconds
uint64 Time();
uint64 TimeInMicroSeconds();
void Sleep(const uint64 miliseconds);
void SleepSeconds(const uint64 seconds);

}; /* SLX */

#endif
