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

#include "lm75b.h"

#define LM75B_TEMP_ADDR  0x00
#define LM75B_CONF_ADDR  0x01
#define LM75B_TOS_ADDR   0x02
#define LM75B_THYST_ADDR 0x03

/*
  Concerning the read operation on LM75B registers, we need to first write
  the "pointer byte" of the LM75B, i.e. set the internal pointer on the
  address of the register to be read/written. Then, we need to send a RESTART
  condition and send a read request to receive one or more bytes of data.

  Here is the I2C frame's look:
  Master: |S|.|.|.|.|.|.|D|w| |.|.|.|.|.|.|.|P| |R|
  Slave:                     A                 A
  Master:   |.|.|.|.|.|.|D|r| |d|d|d|d|d|d|d|d| (A | NA SP)
  Slave                      A                 

  S = Start condition, D = Slave device address, (N)A = (Not) Acknowledge
  R = Restart condition, SP = Stop condition, r/w = Read/Write bit.
 */

uint8_t libboard_lm75b_init()
{
  rflpc_i2c_init(LM75B_I2C_PORT, RFLPC_I2C_MODE_MASTER, 0);
}

int16_t libboard_lm75b_get_temp()
{
  uint8_t addr = LM75B_TEMP_ADDR;
  uint8_t r[2] = { 0, 0 };
  uint16_t temp = 0;

  /* Write pointer byte, but RESTART instead of STOP at the end. */
  if (rflpc_i2c_write(LM75B_I2C_PORT, LM75B_I2C_ADDR, addr, 1, 0))
    return 0xFFFF;
  /* Read two bytes incoming from slave, then STOP the transmission */
  if (rflpc_i2c_read(LM75B_I2C_PORT, LM75B_I2C_ADDR, &r, 2, 1))
    return 0xFFFF;

  /* Temperature is 11 bits long, and stored at MSBs. We first need to shift
     the value, and then, apply the following formula :
         If temp MSB (bit 11) = 0,
	    T(°C) = temp x 0.125
	 else
	    T(°C) = -(2's complement of temp) x 0.125
  */
  temp = ((r[0] << 8) | (r[1] & ~(0x31))) >> 5;
  if (temp & 0x400)
    temp = ~temp + 1;
  temp = temp >> 3; /* For now, just divide by 8 and store resulting integer */

  return temp;
}
