/*! \file turn.cpp
 * \brief
 * \author Kevin Somervill < kevin @ somervill dot org >
 * \date 2018-11-25
 */

#include<iostream>
#include<string>
#include<vector>

#include "turn.h"

turn::turn() : _roll(7,0) {
  _score = 0;
  _big_roll = false;
  _da = MAX_DICE;
}


void turn::clear() {
  _score = 0;
  _big_roll = false;
  _roll.assign(7, 0);
  _da = MAX_DICE;
}

int turn::_score_roll() {
  _big_roll = (_da == MAX_DICE);
  int score = 0;
  int scoring_dice = 0;

  for (int bin=1; bin<7; bin++) {
    if (_roll[bin] == 1) {
      if (bin == 1) {
        score += 100;
        scoring_dice += _roll[bin];
      }
      else if (bin == 5) {
        score += 50;
        scoring_dice += _roll[bin];
      }
      else if (bin == 6) {
        _big_roll = false;
      }
    }
    else if (_roll[bin] == 2) {
      _big_roll = false;
      if (bin == 1) {
        score += bin * 2 * 100;
        scoring_dice += _roll[bin];
      }
      else if (bin == 5) {
        score +=  2 * 50;
        scoring_dice += _roll[bin];
      }
    }
    else if (_roll[bin] == 3) {
      _big_roll = false;
      if (bin == 1) {
        score += 1000;
      }
      else {
        score += bin * 100;
      }
      scoring_dice += _roll[bin];
    }
    else if (_roll[bin] == 4) {
      if (bin == 1) {
        score += 2000;
      }
      else {
        score += bin * 200;
      }
      scoring_dice += _roll[bin];
    }
    else if (_roll[bin] == 5) {
      if (bin == 1) {
        score += 5000;
      }
      else {
        score += bin * 400;
      }
      scoring_dice += _roll[bin];
    }
  }

  std::cout << "Scoring dice: " << scoring_dice << std::endl;
  _da -= scoring_dice;

  if (_big_roll) {
    score = 1500;
    std::cout << "BIG ROLL!!!" << std::endl;
  }

  std::cout << "   ";
  for (auto &v: _roll) {
    std::cout << " " << v;
  }
  return score;
}

int turn::go(dice *d) {
  int roll = 0;
  int turn_score = 0;
  int roll_score = 0;
  bool rolling = true;

  do {
    std::cout << "Rolling " << _da << " dice: ";
    _roll.assign(7, 0);
    for (int i = 0; i<_da; i++) {
      roll = d->roll();
      std::cout << " " << roll;
      _roll[roll]++;
    }
    std::cout << std::endl;

    roll_score = _score_roll();
    std::cout << " [Roll score: " << roll_score << "]" << std::endl;
    std::cout << "  Dice left: " << _da << std::endl;
    if (roll_score == 0) {
      rolling = false;
    }
    else {
      turn_score += roll_score;
      rolling = ((turn_score %100) != 0) and (_da > 0);
    }
  } while (rolling);

  if (roll_score == 0) {
    return roll_score;
  }

  if ((turn_score %100) != 0) {
    std::cout << "Dice available to roll: " << _da << std::endl;
  }

  _score = turn_score;

  return turn_score;
}//end go()

