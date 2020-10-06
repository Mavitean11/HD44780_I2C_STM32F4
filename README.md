## HD44780\_I2C\_STM32F4

Essa API fornece fun��es para controlar displays LCD atrav�s da interface I2C de micro-controladores da familia STMF4. Foi desenvolvida utilizando o [modulo display LCD 16x2 j� com m�dulo I2C integrado](https://www.arduinoecia.com.br/modulo-i2c-display-16x2-arduino/) e a placa de desenvolvimento da [Nucleo-64 STM32F410]. Esta API foi desenvolvida como trabalho da disciplina de Programa��o de Sistemas Embarcados da UFMG � Prof. Ricardo de Oliveira Duarte � Departamento de Engenharia Eletr�nica. 

# Display LCD e interface I2C
Esse m�dulo � baseado em um display LCD 16x02 com controlador [HD44780](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf). A interface I2C � feita pelo expansor de I/O [PCF8574](https://www.nxp.com/docs/en/data-sheet/PCF8574_PCF8574A.pdf). A conex�o entre esses dois componentes � apresentada na tabela abaixo:

| PCF8574 |              HD44780              |
|:-------:|:---------------------------------:|
|    P0   |                 RS                |
|    P1   |                R/W                |
|    P2   |                 E                 |
|    P3   | Circuito de controle da backlight |
|    P4   |                 D4                |
|    P5   |                 D5                |
|    P6   |                 D6                |
|    P7   |                 D7                |

# Utiliza��o da API
Para utilizar a API copie HD44780\_I2C\_STM32F4.c e HD44780\_I2C\_STM32F4.h, encontrados nas pastas Src e Inc respectivamente, e os coloque nas mesmas pastas em seu projeto. Inclua 

```c
\#include "HD44780\_I2C\_STM32F4.h"
```

A API foi projetada de forma que seu uso seja parecido com o de uma biblioteca HAL. O primeiro passo para utiliaz-l� � ent�o inicializar o componente.

  

