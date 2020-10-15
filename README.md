# HD44780\_I2C\_STM32F4 API

Essa API fornece fun��es para controlar displays LCD atrav�s da interface I2C de micro-controladores da familia STMF4. Foi desenvolvida utilizando o [modulo display LCD 16x2 j� com m�dulo I2C integrado](https://www.arduinoecia.com.br/modulo-i2c-display-16x2-arduino/) e a placa de desenvolvimento da [Nucleo-64 STM32F410]. Esta API foi desenvolvida como trabalho da disciplina de Programa��o de Sistemas Embarcados da UFMG � Prof. Ricardo de Oliveira Duarte � Departamento de Engenharia Eletr�nica. 

## Autores

* Eric Drumond Rocha <[edr-1996@ufmg.br](edr-1996@ufmg.br)>
* Jo�o Paulo Fernandes Bonfim <[jfernandesbonfim282@gmail.com](jfernandesbonfim282@gmail.com)>
* Marco Vinicio T. Andrade <[marcovinicio@ufmg.br](marcovinicio@ufmg.br)>

## Display LCD e interface I2C
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

## Inicializa��o do display
Para utilizar a API copie HD44780\_I2C\_STM32F4.c e HD44780\_I2C\_STM32F4.h, encontrados nas pastas Src e Inc respectivamente, e os coloque nas mesmas pastas em seu projeto. Inclua o header onde ele for necess�rio

```c
#include "HD44780_I2C_STM32F4.h"
```

A API foi projetada de forma que seu uso seja parecido com o de uma biblioteca HAL. O primeiro passo para utiliza-l� � ent�o inicializar o componente. Para inicializar o componente s�o sugeridos os seguintes passos

1. Declare um manipulador do LCD, do novo tipo I2C_LCD_HandleTypeDef e preencha os campos dessa struct. Essa vari�vel ser� utilizada pela maioria das fun��es da API.

```c
I2C_LCD_HandleTypeDef lcd1;

lcd1.hi2c = &hi2c1; // Interface I2C na qual o LCD est� conectado.
lcd1.address = 0x4E; // Endere�o I2C do LCD j� deslocado de 1 bit para a esquerda (0x4E � o padr�o para o m�dulo utilizado).
lcd1.backlight = BACKLIGHT_ON; // Op��o para a luz de fundo BACKLIGHT_ON para luz de fundo acesa ou BACKLIGHT_OFF para apagada.
```

2. Declare um manipulador de inicializa��o do LCD, do tipo  do novo tipo I2C_LCD_InitTypeDef e preencha com as op��es com as quais deseja inicializar o LCD. Uma explica��o completa das diferentes fun��es � encontrada nas fun��es que acessam as configura��es do LCD.

```c
I2C_LCD_InitTypeDef lcd1Init; // Armazena as configura��es iniciais do LCD

lcd1Init.lcdHandler = &lcd1; // I2C_LCD_HandleTypeDef do LCD que ser� inicializado
lcd1Init.functionSet = BITS4_LINES2_5X8DOTS; // Tamanho da interface, quantidade de linhas e formato da fonte.
lcd1Init.entryMode = MOVE_CURSOR_INCREMENT; // Comportamento do LCD ao receber dados
lcd1Init.displayMode = DISPLAY_ON_CURSOR_ON_BLINKING_ON; // Exibi��o dos dado no display e as representa��es possiveis para o cursor
```

3. Chame a fun��o LCD_init(I2C_LCD_InitTypeDef *LCD) para inicializar o display LCD.

```c
LCD_init(&lcd1Init); // Realiza os procedimentos de inicializa��o do LCD.
```

4. A partir desse ponto o display LCD est� pronto para ser utilizado atraves das fun��es implementadas nessa API, passando sempre como argumento uma refer�ncia para `lcd1`.

## Fun��es dispon�veis

Essa API disponibiliza 12 fun��es para o usu�rio. A maioria delas tem um parametro em comum, o I2C_LCD_InitTypeDef *LCD. Esse parametro � uma referencia para o manipulador do LCD ao qual deseja aplicar a opera��o.

1. void LCD_init(I2C_LCD_InitTypeDef *LCD)

	Inicializa o display LCD seguindo os passos descritos na p�gina 46 do [datasheet](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf).
	 
2. void LCD_CMD_ClearDisplay(I2C_LCD_HandleTypeDef *lcd)
	
	Limpa o display e retorna o cursor para a posi��o 0,0.
	
3. void LCD_CMD_ReturnHome(I2C_LCD_HandleTypeDef *lcd)

	Retorna o cursor para 0,0 mantendo o conte�do do display. 

4. void LCD_CMD_EntryModeSet(I2C_LCD_HandleTypeDef *lcd, LCD_EntryMode entryMode)

	Define o comportamento do display LCD ao receber um caracter. Os possiveis valores de entryMode e a configura��o correspondente s�o apresetadas na tabela:
	
	|       entryMode       | Comportamento ao receber um caractere |
	|:---------------------:|:-------------------------------------:|
	|SHIFT_DISPLAY_INCREMENT|Todo o conteudo do display � deslocado uma casa para a esquerda|
	|SHIFT_DISPLAY_DECREMENT|Todo o conteudo do display � deslocado uma casa para a direita|
	| MOVE_CURSOR_INCREMENT |O cursor � movido uma casa para a direita|
	| MOVE_CURSOR_DECREMENT |O cursor � movido uma casa para a esquerda|
	 
5. void LCD_CMD_DisplayControl(I2C_LCD_HandleTypeDef *lcd, LCD_DisplayControlOptions displayMode)
	
	Permite ligar ou desligar a exibi��o de caracteres no display. Al�m disso 2 efeitos podem ser adicionados na posi��o atual de escrita do diplay, um cursor e o efeito de ficar piscando. As op��es dispon�veis e os efeitos correpondentes est�o na tabela abaixo:
	
	|            displayMode           | Display |Cursor|Piscar|
	|:--------------------------------:|:-------:|:----:|:----:|
	|            DISPLAY_OFF           |Desligado|  N�o |  N�o |
	|DISPLAY_ON_CURSOR_OFF_BLINKING_OFF|  Ligado |  N�o |  N�o |
	|DISPLAY_ON_CURSOR_OFF_BLINKING_ON |  Ligado |  N�o |  Sim |
	|DISPLAY_ON_CURSOR_ON_BLINKING_OFF |  Ligado |  Sim |  N�o |
	| DISPLAY_ON_CURSOR_ON_BLINKING_ON |  Ligado |  Sim |  Sim |
	
6. void LCD_CMD_CursorOrDisplayShift(I2C_LCD_HandleTypeDef *lcd, LCD_CursorOrDisplayShift cursorOrDisplayShift)

	Move o cursor ou desloca o conteudo do display para esquerda ou direita dependendo do valor de cursorOrDisplayShift. Foram tamb�m definidos macros para cada um dos casos poss�veis. AS op��es o comportamento e a macro correspondente podem ser vistas na tabela abaixo:
	
	|  cursorOrDisplayShift  | Cursor ou Display | Sentido |                        Macro                        |
	|:----------------------:|:-----------------:|:-------:|:---------------------------------------------------:|
	|   SHIFT_DISPLAY_RIGHT  |      Display      | Direita |LCD_CMD_ShiftDisplayRight(I2C_LCD_HandleTypeDef *lcd)|
	|   SHIFT_DISPLAY_LEFT   |      Display      | Esquerda|LCD_CMD_ShiftDisplayLeft(I2C_LCD_HandleTypeDef *lcd) |
	|    MOVE_CURSOR_RIGHT   |       Cursor      | Direita |LCD_CMD_MoveCursorRight(I2C_LCD_HandleTypeDef *lcd)  |
	|    MOVE_CURSOR_LEFT    |       Cursor      | Esquerda|LCD_CMD_MoveCursorRight(I2C_LCD_HandleTypeDef *lcd)  |
	
7. void LCD_CMD_FunctionSet(I2C_LCD_HandleTypeDef *lcd, LCD_FunctionSetOptions functionSet)

	Altera o tamanho da interface de comunica��o, o numero de linhas do display e o tamanho da fonte(pontos por caractere) do display de acordo com o valore de functionSet. Os valores possiveis e a configura��o correspondente s�o apresentadas na tabela abaixo:
	
	|            functionSet           | Interface |Linhas|Fonte|
	|:--------------------------------:|:-------:|:----:|:----:|
	| BITS4_LINES1_5X10DOTS |4bits|1|5x10|
	| BITS4_LINES1_5X8DOTS  |4bits|1|5x8|
	| BITS4_LINES2_5X8DOTS  |4bits|2|5x8|
	 
8. void LCD_PutCursor(I2C_LCD_HandleTypeDef *lcd, int row, int col)

	Coloca o cursor, posi��o onde o pr�ximo caractere recebido � exibido na linha 'row', coluna 'col'. Essa fun��o assume um display de 16 colunas e 2 linhas em sua implementa��o.
	
9. void LCD_Backlight(I2C_LCD_HandleTypeDef *lcd, LCD_BacklightOnOff backlight)

	Liga ou desliga a luz de fundo do display de acordo com o valor de backlight. Os valores possiveis s�o BACKLIGHT_ON e BACKLIGHT_OFF, que respectivamente liga e desliga a luz de fundo. Pode ser tamb�m utilizada pelas macros 'LCD_BacklightON(I2C_LCD_HandleTypeDef *lcd)' e 'LCD_BacklightFF(I2C_LCD_HandleTypeDef *lcd)'

10. void LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data)

	Envia um caracter para a posi��o atual do cursor. Os caracteres dispon�veis podem ser encontrados na tabela da p�gina 17 do [datasheet](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf).

11. void LCD_SendString(I2C_LCD_HandleTypeDef *lcd,char *str)
	
	Envia os caracteres da string sequencialmente para o display.
	
12. void LCD_SendCustomChar(I2C_LCD_HandleTypeDef *lcd, LCD_CustomCharAddress cgram_addr, uint8_t* pattern, LCD_CustomCharType type)
	
	Envia um caractere personalizado pelo usu�rio para o display. O caracetere � um padr�o retangular de 5x8 ou 5x10 pixels. Cada pixel pode ser preto(1) ou transparente(0). Os parametro da fun��o s�o:
	
	* LCD_CustomCharType type: CHAR_5X8 se caractere � um ret�ngulo de 5x8 ou CHAR_5X10 se o caractere � de 5x10 pixels.
	
	* uint8_t* pattern: Vetor de tamanho igual ao n�mero de linhas do caractere. Cada posi��o do vetor representa uma linha do caractere, come�ando do topo do caractere. Os 5 bits menos significativos representam os pixels da linha.
	
	* LCD_CustomCharAddress cgram_addr: Endere�o onde o caractere ser� armazenado. S�o disponibilzados 8 endere��s para carcteres de 5x8 acessados pelos valores CUSTOM_CHAR_5X8_N (N = 1 a 8). Caso esteja trabalhando com fontes de 5x10 apenas 4 endere�os estar�o disponiveis, acessados pelos valores CUSTOM_CHAR_5X10_M (M = 1 a 4).
	
	Para enviar o caractere personalizado ao display substitua o paracmetro 'data' de LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data) pelo endere�o onde gravou o caractere.

	```c
	LCD_SendData(&lcd, CUSTOM_CHAR_5X8_N)
	```


## Outros recursos neste reposit�rio
Al�m dos arquivos fonte e cabe�alho da API, voc� encontra um projeto para demonstrar o funcionamento da API. Os arquivos exemplo.c e exemplo.h contem 6 exemplos de uso da API. Na main.c do projeto encontra-se implementada uma m�quina de estados finitos para navegar pelos diferentes exemplos pressionando o bot�o de usu�rio. Na aplica��o foi usada a interface I2C1 do microcontrolador e o bot�o de usu�rio presente na placa no modo de interrup��o para navegar entre os exemplos. 

