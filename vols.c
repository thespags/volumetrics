/* 
	I am bored so I am making a yahtzee game.
	eventually move functions to another file

	10/09/07-score prints and calculates a single player score
			-menu takes in the number of players
			-rollDice, does one players turn but no scoreDice

			* need to do
			-multiplayers
			-scoreDice
			-ascii graphics
			-edit score ?
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void menu();
void rollDice(int roll[]);
int scoreDice();
int score(char name[], int player[], int print);

#define BARS for(i = 0; i < 80; i++) printf("=");
#define STARS for(i = 0; i < 80; i++) printf("*");
char* terms[] = {"3K","4K","BT","SM","LG","YZ","CH"};

int main()
{
	int i;
	menu();
	int player[13] = {6, 12, 18, 24, 30, 36, 30, 30, 25, 30, 40, 50, 30};
//	score("Spags", player, 1);
	int roll[] = {0, 0, 0, 0, 0};
	rollDice(roll);
		for(i = 0; i < 5; i++)
			printf("%d ", roll[i]);
		printf("\n");
//	system("clear");

	return 0;
}

void menu()
{
	int numPlayers = -1;
	int i = 0;

	STARS;
	printf("                           Welcome to ASCII Vols!\n");
	STARS;

	while (numPlayers < 0)
	{
		printf("\n\nPlease input the number of players: ");
		scanf("%d", &numPlayers);

		if (numPlayers > 5)
			printf("You should split the game");
	}

	return;
}

void turn(int player[])
{

}

void rollDice(int roll[])
{
	int i, c, numRolls;
	int keep[] = {0, 0, 0, 0, 0};

	for(numRolls = 0; numRolls < 3; numRolls++)
	{
		// rolls dice if keep set to 0
		for(i = 0; i < 6; i++)
			if(keep[i] == 0)
				roll[i] = random() % 6 + 1;

		// prints current dice roll
		for(i = 0; i < 5; i++)
			printf("%d ", roll[i]);
		printf("\n");

		// gets a 5 1's or 0's
		if (numRolls != 2)
			for(i = 0; i < 5;)
			{	
				c = getchar();

				// only increments with proper input
				if(c == '0' || c == '1')
				{
					keep[i] = c - 48;
					i++;
				}
			} 
	}

	return;
}


/* calculates a player score
 * if print is set to true, then prints score
 * *** vols not implemented ***
 */
int score(char name[], int player[], int print)
{	
	int i = 0;
	int top = 0;
	int bonus = 0;
	int bottom = 0;

	printf("\n%s\n", name);
	BARS;

	/* calculates the bottom */
	for(i = 0; i < 6; i++)
	{
		if(player[i] != -1)
		{
			top += player[i];
			if(print) printf("%d   = %d\n", i + 1, player[i]);
		}
		else
			printf("%d   =    \n", i + 1);
	}
	
	if(print)
	{
		BARS;
		printf("\nT   = %d\n", top);
	}

	/* is bonus met */
	if (top >= 63)
		bonus = 35;

	if(print)
	{
		printf("B   = %d\n", bonus);
		BARS;
	}

	/* calculates the bottom */
	for(i = 6; i < 13; i++)
	{
		if(player[i] != -1)
		{
			bottom += player[i];
			if(print) printf("%s  = %d\n", terms[i-6], player[i]);
		}
		else
			printf("%s  =    \n", terms[i-6]);
	}
		
	/* prints T, TT, TTT */
	if(print)
	{
		BARS;
		printf("\nT   = %d", top);
		printf("\nTT  = %d\n", bottom);
		BARS;
		printf("\nTTT = %d\n", top + bonus + bottom);
	}

	return top + bonus + bottom;
}
