# HD44780\_I2C\_STM32F4 API

Essa API fornece funções para controlar displays LCD através da interface I2C de micro-controladores da familia STMF4. Foi desenvolvida utilizando o [modulo display LCD 16x2 já com módulo I2C integrado](https://www.arduinoecia.com.br/modulo-i2c-display-16x2-arduino/) e a placa de desenvolvimento da [Nucleo-64 STM32F410]. Esta API foi desenvolvida como trabalho da disciplina de Programação de Sistemas Embarcados da UFMG – Prof. Ricardo de Oliveira Duarte – Departamento de Engenharia Eletrônica. 

## Autores

* Eric Drumond Rocha <[edr-1996@ufmg.br](edr-1996@ufmg.br)>
* João Paulo Fernandes Bonfim <[jfernandesbonfim282@gmail.com](jfernandesbonfim282@gmail.com)>
* Marco Vinicio T. Andrade <[marcovinicio@ufmg.br](marcovinicio@ufmg.br)>

## Display LCD e interface I2C
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

## Inicialização do display
Para utilizar a API copie HD44780\_I2C\_STM32F4.c e HD44780\_I2C\_STM32F4.h, encontrados nas pastas Src e Inc respectivamente, e os coloque nas mesmas pastas em seu projeto. Inclua o header onde ele for necessário

```c
#include "HD44780_I2C_STM32F4.h"
```

A API foi projetada de forma que seu uso seja parecido com o de uma biblioteca HAL. O primeiro passo para utiliza-lá é então inicializar o componente. Para inicializar o componente são sugeridos os seguintes passos

1. Declare um manipulador do LCD, do novo tipo I2C_LCD_HandleTypeDef e preencha os campos dessa struct. Essa variável será utilizada pela maioria das funções da API.

```c
I2C_LCD_HandleTypeDef lcd1;

lcd1.hi2c = &hi2c1; // Interface I2C na qual o LCD está conectado.
lcd1.address = 0x4E; // Endereço I2C do LCD já deslocado de 1 bit para a esquerda (0x4E é o padrão para o módulo utilizado).
lcd1.backlight = BACKLIGHT_ON; // Opção para a luz de fundo BACKLIGHT_ON para luz de fundo acesa ou BACKLIGHT_OFF para apagada.
```

2. Declare um manipulador de inicialização do LCD, do tipo  do novo tipo I2C_LCD_InitTypeDef e preencha com as opções com as quais deseja inicializar o LCD. Uma explicação completa das diferentes funções é encontrada nas funções que acessam as configurações do LCD.

```c
I2C_LCD_InitTypeDef lcd1Init; // Armazena as configurações iniciais do LCD

lcd1Init.lcdHandler = &lcd1; // I2C_LCD_HandleTypeDef do LCD que será inicializado
lcd1Init.functionSet = BITS4_LINES2_5X8DOTS; // Tamanho da interface, quantidade de linhas e formato da fonte.
lcd1Init.entryMode = MOVE_CURSOR_INCREMENT; // Comportamento do LCD ao receber dados
lcd1Init.displayMode = DISPLAY_ON_CURSOR_ON_BLINKING_ON; // Exibição dos dado no display e as representações possiveis para o cursor
```

3. Chame a função LCD_init(I2C_LCD_InitTypeDef *LCD) para inicializar o display LCD.

```c
LCD_init(&lcd1Init); // Realiza os procedimentos de inicialização do LCD.
```

4. A partir desse ponto o display LCD está pronto para ser utilizado atraves das funções implementadas nessa API, passando sempre como argumento uma referência para `lcd1`.

## Funções disponíveis

Essa API disponibiliza 12 funções para o usuário. A maioria delas tem um parametro em comum, o I2C_LCD_InitTypeDef *LCD. Esse parametro é uma referencia para o manipulador do LCD ao qual deseja aplicar a operação.

1. void LCD_init(I2C_LCD_InitTypeDef *LCD)

	Inicializa o display LCD seguindo os passos descritos na página 46 do [datasheet](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf).
	 
2. void LCD_CMD_ClearDisplay(I2C_LCD_HandleTypeDef *lcd)
	
	Limpa o display e retorna o cursor para a posição 0,0.
	
3. void LCD_CMD_ReturnHome(I2C_LCD_HandleTypeDef *lcd)

	Retorna o cursor para 0,0 mantendo o conteúdo do display. 

4. void LCD_CMD_EntryModeSet(I2C_LCD_HandleTypeDef *lcd, LCD_EntryMode entryMode)

	Define o comportamento do display LCD ao receber um caracter. Os possiveis valores de entryMode e a configuração correspondente são apresetadas na tabela:
	
	|       entryMode       | Comportamento ao receber um caractere |
	|:---------------------:|:-------------------------------------:|
	|SHIFT_DISPLAY_INCREMENT|Todo o conteudo do display é deslocado uma casa para a esquerda|
	|SHIFT_DISPLAY_DECREMENT|Todo o conteudo do display é deslocado uma casa para a direita|
	| MOVE_CURSOR_INCREMENT |O cursor é movido uma casa para a direita|
	| MOVE_CURSOR_DECREMENT |O cursor é movido uma casa para a esquerda|
	 
5. void LCD_CMD_DisplayControl(I2C_LCD_HandleTypeDef *lcd, LCD_DisplayControlOptions displayMode)
	
	Permite ligar ou desligar a exibição de caracteres no display. Além disso 2 efeitos podem ser adicionados na posição atual de escrita do diplay, um cursor e o efeito de ficar piscando. As opções disponíveis e os efeitos correpondentes estão na tabela abaixo:
	
	|            displayMode           | Display |Cursor|Piscar|
	|:--------------------------------:|:-------:|:----:|:----:|
	|            DISPLAY_OFF           |Desligado|  Não |  Não |
	|DISPLAY_ON_CURSOR_OFF_BLINKING_OFF|  Ligado |  Não |  Não |
	|DISPLAY_ON_CURSOR_OFF_BLINKING_ON |  Ligado |  Não |  Sim |
	|DISPLAY_ON_CURSOR_ON_BLINKING_OFF |  Ligado |  Sim |  Não |
	| DISPLAY_ON_CURSOR_ON_BLINKING_ON |  Ligado |  Sim |  Sim |
	
6. void LCD_CMD_CursorOrDisplayShift(I2C_LCD_HandleTypeDef *lcd, LCD_CursorOrDisplayShift cursorOrDisplayShift)

	Move o cursor ou desloca o conteudo do display para esquerda ou direita dependendo do valor de cursorOrDisplayShift. Foram também definidos macros para cada um dos casos possíveis. AS opções o comportamento e a macro correspondente podem ser vistas na tabela abaixo:
	
	|  cursorOrDisplayShift  | Cursor ou Display | Sentido |                        Macro                        |
	|:----------------------:|:-----------------:|:-------:|:---------------------------------------------------:|
	|   SHIFT_DISPLAY_RIGHT  |      Display      | Direita |LCD_CMD_ShiftDisplayRight(I2C_LCD_HandleTypeDef *lcd)|
	|   SHIFT_DISPLAY_LEFT   |      Display      | Esquerda|LCD_CMD_ShiftDisplayLeft(I2C_LCD_HandleTypeDef *lcd) |
	|    MOVE_CURSOR_RIGHT   |       Cursor      | Direita |LCD_CMD_MoveCursorRight(I2C_LCD_HandleTypeDef *lcd)  |
	|    MOVE_CURSOR_LEFT    |       Cursor      | Esquerda|LCD_CMD_MoveCursorRight(I2C_LCD_HandleTypeDef *lcd)  |
	
7. void LCD_CMD_FunctionSet(I2C_LCD_HandleTypeDef *lcd, LCD_FunctionSetOptions functionSet)

	Altera o tamanho da interface de comunicação, o numero de linhas do display e o tamanho da fonte(pontos por caractere) do display de acordo com o valore de functionSet. Os valores possiveis e a configuração correspondente são apresentadas na tabela abaixo:
	
	|            functionSet           | Interface |Linhas|Fonte|
	|:--------------------------------:|:-------:|:----:|:----:|
	| BITS4_LINES1_5X10DOTS |4bits|1|5x10|
	| BITS4_LINES1_5X8DOTS  |4bits|1|5x8|
	| BITS4_LINES2_5X8DOTS  |4bits|2|5x8|
	 
8. void LCD_PutCursor(I2C_LCD_HandleTypeDef *lcd, int row, int col)

	Coloca o cursor, posição onde o próximo caractere recebido é exibido na linha 'row', coluna 'col'. Essa função assume um display de 16 colunas e 2 linhas em sua implementação.
	
9. void LCD_Backlight(I2C_LCD_HandleTypeDef *lcd, LCD_BacklightOnOff backlight)

	Liga ou desliga a luz de fundo do display de acordo com o valor de backlight. Os valores possiveis são BACKLIGHT_ON e BACKLIGHT_OFF, que respectivamente liga e desliga a luz de fundo. Pode ser também utilizada pelas macros 'LCD_BacklightON(I2C_LCD_HandleTypeDef *lcd)' e 'LCD_BacklightFF(I2C_LCD_HandleTypeDef *lcd)'

10. void LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data)

	Envia um caracter para a posição atual do cursor. Os caracteres disponíveis podem ser encontrados na tabela da página 17 do [datasheet](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf).

11. void LCD_SendString(I2C_LCD_HandleTypeDef *lcd,char *str)
	
	Envia os caracteres da string sequencialmente para o display.
	
12. void LCD_SendCustomChar(I2C_LCD_HandleTypeDef *lcd, LCD_CustomCharAddress cgram_addr, uint8_t* pattern, LCD_CustomCharType type)
	
	Envia um caractere personalizado pelo usuário para o display. O caracetere é um padrão retangular de 5x8 ou 5x10 pixels. Cada pixel pode ser preto(1) ou transparente(0). Os parametro da função são:
	
	* LCD_CustomCharType type: CHAR_5X8 se caractere é um retângulo de 5x8 ou CHAR_5X10 se o caractere é de 5x10 pixels.
	
	* uint8_t* pattern: Vetor de tamanho igual ao número de linhas do caractere. Cada posição do vetor representa uma linha do caractere, começando do topo do caractere. Os 5 bits menos significativos representam os pixels da linha.
	
	* LCD_CustomCharAddress cgram_addr: Endereço onde o caractere será armazenado. São disponibilzados 8 endereçõs para carcteres de 5x8 acessados pelos valores CUSTOM_CHAR_5X8_N (N = 1 a 8). Caso esteja trabalhando com fontes de 5x10 apenas 4 endereços estarão disponiveis, acessados pelos valores CUSTOM_CHAR_5X10_M (M = 1 a 4).
	
	Para enviar o caractere personalizado ao display substitua o paracmetro 'data' de LCD_SendData(I2C_LCD_HandleTypeDef *lcd, char data) pelo endereço onde gravou o caractere.

	```c
	LCD_SendData(&lcd, CUSTOM_CHAR_5X8_N)
	```


## Outros recursos neste repositório
Além dos arquivos fonte e cabeçalho da API, você encontra um projeto para demonstrar o funcionamento da API. Os arquivos exemplo.c e exemplo.h contem 6 exemplos de uso da API. Na main.c do projeto encontra-se implementada uma máquina de estados finitos para navegar pelos diferentes exemplos pressionando o botão de usuário. Na aplicação foi usada a interface I2C1 do microcontrolador e o botão de usuário presente na placa no modo de interrupção para navegar entre os exemplos. 

