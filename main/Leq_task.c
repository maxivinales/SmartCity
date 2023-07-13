#include "Leq_task.h"

TaskHandle_t TaskHandle_Leq;

void Leq_task(void *parameter){
    printf("Iniciando Leq_task\n");

    while (1)
    {
        printf("Leq_task\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

esp_err_t Leq_launch(){
    xTaskCreatePinnedToCore(             // Use xTaskCreate() in vanilla FreeRTOS
        Leq_task,        // Function to be called
        "Leq_task",          // Name of task
        10000,             // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,              // Parameter to pass
        1,                   // Task priority
        &TaskHandle_Leq, // Task handle
        APP_CORE);              // Run on one core for demo purposes (ESP32 only)

    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}

esp_err_t Leq_kill(){
    if (TaskHandle_Leq != NULL)
    {
        vTaskDelete(TaskHandle_Leq);
        TaskHandle_Leq = NULL;
    }
    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}