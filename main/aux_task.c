#include "aux_task.h"
#include <math.h>

#define _f 100.0 

TaskHandle_t TaskHandle_aux;                                    // "variable para manejar las tareas"

extern void filtro_II_d_I(int32_t muestra, float* _k_veces_to_p, float* _x, float* _y, float* _SOS);    // filtro

// Ponderacion tipo A
const struct filtro_IIR_2ord A_weighting_0 = {.b_0 = 0.197012037038803, .b_1 = 0.394024074077606, .b_2 = 0.197012037038803, .a_1 = -0.224558457732201, .a_2 = 0.012606625445187, .k_f = 1};
const struct filtro_IIR_2ord A_weighting_1 = {.b_0 = 1, .b_1 = -2, .b_2 = 1, .a_1 = -1.893870472908020, .a_2 = 0.895159780979157, .k_f = 1};
const struct filtro_IIR_2ord A_weighting_2 = {.b_0 = 1, .b_1 = -2, .b_2 = 1, .a_1 = -1.994614481925964, .a_2 = 0.994621694087982, .k_f = 1.18927645683289};


void aux_task(void *parameter){
    printf("Iniciando aux_task\n"); 

    // Parametros del filtro

    float seno = 0;

    const float omega_m = 2.0*MPI*_f/48000.0;
    const float _A = 1.0;

    float n = 0;
    
    struct filtro_IIR_2ord *punt = malloc(3*sizeof(struct filtro_IIR_2ord));
    struct filtro_IIR_2ord *aux_punt;

    aux_punt = punt;

    *punt = A_weighting_0;
    *(punt + 1) = A_weighting_1;
    *(punt + 2) = A_weighting_2;
    // punt = aux_punt;

    

    while (1)
    {
        /*
        seno = _A*sin(omega_m*n);
        printf("%f\n", seno);
        n++;
        if(n>= (48000.0/_f)){
            n=0;
        }
        */

       float *punt_f;

       for (int i=0; i<3; i++){
        punt_f = &punt->b_0;
        for(int j=0; j<6; j++){
            printf(" filtro[%d][%d] = %f\n", i, j, *punt_f);
            punt_f++;
            vTaskDelay(100);
        }
        punt++;
       }
       punt = aux_punt;



        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

esp_err_t aux_launch(){
    xTaskCreatePinnedToCore(             // Use xTaskCreate() in vanilla FreeRTOS
        aux_task,        // Function to be called
        "aux_task",          // Name of task
        10000,             // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,              // Parameter to pass
        2,                   // Task priority
        &TaskHandle_aux, // Task handle
        APP_CORE);              // Run on one core for demo purposes (ESP32 only)

    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}

esp_err_t aux_kill(){
    if (TaskHandle_aux != NULL)
    {
        vTaskDelete(TaskHandle_aux);
        TaskHandle_aux = NULL;
    }
    return(ESP_OK);                     // con este tipo de comandos indico si algo no sale bien
}