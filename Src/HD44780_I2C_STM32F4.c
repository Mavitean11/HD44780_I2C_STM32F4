/*
 * HD44780_I2C_STM32F4.c
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

// Define the position of LCD control bits in i2c data see PC8574 and HDD44780 connection
#define RS_bit ((uint8_t) 0x01)
#define RW_bit ((uint8_t) 0x02)
#define E_bit ((uint8_t) 0x04)
#define BL_bit ((uint8_t) 0x08) // This bit must be one to the backlight to function.

#include <stdint.h>
#include <HD44780_I2C_STM32F4.h>

// Private functions that sends commands
void LCD_SendCMD(I2C_LCD_HandleTypeDef *lcd, char cmd){
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd&0xf0);
    data_l = ((cmd<<4)&0xf0);
    data_t[0] = data_u | E_bit | BL_bit;  //en = 1, rs = 0, rw = 0, BL = 1
  	data_t[1] = data_u | BL_bit;  //en = 0, rs = 0, rw = 0, BL = 1
  	data_t[2] = data_l | E_bit | BL_bit;  //en = 1, rs = 0, rw = 0, BL = 1
  	data_t[3] = data_l | BL_bit;  //en=0, rs=0, rw = 0, BL = 1
  	HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address,(uint8_t *) data_t, 4, 100);
}

// Public functions to access commands described in table 6 of the datasheet
void LCD_CMD_ClearDisplay(I2C_LCD_HandleTypeDef *lcd){
	LCD_SendCMD(lcd, 0x01);
	HAL_Delay(1);
}

void LCD_CMD_ReturnHome(I2C_LCD_HandleTypeDef *lcd){
	LCD_SendCMD(lcd, 0x02);
	HAL_Delay(2);
}

void LCD_CMD_EntryModeSet(I2C_LCD_HandleTypeDef *lcd, LCD_EntryMode entryMode){
	LCD_SendCMD(lcd, entryMode);
	HAL_Delay(1);
}

void LCD_CMD_DisplayControl(I2C_LCD_HandleTypeDef *lcd, LCD_DisplayOnOff displayControl, LCD_CursorOnOff cursorControl, LCD_BlinkingOnOff blinkingControl){
	LCD_SendCMD(lcd, (displayControl | cursorControl | blinkingControl));
	HAL_Delay(1);
}

void LCD_CMD_CursorOrDisplayShift(I2C_LCD_HandleTypeDef *lcd, LCD_CursorOrDisplayShift cursorOrDisplayShift){
	LCD_SendCMD(lcd, cursorOrDisplayShift);
	HAL_Delay(1);
}

void LCD_CMD_FunctionSet(I2C_LCD_HandleTypeDef *lcd, LCD_FunctionSetOptions functionSet){
	LCD_SendCMD(lcd, functionSet);
	HAL_Delay(1);
}

void LCD_CMD_SetCGRAMAddr(I2C_LCD_HandleTypeDef *lcd, uint8_t address){
	address &= 0x3F; // Clear 2 msb since CGRAM has 6 bit address
	address |= 0x40; // Set DB6 as it is a function bit
	LCD_SendCMD(lcd, address);
	HAL_Delay(1);
}

void LCD_CMD_SetDDRAMAddr(I2C_LCD_HandleTypeDef *lcd, uint8_t address){
	address &= 0x7F; // Clear the msb since CGRAM has 6 bit address
	address |= 0x80; // Set DB7 as it is a function bit
	LCD_SendCMD(lcd, address);
	HAL_Delay(1);
}

void LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data){
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u | E_bit | RS_bit  | BL_bit;  //en=1, rs=1, rw = 0, BL = 1
	data_t[1] = data_u | RS_bit | BL_bit;  //en=0, rs=1, rw = 0, BL = 1
	data_t[2] = data_l | E_bit | RS_bit | BL_bit;  //en=1, rs=1, rw = 0, BL = 1
	data_t[3] = data_l | RS_bit | BL_bit;  //en=0, rs=1, rw = 0, BL = 1
	HAL_I2C_Master_Transmit (lcd->hi2c, lcd->address,(uint8_t *) data_t, 4, 100);
}

void LCD_PutCursor(I2C_LCD_HandleTypeDef *lcd, int row, int col){
    switch (row){
        case 0:
            col |= 0x00;
            break;
        case 1:
            col |= 0x40;
            break;
    }

    LCD_CMD_SetDDRAMAddr(lcd, col);
}


void LCD_init(I2C_LCD_HandleTypeDef *lcd){
	// 4 bit initialization as describe in datasheet page 46
	// First 4 communications are 4bit only so we will not use the LCD_SendCMD


	uint8_t initData[2];
	initData[0] = 0x30 | E_bit;
	initData[1] = 0x30;

	// First 3 communications are the same
	HAL_Delay(50);  // wait for >40ms
	HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address,(uint8_t *) initData, 2, 100);
	HAL_Delay(5);  // wait for >4.1ms
	HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address,(uint8_t *) initData, 2, 100);
	HAL_Delay(1);  // wait for >100us
	HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address,(uint8_t *) initData, 2, 100);
	HAL_Delay(10);

	// Data is different for the fourth communication
	initData[0] = 0x20 | E_bit;
	initData[1] = 0x20;

	// Set the 4-bit interface
	HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address,(uint8_t *) initData, 2, 100);  // 4bit mode
	HAL_Delay(10);

	// Now we can start configuring the LCD
	// Display initialization
	LCD_CMD_FunctionSet(lcd, lcd->functionSet); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	LCD_SendCMD(lcd, (DISPLAY_OFF | CURSOR_OFF | BLINKING_OFF)); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	LCD_CMD_ClearDisplay(lcd);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	LCD_CMD_EntryModeSet(lcd, lcd->entryMode); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	LCD_CMD_DisplayControl(lcd, lcd->display, lcd->cursor, lcd->blinking); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void LCD_SendCustomChar(I2C_LCD_HandleTypeDef *lcd, LCD_CustomCharAddress cgram_addr, uint8_t* pattern, LCD_CustomCharType type){
	LCD_CMD_SetCGRAMAddr(lcd, cgram_addr);
	for(int i = 0; i < type; i++){
		LCD_SendData(lcd, *pattern++);
	}
}

void LCD_SendString(I2C_LCD_HandleTypeDef *lcd,char *str)
{
	while (*str) LCD_SendData(lcd, *str++);
}

