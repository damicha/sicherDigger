/*! ****************************************************************************
 *
 * \file    TextEngine.cpp
 * \brief   Displays the field objects as text on the console
 * 
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \details
 *  The TextEngine class is implemented that provides functions to get the
 *  user input and to do a ASCII text output of the game field.
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "TextEngine.h"
#include "ObjField/Field.h"
#include "LevelEngine.h"

using namespace SDig;

/* set default value for the instance counter */
int TextEngine::mInstanceCounter = 0;



/* ==========================================================================
 * init functions
 * ========================================================================== */

/*!
 * \brief   Constructor
 *
 * Initializes ncurses if the first instance of this class will be created
 */
TextEngine::TextEngine()
{
    if (mInstanceCounter == 0) {
        /* init ncurses */
        initNCurses();
        /* increment instance counter */
        mInstanceCounter++;
    } 
}

/*!
 * \brief   Destructor
 *
 * Stops ncurses if the last instance of this class will be destroyed
 */
TextEngine::~TextEngine()
{
    /* decrement instance counter */
    mInstanceCounter--;
    if (mInstanceCounter == 0) {
        /* release ncurses */
        stopNCurses();
    } 
}


/*!
 * \brief   Initialize ncurses.
 */
void TextEngine::initNCurses(void)
{
    /* start curses mode */
    initscr();

    /* configure the behavior of the getchar() function */
    noecho();               // getchar() doesn't echo the get character
    nodelay(stdscr, true);  // getchar()'s non blocking mode
    cbreak();               // disable line buffering
    keypad(stdscr, true);   // enable the keypad to get its keys
}


/*!
 * \brief   Stop ncurses.
 */
void TextEngine::stopNCurses(void)
{
    /* End curses mode */
    endwin();
}



/* ==========================================================================
 * input functions
 * ========================================================================== */

/*!
 * \brief   Get key from input buffer and map it to the internal button
 *  representation.
 * \return  Recognized button.
 */
TextEngineTypes::Button TextEngine::getButton(void)
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



/* ==========================================================================
 * output/draw functions
 * ========================================================================== */

/*!
 * \brief   Print the content of the object field as an array to the console
 * \param   pField
 *  Reference to the object field to print
 */
void TextEngine::drawFieldData(const ObjField::Field *pField)
{
    for (int y = 0; y < pField->getSizeY(); y++)
    {
        for (int x = 0; x < pField->getSizeX(); x++)
        {
            DataObject *dataObj = pField->getEntry(x, y)->getData();  
            char c = getSymbol(dataObj->getTypeObject());
            printw("%c ", c);
        }
        printw("\n");
    }
    refresh();
}


/* ==========================================================================
 * draw screen an menu functions
 * ========================================================================== */

/*!
 * \brief   Draw the level header.
 * \param[in] pStr - Additional info string inserted in the header.
 */
void TextEngine::drawHeader(const char *pStr) {
    printw("==== Header (%s) ====\n", (pStr != NULL) ? pStr : "-");
    refresh();
}


/*!
 * \brief   Draw the level footer.
 */
void TextEngine::drawFooter() {
    printw("==== Footer ====\n");
    refresh();
}


/*!
 * \brief   Draw the main menu.
 */
void TextEngine::drawMainMenu()
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
 * \brief   Draw level select menu.
 * \param[in] pSel  Selected level number.
 */
void TextEngine::drawLevelSelectMenu(int pLevelNr)
{
    // move cursor position to (row, col)
    move(0, 0);
    printw("\n");
    printw("==== Level Select ====\n");
    printw("\n");
    printw("    Level <-%02d-> \n", pLevelNr);
    printw("\n");
    printw("  s       - Start\n");
    printw("  q       - Got back to main menu\n");
    refresh();
}


/*!
 * \brief   Draw the level start Screen with level information.
 * \param[in] pLevelNr      Level number.
 * \param[in] pReqSand      Required amount of sand.
 * \param[in] pTimeLimit    Level's time limit.
 */
void TextEngine::drawLevelStartScreen(int pLevelNr, int pReqSand, int pTimeLimit)
{
    // FIXME: add level information as a string copied from level config
    // move cursor position to (row, col)
    move(0, 0);
    printw("\n");
    printw("==== Level %02d ====\n", pLevelNr);
    printw("\n");
    printw(" Required Sand: %d\n", pReqSand);
    printw(" Time Limit:    %d\n", pTimeLimit);
    printw("\n");
    printw("\n");
    printw("  s       - Start\n");
    refresh();
}


/*!
 * \brief   Print the conclusion after the level ends.
 */
void TextEngine::drawLevelEndScreen(int pLevelNr, LevelEngine::LevelEndReason pLevEndReason,
                                    int pEatenSand, int pReqSand, int pTimeLeft)
{
    // move cursor position to (row, col)
    move(0, 0);
    printw("\n");
    printw("==== End of Level %02d ====\n", pLevelNr);
    printw("\n");

    /* evaluate level end reason and draw text message */
    switch (pLevEndReason)
    {
        case LevelEngine::LER_SUCCESS:
            printw("  - SUCCESS! -\n");
            printw("  - You entered the exit -\n");
            break;
        case LevelEngine::LER_TIME_UP:
            printw("  - Failed! -\n");
            printw("  - Time is up -\n");
            break;
    }

    printw("\n");
    printw(" Eaten Sand: %d/%d\n", pEatenSand, pReqSand);
    printw(" Time Left:  %d\n", pTimeLeft);
    printw("\n");
    printw("\n");
    printw("  s       - Restart level\n");
    printw("  q       - Got back to main menu\n");
    refresh();
}

