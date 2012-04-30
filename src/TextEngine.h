/*! ****************************************************************************
 *
 * \file    TextEngine.h
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

#ifndef _SDIG_TEXT_ENGINE_H_
#define _SDIG_TEXT_ENGINE_H_



#include "ObjField/Field.h"
#include "DOT/Base.h"
#include "DOT/DOTs.h"
#include "SDig_TimeEngine.h"
#include "LevelEngine.h"
#include "GameEngineTypes.h"

#include <stdio.h>
#include <ncurses.h>

#include <string>
#include <sstream>


using namespace std;


/*!
 * \namespace   SDig
 * \brief   Namespace of the sicherDigger project.
 *
 * FIXME: move SDig namespace description to a central header file: SDig.h
 */
namespace SDig {

    
/*!
 * \class   TextEngine 
 * \brief
 *  Provides functions to get the user input and to do a ASCII text output
 *  of the game field.
 */
class TextEngine
{

/* ======== attributes ======== */    
private:
    /*! Counts the number of instances of this class. It's used to init the
     *  ncurses library if the first TextEngine instance is created.
     *  The ncurses library will be closed if the last TextEngine instance
     *  is deleted. */
    static int mInstanceCounter;

public:

/* ======== init functions ======== */
    
    /* Constructor */
    TextEngine();
    
    /* Destructor */
    ~TextEngine();

    
    /* Initialize ncurses */
    void initNCurses(void);
    
    /* Stop ncurses */
    void stopNCurses(void);
   

/* ======== input functions ======== */

    /* Get key from input buffer and map it to the internal button representation. */
    GameEngineTypes::Button getButton(void);


/* ======== output/draw functions ======== */
    
    /*!
     * \brief   Prints the current statistics and content of a level engine
     *  to the console
     * \param[in] *pLevel   Reference to the level engine and its data
     */
    void drawLevel(const LevelEngine *pLevel)
    {
        /* create string with timing information */
        const int str_len = 32;
        char str[str_len];
        snprintf(str, str_len, "T:%04d S:%02d/%02d",
                 pLevel->getTimeCnt(), pLevel->getSandCnt(), pLevel->getRequiredSand());
        
        /* display level */
        drawField(pLevel->getField(), str);
    }

private:
    /*!
     * \brief   Print the content of the object field to the console
     * \param   pField
     *  Reference to the object field to print.
     * \param   pHeaderString
     *  String used within the header
     */
    void drawField(const ObjField::Field *pField,
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
    void drawFieldData(const ObjField::Field *pField);


    /*!
     * \brief   Print the content of the object field as a list to the console
     * \param   pField
     *  Reference to the object field to print
     */
    void drawFieldList(const ObjField::Field *pField)
    {
        printw("Field dimensions: (x: %d, y: %d)\n",
               pField->getSizeX(), pField->getSizeY());

        for (int i = 0; i < pField->getSizeX()*pField->getSizeY(); i++) {
            printw("position: %2d, data: %s\n", i, pField->getEntry(i)->str().c_str());
        }
        refresh();
    }


    /*!
     * \brief   Draw debug infos of the time engine
     */
    void drawDebugInfo(SDig::TimeEngine *pTimeEngine)
    {
        printw("%s", pTimeEngine->getDebugInfo().c_str());
        refresh();
    }


    /*!
     * \brief   Gets a character to print that presents the type of the data object.
     * \param   pObjType
     *  Address of data object.
     */
    char getSymbol(DOT::Base *pObjType)
    {
        switch (pObjType->getType())
        {
            case DOT::T_EMPTY:  return ' '; 
            case DOT::T_SAND:   return '.';
            case DOT::T_WALL:   return '#';
            case DOT::T_STONE:  return 'O';
            case DOT::T_PLAYER:
            {
                DOT::Player *player = (DOT::Player *)pObjType;
                switch (player->getState())
                {
                    case DOT::Player::ST_ALIVE:
                        // display normal player
                        return '8';
                
                    case DOT::Player::ST_EXITING:
                        // display exiting player
                        return '0' + player->getStateCnt();
                    
                    case DOT::Player::ST_EXITED:
                        // display the exited player
                        return 'X';
                }
            }
            case DOT::T_EXIT:
            {
                DOT::Exit *exit = (DOT::Exit *)pObjType;
                switch (exit->getState())
                {
                    case DOT::Exit::ST_CLOSED:
                        // display the closed exit
                        return 'e';
                    case DOT::Exit::ST_OPEN:
                        // display the opened exit
                        return 'E';
                }
            }

            case DOT::T_UNKNOWN:
            default:            return '?';
        }
    }


/* ==== draw screen an menu functions ==== */
private:
    /* Draw the level header */
    void drawHeader(const char *pStr = NULL);

    /* Draw the level footer */
    void drawFooter();

public:
    /* Draw the main menu */
    void drawMainMenu();
    
    /* Draw the level select menu. */
    void drawLevelSelectMenu(int pLevelNr);
    
    /* Draw the level start Screen. */
    // FIXME: check how to use string class (normal, as * or as &)
    void drawLevelStartScreen(string pLevelName, string pLevelInfo,
                              int pReqSand, int pTimeLimit);
    
    /* Print a conclusion after a level ends. */
    void drawLevelEndScreen(string pLevelName,
                            LevelEngine::LevelEndReason pLevEndReason,
                            int pEatenSand, int pReqSand, int pTimeLeft);

    /*!
     * \brief   Clear the screen
     */
    void clearScreen() {
        clear();
    }


};

}       // namespace

#endif  // _SDIG_TEXT_ENGINE_H_

