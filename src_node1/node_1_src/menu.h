/**
 * @file menu.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the menu system(UI).
 */


#ifndef MENU_H
#define MENU_H

#include <avr/io.h>
#include "joystick.h"



/**
 * @defgroup PRINTING_CONSTANTS Constants for knowing where to start printing.
 *
 * @{
 */

/** Start colon for the printing of the arrow. */
#define ARROW_COL 20
/** Start colon for the printing of menu titles. */
#define TITLE_COL 12
/** Start colon for the printing of sub-menu titles. */
#define CHILD_COL 32

typedef struct MENU MENU_t;
typedef struct MENU_arrow MENU_arrow_t;


/**
 * @brief Structures representing a menu object.
 *
 */
struct MENU
{
	char* menu_title; /**< The title of the menu object. */
	MENU_t* parent; /**< The parent of the menu object. */
  MENU_t** child_array; /**< Array with the children of the menu object. */

};



/**
 * @brief Structures representing the arrow object.
 *
 */
struct MENU_arrow
{
  int arrow_page; /**< The page where the arrow is currently located. */
  JOYSTICK_direction_t prev_dir; /**< The previous direction of the arrow. */
  JOYSTICK_position_t prev_pos; /**< The previous position of the arrow. */
};



/*! This is an enum with the different states in the program*/
typedef enum
{
	MENU = 0, /**< State where it is possible to navigate through the menu system. */
	PLAY_PONG = 1, /**< State where it is possible to play pong. */
  GAMEOVER = 2, /**< State when the game is lost, resets before returning back to main menu (MENU) . */
}MENU_game_state_t;





/**
 * @brief Creates a pointer to a menu object and sets properties according to the input parameters.
 * 
 * @param title Specify the title of the menu object.
 *
 * @param parent Specify thye parent of the menu object.
 *
 * @param child_size Specify the length of the child array, ie. amount of children.
 *
 * @return MENU_t* returns pointer to a menu object.
 */
MENU_t* MENU_set_new_menu(char* title, MENU_t* parent, uint8_t child_size);


/**
 * @brief Assigns a child to parent menu object.
 * 
 * @param *menu Pointer to the menu object that will be assigned the child @p child.
 *
 * @param *child Pointer to the menu object that will become its parent.
 *
 * @param index Which place che child has in the parents child array.
 */
void MENU_set_child(MENU_t *menu, MENU_t *child, uint8_t index);


/**
 * @brief Prints the menu object that is pointed to by @p *menu on the OLED screen.
 * 
 * @param *menu Pointer to the menu object that will be printed to the OLED screen.
 */
void MENU_print_menu(volatile MENU_t *menu);


/**
 * @brief Initializes the menu and menu organization.
 */
void MENU_init_menus(void);


/**
 * @brief  Creates, initializes and prints the arrow object @p *arrow points to.
 * 
 * @param *arrow Pointer to the arrow that will be created.
 */
void MENU_arrow_creation(MENU_arrow_t *arrow);


/**
 * @brief Uses the joystick position to find
 * 
 * @param[in] channel Which channel to read from.
 * @return uint8_t returns the data on the chosen channel.
 */
//void MENU_arrow_get_position(MENU_arrow_t *arrow);


/**
 * @brief Decides where the arrow is moved depending on the joystick position.
 * 
 * @param *arrow Pointer to the arrow object that moves.
 *
 * @return JOYSTICK_direction_t returns the direction of the arrow objrect.
 */
JOYSTICK_direction_t MENU_move_arrow(MENU_arrow_t *arrow);


/**
 * @brief Reads data on channel @p channel from the ADC.
 * 
 * @param *arrow Pointer to the arrow object that moves.
 *
 * @param page The page where the arrow is currently located.
 *
 * @return int returns "1" if the arrow is allowed to move in its direction, "0" otherwise.
 */
int MENU_set_arrow(MENU_arrow_t *arrow, uint8_t page);


/**
 * @brief Selects the menu located on the page where the arrow is located.
 * 
 * @param *arrow Pointer to the arrow object that moves.
 */
void MENU_select_menu(MENU_arrow_t *arrow);


/**
 * @brief Checks the state of the menu.
 * 
 * @return uint8_t returns state of the menu.
 */
uint8_t MENU_start_game();


/**
 * @brief Configures the game over state.
 */
void MENU_game_over();



#endif
