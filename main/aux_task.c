#include "aux_task.h"
#include <math.h>

#define _f 100.0 

#define K_Aw 1.189276456832886
#define K_Cw 1.004441738128662

TaskHandle_t TaskHandle_aux;                                    // "variable para manejar las tareas"

cmd_audio_weighting_t ponderacion = C;

extern void filtro_II_d_I(float* muestra_p, float* _x, float* _y, float* _SOS);    // filtro
extern void casting_y_escala(int muestra_cuentas, float* muestra_p, float* k_veces_to_p);
extern void producto_y_acumulacion(float *_y, float *_acu, float *_k);

// Ponderacion tipo A
const struct filtro_IIR_2ord A_weighting_0 = {.b_0 = 0.197012037038803, .b_1 = 0.394024074077606, .b_2 = 0.197012037038803, .a_1 = -0.224558457732201, .a_2 = 0.012606625445187, .k_f = 1};
const struct filtro_IIR_2ord A_weighting_1 = {.b_0 = 1, .b_1 = -2, .b_2 = 1, .a_1 = -1.994614481925964, .a_2 = 0.994621694087982, .k_f = 1};
const struct filtro_IIR_2ord A_weighting_2 = {.b_0 = 1, .b_1 = -2, .b_2 = 1, .a_1 = -1.893870472908020, .a_2 = 0.895159780979157, .k_f = 1};

void aux_task(void *parameter){
    printf("Iniciando aux_task\n"); 

    // Parametros del filtro

    float seno = 0;

    const float omega_m = 2.0*MPI*_f/48000.0;
    const float _A = 1.0;

    float n = 0;

    float acumulador = 0;
    float k_cw = K_Cw;
    float k_aw = K_Aw;
    
    struct filtro_IIR_2ord *punt = malloc(3*sizeof(struct filtro_IIR_2ord));    // reservo memoria para tener todos los parametros del filtro en direcciones contiguas
    struct filtro_IIR_2ord *aux_punt;                                               // es para no perder la direccion donde empiezan los parametros del filtro

    aux_punt = punt;
    // guardo en memoria los parametros del filtro
    *punt = A_weighting_0;
    *(punt + 1) = A_weighting_1;
    *(punt + 2) = A_weighting_2;

    float *x_1, *x_2, *x_3, *y_1, *y_2, *y_3; // buffers de x[n] e y[n]
    x_1 = malloc(3*sizeof(float));
    x_2 = malloc(3*sizeof(float));
    x_3 = malloc(3*sizeof(float));
    y_1 = malloc(3*sizeof(float));
    y_2 = malloc(3*sizeof(float));
    y_3 = malloc(3*sizeof(float));

    float _k_veces_to_p = 0.000003695;

    float tuvieja = 0;
    float tuhermana = 1.1;
    float kaka = 1.25;

    for(int i = 0; i<3; i++){
        *(x_1+i) = 0;
        *(x_2+i) = 0;
        *(x_3+i) = 0;
        *(y_1+i) = 0;
        *(y_2+i) = 0;
        *(y_3+i) = 0;
    }

    while (1)
    {
        seno = _A*sin(omega_m*n);

        if(ponderacion != Z){
            filtro_II_d_I(&seno, x_1, y_1, &punt->b_0);
            punt++;
            filtro_II_d_I(y_1, x_2, y_2, &punt->b_0);
            if(ponderacion == A){
                punt++;
                filtro_II_d_I(y_2, x_3, y_3, &punt->b_0);
                producto_y_acumulacion(y_3, &acumulador, &k_aw);
            }else{
                producto_y_acumulacion(y_2, &acumulador, &k_cw);
            }
            punt = aux_punt;
        }


        // casting_y_escala(&enterito, &flotantesito, _k_veces_to_p);
        
        
        printf("%f\t%f\n", seno, k_cw*(*y_1));

       n++;




        vTaskDelay(pdMS_TO_TICKS(100));
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
