/*
 * HD44780_I2C_STM32F4.h
 * Copyright (C) 2020  Marco Vinicio T. Andrade <mvta00@ufmg.br>
 * Version 1.0 - API with the following implemented functions:
 * void lcd_init(I2C_LCD_InitStruct *LCD);
 * void lcd_cmd_clear_display(I2C_LCD_HandleTypeDef *lcd);
 * void lcd_cmd_return_home(I2C_LCD_HandleTypeDef *lcd);
 * void lcd_cmd_entry_mode_set(I2C_LCD_HandleTypeDef *lcd, ENTRY_MODE entryMode);
 * void lcd_cmd_display_control(I2C_LCD_HandleTypeDef *lcd, DISPLAY_CONTROL displayControl, CURSOR_CONTROL cursorControl, BLINKING_CONTROL blinkingControl);
 * void lcd_cmd_cursor_or_display_shift(I2C_LCD_HandleTypeDef *lcd, CURSOR_OR_DISPLAY_SHIFT cursorOrDisplayShift);
 * void lcd_function_set(I2C_LCD_HandleTypeDef *lcd, FUNCTION_SET_OPTION functionSet);
 * void lcd_put_cur(I2C_LCD_HandleTypeDef *lcd, int row, int col);
 * void lcd_send_data(I2C_LCD_HandleTypeDef *lcd, char data);
 * void lcd_send_string(I2C_LCD_HandleTypeDef *lcd,char *str);
 *
 * Based on the i2c-lcd library implementation accessed at
 * https://controllerstech.com/i2c-lcd-in-stm32/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Created on: 11 de sep de 2020
 * Institution: UFMG
 * This API contain functions to provide use of the LCD 16X2 based on the
 * HD44780(https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)
 * LCD driver and controller with I2C communication using the
 * PCF8574(https://www.ti.com/lit/ds/symlink/pcf8574.pdf) I/O expander for I@C bus.
 * The HD44780 and PCF8574 connection is described below:
 * PCF8574		HDD44780
 * P0		->	RS
 * P1		->	R/W
 * P2		->	E
 * P3		->	Something related to LCD backlight
 * P4		->	D4
 * P5		->	D5
 * P6		->	D6
 * P7		->	D7
 */

#ifndef HD44780_I2C_STM32F4_H_
#define HD44780_I2C_STM32F4_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

// Position of control bits in i2c data
#define RS_bit ((uint8_t) 0x01)
#define RW_bit ((uint8_t) 0x02)
#define E_bit ((uint8_t) 0x04)
#define BL_bit ((uint8_t) 0x08) // This bit must be one to the backlight to function.

// Enumerates for setting display options as described in datasheet pages 24-27
enum ENTRY_MODE{
	SHIFT_DISPLAY_INCREMENT = 0x07, // Shift the hole display content to the left when a character is written to DDRAM
	SHIFT_DISPLAY_DECREMENT = 0x05, // Shift the hole display content to the right when a character is written to DDRAM
	MOVE_CURSOR_INCREMENT = 0x06,	// Decrements the DDRAM address by 1 when a character is written
	MOVE_CURSOR_DECREMENT = 0x04    // Decrements the DDRAM address by 1 when a character is written
};
typedef enum ENTRY_MODE ENTRY_MODE;

enum DISPLAY_CONTROL{
    DISPLAY_ON = 0x0C, // Display data on DDRAM
    DISPLAY_OFF = 0x08 // Data remains on DDRAM but is not displayed it on LCD
};
typedef enum DISPLAY_CONTROL DISPLAY_CONTROL;

enum CURSOR_CONTROL{
	CURSOR_ON = 0x0A, // Display a cursor on current DDRAM position
	CURSOR_OFF = 0x08 // Do not display the cursor
};
typedef enum CURSOR_CONTROL CURSOR_CONTROL;

enum BLINKING_CONTROL{
	BLINKING_ON = 0x09, // Blink the current DDRAM position
	BLINKING_OFF = 0x08 // Do not blink current DDRAM position
};
typedef enum BLINKING_CONTROL BLINKING_CONTROL;

enum CURSOR_OR_DISPLAY_SHIFT{
    SHIFT_DISPLAY_RIGHT = 0x0C, // Shift hole display content to the right
	SHIFT_DISPLAY_LEFT = 0x08,  // Shift hole display content to the left
	MOVE_CURSOR_RIGHT = 0x04,   // Move cursor to the right
	MOVE_CURSOR_LEFT = 0x00		// Move cursor to the left
};
typedef enum CURSOR_OR_DISPLAY_SHIFT CURSOR_OR_DISPLAY_SHIFT;

enum FUNCTION_SET_OPTION{
	BITS4_LINES1_5X10DOTS = 0x24, // 4 bit interface. 1 line display. 5X10 font
	BITS4_LINES1_5X8DOTS = 0x20,  // 4 bit interface. 1 line display. 5X8 font
	BITS4_LINES2_5X8DOTS = 0x28   // 4 bit interface. 2 line display. 5X8 font
};
typedef enum FUNCTION_SET_OPTION FUNCTION_SET_OPTION;

// Structs to handle LCD initialization and handler
struct I2C_LCD_HandleTypeDef{
	I2C_HandleTypeDef *hi2c; // I2C interface to connected to the PCF8574
	uint8_t address; //I2C address of the PCF8574 that controls the LCD
};
typedef struct I2C_LCD_HandleTypeDef I2C_LCD_HandleTypeDef;

struct I2C_LCD_InitStruct{
	I2C_LCD_HandleTypeDef *lcd;
	FUNCTION_SET_OPTION functionSet;
	ENTRY_MODE entryMode;
	DISPLAY_CONTROL displayControl;
	CURSOR_CONTROL cursorControl;
	BLINKING_CONTROL blinkingControl;
};
typedef struct I2C_LCD_InitStruct I2C_LCD_InitStruct;

void lcd_init(I2C_LCD_InitStruct *LCD); // initialize lcd
void lcd_cmd_clear_display(I2C_LCD_HandleTypeDef *lcd); // clear lcd display and sets cursor to 0,0
void lcd_cmd_return_home(I2C_LCD_HandleTypeDef *lcd); // set cursor to 0,0
void lcd_cmd_entry_mode_set(I2C_LCD_HandleTypeDef *lcd, ENTRY_MODE entryMode); // set entry mode of the LCD
void lcd_cmd_display_control(I2C_LCD_HandleTypeDef *lcd, DISPLAY_CONTROL displayControl, CURSOR_CONTROL cursorControl, BLINKING_CONTROL blinkingControl); // configure display, cursor and blinking
void lcd_cmd_cursor_or_display_shift(I2C_LCD_HandleTypeDef *lcd, CURSOR_OR_DISPLAY_SHIFT cursorOrDisplayShift); // set display behaviour on receivieng a character
void lcd_function_set(I2C_LCD_HandleTypeDef *lcd, FUNCTION_SET_OPTION functionSet); // set display interface length, lines, and char format
void lcd_put_cur(I2C_LCD_HandleTypeDef *lcd, int row, int col); // put cursor in row, col postion
void lcd_send_data(I2C_LCD_HandleTypeDef *lcd, char data); // sent data to DDRAM or CGRAM
void lcd_send_string(I2C_LCD_HandleTypeDef *lcd,char *str);
void lcd_send_custom_char(I2C_LCD_HandleTypeDef *lcd, uint8_t cgram_addr, uint8_t* pattern);

#endif /* HD44780_I2C_STM32F4_H_ */
