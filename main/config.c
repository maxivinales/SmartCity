#include "config.h"

static const char *TAG_CONFIG = "Configuracion";

esp_err_t loadConfig(){
    ESP_LOGW(TAG_CONFIG, "Inicio ->[APP] Free memory: %lu bytes", esp_get_free_heap_size());
    esp_err_t ret = nvs_flash_init();           // inicializa el manejo de memoria flash (creo que no es la spiffs)
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) { // si tira uno de esos errores
      ESP_ERROR_CHECK(nvs_flash_erase());       // limpia la memoria
      ret = nvs_flash_init();                   // e inicializa nuevamente
    }
    ESP_ERROR_CHECK(ret);                       // comprueba nuevamente los errores

    printf("Cargando configuración\n");
    return(ESP_OK);
}

esp_err_t saveConfig(){
    printf("Guardando configuración\n");
    return(ESP_OK);
}