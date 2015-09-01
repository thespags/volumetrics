#include <curses.h>

#define DIEROW 6
#define DIECOL 12 

void drawOne(int y, int x)
{
    mvaddch(y + 3, x + 6, 'O');
}

void drawTwo(int y, int x)
{
    mvaddch(y + 5, x + 2, 'O');
    mvaddch(y + 1, x + 10, 'O');
}

void drawThree(int y, int x)
{
    mvaddch(y + 5, x + 2, 'O');
    mvaddch(y + 3, x + 6, 'O');
    mvaddch(y + 1, x + 10, 'O');
}

void drawFour(int y, int x)
{
    mvaddch(y + 5, x + 10, 'O');
    mvaddch(y + 5, x + 2, 'O');
    mvaddch(y + 1, x + 10, 'O');
    mvaddch(y + 1, x + 2, 'O');
}

void drawFive(int y, int x)
{
    mvaddch(y + 5, x + 10, 'O');
    mvaddch(y + 5, x + 2, 'O');
    mvaddch(y + 3, x + 6, 'O');
    mvaddch(y + 1, x + 10, 'O');
    mvaddch(y + 1, x + 2, 'O');
}

void drawSix(int y, int x)
{
    mvaddch(y + 5, x + 10, 'O');
    mvaddch(y + 5, x + 2, 'O');
    mvaddch(y + 3, x + 10, 'O');
    mvaddch(y + 3, x + 2, 'O');
    mvaddch(y + 1, x + 10, 'O');
    mvaddch(y + 1, x + 2, 'O');
}

void drawDie(int y, int x, int value)
{
    mvhline(y    , x     , ACS_HLINE, 12);
    mvhline(y + 6, x     , ACS_HLINE, 12);
    mvvline(y    , x + 12, ACS_VLINE, 6);
    mvvline(y    , x     , ACS_VLINE, 6);
    mvaddch(y    , x     , ACS_ULCORNER);
    mvaddch(y + 6, x     , ACS_LLCORNER);
    mvaddch(y    , x + 12, ACS_URCORNER);
    mvaddch(y + 6, x + 12, ACS_LRCORNER);

    switch(value)
    {
        case 1: drawOne(y, x); break;
        case 2: drawTwo(y, x); break;
        case 3: drawThree(y, x); break;
        case 4: drawFour(y, x); break;
        case 5: drawFive(y, x); break;
        case 6: drawSix(y, x); break;
    }
}
