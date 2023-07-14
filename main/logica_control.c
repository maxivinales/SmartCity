#include "logica_control.h"

#include "Leq_task.c"
#include "aux_task.c"
#include "config.h"

TaskHandle_t TaskHandle_control;
QueueHandle_t msg_queue_toControl = NULL;

void control_task(void *parameter){
    struct data_t msd_control_buffer;
    printf("Iniciando control_task\n");
    aux_launch();   // lanzo mi tarea auxiliar

    TickType_t xPeriod = pdMS_TO_TICKS(30000);

    while (1)
    {
        if (xQueueReceive(msg_queue_toControl, (void *)&msg_queue_toControl, xPeriod) == pdTRUE){
            printf("dentro de control task papu\n");
        }
        // vTaskDelay(pdMS_TO_TICKS(1000));        // miro cada 10 ms
    }
}

esp_err_t control_launch(){
    msg_queue_toControl = xQueueCreate(MSG_QUEUE_LENGTH, sizeof(struct data_t));

    xTaskCreatePinnedToCore(             // Use xTaskCreate() in vanilla FreeRTOS
        control_task,        // Function to be called
        "control_task",          // Name of task
        10000,             // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,              // Parameter to pass
        1,                   // Task priority
        &TaskHandle_control, // Task handle
        APP_CORE);              // Run on one core for demo purposes (ESP32 only)

    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}

esp_err_t control_kill(){
    if (TaskHandle_control != NULL)
    {
        vTaskDelete(TaskHandle_control);
        TaskHandle_control = NULL;
    }

    if (msg_queue_toControl != NULL)
    {
        vQueueDelete(msg_queue_toControl);
        msg_queue_toControl = NULL;
    }

    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}