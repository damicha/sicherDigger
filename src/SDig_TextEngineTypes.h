#ifndef _SDIG_TEXT_ENGINE_TYPES_H_
#define _SDIG_TEXT_ENGINE_TYPES_H_

/*
 * This definitions are used to prevent circlary dependencies. This could be
 * happen if the defines are made within a class.
 */


namespace SDig {

namespace TextEngineTypes {

    /*!
     * \brief    button type
     *
     * Internal representation of pressed keys/buttons.
     * FIXME: move to a common SDig HW class
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

}   // namespace Button
}   // namespace SDig

#endif // _SDIG_TEXT_ENGINE_TYPES_H_

