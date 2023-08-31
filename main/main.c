#include "config.c"
#include "WiFi_manager.c"
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
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");          // mensaje de debug por serial
    wifi_init_softap();                         // inicia el WiFi en Modo AP
    ESP_LOGW(TAG, "Luego del WiFi ->[APP] Free memory: %lu bytes", esp_get_free_heap_size());
    if(server == NULL){
        server = start_webserver();
    }
}
