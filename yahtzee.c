/*
 * yahtzee.c
 *
 * 02/10/07 - added createPlayers
 *			- 
 * - to add
 * - players turn
 * - score and what not
 */
#include <time.h>
#include <stdlib.h>
#include "yahtzee.h"

#define NUMDICE 5
#define MAXVALUE 6

/* 
 * checks if all the dice are held 
 * 1 - all dices are held
 * 0 - otherwise
 */
int checkDice(Dice *dice[])
{
	int i;

	for(i = 0; i < NUMDICE; i++)
		if(!dice[i]->hold)
			return 0;

	return 1;
}

void unholdDice(Dice **dice[])
{
	int i; 

	for(i = 0; i < NUMDICE; i++)
		(*dice)[i]->hold = 0;
}

void rollDice(Dice **dice[])
{
	int i;
	srand(time(NULL));

	// rolls dice if hold set to 0
	for(i = 0; i < NUMDICE; i++)
		if((*dice)[i]->hold == 0)
			(*dice)[i]->value = rand() % MAXVALUE + 1;
}

Dice **createDice()
{
	int i;
	Dice **dice = (Dice **)malloc(NUMDICE * sizeof(Dice *));

	for(i = 0; i < NUMDICE; i++)
	{
		dice[i] = (Dice *)malloc(sizeof(Dice));
		dice[i]->value = i % 7 + 1;
		dice[i]->hold = 0;
	}
		
	return dice;
}

/* creates a player, mallocs everything, assigns default value */
Player **createPlayers(int num, char **names, int *metric)
{
	int i;
	Player *p, **players = (Player **)malloc(num * sizeof(Player *));

	for(i = 0; i < num; i++)
	{
		p 			= (Player *)malloc(sizeof(Player));
		p->symbol 	= names[i];
		p->metric 	= metric[i];
		p->rolls 	= 0;
		p->value 	= 0;

		p->score			= (Score *)malloc(sizeof(Score));
		p->score->top 		= 0;
		p->score->bonus 	= -1;
		p->score->bottom 	= 0;
		p->score->total 	= 0;
		p->score->vols		= 0;
		p->score->one 		= NULL;
		p->score->two 		= NULL;
		p->score->three 	= NULL;
		p->score->four 		= NULL;
		p->score->five 		= NULL;
		p->score->six 		= NULL;
		p->score->threeK 	= NULL;
		p->score->fourK		= NULL;
		p->score->boat 		= NULL;
		p->score->small 	= NULL;
		p->score->large 	= NULL;
		p->score->yahtzee 	= NULL;
		p->score->chance 	= NULL;
		players[i] 			= p;
	}

	return players;
}
