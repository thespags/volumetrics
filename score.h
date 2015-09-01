/*
 * score.h
 *
 */

#ifndef SCORE_H
	#define SCORE_H

#include "yahtzee.h"

Mark* scoreTop(int die, Dice *dice[]);
Mark* score3K(Dice *dice[]);
Mark* score4K(Dice *dice[]);
Mark* scoreBoat(Dice *dice[]);
Mark* scoreSmall(Dice *dice[]);
Mark* scoreLarge(Dice *dice[]);
Mark* scoreYahtzee(Dice *dice[]);
Mark* scoreChance(Dice *dice[]);
void updateScore(int choice, Dice *dice[], Player **p);

#endif
