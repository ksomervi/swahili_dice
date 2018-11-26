#ifndef _SWAHILI_TURN_H
#define _SWAHILI_TURN_H

#include <vector>

#include "dice.h"

const int MAX_DICE = 5;

class turn {

  private:
    int _da; // dice available to roll
    std::vector<int> _roll;
    int _score;
    bool _big_roll;

    int _score_roll();
    //int _roll(dice *d);

  public:
    turn();

    void clear();
    int go(dice *);

};//end turn

#endif //!defined(_SWAHILI_TURN_H)
