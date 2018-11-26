#ifndef _DICE_H
#define _DICE_H

#include<random>
//using int_dist = std::uniform_int_distribution<int>;

class dice {
  private:
    std::default_random_engine _generator;
    std::uniform_int_distribution<int> _dice;

  public:
    dice();

    int roll();
};

#endif //!defined(_DICE_H)
