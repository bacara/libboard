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

#ifndef __LIBBOARD_C12832_H__
#define __LIBBOARD_C12832_H__

/*
 * C12832 Library Operating Modes :
 * - OUTPUT:   Use the LCD screen display as a classical output stream.
 *             The function "lcd_putchar()" can be used into any output
 *             formatting function like printf().
 * - DRAW:     Use the LCD screen display as a drawing display. The library 
 *             allows to get/set any pixel value for example.
 * - PROGRESS: Use the LCD screen display as a progress bar display.
 */
typedef enum lcd_mode_e {
  OUTPUT, DRAW, PROGRESS
} lcd_mode_t;

/* LCD screen dimensions */
#define LCD_WIDTH     128
#define LCD_HEIGHT    32

/* Initialize the C12832 LCD screen for use */
void lcd_init();
/* Refresh the screen display according to buffer */
void lcd_refresh();
/* Reset the screen display */
void lcd_reset();
/* Change LCD screen library's operating mode */
void lcd_set_mode(lcd_mode_t mode);

/******************************/
/******    OUTPUT MODE    *****/
/******************************/
/* Put char at buffer's cursor current position then move it forward */
int lcd_putchar(int c);
/* Same as putchar, but highlight text */
int lcd_putchar_highlighted(int c);

/******************************/
/******     DRAW MODE     *****/
/******************************/
typedef enum lcd_line_e {
  HORIZONTAL, VERTICAL
} lcd_line_t;
typedef enum lcd_fill_mode_e {
  FILL, BLANK
} lcd_fill_mode_t;
/* Return any pixel value. Returns -1 in case of errors. */
char lcd_get_pixel(unsigned x, unsigned y);
/* Set any pixel value. */
void lcd_set_pixel(unsigned x, unsigned y, unsigned char value);
/* Draw a right line from (x,y) with specified length. */
void lcd_draw_line(unsigned x, unsigned y, unsigned char len, lcd_line_t kind);
/* Draw a rectangle with (x,y) as upper-left corner. */
void lcd_draw_rectangle(unsigned x, unsigned y, 
			unsigned width, unsigned height,
			lcd_fill_mode_t fillmode);

/******************************/
/******   PROGRESS MODE   *****/
/******************************/
/* Set the progress length (Max: LCD_WIDTH) */
void lcd_set_progress(unsigned char len);

#endif /* __LIBBOARD_C12832_H__ */
