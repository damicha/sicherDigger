/*! ****************************************************************************
 *
 * \file    SDig_TextEngine.h
 * \brief   Displays the field objects as text on the console
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \details
 *  The TextEngine class is implemented that provices functions to get the
 *  user input and to do a ASCII text output of the game field.
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_TEXT_ENGINE_H_
#define _SDIG_TEXT_ENGINE_H_



#include "objField.h"
#include "SDig_BaseDOT.h"
#include "SDig_DOTs.h"
#include "SDig_TimeEngine.h"
#include "SDig_LevelEngine.h"
#include "SDig_TextEngineTypes.h"

#include <stdio.h>
#include <ncurses.h>

#include <string>
#include <sstream>


using namespace std;


/*!
 * \namespace   SDig
 * \brief   Namespace of the sicherDigger project.
 *
 * FIXME: move SDig namespace description to a central header file
 */
namespace SDig {

    
/*!
 * \class   TextEngine 
 * \brief
 *  Provices functions to get the user input and to do a ASCII text output
 *  of the game field.
 */
class TextEngine
{

/* ======== attributes ======== */    
private:
    /*! counts the number of intances. It's used to init the ncurses library
     *  if the first TextEngine instance is created. The ncurses library is
     *  closed if the last TextEngine instance will be deleted. */
    static int mInstanceCounter;

/* ======== functions ======== */
public:

    /*!
     * \brief   constructor
     *
     * Initialize ncurses if the first instance of this class will be created
     */
    TextEngine() {
        if (mInstanceCounter == 0) {
            /* init ncurses */
            initNCurses();
            /* increment instance counter */
            mInstanceCounter++;
        } 
    }
    
    /*!
     * \brief   destructor
     *
     * Stop ncurses if the last instance of this class will be destroyed
     */
    ~TextEngine() {
        /* decrement instance counter */
        mInstanceCounter--;
        if (mInstanceCounter == 0) {
            /* release ncurses */
            stopNCurses();
        } 
    }

    
    /*!
     * \brief   initialize ncurses
     */
    void initNCurses(void) {
        /* start curses mode */
        initscr();

        /* configure the behavior of the getchar() function */
        noecho();               // getchar() doesn't echo the get character
        nodelay(stdscr, true);  // getchar()'s non blocking mode
        cbreak();               // disable line buffering
        keypad(stdscr, true);   // enable the keypad to get its keys
    }

    
    /*!
     * \brief   stop ncurses
     */
    void stopNCurses(void) {
        /* End curses mode */
        endwin();
    }
    
    /*!
     * \brief   Get key from input buffer and map it to the internal butten
     *  representation.
     * \return  Recognized button.
     */
    TextEngineTypes::Button getButton(void)
    {
        using namespace TextEngineTypes;    // refer to button types (BT_...)
        TextEngineTypes::Button button = BT_NONE;

        int c = getch();    // get first entry (key) of the input buffer    
        flushinp();         // flush all other keys from input buffer
    
        if (c != ERR)
        {
            /* keyboard button mapping */
            switch(c)
            {
                case (int)'q'   : button = BT_SELECT;   break;
                case (int)'s'   : button = BT_START;    break;
                case (int)'o'   : button = BT_A;        break;
                case (int)'p'   : button = BT_B;        break;
                case KEY_DOWN   : button = BT_DOWN;     break;
                case KEY_UP     : button = BT_UP;       break;
                case KEY_LEFT   : button = BT_LEFT;     break;
                case KEY_RIGHT  : button = BT_RIGHT;    break;
            }
        }

        return button;
    }


    /*!
     * FIXME: header
     * \brief   Print the content of the object field to the console
     * \param   pField
     *  Reference to the object field to print.
     * \param   pHeaderString
     *  String used within the header
     */
    // FIXME: use pinter to pLevel
    void drawLevel(LevelEngine &pLevel)
    {
        /* create string with timing information */
        const int str_len = 32;
        char str[str_len];
        snprintf(str, str_len, "T:%04d S:%02d/%02d",
                 pLevel.getTimeCnt(), pLevel.getSandCnt(), pLevel.getRequiredSand());
        
        /* display level */
        drawField(pLevel.getField(), str);
    }

private:
    /*!
     * \brief   Print the content of the object field to the console
     * \param   pField
     *  Reference to the object field to print.
     * \param   pHeaderString
     *  String used within the header
     */
    void drawField(const objField *pField,
                   const char *pHeaderString = NULL)
    {
        // move cursor position to (row, col)
        move(0, 0);

        // draw the object field
        drawHeader(pHeaderString);
        drawFieldData(pField);
        drawFooter();
    }


    /* Print the content of the object field as an array to the console. */
    void drawFieldData(const objField *pField);


    /*!
     * \brief   Print the content of the object field as a list to the console
     * \param   pField
     *  Reference to the object field to print
     */
    void drawFieldList(const objField &pField)
    {
        printw("Field dimensions: (x: %d, y: %d)\n",
               pField.size_x, pField.size_y);
        for (int i = 0; i < pField.size_x*pField.size_y; i++) {
            printw("position: %2d, data: %s\n", i, pField.entries[i].str().c_str());
        }
        refresh();
    }


    /*!
     * \brief   Draw debug infos of the time engine
     */
    void drawDebugInfo(SDig::TimeEngine &te)
    {
        printw("%s", te.getDebugInfo().c_str());
        refresh();
    }


    /*!
     * \brief   Gets a character to print that presents the type of the data object.
     * \param   pObjType
     *  Address of data object.
     */
    char getSymbol(BaseDOT *pObjType)
    {
        switch (pObjType->getType())
        {
            case BaseDOT::empty:    return ' '; 
            case BaseDOT::sand:     return '.';
            case BaseDOT::wall:     return '#';
            case BaseDOT::stone:    return 'O';
            case BaseDOT::player:
            {
                SDig::DOTPlayer *player = (SDig::DOTPlayer *)pObjType;
                switch (player->getState())
                {
                    case DOTPlayer::ST_ALIVE:
                        // display normal player
                        return '8';
                
                    case DOTPlayer::ST_EXITING:
                        // display exiting player
                        return '0' + player->getStateCnt();
                    
                    case DOTPlayer::ST_EXITED:
                        // display the exited player
                        return 'X';
                }
            }
            case BaseDOT::exit:
            {
                SDig::DOTExit *exit = (SDig::DOTExit *)pObjType;
                switch (exit->getState())
                {
                    case DOTExit::ST_CLOSED:
                        // display the closed exit
                        return 'e';
                    case DOTExit::ST_OPEN:
                        // display the opened exit
                        return 'E';
                }
            }

            case BaseDOT::unknown:
            default:                return '?';
        }
    }


    /*!
     * \brief   Print the header
     * \param   pStr
     *  Additional info string inserted in the header
     */
    void drawHeader(const char *pStr = NULL) {
        printw("==== Header (%s) ====\n", (pStr != NULL) ? pStr : "-");
        refresh();
    }

    /*!
     * \brief   Print the footer
     */
    void drawFooter() {
        printw("==== Footer ====\n");
        refresh();
    }

public:
    /*!
     * \brief   Print main menu
     */
    void drawMainMenu()
    {
        // move cursor position to (row, col)
        move(0, 0);
        printw("\n");
        printw("==== Main Menu ====\n");
        printw("\n");
        printw("  s       - Start\n");
        printw("  q       - Exit\n");
        refresh();
    }
    
    
    /*!
     * \brief   Print level start.
     */
    void drawLevelStart()
    {
        // move cursor position to (row, col)
        move(0, 0);
        printw("\n");
        // FIXME: add level number
        printw("==== Level x ====\n");
        printw("\n");
        printw("  s       - Start\n");
        printw("  q       - Got back to main menu\n");
        refresh();
    }
    
    /*!
     * \brief   Print a conclusion after a level ends.
     */
    void drawLevelEnd()
    {
        // move cursor position to (row, col)
        move(0, 0);
        printw("\n");
        // FIXME: add level number
        printw("==== End of Level x ====\n");
        printw("\n");
        printw("  s       - Restart level\n");
        printw("  q       - Got back to main menu\n");
        refresh();
    }


    /*!
     * \brief   Clear the screen
     */
    void clearScreen() {
        clear();
    }


};

}       // namespace

#endif  // _SDIG_TEXT_ENGINE_H_

