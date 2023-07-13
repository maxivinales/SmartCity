#include "config.c"
#include "logica_control.c"

void app_main(void)
{  
    loadConfig();
    vTaskDelay(pdMS_TO_TICKS(200));
    control_launch();
    // while (1)
    // {
        
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    // }
    

}
