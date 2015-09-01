#include <curses.h>
#include <string.h>
#include "score.h"
#include "yahtzee.h"

static int top, bottom, total, bonus, vols, x;

/* print helpers */
void printInt(int y, int x, int num, int bonus);
void printHelp(int top);
int printBonus(Player *p);

/* for scores */
int printOne(Dice **dice);
int printTwo(Dice **dice);
int printThree(Dice **dice);
int printFour(Dice **dice);
int printFive(Dice **dice);
int printSix(Dice **dice);
int printThreeK(Dice **dice);
int printFourk(Dice **dice);
int printBoat(Dice **dice);
int printSmall(Dice **dice);
int printLarge(Dice **dice);
int printYahtzee(Dice **dice);
int printChance(Dice **dice);

void printInt(int y, int x, int num, int bonus)
{
    if(num > 99)
        mvprintw(y, x-4, "%d", num);
    else if(num > 9)
        mvprintw(y, x-3, "%d", num);
    else
        mvprintw(y, x-2, "%d", num);

    if(bonus < 63 && bonus)
        addch('v');
}

void printMark(int y, int x, Mark *mark)
{
    int num;

    /* if there is a mark then print else do nothing */
    if(mark)
    {
        num = mark->value;

        if(num > 99)
            mvprintw(y, x-4, "%d", num);
        else if(num > 9)
            mvprintw(y, x-3, "%d", num);
        else
            mvprintw(y, x-2, "%d", num);

        if(mark->vol)
            addch('v');
    }
}

int printOne(Dice **dice)
{
    Mark *mark = scoreTop(1, dice);
    int oldtop = top;
    attron(A_BOLD);
    mvprintw(2, 0, "  1:");
    printMark(2, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    bonus++;
    printHelp(oldtop < 63 && top >= 63 ? 2 : 1);
    attroff(A_BOLD);

    return 1;
}

int printTwo(Dice **dice)
{
    Mark *mark = scoreTop(2, dice);
    int oldtop = top;
    attron(A_BOLD);
    mvprintw(3, 0, "  2:");
    printMark(3, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    bonus++;
    printHelp(oldtop < 63 && top >= 63 ? 2 : 1);
    attroff(A_BOLD);

    return 1;
}

int printThree(Dice **dice)
{
    Mark *mark = scoreTop(3, dice);
    int oldtop = top;
    attron(A_BOLD);
    mvprintw(4, 0, "  3:");
    printMark(4, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    bonus++;
    printHelp(oldtop < 63 && top >= 63 ? 2 : 1);
    attroff(A_BOLD);

    return 1;
}

int printFour(Dice **dice)
{
    Mark *mark = scoreTop(4, dice);
    int oldtop = top;
    attron(A_BOLD);
    mvprintw(5, 0, "  4:");
    printMark(5, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    bonus++;
    printHelp(oldtop < 63 && top >= 63 ? 2 : 1);
    attroff(A_BOLD);

    return 1;
}

int printFive(Dice **dice)
{
    Mark *mark = scoreTop(5, dice);
    int oldtop = top;
    attron(A_BOLD);
    mvprintw(6, 0, "  5:");
    printMark(6, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    bonus++;
    printHelp(oldtop < 63 && top >= 63 ? 2 : 1);
    attroff(A_BOLD);

    return 1;
}

int printSix(Dice **dice)
{
    Mark *mark = scoreTop(6, dice);
    int oldtop = top;
    attron(A_BOLD);
    mvprintw(7, 0, "  6:");
    printMark(7, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    bonus++;
    printHelp(oldtop < 63 && top >= 63 ? 2 : 1);
    attroff(A_BOLD);

    return 1;
}

int printThreeK(Dice **dice)
{
    Mark *mark = score3K(dice);
    attron(A_BOLD);
    mvprintw(12, 0, " 3K:");
    printMark(12, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

int printFourK(Dice **dice)
{
    Mark *mark = score4K(dice);
    attron(A_BOLD);
    mvprintw(13, 0, " 4K:");
    printMark(13, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

int printBoat(Dice **dice)
{
    Mark *mark = scoreBoat(dice);
    attron(A_BOLD);
    mvprintw(14, 0, " BT:");
    printMark(14, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

int printSmall(Dice **dice)
{
    Mark *mark = scoreSmall(dice);
    attron(A_BOLD);
    mvprintw(15, 0, " SM:");
    printMark(15, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

int printLarge(Dice **dice)
{
    Mark *mark = scoreLarge(dice);
    attron(A_BOLD);
    mvprintw(16, 0, " LG:");
    printMark(16, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

int printYahtzee(Dice **dice)
{
    Mark *mark = scoreYahtzee(dice);
    attron(A_BOLD);
    mvprintw(17, 0, " YZ:");
    printMark(17, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

int printChance(Dice **dice)
{
    Mark *mark = scoreChance(dice);
    attron(A_BOLD);
    mvprintw(18, 0, " CH:");
    printMark(18, x, mark);
    top     += mark->value;
    total   += mark->value;
    vols    += mark->vol;
    printHelp(0);
    attroff(A_BOLD);

    return 1;
}

void sheet(int num, Player **players)
{
    int i, x = 4;
    clear();
    curs_set(0);

    for(i = 0; i < num; i++)
    {
        x += 9;
        mvprintw(0, x - strlen(players[i]->symbol), players[i]->symbol);
        printMark(2, x, players[i]->score->one);
        printMark(3, x, players[i]->score->two);
        printMark(4, x, players[i]->score->three);
        printMark(5, x, players[i]->score->four);
        printMark(6, x, players[i]->score->five);
        printMark(7, x, players[i]->score->six);
        printInt(9, x, players[i]->score->top, 0);
        if(printBonus(players[i]) > 0)
            printInt(10, x, players[i]->score->bonus, 1);
        printMark(12, x, players[i]->score->threeK);
        printMark(13, x, players[i]->score->fourK);
        printMark(14, x, players[i]->score->boat);
        printMark(15, x, players[i]->score->small);
        printMark(16, x, players[i]->score->large);
        printMark(17, x, players[i]->score->yahtzee);
        printMark(18, x, players[i]->score->chance);
        printInt(20, x, players[i]->score->bottom,0);
        printInt(21, x, players[i]->score->top, 0);
        printInt(23, x, players[i]->score->total, 0);
        printInt(24, x, players[i]->score->vols, 1);
    }

    mvhline(1, 0, 0, 80);
    mvprintw(2, 0, "  1:");
    mvprintw(3, 0, "  2:");
    mvprintw(4, 0, "  3:");
    mvprintw(5, 0, "  4:");
    mvprintw(6, 0, "  5:");
    mvprintw(7, 0, "  6:");
    mvhline(8, 0, 0, 80);
    mvprintw(9, 0, "  T:");
    mvprintw(10, 0, "  B:");
    mvhline(11, 0, 0, 80);
    mvprintw(12, 0, " 3K:");
    mvprintw(13, 0, " 4K:");
    mvprintw(14, 0, " BT:");
    mvprintw(15, 0, " SM:");
    mvprintw(16, 0, " LG:");
    mvprintw(17, 0, " YZ:");
    mvprintw(18, 0, " CH:");
    mvhline(19, 0, 0, 80);
    mvprintw(20, 0, "  T:");
    mvprintw(21, 0, " TT:");
    mvhline(22, 0, 0, 80);
    mvprintw(23, 0, "TTT:");
}

/* prints a number between 1 and 13 */
void getScore(int num, int i, Dice **dice, Player ***players)
{
    int counter = 1,
        print = 0,
        up = 1;
    char c;
    curs_set(0);

    /* sets x pos */
    x = 4 + 9 * (i + 1);

    /* ERROR */
    if(i >= num)
        return;

    for(;;)
    {
        sheet(num, *players);

        while(!print)
        {
            /* resets stats */;
            top         = (*players)[i]->score->top; 
            bottom      = (*players)[i]->score->bottom; 
            total       = (*players)[i]->score->total; 
            bonus       = printBonus((*players)[i]);
            vols        = (*players)[i]->score->vols; 

            switch(counter)
            {
                case 1: 
                    if((*players)[i]->score->one)
                        up ? counter++ : counter--;
                    else
                        print = printOne(dice); 
                    break;
                case 2: 
                    if((*players)[i]->score->two)
                        up ? counter++ : counter--;
                    else
                        print = printTwo(dice); 
                    break;
                case 3: 
                    if((*players)[i]->score->three)
                        up ? counter++ : counter--;
                    else
                        print = printThree(dice); 
                    break;
                case 4: 
                    if((*players)[i]->score->four)
                        up ? counter++ : counter--;
                    else
                        print = printFour(dice); 
                    break;
                case 5: 
                    if((*players)[i]->score->five)
                        up ? counter++ : counter--;
                    else
                        print = printFive(dice); 
                    break;
                case 6: 
                    if((*players)[i]->score->six)
                        up ? counter++ : counter--;
                    else
                        print = printSix(dice);
                    break;
                case 7: 
                    if((*players)[i]->score->threeK)
                        up ? counter++ : counter--;
                    else
                        print = printThreeK(dice); 
                    break;
                case 8: 
                    if((*players)[i]->score->fourK)
                        up ? counter++ : counter--;
                    else
                        print = printFourK(dice); 
                    break;
                case 9: 
                    if((*players)[i]->score->boat)
                        up ? counter++ : counter--;
                    else
                        print = printBoat(dice); 
                    break;
                case 10: 
                    if((*players)[i]->score->small)
                        up ? counter++ : counter--;
                    else
                        print = printSmall(dice); 
                    break;
                case 11: 
                    if((*players)[i]->score->large)
                        up ? counter++ : counter--;
                    else
                        print = printLarge(dice); 
                    break;
                case 12:
                    if((*players)[i]->score->yahtzee)
                        up ? counter++ : counter--;
                    else 
                        print = printYahtzee(dice); 
                    break;
                case 13:
                    if((*players)[i]->score->chance)
                        up ? counter++ : counter--;
                    else
                        print = printChance(dice); 
                    break;
             }

            if(counter > 13)
                counter = 1;
            else if(counter < 1)
                counter = 13;
        }

        c = getch();

        if(c == 'w')
        {
            counter--;
            up = 0;
        }
        else if(c == 's')
        {
            counter++;
            up = 1;
        }
        else if(c == '\n')
        {
            updateScore(counter, dice, &(*players)[i]);
            break;
        }

        print = 0;
    }

    sheet(num, *players);
    getch();
}

void printHelp(int up)
{
    if(bonus > 0)
    {
        mvprintw(10, 0, "  B:");

        if(up == 2 && top >= 63)
            printInt(10, x, 35, 1);
        else
        {
            printInt(10, x, 0, 1);
            vols++;
        }
    }

    if(up)
    {
        mvprintw(9, 0, "  T:");
        printInt(9, x, top, 0);
        mvprintw(21, 0, " TT:");
        printInt(21, x, top >= 63 ? top + 35 : top, 0);
    }
    else
    {
        mvprintw(20, 0, "  T:");
        printInt(20, x, bottom,0);
    }

    mvprintw(23, 0, "TTT:");
    printInt(23, x, total, 0);
    printInt(24, x, vols, 1);
}

/* 
 * returns 1 if top is complete
 * otherwise returns a non positive value
 */
int printBonus(Player *p)
{
    return -5 + ((p->score->one     ? 1 : 0) +
                 (p->score->two     ? 1 : 0) +
                 (p->score->three   ? 1 : 0) +
                 (p->score->four    ? 1 : 0) +
                 (p->score->five    ? 1 : 0) +
                 (p->score->six     ? 1 : 0));
}
