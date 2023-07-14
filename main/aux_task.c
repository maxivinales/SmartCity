#include "aux_task.h"
#include <math.h>

#define _f 100.0

TaskHandle_t TaskHandle_aux;                                    // "variable para manejar las tareas"

void aux_task(void *parameter){
    printf("Iniciando aux_task\n");

    float seno = 0;

    const float omega_m = 2.0*MPI*_f/48000.0;
    const float _A = 1.0;

    float n = 0;

    while (1)
    {
        seno = _A*sin(omega_m*n);
        printf("%f\n", seno);
        n++;
        if(n>= (48000.0/_f)){
            n=0;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

esp_err_t aux_launch(){
    xTaskCreatePinnedToCore(             // Use xTaskCreate() in vanilla FreeRTOS
        aux_task,        // Function to be called
        "aux_task",          // Name of task
        10000,             // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,              // Parameter to pass
        2,                   // Task priority
        &TaskHandle_aux, // Task handle
        APP_CORE);              // Run on one core for demo purposes (ESP32 only)

    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}

esp_err_t aux_kill(){
    if (TaskHandle_aux != NULL)
    {
        vTaskDelete(TaskHandle_aux);
        TaskHandle_aux = NULL;
    }
    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}