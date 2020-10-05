/*
 * examples.c
 *
 *  Created on: 2 de out de 2020
 *      Author: mvta0
 */

#include "examples.h"


void EX_HelloWorld(I2C_LCD_HandleTypeDef *lcd){
	// Setup Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_OFF);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	// Send smile character to display
	uint8_t smile[8] = {0x00, 0x0A, 0x0A, 0x00, 0x11, 0x1B, 0x0E, 0x00};
	LCD_SendCustomChar(lcd, CUSTOM_CHAR_5X8_1, (uint8_t*) smile, CHAR_5X8);

	// Write Hello World message on display
	LCD_PutCursor(lcd, 0,0);
	LCD_SendString(lcd, " Hello World!");
	LCD_CMD_MoveCursorRight(lcd);
	LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);
	LCD_PutCursor(lcd, 1,0);
	LCD_SendString(lcd, "HD44780 4STM API");
}

void EX_WriteLeftToRight(I2C_LCD_HandleTypeDef *lcd){
	// Setup Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_ON_BLINKING_ON);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	// Write sequentially from left to right top to bottom
	int8_t col = 0;
	int8_t row = 0;
	for (uint8_t i = 0; i <128; i++){
		LCD_PutCursor(lcd, row, col);

		LCD_SendData(lcd, i+48);

		col++;

		if (col > 15) {row++; col = 0;}
		if (row > 1) row=0;

		HAL_Delay(100);
	}
}

void EX_WriteRightToLeft(I2C_LCD_HandleTypeDef *lcd){
	// Setup Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_DECREMENT);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_ON_BLINKING_OFF);
	LCD_Backlight(lcd, BACKLIGHT_OFF);

	// Write sequentially from right to left bottom to top
	int8_t col = 15;
	int8_t row = 1;
	for (uint8_t i = 0; i <128; i++){
		LCD_PutCursor(lcd, row, col);

		LCD_SendData(lcd, i+48);

		col--;

		if (col < 0) {row--; col = 15;}
		if (row < 0) row=1;

		HAL_Delay(100);
	}
}

void EX_ShiftingDisplayRight(I2C_LCD_HandleTypeDef *lcd){
	// Setup Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_ON);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_PutCursor(lcd, 0, 3);
	LCD_SendString(lcd, "Shift Right");
	LCD_CMD_EntryModeSet(lcd, SHIFT_DISPLAY_DECREMENT);


	// Write sequentially from right to left bottom to top
	LCD_PutCursor(lcd, 1, 8);
	for(uint8_t i = 0; i < 80; i++){
		LCD_SendData(lcd, i+48);
		HAL_Delay(250);
	}
}

void EX_ShiftingDisplayLeft(I2C_LCD_HandleTypeDef *lcd){
	// Setup Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_ON);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_PutCursor(lcd, 0, 3);
	LCD_SendString(lcd, "Shift Left");
	LCD_CMD_EntryModeSet(lcd, SHIFT_DISPLAY_INCREMENT);

	// Write sequentially from right to left bottom to top
	LCD_PutCursor(lcd, 1, 8);
	for(uint8_t i = 0; i < 80; i++){
		LCD_SendData(lcd, i+48);
		HAL_Delay(250);
	}
}

void EX_Animation(I2C_LCD_HandleTypeDef *lcd){
	// Setup Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_OFF);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	// Send 2 custom character to the HD44780 (frames off the animation)
	uint8_t frame0[8] = {0x0E, 0x0E, 0x04, 0x04, 0x04, 0x0A, 0x0A, 0x00};
	LCD_SendCustomChar(lcd, CUSTOM_CHAR_5X8_1, (uint8_t*) frame0, CHAR_5X8);

	uint8_t frame1[8] = {0x0E, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00};
	LCD_SendCustomChar(lcd, CUSTOM_CHAR_5X8_2, (uint8_t*) frame1, CHAR_5X8);


	// Move to the right
	for(int i = 0; i < 15; i++){
		LCD_PutCursor(lcd, 0, 0);
		if(i%2 == 0){
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_2);
		}else{
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);
		}

		LCD_PutCursor(lcd, 1, 0);
		if(i%2 == 0){
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);
		}else{
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_2);
		}

		LCD_CMD_ShiftDisplayRight(lcd);
		HAL_Delay(200);
	}

	// Move to the left
	for(int i = 0; i < 15; i++){
		LCD_PutCursor(lcd, 0, 0);
		if(i%2 == 0){
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);
		}else{
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_2);
		}

		LCD_PutCursor(lcd, 1, 0);
		if(i%2 == 0){
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_2);
		}else{
			LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);
		}
		LCD_CMD_ShiftDisplayLeft(lcd);
		HAL_Delay(200);
	}
}
