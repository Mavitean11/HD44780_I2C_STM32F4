/*
 * examples.c
 * Copyright (C) 2020
 * Autores:
 * Eric Drumond Rocha <edr-1996@ufmg.br>,
 * João Paulo Fernandes Bonfim <jfernandesbonfim282@gmail.com> e
 * Marco Vinicio T. Andrade <marcovinicio@ufmg.br>
 * Version 1.0 - API com as seguintes funções:
 * void EX_HelloWorld(I2C_LCD_HandleTypeDef *lcd);
 * void EX_WriteLeftToRight(I2C_LCD_HandleTypeDef *lcd);
 * void EX_WriteRightToLeft(I2C_LCD_HandleTypeDef *lcd);
 * void EX_ShiftingDisplayRight(I2C_LCD_HandleTypeDef *lcd);
 * void EX_ShiftingDisplayLeft(I2C_LCD_HandleTypeDef *lcd);
 * void EX_Animation(I2C_LCD_HandleTypeDef *lcd);
 *
 * Esta API foi desenvolvida como trabalho da disciplina de
 * Programação de Sistemas Embarcados da UFMG – Prof. Ricardo de Oliveira Duarte – Departamento de Engenharia Eletrônica.
 *
 * Esse programa é software livre; Você pode redistribuí-lo e/ou modificá-lo
 * nos termos da Licença Pública Geral GNU publicada pela
 * Free Software Foundation; Na versão 2 (ou superior) da licença.
 *
 * Esse programa é distribuidp na esperança de que será útil, mas sem nenhuma
 * GARANTIA; Nem mesmo quanto a sua COMERCIABILIDADE ou ADEQUAÇÂO A UM APLICAÇÂO ESPECIFICA.
 * Para mais detealhes refira-se a Licença Pública Geral GNU.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU
 * junto com esse progama; Caso não tenha recebido, escreva para:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Criado em: 1 de setembro de 2020
 * Instituição: UFMG
 * Essa API contém funções com alguns exemplos de usos para demosntrar as funcionalidades da
 * API principal desse repositório, a HD44780_I2C_STM32F4
 */

#include "examples.h"


void EX_HelloWorld(I2C_LCD_HandleTypeDef *lcd){
	// Configura o Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_OFF);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	// Envia um caractere sorriso
	uint8_t smile[8] = {0x00, 0x0A, 0x0A, 0x00, 0x11, 0x1B, 0x0E, 0x00};
	LCD_SendCustomChar(lcd, CUSTOM_CHAR_5X8_1, (uint8_t*) smile, CHAR_5X8);

	// Escreve Hello World no Display
	LCD_PutCursor(lcd, 0,0);
	LCD_SendString(lcd, "Hello World!");
	LCD_CMD_MoveCursorRight(lcd);
	LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);
	LCD_PutCursor(lcd, 1, 0);
	LCD_SendString(lcd, "HD44780 I2C API");
}

void EX_WriteLeftToRight(I2C_LCD_HandleTypeDef *lcd){
	// Configura o Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_ON_BLINKING_ON);
	LCD_BacklightON(lcd);

	// Escreve sequencialmente no display da esquerda para a direita de cima para baixo
	int8_t col = 0;
	int8_t row = 0;
	static const char text[240] = "Nesse exemplo o texto e escrito da esquerda para a direita de cima para baixo";
	for(uint8_t i = 0; i <strlen(text); i++){
		LCD_PutCursor(lcd, row, col);

		LCD_SendData(lcd, text[i]);

		col++;

		if (col > 15) {row++; col = 0;}
		if (row > 1) row=0;

		HAL_Delay(200);
	}
}

void EX_WriteRightToLeft(I2C_LCD_HandleTypeDef *lcd){
	// Configura o Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_DECREMENT);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_ON_BLINKING_OFF);
	LCD_BacklightOFF(lcd);

	// Escreve sequencialmente no display da direita para a esquerda de baixo para cima
	int8_t col = 15;
	int8_t row = 1;
	static const char text[240] = "Para ler esse exemplo só no reflexo do espelho";
	for(uint8_t i = 0; i <strlen(text); i++){
		LCD_PutCursor(lcd, row, col);

		LCD_SendData(lcd, text[i]);

		col--;

		if (col < 0) {row--; col = 15;}
		if (row < 0) row=1;

		HAL_Delay(200);
	}
}

void EX_ShiftingDisplayRight(I2C_LCD_HandleTypeDef *lcd){
	// Configura o Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_ON);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_PutCursor(lcd, 0, 3);
	LCD_SendString(lcd, "Deslocando para direita");
	LCD_CMD_EntryModeSet(lcd, SHIFT_DISPLAY_DECREMENT);


	// Aqui a medida que se escreve o todo o conteudo do display é deslocado para a direita
	LCD_PutCursor(lcd, 1, 39);
	static const char text[240] = "Quando escreve tudo mexe";
	for(int8_t i = strlen(text)-1; i >= 0 ; i--){
		LCD_SendData(lcd, text[i]);
		HAL_Delay(250);
	}
}

void EX_ShiftingDisplayLeft(I2C_LCD_HandleTypeDef *lcd){
	// Configura o Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_ON);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_PutCursor(lcd, 0, 3);
	LCD_SendString(lcd, "Deslocando para esquerda");
	LCD_CMD_EntryModeSet(lcd, SHIFT_DISPLAY_INCREMENT);

	// Write sequentially from right to left bottom to top
	LCD_PutCursor(lcd, 1, 15);
	static const char text[240] = "Quando escreve tudo mexe";
	for(uint8_t i = 0; i <strlen(text); i++){
		LCD_SendData(lcd, text[i]);
		HAL_Delay(250);
	}
}

void EX_Animation(I2C_LCD_HandleTypeDef *lcd){
	// Configura o Display
	LCD_CMD_ClearDisplay(lcd);
	LCD_CMD_ReturnHome(lcd);
	LCD_CMD_DisplayControl(lcd, DISPLAY_ON_CURSOR_OFF_BLINKING_OFF);
	LCD_CMD_EntryModeSet(lcd, MOVE_CURSOR_INCREMENT);
	LCD_Backlight(lcd, BACKLIGHT_ON);

	// Envia 2 caracteres personalizados que são os frames da animação
	uint8_t frame0[8] = {0x0E, 0x0E, 0x04, 0x04, 0x04, 0x0A, 0x0A, 0x00};
	LCD_SendCustomChar(lcd, CUSTOM_CHAR_5X8_1, (uint8_t*) frame0, CHAR_5X8);

	uint8_t frame1[8] = {0x0E, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00};
	LCD_SendCustomChar(lcd, CUSTOM_CHAR_5X8_2, (uint8_t*) frame1, CHAR_5X8);

	// Titulo da animação
	LCD_PutCursor(lcd, 0, 3);
	LCD_SendString(lcd, "A corrida");
	HAL_Delay(3000);

	// Posiciona os corredores
	LCD_CMD_ClearDisplay(lcd);
	LCD_PutCursor(lcd, 0, 0);
	LCD_SendData(lcd, CUSTOM_CHAR_5X8_2);

	LCD_PutCursor(lcd, 1, 0);
	LCD_SendData(lcd, CUSTOM_CHAR_5X8_1);

	// Contagem regressiva
	for(int i = 5; i >= 0; i--){
		LCD_PutCursor(lcd, 0, 8);
		if(i==0){
			LCD_SendString(lcd, " ");
		}else{
			LCD_SendData(lcd, i+48);
			HAL_Delay(1000);
		}
	}


	// Bonecos correm para a direita
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

	// Correm para a esquerda
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

	// Resultado da corrida
	LCD_CMD_ClearDisplay(lcd);
	LCD_PutCursor(lcd, 0, 5);
	LCD_SendString(lcd, "Empate");
	HAL_Delay(3000);
}
