/*! ****************************************************************************
 *
 * \file    getKey.cpp
 * \brief   The ncurses library is used to get key from the input buffer and
 *          to print text to the console (output buffer).
 *
 * \details It seems that it's not possible to disable the autorepeat function
 *          of the keyboard. The only way that I found is the "xset -r" command.
 *          But this command disables the autorepeat function of an singe key or
 *          at all in the whole system. It seems that it's also not possible
 *          to get key press or key release events from linux. This sux.
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

/*
 * main
 */
int main(void)
{
    /* start curses mode */
    initscr();         
    /* print the welcome message */
    printw("Welcome\n");
    printw("Press keys:\n");
    printw("  Up    - to increase the value\n");
    printw("  Down  - to decrease the value\n");
    printw("  Left  - to halve the value\n");
    printw("  Right - to double the value\n");
    printw("  r     - to reset the value\n");
    printw("  q     - to quit\n");
    /* Print it on to the real screen */
    refresh();

    

    /* configure the behavor of the getchar() function */
    noecho();               // getchar() doesn't echo the get character
    nodelay(stdscr, true);  // getchar()'s non blocking mode
    cbreak();               // disable the buffer of typed characters until a
                            // "\n" or "\r" is typed
    keypad(stdscr, true);   // enable the keypad to get its keys


    int c;                  // character to read
    int exit = false;        // exit flag
#define A_RESET_VALUE 1024
    long long a = A_RESET_VALUE;    // accumulator
    while (exit == false)
    {
        /* get the first key in the input buffer and discard all other */
        c = getch();    // get first entry (key) of the input buffer    
        flushinp();     // flush all other keys from input buffer

        if (c != ERR)
        {

            /* check got key and calculate the new accumulator value */
            switch (c)
            {
                case 'q':       exit = true;        break;
                case 'r':       a = A_RESET_VALUE;  break;
                case KEY_UP:    a++;                break;
                case KEY_DOWN:  a--;                break;
                case KEY_LEFT:  a /= 2;             break;
                case KEY_RIGHT: a *= 2;             break;
            }


        }

        /* generate output */
        move(10, 0);             // move cursor position to (row, col)
        printw("The char %c has the ASCII code %3d (0x%02x)\n",
               (char)c&0xff, c, c);
        printw("\n");
        printw("Value A: %24lld (0x%016llx)\n", a, a);
        refresh();
        
        /* sleep for 25 ms seconds */
        usleep(25*1000);

    }

    /* End curses mode */
    endwin();
    return 0;
}

