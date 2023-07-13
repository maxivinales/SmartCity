#include "logica_control.h"
#include "esp_err.h"
#include "freertos/projdefs.h"

TaskHandle_t TaskHandle_control;

void control_task(void *parameter){
    printf("Iniciando control_task\n");

    while (1)
    {
        printf("control_task\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

esp_err_t control_launch(){
    xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
        control_task,        // Function to be called
        "control_task",      // Name of task
        10000,               // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                // Parameter to pass
        1,                   // Task priority
        &TaskHandle_control, // Task handle
        APP_CORE);           // Run on one core for demo purposes (ESP32 only)
    return(ESP_OK);
}

esp_err_t control_kill(){
    if (TaskHandle_control != NULL)
    {
        vTaskDelete(TaskHandle_control);
        TaskHandle_control = NULL;
    }
    return(ESP_OK);
}