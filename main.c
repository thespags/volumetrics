/*
 * Volumetric Yahtzee
 *
 * ver. 1.00
 * - completed basic commands for a game
 *
 * ver. 1.01
 * - fixed and changed display in score sheet
 * - added cheat feature
 * - added balls and dick
 * - adjusted balls and dick display
 * - edit display of turn (different layout?)
 *
 * ver. 1.02
 * - added iscorrect function
 * - added volumetric input
 * - edited main menu
 * - edited roll
 *
 * things to add
 * - tell user when to drink
 * - penalties
 * - no dice/ dice
 * - add insults
 *
 */
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "yahtzee.h"
#include "score.h"
#include "draw.h"
#include "sheet.h"

static WINDOW *scr;
static int xMax, yMax;

/* helper methods */
void highlight(int x, int y, char *str);
void anykey(int y, int x);
int iscorrect(int y, int x);
void printCenter(int y,char *str);
void printHLine(int y);
char *getHold(int hold);
void displayHelp();

/* helper functions */
void menu(int *num, Player ***players);
void displayMenu();
int getNumPlayers();
char **getNamePlayers(int num, int **metric);
void ballsanddick(int num, Dice ***dice, Player ***players);

/* turn functions */
void turn(int num, int i, Dice ***dice, Player ***players, int type);
void displayTurn(int pos, int x, int num, int counter, Dice **dice, Player **players, int type);

/* for cheating */
void rollYahtzee(Dice ***dice);

int main()
{
    int i, j, num = 0;
    Dice **dice;
    Player **players;

    dice = createDice();

    scr = initscr();
    cbreak();
    noecho();
    getmaxyx(scr, yMax, xMax);
    keypad(scr, TRUE);

    menu(&num, &players);

    /* one player no point for balls and dick */
    if(num > 1)
        ballsanddick(num, &dice, &players);

    /* goes through 13 scores per player */
    for(i = 0; i < 13; i++)
    {
        /* goes through each players turn */
        for(j = 0; j < num; j++)
        {
            turn(num, j, &dice, &players, 1);
            getScore(num, j, dice, &players);
        }
    }

    getch();

    endwin();
    return 0;
}

/* pauses for any key */
void anykey(int y, int x)
{
    curs_set(0);
    mvprintw(y, x, "Press any key to continue...");
    getch();
}

/*
 * returns 1 if input is y
 * returns 0 otherwise
 */
int iscorrect(int y, int x)
{
    char c;
    curs_set(1);
    mvprintw(y, x, "Is this correct (y/n): ");

    for(;;)
    {
        c = getch();

        if(c == 'y')
        {
            addch('y');
            return 1;
        }
        else if(c == 'n')
        {
            addch('n');
            return 0;
        }
    }
}

/* high lights a given string at x,y */
void highlight(int y, int x, char *str)
{
    attron(A_BOLD);
    mvaddstr(y, x, str);
    attroff(A_BOLD);
    refresh();
}

void menu(int *num, Player ***players)
{
    int *metric = (int *)malloc((*num) * sizeof(int));
    char **names;

    displayMenu();
    attron(A_BOLD);
    mvprintw(10, 4, "===/ |====| |====|       /==\\ |==\\ ===== |\\   | |\\   | ===== |\\   | /==\\");
    mvprintw(11, 4, "  /  |    | |    |        \\   |  |   |   | \\  | | \\  |   |   | \\  | |   ");
    mvprintw(12, 4, " /   |    | |    |         \\  |==/   |   |  \\ | |  \\ |   |   |  \\ | |  \\");
    mvprintw(13, 4, "/=== |====| |====|       \\==/ |    ===== |   \\| |   \\| ===== |   \\| \\==/");
    mvprintw(14, 4, "------------------------------------------------------------------------");
    attroff(A_BOLD);
    anykey(18, 2);

    *num     = getNumPlayers();
    names    = getNamePlayers(*num, &metric);
    *players = createPlayers(*num, names, metric);
}

char **getNamePlayers(int num, int **metric)
{
    int i, j;
    char c, temp[9];
    char **names = (char **)malloc(num * sizeof(char *));

    for(i = 0; i < num; i++)
    {
        curs_set(1);

        for(;;)
        {
            displayMenu();
            mvprintw(18, 2, "Note: Maximum symbol length is 8 characters.");
            mvprintw(10, 2, "Enter the symbol for player %d: ", i + 1);

            for(j = 0; j < 8;)
            {
                c = getch();

                if(c == '\n')
                    break;
                else if(c == 7 || c == 127)
                {
                    mvprintw(10, 32, "        ");
                    j = j ? j - 1 : 0;
                }
                else if(j >= 8)
                    continue;
                else
                {
                    addch(c);
                    temp[j] = c;
                    j++;
                }

                temp[j] = '\0';
                mvprintw(10, 33 , "%s", temp);
            }

            for(;;)
            {
                curs_set(1);
                displayMenu();
                mvprintw(18, 2, "Note: Maximum symbol length is 8 characters.");
                mvprintw(10, 2, "Enter the symbol for player %d: %s", i + 1, temp);
                mvprintw(12, 2, "Choose a volumetric whole (1), halves (2), thirds (3): ", i + 1);
                c = getch();

                if(c != '\n')
                    addch(c);

                if(c == '1')
                {
                    (*metric)[i] = 1;
                    break;
                }
                else if(c == '2')
                {
                    (*metric)[i] = 2;
                    break;
                }
                else if(c == '3')
                {
                    (*metric)[i] = 3;
                    break;
                }
                else if(c == '\n')
                    mvprintw(14, 2, "Invalid input: No input given.");
                else
                    mvprintw(14, 2, "Invalid input: Not a proper volumetric.");

                anykey(20, 2);
            }

            if(iscorrect(14, 2))
                break;

            anykey(20, 2);
        }

        names[i] = (char *)malloc(strlen(temp) * sizeof(char));
        strcpy(names[i], temp);
        anykey(20, 2);
        mvprintw(10, 33, "        ");
    }

    return names;
}

void ballsanddick(int num, Dice ***dice, Player ***players)
{
    int i, low = 0;
    Player **p = NULL;

    for(i = 0; i < num; i++)
        turn(num, i, dice, players, 0);

    for(i = 0; i < num; i++)
    {
        if((*players)[low]->rolls >  (*players)[i]->rolls)
            low = i;
        else if((*players)[low]->rolls == (*players)[i]->rolls)
            if((*players)[low]->value < (*players)[i]->value)
                low = i;
    }

    for(i = 0; i < num; i++)
    {
        *p = (*players)[i];
        (*players)[i] = (*players)[low];
        (*players)[low]= *p;

        low = low + 1 == num ? low : low + 1;
    }
}

int getNumPlayers()
{
    char c;
    int num, setBreak = 0;

    for(;;)
    {
        displayMenu();
        curs_set(1);
        mvprintw(10, 2, "Enter the number of players (1-5): ");
        c = getch();

        if(c == '\n')
            mvprintw(12, 2, "Invalid input: No input given.");
        else
            addch(c);

        if(isdigit(c))
        {
            num = c - 48;

            if(num > 5)
                mvprintw(12, 2, "Invalid input: Too many players.");
            else if(num == 0)
                mvprintw(12, 2, "Invalid input: No players.");
            else
            {
                mvprintw(12, 2, "You have selected %d player(s).", num);
                setBreak = iscorrect(14, 2);
            }
        }
        else if(c != '\n')
            mvprintw(12, 2, "Invalid input: Not a number.");

        anykey(18, 2);

        if(setBreak)
            return num;
    }
}

void displayMenu()
{
    clear();
    border(0, 0, 0, 0, 0, 0, 0, 0);
    printCenter(2, "Welcome to ASCII Volumetric Yahtzee!!!");
    printCenter(4, "ver 1.02");
    printCenter(6, "created by spags.");
    printHLine(8);
    printHLine(16);
}

void printCenter(int y, char *str)
{
    mvprintw(y, xMax/2 - strlen(str)/2, str);
}

void printHLine(int y)
{
    mvhline(y, 0, 0, xMax);
    mvaddch(y, 0, ACS_LTEE);
    mvaddch(y, xMax - 1, ACS_RTEE);
}

void turn(int num, int i, Dice ***dice, Player ***players, int type)
{
    int counter, pos = 0, hold = 0;
    char c;

    int cheat = 0;
    counter = type ? 2 : 0;

    clear();
    curs_set(0);
    rollDice(dice);
    displayTurn(pos, i, num, counter, *dice, *players, type);

    for(;;)
    {
        c = getch();

        if(c == 'a')
        {
            mvaddstr(8, 8 + 15 * pos, getHold(hold));
            pos--;

            cheat++;
        }
        else if(c == 'd')
        {
            mvaddstr(8, 8 + 15 * pos, getHold(hold));
            pos++;

            cheat = 0;
        }
        else if(c == 'x')
        {
            (*dice)[pos]->hold = (hold) ? 0 : 1;

            cheat = 0;
        }
        else if(c == 'r')
        {
            printf("this is the cheat %d", cheat);
            if(cheat == 5)
                rollYahtzee(dice);
            else
                rollDice(dice);

            /* depending on balls and dick */
            type ? counter-- : counter++;
            displayTurn(pos, i, num, counter, *dice, *players, type);

            cheat = 0;
        }
        else if(c == 'v')
        {
            if(type)
            {
                sheet(num, *players);
                getch();
                displayTurn(pos, i, num, counter, *dice, *players, type);
            }

            cheat = 0;
        }
        else if(c == 'h')
        {
            displayHelp();
            displayTurn(pos, i, num, counter, *dice, *players, type);

            cheat = 0;
        }

        pos = (pos < 0) ? 4 : pos % 5;
        hold = (*dice)[pos]->hold;
        highlight(8, 8 + 15 * pos, getHold(hold));

        if(type)
        {
            if(counter == 0 || c == 'e' || c == '\n')
                break;
        }
        else if(scoreYahtzee(*dice)->value > 0)
        {
            (*players)[i]->rolls = counter;
            (*players)[i]->value = (*dice)[0]->value;
            break;
        }
    }

    anykey(18, 2);
    unholdDice(dice);
}

/*
 * if hold is true then returns [X]
 * otherwise returns [ ]
 */
char* getHold(int hold)
{
    return (hold) ? "[X]" : "[ ]";
}

void displayTurn(int pos, int x, int num, int counter, Dice **dice, Player **players, int type)
{
    int i;
    int die0 = dice[0]->value,
        die1 = dice[1]->value,
        die2 = dice[2]->value,
        die3 = dice[3]->value,
        die4 = dice[4]->value;

    clear();
    border(0, 0, 0, 0, 0, 0, 0, 0);
    drawDie(1, 3, die0);
    mvprintw(8, 8, getHold(dice[0]->hold));
    drawDie(1, 3 + 15, die1);
    mvprintw(8, 8 + 15, getHold(dice[1]->hold));
    drawDie(1, 3 + 15 * 2, die2);
    mvprintw(8, 8 + 15 * 2, getHold(dice[2]->hold));
    drawDie(1, 3 + 15 * 3, die3);
    mvprintw(8, 8 + 15 * 3, getHold(dice[3]->hold));
    drawDie(1, 3 + 15 * 4, die4);
    mvprintw(8, 8 + 15 * 4, getHold(dice[4]->hold));
    printHLine(9);

    attron(A_BOLD);
    mvprintw(10, 2, "%s's turn:", players[x]->symbol);
    attroff(A_BOLD);

    if(type)
        mvprintw(12, 2, "Select dice to hold.");
    else
        mvprintw(12, 2, "Balls and Dick");

    mvprintw(14, 2, "You rolled: %d, %d, %d, %d, %d",
        die0, die1, die2, die3, die4);

    if(type)
        mvprintw(16, 2, "You have %d roll(s) left...", counter);
    else
        mvprintw(16, 2, "You have rolled %d time(s)...", counter);

    if(!type)
    {
        mvprintw(10, 40, "Players  -  Rolls  -  Value");

        for(i = 0; i < num; i++)
        {
            mvprintw(12 + i * 2, 40, players[i]->symbol);

            if(players[i]->rolls)
            {
                mvprintw(12 + i * 2, 52, "%d", players[i]->rolls);
                mvprintw(12 + i * 2, 62, "%d", players[i]->value);
            }
            else
            {
                mvprintw(12 + i * 2, 52, "-");
                mvprintw(12 + i * 2, 62, "-");
            }
        }
    }
    else
    {
        attron(A_BOLD);
        mvprintw(10, 40, " Possible Scores");
        attroff(A_BOLD);
        mvprintw(12, 40, "  1:");
        if(players[x]->score->one)
            mvprintw(12, 52, "  -", x);
        else
            printMark(12, 56, scoreTop(1, dice));
        mvprintw(14, 40, "  2:");
        if(players[x]->score->two)
            mvprintw(14, 52, "  -");
        else
            printMark(14, 56, scoreTop(2, dice));
        mvprintw(16, 40, "  3:");
        if(players[x]->score->three)
            mvprintw(16, 52, "  -");
        else
            printMark(16, 56, scoreTop(3, dice));
        mvprintw(18, 40, "  4:");
        if(players[x]->score->four)
            mvprintw(18, 52, "  -");
        else
            printMark(18, 56, scoreTop(4, dice));
        mvprintw(20, 40, "  5:");
        if(players[x]->score->five)
            mvprintw(20, 52, "  -");
        else
            printMark(20, 56, scoreTop(5, dice));
        mvprintw(22, 40, "  6:");
        if(players[x]->score->six)
            mvprintw(22, 52, "  -");
        else
            printMark(22, 56, scoreTop(6, dice));
        mvprintw(10, 60, " 3K:");
        if(players[x]->score->threeK)
            mvprintw(10, 72, "  -");
        else
            printMark(10, 76, score3K(dice));
        mvprintw(12, 60, " 4K:");
        if(players[x]->score->fourK)
            mvprintw(12, 72, "  -");
        else
            printMark(12, 76, score4K(dice));
        mvprintw(14, 60, " BT:");
        if(players[x]->score->boat)
            mvprintw(14, 72, "  -");
        else
            printMark(14, 76, scoreBoat(dice));
        mvprintw(16, 60, " SM:");
        if(players[x]->score->small)
            mvprintw(16, 72, "  -");
        else
            printMark(16, 76, scoreSmall(dice));
        mvprintw(18, 60, " LG:");
        if(players[x]->score->large)
            mvprintw(18, 72, "  -");
        else
            printMark(18, 76, scoreLarge(dice));
        mvprintw(20, 60, " YZ:");
        if(players[x]->score->yahtzee)
            mvprintw(20, 72, "  -");
        else
            printMark(20, 76, scoreYahtzee(dice));
        mvprintw(22, 60, " CH:");
        if(players[x]->score->chance)
            mvprintw(22, 72, "  -");
        else
            printMark(22, 76, scoreChance(dice));
    }

    // highlights current [ ]
    highlight(8, 8 + 15 * pos, getHold(dice[pos]->hold));
    mvprintw(22, 2, "Press 'h' for the help menu");
}

/* for cheating */
void rollYahtzee(Dice ***dice)
{
    int i, value = 0;

    for(i = 0; i < 5; i++)
        if((*dice)[i]->hold)
        {
            if(!value)
                value = (*dice)[i]->value;
            else if(value != (*dice)[i]->value)
                break;
        }

    if(value == 0 || i < 5)
        rollDice(dice);
    else
    {
        for(i = 0; i < 5; i++)
            (*dice)[i]->value = value;
    }
}

void displayHelp()
{
    clear();
    border(0, 0, 0, 0, 0, 0, 0, 0);

    mvprintw(2, 2, "w - moves up");
    mvprintw(4, 2, "s - moves down");
    mvprintw(6, 2, "a - moves left");
    mvprintw(8, 2, "d - moves right");
    mvprintw(10, 2, "x - (un)hold die");
    mvprintw(12, 2, "r - roll dice");
    mvprintw(14, 2, "e - score dice (or press enter)");
    mvprintw(16, 2, "v - view score");
    mvprintw(18, 2, "h - view help");

    anykey(20, 2);
}

// testing values of input
void charTest(char c, int x, int y)
{
    char string[10];
    sprintf(string, "char value %d", (int) c);
    mvprintw(x, y, string);
}
