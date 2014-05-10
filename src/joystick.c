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
*/

#include <rflpc17xx/rflpc17xx.h>

#include "joystick.h"

joystick_state_t joystick_state = RELEASED;

#define JOYSTICK_UP_BIT     (1 << 23) /* DIP15 <=> P0_23 */
#define JOYSTICK_DOWN_BIT   (1 << 17) /* DIP12 <=> P0_17 */
#define JOYSTICK_LEFT_BIT   (1 << 15) /* DIP13 <=> P0_15 */
#define JOYSTICK_RIGHT_BIT  (1 << 24) /* DIP16 <=> P0_24 */
#define JOYSTICK_CENTER_BIT (1 << 16) /* DIP14 <=> P0_16 */

static rflpc_irq_handler_t _handler = NULL;

rflpc_irq_handler_t joystick_eint3_handler()
{
  rflpc_irq_global_disable();

  /* JOYSTICK_UP */
  if (LPC_GPIOINT->IO0IntStatR & JOYSTICK_UP_BIT) {
    joystick_state = UP;
    goto EXIT_HANDLER;
  }
  else if (LPC_GPIOINT->IO0IntStatF & JOYSTICK_UP_BIT) {
    joystick_state = RELEASED;
    goto EXIT_HANDLER;
  }

  /* JOYSTICK_DOWN */
  if (LPC_GPIOINT->IO0IntStatR & JOYSTICK_DOWN_BIT) {
    joystick_state = DOWN;
    goto EXIT_HANDLER;
  }
  else if (LPC_GPIOINT->IO0IntStatF & JOYSTICK_DOWN_BIT) {
    joystick_state = RELEASED;
    goto EXIT_HANDLER;
  }

  /* JOYSTICK_LEFT */
  if (LPC_GPIOINT->IO0IntStatR & JOYSTICK_LEFT_BIT) {
    joystick_state = LEFT;
    goto EXIT_HANDLER;
  }
  else if (LPC_GPIOINT->IO0IntStatF & JOYSTICK_LEFT_BIT) {
    joystick_state = RELEASED;
    goto EXIT_HANDLER;
  }

  /* JOYSTICK_RIGHT */
  if (LPC_GPIOINT->IO0IntStatR & JOYSTICK_RIGHT_BIT) {
    joystick_state = RIGHT;
    goto EXIT_HANDLER;
  }
  else if (LPC_GPIOINT->IO0IntStatF & JOYSTICK_RIGHT_BIT) {
    joystick_state = RELEASED;
    goto EXIT_HANDLER;
  }

  /* JOYSTICK_CENTER */
  if (LPC_GPIOINT->IO0IntStatR & JOYSTICK_CENTER_BIT) {
    joystick_state = CENTER;
    goto EXIT_HANDLER;
  }
  else if (LPC_GPIOINT->IO0IntStatF & JOYSTICK_CENTER_BIT) {
    joystick_state = RELEASED;
    goto EXIT_HANDLER;
  }

 EXIT_HANDLER:
  if (_handler != NULL)
    _handler();
  
  /* Clear pending interrupts for joysticks */
  LPC_GPIOINT->IO0IntClr =
    (JOYSTICK_UP_BIT | JOYSTICK_DOWN_BIT | JOYSTICK_LEFT_BIT
     | JOYSTICK_RIGHT_BIT | JOYSTICK_CENTER_BIT);

  rflpc_irq_global_enable();
}

void libboard_joystick_init(rflpc_irq_handler_t handler)
{
  /* Initialize joystick's pins as GPIO inputs */
  rflpc_pin_set(MBED_DIP12, 0, RFLPC_PIN_MODE_RESISTOR_PULL_DOWN, 0);
  rflpc_pin_set(MBED_DIP13, 0, RFLPC_PIN_MODE_RESISTOR_PULL_DOWN, 0);
  rflpc_pin_set(MBED_DIP14, 0, RFLPC_PIN_MODE_RESISTOR_PULL_DOWN, 0);
  rflpc_pin_set(MBED_DIP15, 0, RFLPC_PIN_MODE_RESISTOR_PULL_DOWN, 0);
  rflpc_pin_set(MBED_DIP16, 0, RFLPC_PIN_MODE_RESISTOR_PULL_DOWN, 0);

  /* Set RE interrupts */
  LPC_GPIOINT->IO0IntEnR = 
    (JOYSTICK_UP_BIT | JOYSTICK_DOWN_BIT | JOYSTICK_LEFT_BIT
     | JOYSTICK_RIGHT_BIT | JOYSTICK_CENTER_BIT);
  
  /* Set FE interrupts */
  LPC_GPIOINT->IO0IntEnF =
    (JOYSTICK_UP_BIT | JOYSTICK_DOWN_BIT | JOYSTICK_LEFT_BIT
     | JOYSTICK_RIGHT_BIT | JOYSTICK_CENTER_BIT);

  /* Set irq handler */
  rflpc_irq_set_handler(EINT3_IRQn, joystick_eint3_handler);

  /* Set additionnal handler if needed */
  _handler = handler;

  /* Enable EINT3 */
  rflpc_irq_enable(EINT3_IRQn);
}

void libboard_joystick_set_handler(rflpc_handler_t handler)
{
  _handler = handler;
}
