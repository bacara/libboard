/* This file is part of libboard, originally written by Christophe Bacara. You
 * should find the original repository at https://github.com/bacara/libboard.
 *
 * libboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libboard.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
  Author: Christophe Bacara <christophe.bacara@etudiant.univ-lille1.fr>
  Created: <2013-11-18 16:23:09 (bacara)>
*/

#ifndef __LIBBOARD_JOYSTICK_H__
#define __LIBBOARD_JOYSTICK_H__

/** Joystick state representation. */
typedef enum libboard_joystick_state_e {
  RELEASED = 0, LEFT, RIGHT, UP, DOWN, CENTER
} libboard_joystick_state_t;

/** Current state of joystick */
extern libboard_joystick_state_t joystick_state;

/** Initializes the joystick handling.
 * @param handler Pointer to a function handler for user operations.
 * @note Once initialized, any state change on the joystick will generates an
 *       interrupt and calling internal handler which set the joystick_state
 *       variable. If the handler param is set, the pointed-to function will be
 *       called AFTER the internal handler.
 */
void libboard_joystick_init(rflpc_irq_handler_t handler);

/** Set the user handler for joystick interruptions.
 * @param handler Pointer to a function handler for user operations.
 * @note Once called, the specified handler will erase any other handler
 *       set before using this function or the initialization one. This can be
 *       used to set handler on NULL, removing this way any user handler call.
 */
void libboard_joystick_set_handler(rflpc_irq_handler_t handler);

#endif /* __LIBBOARD_JOYSTICK_H__ */
