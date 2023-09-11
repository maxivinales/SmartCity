#include "http_client.h"

const char *TAG_http_client = "HTTTP client";

esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        cJSON *Jsonsito = cJSON_Parse((char *)evt->data);

        if(Jsonsito == NULL) {
            ESP_LOGW(TAG_http_client, "Error al analizar el JSON\n");
            const char *error_ptr = cJSON_GetErrorPtr();
            if (error_ptr != NULL) {
                printf("Error: %s\n", error_ptr);
            }
            return(ESP_FAIL);
        }

         cJSON *firmware_version = cJSON_GetObjectItemCaseSensitive(Jsonsito, "firmware_version");
        if (firmware_version != NULL) {
            printf("firmware_version: %s\n", firmware_version->valuestring);
            strcpy(new_firmware_version.value_str, firmware_version->valuestring);
            new_firmware_version.value = 1;
        } else {
            ESP_LOGW(TAG_http_client, "Objeto get_chipid no encontrado o no válido\n");
            return(ESP_FAIL);
        }

        break;

    default:
        break;
    }
    return ESP_OK;
}

static void rest_get()
{
    esp_http_client_config_t config_get = {
        .url = "http://fabrica.faniot.ar:1880/ota/firmwareversion?chip_id=C44F33605219",//"http://worldclockapi.com/api/json/utc/now",
        .method = HTTP_METHOD_GET,
        .cert_pem = NULL,
        .event_handler = client_event_get_handler};
        
    esp_http_client_handle_t client = esp_http_client_init(&config_get);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}