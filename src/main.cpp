/*! \file main.cpp
 * \brief Simple game simulates swahili dice game.
 * \author Kevin Somervill < kevin @ somervill dot org >
 * \date 2018-11-24
 */



#include<iostream>
#include<string>
#include<vector>

#include "dice.h"
#include "turn.h"

/*
int score_roll(std::vector<int> &turn_score) {

  bool big_roll = true;
  int scoring_dice = 0;

  for (int bin=1; bin<7; bin++) {
    if (turn_score[bin] == 1) {
      if (bin == 1) {
        turn_score[0] += 100;
        scoring_dice += turn_score[bin];
      }
      else if (bin == 5) {
        turn_score[0] += 50;
        scoring_dice += turn_score[bin];
      }
      else if (bin == 6) {
        big_roll = false;
      }
    }
    else if (turn_score[bin] == 2) {
      big_roll = false;
      if (bin == 1) {
        turn_score[0] += bin * 2 * 100;
        scoring_dice += turn_score[bin];
      }
      else if (bin == 5) {
        turn_score[0] +=  2 * 50;
        scoring_dice += turn_score[bin];
      }
    }
    else if (turn_score[bin] == 3) {
      big_roll = false;
      if (bin == 1) {
        turn_score[0] += 1000;
      }
      else {
        turn_score[0] += bin * 100;
      }
      scoring_dice += turn_score[bin];
    }
    else if (turn_score[bin] == 4) {
      if (bin == 1) {
        turn_score[0] += 2000;
      }
      else {
        turn_score[0] += bin * 200;
      }
      scoring_dice += turn_score[bin];
    }
    else if (turn_score[bin] == 5) {
      if (bin == 1) {
        turn_score[0] += 5000;
      }
      else {
        turn_score[0] += bin * 400;
      }
      scoring_dice += turn_score[bin];
    }
  }

  std::cout << "Scoring dice: " << scoring_dice << std::endl;

  if (big_roll) {
    turn_score[0] = 1500;
    std::cout << "BIG ROLL!!!" << std::endl;
  }

  for (auto &v: turn_score) {
    std::cout << " " << v;
  }
  std::cout << std::endl;
  return c-scoring_dice;
  return turn_score[0];
}

int do_turn(dice *d, const int &c=5) {
  std::vector<int> turn_score(7, 0);
  int roll = 0;
  std::cout << "Roll:" << roll;
  for (int i = 0; i<c; i++) {
    roll = d->roll();
    std::cout << " " << roll;
    turn_score[roll]++;
  }

  std::cout << std::endl;

  return score_roll(turn_score);
}//end do_turn()
*/

bool continue_play() {
  char response;
  std::cout << "  Roll again [y/n]? ";
  std::cin >> response;
  return ('y' == ::tolower(response));
}

int main(int ac, char **av) {
  dice *d = new dice();
  turn *t;
  int score = 0;
  int total = 0;
  bool playing = true;

  do {
    t = new turn();
    score = t->go(d);
    std::cout << std::endl;
    std::cout << "Turn score: " << score << std::endl;
    total += score;
    std::cout << "Total: " << total << std::endl;
    std::cout << std::endl;

    if (score) {
      playing = continue_play();
    }
    else {
      playing = false;
    }
    delete t;
  } while (playing);

  std::cout << std::endl;

}//end main()


