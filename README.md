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
Para utilizar a API copie HD44780\_I2C\_STM32F4.c e HD44780\_I2C\_STM32F4.h, encontrados nas pastas Src e Inc respectivamente, e os coloque nas mesmas pastas em seu projeto. Inclua o header onde ele for necess�rio

```c
#include "HD44780_I2C_STM32F4.h"
```

A API foi projetada de forma que seu uso seja parecido com o de uma biblioteca HAL. O primeiro passo para utiliaz-l� � ent�o inicializar o componente. S�o sugeridos os seguintes passos:

1. Declare um manipulador do LCD, do novo tipo I2C_LCD_HandleTypeDef

```c
I2C_LCD_HandleTypeDef lcd1;
```

2. Crie uma fun��o para inicializar o LCD. E a chame antes de entrar no loop principal de sua aplica��o.

	* Prot�tipo
	
	```c
	static void LCD1_init(void);
	```

	* Implementa��o
	
	```c
	static void LCD1_init(void){
	  lcd1.hi2c = &hi2c1; // Interface I2C a qual o LCD est� conectado
	  lcd1.address = 0x4E; // Endere�o I2C do LCD j� deslocado de 1 bit para a esquerda (0x4E � o padr�o para o m�dulo utilizado)
	  lcd1.backlight = BACKLIGHT_ON; // Op��o para a luz de fundo
	
	  I2C_LCD_InitTypeDef lcd1Init; // Armazena as configura��es iniciais do LCD
	
	  lcd1Init.lcdHandler = &lcd1; 
	  lcd1Init.functionSet = BITS4_LINES2_5X8DOTS;
	  lcd1Init.entryMode = MOVE_CURSOR_INCREMENT;
	  lcd1Init.displayMode = DISPLAY_ON_CURSOR_ON_BLINKING_ON;
	
	  LCD_init(&lcd1Init); // Realiza os procedimentos de inicializa��o do LCD.
	}
	```
	
	* Chame a fun��o.
	
	```c
	LCD1_init();
	```

# Outros recursos neste reposit�rio
Al�m dos arquivos fonte e cabe�alho da API, voc� encontra um projeto para demonstrar o funcionamento da API. Os arquivos exemplo.c e exemplo.h contem 6 exemplos de uso da API. Na main.c do projeto encontra-se implementada uma m�quina de estados finitos para navegar pelos diferentes exemplos pressionando o bot�o de usu�rio. Na aaplica��o foi usada a interface I2C1 do microcontrolador e o bot�o de usu�rio presente na placa no modo de interrup��o para navegar entre os exemplos. 

