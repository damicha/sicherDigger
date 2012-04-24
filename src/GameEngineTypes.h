/*! ****************************************************************************
 *
 * \file    GameEngineTypes.h
 * \brief   Type definitions used by the GameEngine class
 * 
 * \author  damicha of defect
 * \date    2012 
 *
 * \details
 *  This definitions are used to prevent circular dependencies. This could be
 *  happen if the defines are made within a class.
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_GAME_ENGINE_TYPES_H_
#define _SDIG_GAME_ENGINE_TYPES_H_


namespace SDig {
namespace GameEngineTypes {
    /*!
     * \brief    button type
     *
     * Internal representation of pressed keys/buttons.
     */
    enum Button {
        BT_NONE,    //!< no key identifier
        BT_UP,      //!< up key
        BT_DOWN,    //!< down key
        BT_LEFT,    //!< left key
        BT_RIGHT,   //!< right key
        BT_A,       //!< A button
        BT_B,       //!< B button
        BT_START,   //!< start button
        BT_SELECT   //!< select button
    };
}   // namespace GameEngineTypes
}   // namespace SDig

#endif // _SDIG_GAME_ENGINE_TYPES_H_

