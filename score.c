/* 
 *  score.c
 *
 *  -calculates yahtzee scores and vols
 */

#include <stdio.h>
#include <stdlib.h>
#include "score.h"

/* helper functions */
static int sumAll(Dice *dice[])
{
    int i, sum = 0;

    for(i = 0; i < 5; i++)
        sum += dice[i]->value;

    return sum;
}

static int compareInt(const int *a, const int *b)
{
    //int temp = *a - *b;
    return *a - *b;

    /*
    if(temp > 0)
        return 1;
    else if(temp < 0)
        return -1;
    else
        return 0;
    */
}

/* for any roll on top(ie. 1-6) */
Mark* scoreTop(int die, Dice *dice[])
{
    int i,
        sum = 0,
        total = 0;
    Mark *mark = (Mark *)malloc(sizeof(Mark));

    for(i = 0; i < 5; i++)
        if(die == dice[i]->value)
        {
            total++;
            sum += die;
        }

    mark->value = sum;

    /* if 4K is non-zero then no value */
    mark->vol = (total >= 4) ? 0 : 1;

    return mark;
}

Mark* score3K(Dice *dice[])
{
    int i, j, count;
    Mark *mark = (Mark *)malloc(sizeof(Mark));

    /* test each die value for 3K or better */
    for(i = 1; i <= 6; i++)
    {
        count = 0;

        /* counts the number of occurences */
        for(j = 0; j < 5; j++)
            if(i == dice[j]->value)
                count++;

        /* if 3K or better break */
        if(count >= 3)
        {
            mark->value = sumAll(dice);
            break;
        }
    }

    mark->vol = (count >= 4) ? 0 : 1;
    return mark;
}

Mark* score4K(Dice *dice[])
{
    int i, j, count;
    Mark *mark = (Mark *)malloc(sizeof(Mark));

    /* tests each die value for a 4k or better */
    for(i = 1; i <= 6; i++)
    {
        count = 0;

        /* counts the number of occurence of the die */
        for(j = 0; j < 5; j++)
            if(i == dice[j]->value)
                    count++;

        /* if 4k or better breka */
        if(count >= 4)
        {
            mark->value = sumAll(dice);
            break;
        }
    }

    mark->vol = (count >= 4) ? 0 : 1;
    return mark;
}

Mark* scoreBoat(Dice *dice[])
{
    int array[] = { dice[0]->value,
                     dice[1]->value,
                     dice[2]->value,
                     dice[3]->value,
                     dice[4]->value};
    int one, two, three, four, five;
    Mark *mark = (Mark *)malloc(sizeof(Mark));
    qsort(array, 5, sizeof(int), (void *)compareInt);

    /* for easier readability */
    one     = array[0];
    two     = array[1];
    three   = array[2];
    four    = array[3];
    five    = array[4];

    /* should be XX_YY where _ is either X or Y */
    if(one == two && four == five && (two == three || three == four))
    {
        mark->value = 25;
        mark->vol = 0;
    }
    else    
    {
        mark->value = 0;
        mark->vol = 1;
    }

    return mark;
}

Mark* scoreSmall(Dice *dice[])
{
    int array[] = { dice[0]->value,
                    dice[1]->value,
                    dice[2]->value,
                    dice[3]->value,
                    dice[4]->value};
    int i, j, temp, one, two, three, four, five;
    Mark *mark = (Mark *)malloc(sizeof(Mark));
    qsort(array, 5, sizeof(int), (void *)compareInt);

    /* puts duplicates at the end of the list if there are any */
    for(i = 0; i < 4; i++)
    {
        temp = 0;

        if(array[i] == array[i+1])
        {
            temp = array[i];
                
            for(j = i; j < 4; j++)
                array[j] = array[j+1];
            
            array[4] = temp;
        }
    }


    /* for easier readability */
    one   = array[0];
    two   = array[1];
    three = array[2];
    four  = array[3];
    five  = array[4];

    /* 6 possibilities for a small straight */
    if((one == 1 && two == 2 && three == 3 && four == 4) ||
       (one == 2 && two == 3 && three == 4 && four == 5) ||
       (one == 3 && two == 4 && three == 5 && four == 6) ||
       (two == 1 && three == 2 && four == 3 && five == 4) ||
       (two == 2 && three == 3 && four == 4 && five == 5) ||
       (two == 3 && three == 4 && four == 5 && five == 6)) 
    {
        mark->value = 30;
        mark->vol = 0;
    }
    else
    {
        mark->value = 0;
        mark->vol = 1;
    }

    return mark;
}

Mark* scoreLarge(Dice *dice[])
{
    int array[] = { dice[0]->value,
                     dice[1]->value,
                     dice[2]->value,
                     dice[3]->value,
                     dice[4]->value};
    int i;
    Mark *mark = (Mark *)malloc(sizeof(Mark));
    qsort(array, 5, sizeof(int), (void *)compareInt);

    /* only two types of larges */
    /* 1 2 3 4 5 */
    for(i = 0; i < 5; i++)
        if((i + 1) != array[i]) 
            break;

    /* 2 3 4 5 6 */
    if(i != 5)
        for(i = 0; i < 5; i++)
            if((i + 2) != array[i]) 
                break;

    if(i == 5)
    {
        mark->value = 40;
        mark->vol = 0;
    }
    else
    {
        mark->value = 0;
        mark->vol = 1;
    }

    return mark;
}

Mark* scoreYahtzee(Dice *dice[])
{
    int i, j, count;
    Mark *mark = (Mark *)malloc(sizeof(Mark));

    for(i = 0; i < 6; i++)
    {
        count = 0;

        for(j = 0; j < 5; j++)
            if(i + 1 == dice[j]->value)
                count++;

        if(count >= 5)
        {
            mark->value = 50;
            break;
        }
    }

    mark->vol = (count >= 5) ? 0 : 1;
    return mark;
}

Mark* scoreChance(Dice *dice[])
{
    Mark *temp = score4K(dice), 
         *mark = (Mark *)malloc(sizeof(Mark));

    mark->value  = sumAll(dice);
    mark->vol    = (temp->value > 0) ? 0 : 1;
    free(temp);

    return mark;
}

/* choice should be a menu option */
void updateScore(int choice, Dice *dice[], Player **p)
{   
    Mark *m;
    
    switch(choice)
    {
        case 1:
            m = scoreTop(1, dice);
            (*p)->score->one = m;
            (*p)->score->top += m->value;
            break;
        case 2:
            m = scoreTop(2, dice);
            (*p)->score->two = m;
            (*p)->score->top += m->value;
            break;
        case 3:
            m = scoreTop(3, dice);
            (*p)->score->three = m;
            (*p)->score->top += m->value;
            break;
        case 4:
            m = scoreTop(4, dice);
            (*p)->score->four = m;
            (*p)->score->top += m->value;
            break;
        case 5:
            m = scoreTop(5, dice);
            (*p)->score->five = m;
            (*p)->score->top += m->value;
            break;
        case 6:
            m = scoreTop(6, dice);
            (*p)->score->six = m;
            (*p)->score->top += m->value;
            break;
        case 7:
            m = score3K(dice);
            (*p)->score->threeK = m;
            (*p)->score->bottom += m->value;
            break;
        case 8:
            m = score4K(dice);
            (*p)->score->fourK = m;
            (*p)->score->bottom += m->value;
            break;
        case 9:
            m = scoreBoat(dice);
            (*p)->score->boat = m;
            (*p)->score->bottom += m->value;
            break;
        case 10:
            m = scoreSmall(dice);
            (*p)->score->small = m;
            (*p)->score->bottom += m->value;
            break;
        case 11:
            m = scoreLarge(dice);
            (*p)->score->large = m;
            (*p)->score->bottom += m->value;
            break;
        case 12:
            m = scoreYahtzee(dice);
            (*p)->score->yahtzee = m;
            (*p)->score->bottom += m->value;
            break;
        case 13:
            m = scoreChance(dice);
            (*p)->score->chance = m;
            (*p)->score->bottom += m->value;
            break;
        default:
            printf("ERROR!!!\n");
        }

        /* 
         * if top is finished print bonus
         * calculates the bonus if top >= 63
         */
        if( (*p)->score->bonus == -1 &&
            (*p)->score->one && (*p)->score->two  && (*p)->score->three &&
            (*p)->score->four && (*p)->score->five && (*p)->score->six)
             
        {
            if((*p)->score->top >= 63)
            {
                (*p)->score->bonus  = 35;
                (*p)->score->total += 35;
            }
            else
            {
                (*p)->score->bonus  = 0;
                (*p)->score->vols++;
            }
        }


        (*p)->score->total += m->value;
        (*p)->score->vols  += m->vol;
}
