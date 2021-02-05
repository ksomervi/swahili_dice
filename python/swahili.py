#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 26 11:09:20 2018

@author: ksomervi
"""

import cmd
#from datetime import datetime
#import random
import numpy as np

# Constants
MAX_DICE = 5
START_SCORE = 500
BIG_ROLL = [x+1 for x in range(0, MAX_DICE)]
ALL_ONES = [1]*MAX_DICE

class Player():
    '''Player object for game play'''
    def __init__(self):
        self.turn_score = 0
        self.total_score = 0
        self.default_min_score = 100
        self.turn_count = 0

def score_roll(roll):
    '''Calculate score from roll'''
    score = 0
    scoring_dice = 0
    roll.sort()
    # Handle the special cases
    if roll == BIG_ROLL: #[1, 2, 3, 4, 5]:
        # Big roll
        return (1500, 0)

    if roll == ALL_ONES: # [1]*5:
        # Game over
        return (5000, 0)

    for i in range(1, 7):
        cnt = roll.count(i)
        if cnt > 2:
            score += i * 100 * (2**(cnt-3))
            scoring_dice += cnt
        elif i == 1:
            score += cnt * 100
            scoring_dice += cnt
        elif i == 5:
            score += cnt * 50
            scoring_dice += cnt
    return (score, (len(roll)-scoring_dice))


class SwahiliGame(cmd.Cmd):
    '''Console based dice game.'''
    total_score = 0
    turn_score = 0

    def __init__(self):
        super().__init__()
        self.intro = 'Swahili dice game simulator'
        self.prompt = 'swahili> '
        self.rng = np.random.RandomState(13)
        self.turn_count = 0
        self.available_dice = 5
        self.default_min_score = 100
        self.verbose = True
        self.in_turn = False

    def roll_dice(self, live_dice):
        '''Roll simulated dice for turn'''
        if self.verbose:
            print('rolling {:d} dice'.format(live_dice))
        #rv = []
        #for d in range(live_dice):
            #rv.append(random.Random().randint(1, 6))
        #return rv
        return list(self.rng.randint(1, 6, live_dice))

    def do_q(self, args):
        '''Exit the game simulator'''
        return self.do_quit(args)


    def do_quit(self, *_):
        '''Exit the game simulator'''
        return True


    def do_new(self, *_):
        '''Clear the score and start a new game'''
        self.total_score = 0
        self.turn_score = 0
        self.available_dice = 5
        self.default_min_score = 100
        self.turn_count = 0
        self.in_turn = False

    def do_roll(self, min_score='100'):
        '''Take turn rolling the dice to score'''
        on_scoreboard = self.total_score >= START_SCORE

        if self.total_score < START_SCORE:
            target = START_SCORE
        elif not min_score:
            target = self.default_min_score
        else:
            try:
                target = int(min_score)
                if target < 100:
                    target = 100
            except Exception:
                print('  Invalid target value: "{:s}"'.format(min_score))
                print('  Try a multiple of 100')
                return
        self.turn_count += 1
        in_turn = True
        turn_score = 0
        live = MAX_DICE
        while in_turn:
            roll_score = 0
            roll = self.roll_dice(live)
            msg = 'Rolled: ' + str(roll)
            (roll_score, live) = score_roll(roll)
            msg += ' ' + str(roll_score) + ' pts'
            if self.verbose:
                print(msg, '[Dice left: {:d}]'.format(live))
            if roll_score > 0:
                turn_score += roll_score
                if (turn_score % 100) == 0 and (turn_score >= target):
                    in_turn = False
                elif live == 0:
                    live = MAX_DICE
            else:
                if self.verbose:
                    print('Garbage roll - turn over')
                turn_score = 0
                in_turn = False
            if in_turn:
                if self.verbose:
                    print('Turn score:', turn_score)

        if on_scoreboard:
            self.total_score += turn_score
        elif turn_score >= START_SCORE:
            self.total_score += turn_score
            if self.verbose:
                print('  On scoreboard!')
        if self.verbose:
            print('Score [turn/total]: {:d}/{:d}'.format(turn_score, self.total_score))


    def do_target(self, min_score):
        '''Set the target threshold for accepting a turn score'''
        if not min_score:
            print('Default target:', self.default_min_score)
        else:
            self.default_min_score = int(min_score)
            print('New default target:', self.default_min_score)

    def do_pass(self, *_):
        '''Pass the dice to the next player - not implemented yet'''
        print('Passing dice...')

if __name__ == '__main__':
    print('do you want to play a game...')
    game = SwahiliGame()
    game.cmdloop()
