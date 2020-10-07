/*
 * examples.h
 * Copyright (C) 2020
 * Autores:
 * Eric Drumond Rocha <edr-1996@ufmg.br>,
 * Jo�o Paulo Fernandes Bonfim <jfernandesbonfim282@gmail.com> e
 * Marco Vinicio T. Andrade <marcovinicio@ufmg.br>
 * Version 1.0 - API com as seguintes fun��es:
 * void EX_HelloWorld(I2C_LCD_HandleTypeDef *lcd);
 * void EX_WriteLeftToRight(I2C_LCD_HandleTypeDef *lcd);
 * void EX_WriteRightToLeft(I2C_LCD_HandleTypeDef *lcd);
 * void EX_ShiftingDisplayRight(I2C_LCD_HandleTypeDef *lcd);
 * void EX_ShiftingDisplayLeft(I2C_LCD_HandleTypeDef *lcd);
 * void EX_Animation(I2C_LCD_HandleTypeDef *lcd);
 *
 * Esta API foi desenvolvida como trabalho da disciplina de
 * Programa��o de Sistemas Embarcados da UFMG � Prof. Ricardo de Oliveira Duarte � Departamento de Engenharia Eletr�nica.
 *
 * Esse programa � software livre; Voc� pode redistribu�-lo e/ou modific�-lo
 * nos termos da Licen�a P�blica Geral GNU publicada pela
 * Free Software Foundation; Na vers�o 2 (ou superior) da licen�a.
 *
 * Esse programa � distribuidp na esperan�a de que ser� �til, mas sem nenhuma
 * GARANTIA; Nem mesmo quanto a sua COMERCIABILIDADE ou ADEQUA��O A UM APLICA��O ESPECIFICA.
 * Para mais detealhes refira-se a Licen�a P�blica Geral GNU.
 *
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU
 * junto com esse progama; Caso n�o tenha recebido, escreva para:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Criado em: 1 de setembro de 2020
 * Institui��o: UFMG
 * Essa API cont�m fun��es com alguns exemplos de usos para demosntrar as funcionalidades da
 * API principal desse reposit�rio, a HD44780_I2C_STM32F4
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
