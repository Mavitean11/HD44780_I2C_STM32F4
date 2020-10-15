/*
 * HD44780_I2C_STM32F4.h
 * Copyright (C) 2020
 * Autores:
 * Eric Drumond Rocha <edr-1996@ufmg.br>,
 * João Paulo Fernandes Bonfim <jfernandesbonfim282@gmail.com> e
 * Marco Vinicio T. Andrade <marcovinicio@ufmg.br>
 * Version 1.0 - API com as seguintes funções:
 * void LCD_init(I2C_LCD_InitTypeDef *LCD);
 * void LCD_CMD_ClearDisplay(I2C_LCD_HandleTypeDef *lcd);
 * void LCD_CMD_ReturnHome(I2C_LCD_HandleTypeDef *lcd);
 * void LCD_CMD_EntryModeSet(I2C_LCD_HandleTypeDef *lcd, LCD_EntryMode entryMode);
 * void LCD_CMD_DisplayControl(I2C_LCD_HandleTypeDef *lcd, LCD_DisplayControlOptions displayMode);
 * void LCD_CMD_CursorOrDisplayShift(I2C_LCD_HandleTypeDef *lcd, uint8_t cursorOrDisplayShift);
 * void LCD_CMD_FunctionSet(I2C_LCD_HandleTypeDef *lcd, LCD_FunctionSetOptions functionSet);
 * void LCD_PutCursor(I2C_LCD_HandleTypeDef *lcd, int row, int col);
 * void LCD_Backlight(I2C_LCD_HandleTypeDef *lcd, LCD_BacklightOnOff backlight);
 * void LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data);
 * void LCD_SendString(I2C_LCD_HandleTypeDef *lcd,char *str);
 * void LCD_SendCustomChar(I2C_LCD_HandleTypeDef *lcd, LCD_CustomCharAddress cgram_addr, uint8_t* pattern, LCD_CustomCharType type);
 *
 * Baseado na API i2c-lcd accessada em: https://controllerstech.com/i2c-lcd-in-stm32/
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
 * Criado em: 11 de setembro de 2020
 * Instituição: UFMG
 * Essa API contém funções para usar com o LCD16X2 baseado no controlador
 * HD44780(https://www.sparkfun.com/datasheets/LCD/HD44780.pdf) com comunicação
 * I2C utilizando o expansor de I/O PCF8574(https://www.ti.com/lit/ds/symlink/pcf8574.pdf)
 * A conexão entre HD44780 e PCF8574 é a seguinte:
 * PCF8574		HDD44780
 * P0		->	RS
 * P1		->	R/W
 * P2		->	E
 * P3		->	Backlight control circuit
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

/* Macros Exportadas ---------------------------------------------------------*/
/* Para LCD_CMD_CursorOrDisplayShift -----------------------------------------*/
#define LCD_CMD_MoveCursorRight(LCD) LCD_CMD_CursorOrDisplayShift(LCD, MOVE_CURSOR_RIGHT)
#define LCD_CMD_MoveCursorLeft(LCD) LCD_CMD_CursorOrDisplayShift(LCD, MOVE_CURSOR_LEFT)
#define LCD_CMD_ShiftDisplayRight(LCD) LCD_CMD_CursorOrDisplayShift(LCD, SHIFT_DISPLAY_RIGHT)
#define LCD_CMD_ShiftDisplayLeft(LCD) LCD_CMD_CursorOrDisplayShift(LCD, SHIFT_DISPLAY_LEFT)

/* Para LCD_Backlight -------------------------------------------------------*/
#define LCD_BacklightON(LCD) LCD_Backlight(LCD, BACKLIGHT_ON)
#define LCD_BacklightOFF(LCD) LCD_Backlight(LCD, BACKLIGHT_OFF)

/* Tipos Exportados ---------------------------------------------------------*/

// Opções de modo de Entrada do HD44780
typedef enum{
	SHIFT_DISPLAY_INCREMENT = 0x03U, // Shift the hole display content to the left when a character is written to DDRAM
	SHIFT_DISPLAY_DECREMENT = 0x01U, // Shift the hole display content to the right when a character is written to DDRAM
	MOVE_CURSOR_INCREMENT = 0x02U,	// Decrements the DDRAM address by 1 when a character is written
	MOVE_CURSOR_DECREMENT = 0x00U    // Decrements the DDRAM address by 1 when a character is written
} LCD_EntryMode;

// Opções de controle do display do HD44780
typedef enum{
	DISPLAY_OFF = 0x00U, // Data on DDRAM is not displayed on LCD. You can still write to DDRAM
	DISPLAY_ON_CURSOR_OFF_BLINKING_OFF = 0x04U, // Display data on LCD
	DISPLAY_ON_CURSOR_OFF_BLINKING_ON = 0x05U,	// Display data and blink current DDRAM address
	DISPLAY_ON_CURSOR_ON_BLINKING_OFF = 0x06U, // Display data and a cursor current DDRAM address
	DISPLAY_ON_CURSOR_ON_BLINKING_ON = 0x07U // Display data with cursor and blink effect
} LCD_DisplayControlOptions;

// Opções de movimento do cursor do HD44780
typedef enum{
    SHIFT_DISPLAY_RIGHT = 0x0CU, // Shift hole display content to the right
	SHIFT_DISPLAY_LEFT = 0x08U,  // Shift hole display content to the left
	MOVE_CURSOR_RIGHT = 0x04U,   // Move cursor to the right
	MOVE_CURSOR_LEFT = 0x00U     // Move cursor to the left
} LCD_CursorOrDisplayShift;

// Opções de tamanho da interface de comunicação, linhas do display e fontes do HD44780
typedef enum{
	BITS4_LINES1_5X10DOTS = 0x04U, // 4 bit interface. 1 line display. 5X10 font
	BITS4_LINES1_5X8DOTS = 0x00U,  // 4 bit interface. 1 line display. 5X8 font
	BITS4_LINES2_5X8DOTS = 0x08U   // 4 bit interface. 2 line display. 5X8 font
} LCD_FunctionSetOptions;

// Opções do backlight do display
typedef enum{
	BACKLIGHT_ON = 0x08U,
	BACKLIGHT_OFF = 0x00U,
} LCD_BacklightOnOff;

// Endereços de memória disponiveis para caracteres personalizados
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

// Opções de fonte para caracteres personalizados
typedef enum{
	CHAR_5X8 = 0x08U,
	CHAR_5X10 = 0x0AU,
} LCD_CustomCharType;

// Manipulador do LCD
typedef struct{
	I2C_HandleTypeDef *hi2c; // I2C interface to connected to the PCF8574
	uint8_t address; //I2C address of the PCF8574 that controls
	LCD_BacklightOnOff backlight;
} I2C_LCD_HandleTypeDef;

// Manipulador de inicialização do LCD
typedef struct{
	I2C_LCD_HandleTypeDef *lcdHandler;
	LCD_FunctionSetOptions functionSet;
	LCD_EntryMode entryMode;
	LCD_DisplayControlOptions displayMode;
} I2C_LCD_InitTypeDef;


/* Funcões Exportadas ---------------------------------------------------*/
// Função de inicialização
void LCD_init(I2C_LCD_InitTypeDef *LCD); // initialize lcd

// Funções de Comandos para o HD44780
void LCD_CMD_ClearDisplay(I2C_LCD_HandleTypeDef *lcd); // Limpa o display e retorna o cursor para 0,0
void LCD_CMD_ReturnHome(I2C_LCD_HandleTypeDef *lcd); // Retorna o cursor para 0,0
void LCD_CMD_EntryModeSet(I2C_LCD_HandleTypeDef *lcd, LCD_EntryMode entryMode); // Define o modo de entrada do LCD
void LCD_CMD_DisplayControl(I2C_LCD_HandleTypeDef *lcd, LCD_DisplayControlOptions displayMode); // Configura o display a exibição do cursor e o efeito de piscar
void LCD_CMD_CursorOrDisplayShift(I2C_LCD_HandleTypeDef *lcd, LCD_CursorOrDisplayShift cursorOrDisplayShift); // Move o cursor ou desloca o display.
void LCD_CMD_FunctionSet(I2C_LCD_HandleTypeDef *lcd, LCD_FunctionSetOptions functionSet); // Define o tamanho da interface, numero de linhas do display e a fonte dos caracteres
void LCD_PutCursor(I2C_LCD_HandleTypeDef *lcd, int row, int col); // Coloca o cursor na posição row, col
void LCD_Backlight(I2C_LCD_HandleTypeDef *lcd, LCD_BacklightOnOff backlight); // Liga ou desliga a luz de fundo do display

// Funções para enviar dados ao cursor
void LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data); // Envia dados para o endereço atual do HD44780
void LCD_SendString(I2C_LCD_HandleTypeDef *lcd,char *str); // Envia os caracteres da string sequencialmente para o display
void LCD_SendCustomChar(I2C_LCD_HandleTypeDef *lcd, LCD_CustomCharAddress cgram_addr, uint8_t* pattern, LCD_CustomCharType type); // Envia um carctere customizazdo pelo usuario

#endif /* HD44780_I2C_STM32F4_H_ */
