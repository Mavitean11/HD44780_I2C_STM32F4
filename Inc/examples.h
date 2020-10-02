/*
 * examples.h
 *
 *  Created on: 2 de out de 2020
 *      Author: mvta0
 */

#ifndef EXAMPLES_H_
#define EXAMPLES_H_

#include <stdint.h>
#include "HD44780_I2C_STM32F4.h"
#include <string.h>

void EX_HelloWorld(I2C_LCD_HandleTypeDef *lcd);
void EX_WriteLeftToRight(I2C_LCD_HandleTypeDef *lcd);
void EX_WriteRightToLeft(I2C_LCD_HandleTypeDef *lcd);
void EX_ShiftingDisplayRight(I2C_LCD_HandleTypeDef *lcd);
void EX_ShiftingDisplayLeft(I2C_LCD_HandleTypeDef *lcd);
void EX_Animation(I2C_LCD_HandleTypeDef *lcd);

#endif /* EXAMPLES_H_ */
