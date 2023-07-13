#ifndef _CONFIG_H_
#define _CONFIG_H_

// Librerias externas
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "sdkconfig.h"

#include "xtensa/config/core-isa.h"
#include "esp_err.h"


// incluir todas las tareas aca
/*tareas*/

// pines
#define LED_ESP 2

// uC
#define APP_CORE 1
#define PRO_CORE 0

enum SOS_index{     // enumera los coeficientes del filtro
    K_f = 0,        // constante proporcional del filtro
    b_0 = 1,
    b_1 = 2,
    b_2 = 3,
    a_0 = 4,        // a_0 debe ser siempre = 1
    a_1 = 5,
    a_2 = 6
};



esp_err_t loadConfig();
esp_err_t saveConfig();

#endif