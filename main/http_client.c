#include "http_client.h"
#include "esp_http_client.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const char *TAG_http_client = "HTTTP client";

bool http_receiving = false;
char *recv_http = NULL; // Inicializa a NULL

esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %d, %s\n", evt->data_len, (char *)evt->data);
        if (evt->data_len > 0) {
            if (http_receiving == false) {
                http_receiving = true;
                recv_http = malloc((evt->data_len + 1) * sizeof(char)); // +1 para el carácter nulo
                if (recv_http == NULL) {
                    ESP_LOGE(TAG_http_client, "Error de asignación de memoria\n");
                    return ESP_FAIL;
                }
                strcpy(recv_http, (char *)evt->data);
            } else {
                char *aux_S1;
                size_t len_string = strlen(recv_http) + 1 + evt->data_len + 1; // +1 para el carácter nulo
                aux_S1 = malloc(len_string);
                if (aux_S1 == NULL) {
                    ESP_LOGE(TAG_http_client, "Error de asignación de memoria\n");
                    return ESP_FAIL;
                }
                snprintf(aux_S1, len_string, "%s%s", recv_http, (char *)evt->data);
                free(recv_http);
                recv_http = aux_S1;
            }
        }
        break;
    case HTTP_EVENT_ON_FINISH:
        printf("HTTP_EVENT_ON_FINISH: %s\n", recv_http);
        if (http_receiving == true) {
            http_receiving = false;
            cJSON *Jsonsito = cJSON_Parse(recv_http);

            if (Jsonsito == NULL) {
                ESP_LOGW(TAG_http_client, "Error al analizar el JSON\n");
                const char *error_ptr = cJSON_GetErrorPtr();
                if (error_ptr != NULL) {
                    printf("Error: %s\n", error_ptr);
                }
                free(recv_http); // Libera la memoria antes de salir
                return ESP_FAIL;
            }

            cJSON *firmware_version = cJSON_GetObjectItemCaseSensitive(Jsonsito, "firmware_version");
            if (firmware_version != NULL) {
                printf("firmware_version: %s\n", firmware_version->valuestring);
                strcpy(new_firmware_version.value_str, firmware_version->valuestring);
                new_firmware_version.value = 1;
            } else {
                ESP_LOGW(TAG_http_client, "Objeto firmware_version no encontrado o no válido\n");
                // return ESP_FAIL;
            }

            cJSON *datetime = cJSON_GetObjectItemCaseSensitive(Jsonsito, "datetime");
            if (datetime != NULL) {
                printf("datetime: %s\n", datetime->valuestring);
                strcpy(fecha_y_hora.value_str, datetime->valuestring);
                // TRABAJAR DESDE ACA
            } else {
                ESP_LOGW(TAG_http_client, "Objeto datetime no encontrado o no válido\n");
                // return ESP_FAIL;
            }

            free(recv_http); // Libera la memoria después de analizar el JSON
            recv_http = NULL; // Establece el puntero a NULL para evitar errores futuros
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
        // .buffer_size = 1024,
        .event_handler = client_event_get_handler};
        
    esp_http_client_handle_t client = esp_http_client_init(&config_get);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
    // esp_http_client_close(client);
}

void get_data_time(char* _URL){
    esp_http_client_config_t config_get = {
        .url = _URL,
        .method = HTTP_METHOD_GET,
        .cert_pem = NULL,
        .buffer_size = 1024,
        .event_handler = client_event_get_handler};
        
    esp_http_client_handle_t client = esp_http_client_init(&config_get);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
    // esp_http_client_close(client);
}