/*
 * yahtzee.h
 *
 * - defines data types for yahtzee
 * - may add background functions
 */

#ifndef yahtzee_h
    #define yahtzee_h

#define NUMDICE 5
#define MAXVALUE 6

typedef struct
{
    int value;
    int hold;
} Dice;

typedef struct
{
    int value;
    int vol;
    int choice;
} Mark;

typedef struct
{
    Mark *one; 
    Mark *two; 
    Mark *three;
    Mark *four; 
    Mark *five;
    Mark *six;
    int top; 
    int bonus;
    Mark *threeK;
    Mark *fourK;
    Mark *boat;
    Mark *small;
    Mark *large;
    Mark *yahtzee;
    Mark *chance;
    int bottom;
    int total;
    int vols;
} Score;

typedef struct
{
    char* symbol;
    Score *score;
    int rolls;
    int value;
    int metric;
} Player;

int checkDice(Dice *dice[]);
void unholdDice(Dice **dice[]);
void rollDice(Dice **dice[]);
Dice **createDice();
Player **createPlayers(int num, char **names, int *metric);

#endif
