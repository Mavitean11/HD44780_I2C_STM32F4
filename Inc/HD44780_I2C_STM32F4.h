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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HD44780_I2C_STM32F4_H_
#define HD44780_I2C_STM32F4_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdint.h>

// Enumerates for setting display options as described in datasheet pages 24-27
typedef enum{
	SHIFT_DISPLAY_INCREMENT = 0x03U, // Shift the hole display content to the left when a character is written to DDRAM
	SHIFT_DISPLAY_DECREMENT = 0x01U, // Shift the hole display content to the right when a character is written to DDRAM
	MOVE_CURSOR_INCREMENT = 0x02U,	// Decrements the DDRAM address by 1 when a character is written
	MOVE_CURSOR_DECREMENT = 0x00U    // Decrements the DDRAM address by 1 when a character is written
} LCD_EntryMode;

typedef enum{
	DISPLAY_OFF = 0x00U, // Data on DDRAM is not displayed on LCD. You can still write to DDRAM
	DISPLAY_ON_CURSOR_OFF_BLINKING_OFF = 0x04U, // Display data on LCD
	DISPLAY_ON_CURSOR_OFF_BLINKING_ON = 0x05U,	// Display data and blink current DDRAM address
	DISPLAY_ON_CURSOR_ON_BLINKING_OFF = 0x06U, // Display data and a cursor current DDRAM address
	DISPLAY_ON_CURSOR_ON_BLINKING_ON = 0x07U // Display data with cursor and blink effect
} LCD_DisplayControlOptions;

typedef enum{
    SHIFT_DISPLAY_RIGHT = 0x0CU, // Shift hole display content to the right
	SHIFT_DISPLAY_LEFT = 0x08U,  // Shift hole display content to the left
	MOVE_CURSOR_RIGHT = 0x04U,   // Move cursor to the right
	MOVE_CURSOR_LEFT = 0x00U     // Move cursor to the left
} LCD_CursorOrDisplayShift;

typedef enum{
	BITS4_LINES1_5X10DOTS = 0x04U, // 4 bit interface. 1 line display. 5X10 font
	BITS4_LINES1_5X8DOTS = 0x00U,  // 4 bit interface. 1 line display. 5X8 font
	BITS4_LINES2_5X8DOTS = 0x08U   // 4 bit interface. 2 line display. 5X8 font
} LCD_FunctionSetOptions;

typedef enum{
	BACKLIGHT_ON = 0x08U,
	BACKLIGHT_OFF = 0x00U,
} LCD_BacklightOnOff;

typedef enum{
	CUSTOM_CHAR_5X8_1 = 0x00U,
	CUSTOM_CHAR_5X8_2 = 0x01U,
	CUSTOM_CHAR_5X8_3 = 0x02U,
	CUSTOM_CHAR_5X8_4 = 0x03U,
	CUSTOM_CHAR_5X8_5 = 0x04U,
	CUSTOM_CHAR_5X8_6 = 0x05U,
	CUSTOM_CHAR_5X8_7 = 0x06U,
	CUSTOM_CHAR_5X8_8 = 0x07U,
	CUSTOM_CHAR_5X10_1 = 0x00U,
	CUSTOM_CHAR_5X10_2 = 0x01U,
	CUSTOM_CHAR_5X10_3 = 0x02U,
	CUSTOM_CHAR_5X10_4 = 0x03U,
} LCD_CustomCharAddress;

typedef enum{
	CHAR_5X8 = 0x08U,
	CHAR_5X10 = 0x0AU,
} LCD_CustomCharType;

// Struct to handle LCD
typedef struct{
	I2C_HandleTypeDef *hi2c; // I2C interface to connected to the PCF8574
	uint8_t address; //I2C address of the PCF8574 that controls
	LCD_BacklightOnOff backlight;
} I2C_LCD_HandleTypeDef;

// Struct to handle LCD initialization
typedef struct{
	I2C_LCD_HandleTypeDef *lcdHandler;
	LCD_FunctionSetOptions functionSet;
	LCD_EntryMode entryMode;
	LCD_DisplayControlOptions displayMode;
} I2C_LCD_InitTypeDef;

void LCD_init(I2C_LCD_InitTypeDef *LCD); // initialize lcd
void LCD_CMD_ClearDisplay(I2C_LCD_HandleTypeDef *lcd); // clear lcd display and sets cursor to 0,0
void LCD_CMD_ReturnHome(I2C_LCD_HandleTypeDef *lcd); // set cursor to 0,0
void LCD_CMD_EntryModeSet(I2C_LCD_HandleTypeDef *lcd, LCD_EntryMode entryMode); // set entry mode of the LCD
void LCD_CMD_DisplayControl(I2C_LCD_HandleTypeDef *lcd, LCD_DisplayControlOptions displayMode); // configure display, cursor and blinking
void LCD_CMD_CursorOrDisplayShift(I2C_LCD_HandleTypeDef *lcd, LCD_CursorOrDisplayShift cursorOrDisplayShift); // set display behaviour on receivieng a character
void LCD_CMD_FunctionSet(I2C_LCD_HandleTypeDef *lcd, LCD_FunctionSetOptions functionSet); // set display interface length, lines, and char format
void LCD_PutCursor(I2C_LCD_HandleTypeDef *lcd, int row, int col); // put cursor in row, col postion
void LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data); // send data to DDRAM or CGRAM
void LCD_SendString(I2C_LCD_HandleTypeDef *lcd,char *str); // send string data to display sequentially
void LCD_SendCustomChar(I2C_LCD_HandleTypeDef *lcd, LCD_CustomCharAddress cgram_addr, uint8_t* pattern, LCD_CustomCharType type); // send custom character to display
void LCD_Backlight(I2C_LCD_HandleTypeDef *lcd, LCD_BacklightOnOff backlight);

#endif /* HD44780_I2C_STM32F4_H_ */
