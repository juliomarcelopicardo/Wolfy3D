/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserveds.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __SILVERLYNX_H__
#define __SILVERLYNX_H__ 1

#include <stdint.h>

namespace SLX {

/*******************************************************************************
***                                 TYPES                                    ***
*******************************************************************************/

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

/*******************************************************************************
********************************************************************************
***                                                                          ***
***                    GLOBAL DECLARATIONS AND UTILITIES                     ***
***                                                                          ***
********************************************************************************
*******************************************************************************/

// MAIN DECLARATION
int32 main();

/*******************************************************************************
***                              CONST VALUES                                ***
*******************************************************************************/

const int32 ejemplo = 69;

/*******************************************************************************
***                                 ENUMS                                    ***
*******************************************************************************/

enum EjemploEnum {
  kEjemploEnum_A = 0,
  kEjemploEnum_B = 1
};

/*******************************************************************************
***                          STRUCTS DECLARATIONS                            ***
*******************************************************************************/

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


/*******************************************************************************
***                                 UTILS                                    ***
*******************************************************************************/

/// @brief returns time in milliseconds
uint64 Time();
uint64 TimeInMicroSeconds();
void Sleep(const uint64 miliseconds);
void SleepSeconds(const uint64 seconds);

/*******************************************************************************
***                                 INPUT                                    ***
*******************************************************************************/

double MousePosX();
double MousePosY();

/*******************************************************************************
***                   EJEMPLO CAPA DE USER CON LA WINDOW                     ***
*******************************************************************************/

void WindowInit(const int32 width = 800,
                const int32 height = 600,
                const bool mouse_cursor_visible = true,
                const char* display_name = "Silverlynx Window");
void WindowInitMaximized(const bool full_screen_mode = false,
                         const bool mouse_cursor_visible = true,
                         const char* title = "Silverlynx Window");
void WindowInitByLua(const char* lua_path);
bool WindowIsOpened();
void WindowFrame();
void WindowClear(float red = 0.0f, float green = 0.3f, float blue = 0.0f);
void WindowDestroy();
void WindowSetMouseVisibility(const bool visible);
int32 WindowHeight();
int32 WindowWidth();

}; /* SLX */

#endif
