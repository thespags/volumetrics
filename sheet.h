/*
 * sheet.h
 *
 */

#ifndef sheet_h
	#define sheet_h

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include "score.h"
#include "yahtzee.h"

void printMark(int y, int x, Mark *mark);
void getScore(int num, int i, Dice **dice, Player ***players);
void sheet(int num, Player **players);

#endif
