## HD44780\_I2C\_STM32F4

Essa API fornece funções para controlar displays LCD através da interface I2C de micro-controladores da familia STMF4. Foi desenvolvida utilizando o [modulo display LCD 16x2 já com módulo I2C integrado](https://www.arduinoecia.com.br/modulo-i2c-display-16x2-arduino/) e a placa de desenvolvimento da [Nucleo-64 STM32F410]. Esta API foi desenvolvida como trabalho da disciplina de Programação de Sistemas Embarcados da UFMG – Prof. Ricardo de Oliveira Duarte – Departamento de Engenharia Eletrônica. 

# Display LCD e interface I2C
Esse módulo é baseado em um display LCD 16x02 com controlador [HD44780](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf). A interface I2C é feita pelo expansor de I/O [PCF8574](https://www.nxp.com/docs/en/data-sheet/PCF8574_PCF8574A.pdf). A conexão entre esses dois componentes é apresentada na tabela abaixo:

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

# Utilização da API
Para utilizar a API copie HD44780\_I2C\_STM32F4.c e HD44780\_I2C\_STM32F4.h, encontrados nas pastas Src e Inc respectivamente, e os coloque nas mesmas pastas em seu projeto. Inclua o header onde ele for necessário

```c
#include "HD44780_I2C_STM32F4.h"
```

A API foi projetada de forma que seu uso seja parecido com o de uma biblioteca HAL. O primeiro passo para utiliaz-lá é então inicializar o componente. São sugeridos os seguintes passos:

1. Declare um manipulador do LCD, do novo tipo I2C_LCD_HandleTypeDef

```c
I2C_LCD_HandleTypeDef lcd1;
```

2. Crie uma função para inicializar o LCD. E a chame antes de entrar no loop principal de sua aplicação.

	* Protótipo
	
	```c
	static void LCD1_init(void);
	```

	* Implementação
	
	```c
	static void LCD1_init(void){
	  lcd1.hi2c = &hi2c1; // Interface I2C a qual o LCD está conectado
	  lcd1.address = 0x4E; // Endereço I2C do LCD já deslocado de 1 bit para a esquerda (0x4E é o padrão para o módulo utilizado)
	  lcd1.backlight = BACKLIGHT_ON; // Opção para a luz de fundo
	
	  I2C_LCD_InitTypeDef lcd1Init; // Armazena as configurações iniciais do LCD
	
	  lcd1Init.lcdHandler = &lcd1; 
	  lcd1Init.functionSet = BITS4_LINES2_5X8DOTS;
	  lcd1Init.entryMode = MOVE_CURSOR_INCREMENT;
	  lcd1Init.displayMode = DISPLAY_ON_CURSOR_ON_BLINKING_ON;
	
	  LCD_init(&lcd1Init); // Realiza os procedimentos de inicialização do LCD.
	}
	```
	
	* Chame a função.
	
	```c
	LCD1_init();
	```

# Outros recursos neste repositório
Além dos arquivos fonte e cabeçalho da API, você encontra um projeto para demonstrar o funcionamento da API. Os arquivos exemplo.c e exemplo.h contem 6 exemplos de uso da API. Na main.c do projeto encontra-se implementada uma máquina de estados finitos para navegar pelos diferentes exemplos pressionando o botão de usuário. Na aaplicação foi usada a interface I2C1 do microcontrolador e o botão de usuário presente na placa no modo de interrupção para navegar entre os exemplos. 

