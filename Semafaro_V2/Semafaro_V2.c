#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ws2812.pio.h"
#include "hardware/pwm.h"
#include "ssd1306.h"
#include "font.h"

#define vermelho 13
#define verde 11
#define azul 12
#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define PWM_WRAP 4095
#define PWM_CLK_DIV 30.52f
#define buzzer1 10
#define buzzer2 21
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define botaoa 5

ssd1306_t ssd;
bool global = false;
absolute_time_t last_interrupt_time = 0;
volatile uint8_t cor_atual = 0;

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

int i = 0;

double desenho0[25] = {
    0.2, 0.2, 0.2, 0.2, 0.2,
    0.2, 0.2, 0.2, 0.2, 0.2,
    0.2, 0.2, 0.2, 0.2, 0.2,
    0.2, 0.2, 0.2, 0.2, 0.2,
    0.2, 0.2, 0.2, 0.2, 0.2
};

void num0(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho0[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

// Desenho do número 1
double desenho1[25] = 
    {0.0, 0.2, 0.0, 0.2, 0.0,
     0.0, 0.0, 0.2, 0.0, 0.0,
     0.0, 0.2, 0.2, 0.2, 0.0,
     0.0, 0.0, 0.2, 0.0, 0.0,
     0.0, 0.0, 0.2, 0.2, 0.0};

void num1(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho1[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

//configurações do PWM
void pwm_init_gpio(uint gpio, uint wrap, float clkdiv) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, wrap);
    pwm_config_set_clkdiv(&config, clkdiv);
    pwm_init(slice_num, &config, true);
}

void vDisplayTask(){
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    while(true){
        ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
        if(global == 0){

            cor_atual = 0;
            //vermelho
            num0(255,0,0); //define a cor da matriz de LED RBG
            for(int i = 0; i < 4000; i++) {
                vTaskDelay(pdMS_TO_TICKS(1));
                if(global != 0) {break;}
            }

            //amarelo
            cor_atual = 1;
            num0(255,255,0); //define a cor da matriz de LED RBG
            for(int i = 0; i < 2000; i++) {
                vTaskDelay(pdMS_TO_TICKS(1));
                if(global != 0) {break;}
            }
            //verde
            cor_atual = 2;
            num1(0,255,0);
            for(int i = 0; i < 4000; i++) {
                vTaskDelay(pdMS_TO_TICKS(1));
                if(global != 0) {break;}
            }

        }
        else if(global == 1){
            num0(255,255,0);
            vTaskDelay(pdMS_TO_TICKS(1000));

        }
    }   
}
//Task do LED RGB
void vPiscaTask(){
    //inicializa os pinos LED RBG
    gpio_init(vermelho);
    gpio_set_dir(vermelho, GPIO_OUT);
    gpio_init(verde);
    gpio_set_dir(verde, GPIO_OUT);
    gpio_init(azul);
    gpio_set_dir(azul, GPIO_OUT);
    while(true){
        if(global == 0){
            //SEMAFARO
            gpio_put(verde, true);
            for(int i = 0; i < 4000; i++) {
                //verifica o estado da variável "Global" a cada 1 milisegundo 
                vTaskDelay(pdMS_TO_TICKS(1));
                if(global != 0) {break;}
            }

            gpio_put(verde, false);
            gpio_put(verde, true);
            gpio_put(vermelho, true);
            for(int i = 0; i < 2000; i++) {
                vTaskDelay(pdMS_TO_TICKS(1));
                if(global != 0) {break;}
            }           
            gpio_put(verde, false);
            gpio_put(vermelho, false);
            gpio_put(vermelho, true);
            for(int i = 0; i < 4000; i++) {
                vTaskDelay(pdMS_TO_TICKS(1));
                if(global != 0) {break;}
            }
            gpio_put(vermelho, false);
        }
        else if(global == 1){
            gpio_put(vermelho, true);
            gpio_put(verde, true);
            vTaskDelay(pdMS_TO_TICKS(1000));
            gpio_put(vermelho, false);
            gpio_put(verde, false);
        }
    }
}
//Task dos buzzers
void vBuzzerTask(){
    pwm_init_gpio(buzzer1, 500, 125.0f);
    while(1){
        if(global == 0){
            if(cor_atual == 0){
                pwm_set_gpio_level(buzzer1, 250); // 50%
                pwm_set_gpio_level(buzzer2, 250);
                vTaskDelay(pdMS_TO_TICKS(500));
                pwm_set_gpio_level(buzzer1, 0);   // silencia
                pwm_set_gpio_level(buzzer2, 0);   // silencia
                vTaskDelay(pdMS_TO_TICKS(1500));
                printf("Vermelho\n");
            }
            else if(cor_atual == 1){
                pwm_set_gpio_level(buzzer1, 250);
                pwm_set_gpio_level(buzzer2, 250);
                vTaskDelay(pdMS_TO_TICKS(100));
                pwm_set_gpio_level(buzzer1, 0);
                pwm_set_gpio_level(buzzer2, 0);
                vTaskDelay(pdMS_TO_TICKS(100));
                printf("Amarelo\n");
            }
            else if(cor_atual == 2){
                pwm_set_gpio_level(buzzer1, 250); // 50%
                pwm_set_gpio_level(buzzer2, 250);
                vTaskDelay(pdMS_TO_TICKS(200));
                pwm_set_gpio_level(buzzer1, 0);   // silencia
                pwm_set_gpio_level(buzzer2, 0);   // silencia
                vTaskDelay(pdMS_TO_TICKS(800));
                printf("Verde\n");
            } 
        }
        else if(global == 1){

            pwm_set_gpio_level(buzzer1, 250);
            pwm_set_gpio_level(buzzer2, 250);
            vTaskDelay(pdMS_TO_TICKS(100));
            pwm_set_gpio_level(buzzer1, 0);
            pwm_set_gpio_level(buzzer2, 0);
            vTaskDelay(pdMS_TO_TICKS(1900));
        }

    }
}
void vMensagemTask(){
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
  gpio_pull_up(I2C_SDA);                                        // Pull up the data line
  gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
  ssd1306_config(&ssd);                                         // Configura o display
  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);
  bool cor = true;
  while(true){  
    ssd1306_fill(&ssd, !cor);                          // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor);      // Desenha um retângulo
    if(global == 0){
        if(cor_atual == 0){
            //Vermelho
            ssd1306_draw_string(&ssd, "Pare", 12, 28);  // Desenha uma string
    
        }
        else if(cor_atual == 1){
            //Amarelo
            ssd1306_draw_string(&ssd, "Atencao", 11, 28);  // Desenha uma string
        
        }
        else if(cor_atual == 2){
            //Verde
            ssd1306_draw_string(&ssd, "Pode Atravesar", 10, 28);  // Desenha uma string 
            
        }
    }
    else if(global == 1){
        ssd1306_draw_string(&ssd, "Modo Noturno", 10, 28);  // Desenha uma string 
    }
    ssd1306_send_data(&ssd);          
  }
}
//Task para o botão A
void vBotaoATask(){
    bool last_state = true;
    gpio_init(botaoa);
    gpio_pull_up(botaoa);  // Ativa o resistor de pull-up interno
    gpio_set_dir(botaoa, GPIO_IN);
    while(true){
        bool current_state = gpio_get(botaoa);
        if(last_state && !current_state){
            //Intercala entre os estados
            global = !global;
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
int main()
{


    stdio_init_all();
    //chamada das tasks da função principal
    xTaskCreate(vPiscaTask, "Pisca Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY +3, NULL);
    xTaskCreate(vDisplayTask, "RBG Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY +3, NULL);
    xTaskCreate(vBuzzerTask, "Buzzer Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY +1, NULL);
    xTaskCreate(vMensagemTask, "Mensagem Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY +1, NULL);
    xTaskCreate(vBotaoATask, "Botao Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY +3, NULL);

    vTaskStartScheduler();
    panic_unsupported();

}
