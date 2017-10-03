/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/time.h"
#include "core/core.h"
#include <chrono>
#include <thread>

namespace SLX {


uint64 Time() {
  return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - Core::instance().start_time_);
}

uint64 TimeInMicroSeconds() {
  return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - Core::instance().start_time_);
}

void Sleep(const uint64 miliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

void SleepSeconds(const uint64 seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


void Chronometer::start() {
  timer = Time();
}

void Chronometer::restart() {
  timer = 0;
  total_average = 0;
  iterations = 0;
}

uint64 Chronometer::end() {
  uint64 result = Time() - timer;
  total_average += result;
  iterations += 1;
  return result;
}

uint64 Chronometer::average() {
  if (!iterations) { return 0; }
  else {
    return total_average / iterations;
  }
}


}; /* SLX */