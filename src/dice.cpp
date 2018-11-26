/*! \file dice.cpp
 * \brief
 * \author Kevin Somervill < kevin @ somervill dot org >
 * \date 2018-11-25
 */

#include "dice.h"

dice::dice() : _dice(1,6) {
}

int dice::roll() {
  return _dice(_generator);
}

