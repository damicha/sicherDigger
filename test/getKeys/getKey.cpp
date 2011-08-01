/* poly.cpp */
/* damicha of defect (2011) */

/* FIXME: Test how to store objects of inherent classes of a virtual class in an array of type of
 * the virtual class.
 * -> Don't store the objects directly.
 * -> Store only pointer of the objects.
 * -> Create and destroy the objects by the class functions !!
 */


#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

/*
 * main
 * FIXME improve description
 * use cursor keys
 * do something useful (add, sub, ...)
 */
int main(void)
{
    initscr();          /* Start curses mode          */
    printw("Hello World !!!");  /* Print Hello World          */
    refresh();          /* Print it on to the real screen */

    int c;

    /* configure */
    noecho();           // getchar() doesn't echo the get character
    nodelay(stdscr, true);          // getchar()'s no blocking mode
    cbreak();
    //keypad();

    // get the first key in the input buffer and discard all other
    while (c != 'q')
    {
        c = getch();    // get first entry (key) of the input buffer    
        flushinp();     // flush all other keys from input buffer

        if (c != ERR) {
            printw("The char %c has the ASCII code %d\n", (char)c&0xff, c);
            refresh();
        }
        sleep(1);

    }

    endwin();           /* End curses mode        */
    return 0;




#if 0
    char c;
    puts ("Enter text. Include a dot ('.') in a sentence to exit:");
    do {
        c=getchar();
        putchar (c);
    } while (c != '.');

    bool exit = false; 
    while(!exit) 
    { 
        if( kbhit() ) // Nur wenn auch eine Taste gedrückt ist 
        {   
            char c = getch(); // Muss auf keine Eingabe warten, Taste ist bereits gedrückt 
            switch(c) 
            { 
                case "x": exit = true; break; // Verarbeite Eingabe
                default: break;
            } 
        } 
        // Geschwindigkeitsregler 
        sleep(10); 
    }

#endif



    return 0;
}

