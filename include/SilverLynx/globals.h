/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __SILVERLYNX_GLOBALS_H__
#define __SILVERLYNX_GLOBALS_H__ 1

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

}; /* SLX */

#endif
