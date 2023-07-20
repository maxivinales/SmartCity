#include "aux_task.h"
#include <math.h>

#define _f 8000.0 

#define K_Aw 1.189276456832886
#define K_Cw 1.004441738128662

#define F_sample 48000.0

TaskHandle_t TaskHandle_aux;                                    // "variable para manejar las tareas"

cmd_audio_weighting_t ponderacion = A;

extern void filtro_II_d_I(float* muestra_p, float* _x, float* _y, float* _SOS);    // filtro
extern void casting_y_escala(int muestra_cuentas, float* muestra_p, float* k_veces_to_p);
extern void producto_y_acumulacion(float *_y, float *_acu, float *_k);
extern void test_asm(float* x, float* y, float* z);

// Ponderacion tipo A
const struct filtro_IIR_2ord A_weighting_0 = {.b_0 = 0.197012037038803, .b_1 = 0.394024074077606, .b_2 = 0.197012037038803, .a_1 = -0.224558457732201, .a_2 = 0.012606625445187, .k_f = 1};
const struct filtro_IIR_2ord A_weighting_1 = {.b_0 = 1, .b_1 = -2, .b_2 = 1, .a_1 = -1.893870472908020, .a_2 = 0.895159780979157, .k_f = 1};
const struct filtro_IIR_2ord A_weighting_2 = {.b_0 = 1, .b_1 = -2, .b_2 = 1, .a_1 = -1.994614481925964, .a_2 = 0.994621694087982, .k_f = 1};

float k_cw = K_Cw;
float k_aw = K_Aw;

void aux_task(void *parameter){
    printf("Iniciando aux_task\n"); 

    // Parametros del filtro

    float seno = 0;

    const float omega_m = 2.0*MPI*_f/48000.0;
    const float _A = 1.0;

    float n = 0;

    float acumulador = 0;
    
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

    float *xa, *xb, *xc, *ya, *yb, *yc;
    xa = malloc(3*sizeof(float));
    xb = malloc(3*sizeof(float));
    xc = malloc(3*sizeof(float));
    ya = malloc(3*sizeof(float));
    yb = malloc(3*sizeof(float));
    yc = malloc(3*sizeof(float));

    float _k_veces_to_p = 0.000003695;

    float tuvieja = 1;
    float tuhermana = 0.2;
    float kaka = 0.3;

    for(int i = 0; i<3; i++){
        *(x_1+i) = 0;
        *(x_2+i) = 0;
        *(x_3+i) = 0;
        *(y_1+i) = 0;
        *(y_2+i) = 0;
        *(y_3+i) = 0;

        *(xa+i) = 0;
        *(xb+i) = 0;
        *(xc+i) = 0;
        *(ya+i) = 0;
        *(yb+i) = 0;
        *(yc+i) = 0;
    } // voy a probar el filtro en el void

    int aux1 = 10;
    float aux2 = 1, aux3 = 1;

    uint32_t tiempo;

    test_filtro();
    while (1)
    {
        /*
        seno = _A*sin(omega_m*n);
        tiempo = esp_cpu_get_cycle_count();             // tomo los ciclos del procesador
        casting_y_escala(aux1, &aux2, &aux3);
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
        tiempo = esp_cpu_get_cycle_count() - tiempo;             // tomo los ciclos del procesador


        // casting_y_escala(&enterito, &flotantesito, _k_veces_to_p);
        
        
        // printf("%f\t%f\n", seno, k_aw*(*y_3));
        printf("tiempo procesamiento: %ld ns\n", 4*tiempo);

       n++;

        // test_asm(&tuvieja, &tuhermana, &kaka);
        // printf("x = %f\ty = %f\t z = %f\n", tuvieja, tuhermana, kaka);

        */
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void test_filtro(void){
    printf("test filtro");
    float frecuencias[34] = {10, 12.59, 15.85, 19.95, 25.12, 31.62, 39.81, 50.12, 63.1, 79.43, 100, 125.9, 158.5, 199.5, 251.2, 316.2, 398.1, 501.2, 63, 794.3, 1000, 1259, 1585, 1995, 2512, 3162, 3981, 5012, 6310, 7943, 10000, 12590, 15850, 19950};
    float atenuacion_A_IRAM[34] = {-70.4, -63.4, -56.7, -50.5, -44.7, -39.4, -34.6, -30.2, -26.2, -22.5, -19.1, -16.1, -13.4, -10.9, -8.6, -6.6, -4.8, -3.2, -1.9, -0.8, 0, 0.6, 1, 1.2, 1.3, 1.2, 1, 0.5, -0.1, -1.1, -2.5, -4.3, -6.6, -9.3};
    float atenuacion_C_IRAM[34] = {-14.3, -11.2, -8.5, -6.2, -4.4, -3, -2, -1.3, -0.8, -0.5, -0.3, -0.2, -0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.1, -0.2, -0.3, -0.5, -0.8, -1.3, -2, -3, -4.4, -6.2, -8.5, -11.2};
    float atenuacion_A_nuestra[34], atenuacion_C_nuestra[34];

    int ciclos_A, ciclos_C;

    struct filtro_IIR_2ord* punt_test = malloc(3*sizeof(struct filtro_IIR_2ord));
    *(punt_test+0) = A_weighting_0;
    *(punt_test+1) = A_weighting_1;
    *(punt_test+2) = A_weighting_2;

    float *x0, *x1, *x2, *y0, *y1, *y2;
    x0 = malloc(3*sizeof(float));
    x1 = malloc(3*sizeof(float));
    x2 = malloc(3*sizeof(float));
    y0 = malloc(3*sizeof(float));
    y1 = malloc(3*sizeof(float));
    y2 = malloc(3*sizeof(float));

    float *xa, *xb, *xc, *ya, *yb, *yc;
    xa = malloc(3*sizeof(float));
    xb = malloc(3*sizeof(float));
    xc = malloc(3*sizeof(float));
    ya = malloc(3*sizeof(float));
    yb = malloc(3*sizeof(float));
    yc = malloc(3*sizeof(float));
    printf("linea 168");
    for(int i=0; i<3; i++){
        *(x0+i) = 0;
        *(x1+i) = 0;
        *(x2+i) = 0;
        *(xa+i) = 0;
        *(xb+i) = 0;
        *(xc+i) = 0;

        *(y0+i) = 0;
        *(y1+i) = 0;
        *(y2+i) = 0;
        *(ya+i) = 0;
        *(yb+i) = 0;
        *(yc+i) = 0;
    }

    float frecuencia, omega, seno;
    int seno_int;
    float Amplitud = 1;
    float k_p_m = (1.0/10000.0);

    float acumulador_seno, acumulador_A, acumulador_C;
    acumulador_seno = 0;
    acumulador_A = 0;
    acumulador_C = 0;
    printf("linea 194");
    for(int i=0; i<34; i++){
        omega = 2.0*MPI*frecuencias[i]/48000.0;
        printf("linea 197");
        int N_muestras = (int)(frecuencias[i]*15*F_sample);    // defino la cantidad de muestras para 15 periodos
        for(int j=0;j<N_muestras;j++){
            seno_int = (int)(10000.0*sin(omega*j));
            // Ponderacion A
            ciclos_A = esp_cpu_get_cycle_count(); 
            casting_y_escala(seno_int, &seno, &k_p_m);
            filtro_II_d_I(&seno, x0, y0, &(punt_test+0)->b_0);
            filtro_II_d_I(y0, x1, y1, &(punt_test+1)->b_0);
            filtro_II_d_I(y1, x2, y2, &(punt_test+2)->b_0);
            producto_y_acumulacion(y2, &acumulador_A, &k_aw);
            ciclos_A = esp_cpu_get_cycle_count() - ciclos_A; 

            // Ponderacion C
            ciclos_C = esp_cpu_get_cycle_count(); 
            casting_y_escala(seno_int, &seno, &k_p_m);
            filtro_II_d_I(&seno, xa, ya, &(punt_test+0)->b_0);
            filtro_II_d_I(ya, xb, yb, &(punt_test+2)->b_0);
            producto_y_acumulacion(yb, &acumulador_C, &k_cw);
            ciclos_C = esp_cpu_get_cycle_count() - ciclos_C;
            
            acumulador_seno = acumulador_seno +  seno*seno;       // acumulo para calcular el rms en 1 s
        }

        atenuacion_A_nuestra[i] = 20.0*log10((acumulador_A)/(acumulador_seno));
        atenuacion_C_nuestra[i] = 20.0*log10((acumulador_C)/(acumulador_seno));
        // printf("\n\nciclos_A = %d\tciclos_C = %d\n\n", ciclos_A, ciclos_C);
        // vTaskDelay(pdMS_TO_TICKS(20));
        printf("dBA_filtro\tdBA_IRAM\tdBC_flitro\tdBC_IRAM\n");
        vTaskDelay(pdMS_TO_TICKS(20));
        printf("%f\t%f\t%f\t%f\n", atenuacion_A_nuestra[i], atenuacion_A_IRAM[i], atenuacion_C_nuestra[i], atenuacion_C_IRAM[i]);
    }
}

esp_err_t aux_launch(){
    xTaskCreatePinnedToCore(             // Use xTaskCreate() in vanilla FreeRTOS
        aux_task,        // Function to be called
        "aux_task",          // Name of task
        100000,             // Stack size (bytes in ESP32, words in FreeRTOS)
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
