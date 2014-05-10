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

/*
  This file allows operations with the NXP LM75B "Digital temperature sensor
  and thermal watchdog". Product data sheet by NXP should be located in the
  datasheet folder of this library. Hardware manipulation is made by the I2C
  driver of the RFLPC library.
*/

#ifndef __LIBBOARD_LM75B_H__
#define __LIBBOARD_LM75B_H__

#include <rflpc17xx/drivers/i2c.h>

/* Default configuration for mbed application board. You should verify these
 * values match your own configuration. */
#define LM75B_I2C_PORT   RFLPC_I2C_PORT2
#define LM75B_I2C_ADDR   0x90

/** Initializes the I2C driver on the port defined by LM75B_I2C_PORT.
 * @return If initialization was successful, returns 0. Returns -1 otherwise.
 */
uint8_t libboard_lm75b_init();

/** Get temperature from LM75B thermometer.
 * @return If successful, return the current temperature in Celsius degrees.
 *         Returns 0xFFFF otherwise.
 */
int16_t libboard_lm75b_get_temp();

#endif /* __LIBBOARD_LM75B_H__ */
