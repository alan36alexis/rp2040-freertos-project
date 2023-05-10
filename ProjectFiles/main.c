#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

TaskHandle_t h_ledon, h_ledoff;

void ledon_task()
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        
        gpio_put(LED_PIN, 1);
        vTaskDelay(100);
        vTaskResume(h_ledoff);
        vTaskSuspend(NULL);
    }
}

void ledoff_task()
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {

        gpio_put(LED_PIN, 0);
        vTaskDelay(20);
        vTaskResume(h_ledon);
        vTaskSuspend(NULL);
    }
}

int main()
{
    stdio_init_all();

    xTaskCreate(ledon_task, "LED_Task", 256, NULL, 1, &h_ledon);
    xTaskCreate(ledoff_task, "LED_Task", 256, NULL, 1, &h_ledoff);
    vTaskStartScheduler();

    //while(1){};
}
