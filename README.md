# EmbarcaTech_Conversores_A-D
Tarefa do EmbarcaTech com o objetivo de consolidar os conceitos sobre o uso de conversores analógico-digitais (ADC) no RP2040

# Vídeo Explicativo
A seguir um vídeo explicativo sobre o projeto.

"link"

# Intruções
Para executar o código em questão, deve-se possuir acesso a placa BitDogLab. 

**Funcionalidades**
1. Movimento do Quadrado: 

    - Um quadrado é exibido no centro do display.

    - Ao movimentar o joystick, o quadrado se move na mesma direção.

2. Controle dos LEDs:

    - LED Azul: Acende com intensidade proporcional ao movimento do eixo Y do joystick.

    - LED Vermelho: Acende com intensidade proporcional ao movimento do eixo X do joystick.

    - LED Verde: Acende ou apaga ao pressionar o botão do joystick.

3. Botões:

    - Botão A: Ativa ou desativa o controle dos LEDs Azul e Vermelho.

    - Botão do Joystick: Alterna o estado do LED Verde e muda o estilo da borda no display.

    - Botão B: Reinicia a placa no modo de bootloader USB. (Extra)

4. Estilos de Borda:

    - O display alterna entre diferentes estilos de borda a cada pressionamento do botão do joystick.

# Composição do código
**Arquivo Principal: EmbarcaTech_Conversores_A-D.c**
- main(): Função principal do programa, responsável por inicializar os periféricos e executar o loop principal.

- setup(): Configura os pinos GPIO, I2C, ADC e inicializa o display.

- button_isr(uint gpio, uint32_t events): Rotina de interrupção para tratar os eventos dos botões.

- pwm_setup(uint gpio): Configura o PWM para controlar a intensidade dos LEDs.

- desenhar_borda(uint tipo_borda): Desenha diferentes estilos de borda no display, dependendo do valor de tipo_borda.

**Biblioteca: ssd1306.c**
- Contém as funções para controlar o display SSD1306, como inicialização, desenho de formas e envio de dados.

# Desenvolvedor
Abel José Rocha Barros Bezerra