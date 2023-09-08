#include "config.c"
#include "logica_control.c"
// #include "WiFi_manager.c"

// recursos RTOS
SemaphoreHandle_t mutex_handles;

void app_main(void)
{  
    mutex_handles = xSemaphoreCreateMutex();
    control_launch();

    // while (1)
    // {
        
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    // }
   
}
