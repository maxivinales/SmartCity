#ifndef _OTA_H_
#define _OTA_H_

#include "config.h"

#define OTA_URL_SIZE 256
#define CONFIG_OTA_RECV_TIMEOUT 5000

static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
static esp_err_t validate_image_header(esp_app_desc_t *new_app_info);

static esp_err_t _http_client_init_cb(esp_http_client_handle_t http_client);
// void advanced_ota_example_task(void *pvParameter);      // este lo tengo que cambiar

// esp_err_t get_firmware_version(char* _chipid, char* _dest_firmware_version);
esp_err_t update_firmware(char* _chipid);               // este hereda la mayoria de las cosas de advanced_ota_example_task

esp_err_t init_OTA(void);

// esp_err_t OTA_launch();
// esp_err_t OTA_kill();

#endif