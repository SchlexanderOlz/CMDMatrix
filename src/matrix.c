#include "../include/matrix.h"

int main()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    init_color(COLOR_GRAY, 500, 500, 500);
    init_pair(3, COLOR_GRAY, COLOR_BLACK);

    init_color(COLOR_LIGHT_MATRIX_GREEN, 200 * 1000 / 255, 255 * 1000 / 255, 200 * 1000 / 255);
    init_pair(4, COLOR_LIGHT_MATRIX_GREEN, COLOR_BLACK);


    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    srand(time(NULL));

    raindrops.content = (struct raindrop*)malloc(MAX_X * sizeof(struct raindrop)) ;
    raindrops.length = MAX_X;

    for (size_t i = 0; i < MAX_X; i++) {
        raindrops.content[i] = CreateNewRaindrop(i);
    }

    while (true)
    {
        
        RainDropTick(raindrops);
        DisplayFrame(raindrops);
        refresh();
        SetEmpty();
        napms(100);
    }

    endwin();
    free(raindrops.content);
    return 0;
}

char *CreateRandomCharArray(const char *selection, int len)
{
    size_t selec_size = strlen(selection);
    char *shuffled = (char *)malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        shuffled[i] = selection[rand() % selec_size];
    }
    return shuffled;
}

char GetRandomCharacter(const char *selection)
{
    return selection[rand() % strlen(selection)];
}


void DisplayFrame(struct raindropList drops)
{
    for (size_t y = 0; y < getmaxx(stdscr); y++) // TODO: SIZE used
    {
        DisplayMatrixRow(drops.content[y]);
    }
}

void DisplayMatrixRow(struct raindrop drop)
{

    size_t len = strlen(drop.content);

    attron(COLOR_PAIR(1));
    for (size_t y = 0; y < len - 3; y++)
    {
        int row = y + drop.last_back.y;
        if (row < 0 || row >= MAX_Y) {continue;}
        wmove(stdscr, row, drop.last_back.x);
        wprintw(stdscr, "%c", drop.content[y]);
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    size_t green_row = len + drop.last_back.y - 3;
    if (!(green_row < 0 || green_row >= MAX_Y)) {
        wmove(stdscr, green_row, drop.last_back.x);
        wprintw(stdscr, "%c", drop.content[len - 4]); 
    }
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(2));
    for (size_t y = len - 2; y <= len; y++)
    {
        int row = y + drop.last_back.y;
        if (row < 0 || row >= MAX_Y) {continue;}
        wmove(stdscr, row, drop.last_back.x);
        wprintw(stdscr, "%c", drop.content[y]);
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    size_t row = len + drop.last_back.y;
    if (!(row < 0 || row >= MAX_Y)) {
        attron(COLOR_PAIR(3));
        wmove(stdscr, row, drop.last_back.x);
        wprintw(stdscr, "%c", drop.content[len - 1]); 
    }
    attroff(COLOR_PAIR(3));
}

void RainDropTick(struct raindropList raindrops) {
    for (size_t i = 0; i < raindrops.length; i++) {
        raindrops.content[i].last_back.y++;
        raindrops.content[i].last_front.y++;

        size_t len = strlen(raindrops.content[i].content);
        char *new_content = (char*)malloc(len + 2);
        memset(new_content, '\0', len + 1);

        new_content[len] = GetRandomCharacter(matrix_chars);
        for (size_t j = 0; j < strlen(raindrops.content[i].content); j++) {
            new_content[j] = raindrops.content[i].content[j];
        }
        free(raindrops.content[i].content);
        raindrops.content[i].last_front.y++;
        raindrops.content[i].content = new_content;
        if (raindrops.content[i].last_back.y >= getmaxy(stdscr)) {
            free(raindrops.content[i].content);
            raindrops.content[i] = CreateNewRaindrop(i);
        }
    }
}

struct raindrop CreateNewRaindrop(int x) {
    char* content = CreateRandomCharArray(matrix_chars, rand() % (MAX_Y / 2) + 3); // Potential error source
    return (struct raindrop){(struct coord){x, -strlen(content)}, (struct coord){x, 0}, content};
}

void SetEmpty() {
    for (size_t y = 0; y < MAX_Y; y++) {
        for (size_t x = 0; x < MAX_X; x++) {
            move(y, x);
            printw(" ");
        }
    }
}