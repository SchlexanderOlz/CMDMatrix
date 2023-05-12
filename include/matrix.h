#include <ncurses.h>

char* matrix_chars = new char(
    '0123456789ABCDEFGHRSTUVWXYZcdefghijklmnopz!@#$%^&*()_+{}[]|;:",./<>?あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをん゛゜ー');

void SetupWindow();
char* FormatCharArray(char*);
void DisplayFrame(char**);
char* CreateRandomCharArray(char*, int);