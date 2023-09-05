#ifndef _CONFIG_H_
#define _CONFIG_H_

// Librerias externas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/gpio.h"

// #include <stdio.h>

#include "esp_err.h"
#include "esp_wifi_types.h"
#include "esp_wifi_default.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/projdefs.h"
// #include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include <esp_system.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>


#include <cJSON.h>      // librerpia para manejar Json

// #include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"


// #include "esp_log.h"
#include "sdkconfig.h"

#include "xtensa/config/core-isa.h"
// #include "esp_err.h"

// #include <string.h>


// incluir todas las tareas aca
/*tareas*/

// pines
#define LED_ESP 2

// uC
#define APP_CORE 1
#define PRO_CORE 0

// constantes
#ifndef MPI         // numero pi
#define MPI 3.14159265358979323846
#endif

#define MSG_QUEUE_LENGTH 20
#define MSG_QUEUE_TOSENSOR_LENGTH 5

//// Cuestiones referidas al WiFi
struct WiFi_data_t{
    char SSID[32];
    char pass[64];
    wifi_auth_mode_t authmode;
};

struct MQTT_user_data_t{
    char User[32];
    char pass[64];
};






// enum SOS_index{     // enumera los coeficientes del filtro
//     K_f = 0,        // constante proporcional del filtro
//     b_0 = 1,
//     b_1 = 2,
//     b_2 = 3,
//     a_0 = 4,        // a_0 debe ser siempre = 1
//     a_1 = 5,
//     a_2 = 6
// };

typedef enum    //definimos un tipo de datos categoricos, para trabajar mas comodamente
{               //puede tomar uno de los valores a continuacion
    NADA,
    SAVE
} cmd_control_t;

typedef enum    //definimos un tipo de datos categoricos, para trabajar mas comodamente
{               //puede tomar uno de los valores a continuacion
    Z,
    A,
    C
} cmd_audio_weighting_t;


struct data_t{
    cmd_control_t cmd;  //mensaje de control
    int value;          //valor entero que se puede usar depende de lo que uno necesite
    float value_f;      //valor flotante que se puede usar depende de lo que uno necesite
    char  value_str[32]; //string que se puede usar depende de lo que uno necesite
};

esp_err_t loadConfig();
esp_err_t saveConfig();

esp_err_t get_chipid();

// Variables
struct WiFi_data_t data_WiFi_SC;
struct MQTT_user_data_t data_MQTT_SC;

nvs_handle_t handle_NVS;   // para guardar SSID y pass

struct data_t MAC;          // la diferencia entre CHIPID y MAC es que CHIPID está en ascii y MAC en hex
struct data_t CHIPID;
struct data_t mode_WiFi_manager = {.value = 0};    // .value = 0 -> WiFi manager encendido, .value = 1 -> WiFi manager apagado
struct data_t SSID_WiFi_Manager = {.value_str  = "Smart City"}; // nombre de la red WiFi, se cambia luego por el nombre del dispositivo y el chipid


#endif