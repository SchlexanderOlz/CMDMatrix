#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE(arr) ((arr) != NULL ? sizeof(arr) / sizeof(arr[0]) : 0)
#define MAX_X getmaxx(stdscr)
#define MAX_Y getmaxy(stdscr)

#define BEGIN_CHAR 4


#define COLOR_LIGHT_MATRIX_GREEN 10
#define COLOR_GRAY 11

const char *matrix_chars = "0123456789ABCDEFGHRSTUVWXYZcdefghijklmnopz!@#~$%^&*()_+{}[]|;:,./<>?";
struct coord
{
    int x;
    int y;
};

struct raindrop
{
    struct coord last_back;
    struct coord last_front;
    char *content;
};

struct raindropList
{
    struct raindrop *content;
    size_t length;
    void (*sos)();
};

struct raindropList raindrops;

void DisplayFrame(struct raindropList);
char *CreateRandomCharArray(const char *, int);
char GetRandomCharacter(const char *);
void DisplayMatrixRow(struct raindrop);
void RainDropTick(struct raindropList);
struct raindrop CreateNewRaindrop(int x);
void SetEmpty();
struct raindrop CreateNewRaindropRandomPos(int);