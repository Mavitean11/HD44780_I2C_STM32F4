/*
 * examples.h
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
