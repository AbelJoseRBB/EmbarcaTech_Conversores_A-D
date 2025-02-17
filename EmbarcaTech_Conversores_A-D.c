#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "Bibliotecas/ssd1306.h"
#include "Bibliotecas/font.h"

#define pin_red 13
#define pin_blue 12
#define pin_green 11

#define botaoA 5
#define botaoJ 22

#define I2C_PORT i2c1
#define ADDR 0x3c
#define I2C_SDA 14
#define I2C_SCL 15

#define JoyX 27 
#define JoyY 26
#define sensibilidade 50 

#define wrap 4096

volatile bool botaoA_press = false;
volatile bool botaoJ_press = false;
ssd1306_t ssd;
bool cor = true;
uint16_t adc_value_x, adc_value_y;

void setup();
void button_isr(uint gpio, uint32_t events);
uint pwm_setup(uint gpio);

int main()
{
    stdio_init_all();
    setup();
    uint sliceB = pwm_setup(pin_blue);
    uint sliceR = pwm_setup(pin_red);
    
    while (true) {  
        adc_select_input(0);
        adc_value_x = adc_read();
        printf("X: %d\n", adc_value_x);
        adc_select_input(1);
        adc_value_y = adc_read();
        printf("Y: %d\n", adc_value_y);

        if (adc_value_x > 1900 && adc_value_x < 2100 && adc_value_y > 1700 && adc_value_y < 2000) {
            // Desliga os LEDs se o joystick estiver centralizado
            pwm_set_gpio_level(pin_red, 0);
            pwm_set_gpio_level(pin_blue, 0);
        } else {
            // Ajusta o brilho dos LEDs com base nos valores do joystick
            uint16_t pwm_value_x = abs(adc_value_x - 2048) * 2;
            uint16_t pwm_value_y = abs(adc_value_y - 2048) * 2;  
            pwm_set_gpio_level(pin_red, pwm_value_x);
            pwm_set_gpio_level(pin_blue, pwm_value_y);
        }
        
        sleep_ms(10);
    }
}

uint pwm_setup(uint gpio){
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, wrap);
    
    pwm_set_enabled(slice_num, true);  
    return slice_num;
}

void setup(){

    gpio_init(botaoA);
    gpio_set_dir(botaoA, GPIO_IN);
    gpio_pull_up(botaoA);
    gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, button_isr);

    gpio_init(botaoJ);
    gpio_set_dir(botaoJ, GPIO_IN);
    gpio_pull_up(botaoJ);
    gpio_set_irq_enabled_with_callback(botaoJ, GPIO_IRQ_EDGE_FALL, true, button_isr);

    i2c_init(I2C_PORT, 400 * 1000); // Configura a comunicação I2C com velocidade de 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADDR, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    adc_init();
    adc_gpio_init(JoyX);
    adc_gpio_init(JoyY);
}

void button_isr(uint gpio, uint32_t events){
    static absolute_time_t last_press = 0;
    absolute_time_t now = get_absolute_time();

    if(absolute_time_diff_us(last_press, now) > 200000){
        if(!gpio_get(botaoA)){
            botaoA_press = true;
        }else{
            if(!gpio_get(botaoJ)){
                botaoJ_press = true;
            }
        }
        last_press = now;
    }
}