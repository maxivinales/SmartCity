#ifndef _AUX_TASK_H_
#define _AUX_TASK_H_

#include "config.h"

struct filtro_IIR_2ord
{
    // constantes del filtro
    float b_0;
    float b_1;
    float b_2;
    float a_1;
    float a_2;
    
    // constante de escala
    float k_f;
    // funcion para cargar los parametros del filtro
    // esp_err_t carga_filtro(float);
};

esp_err_t aux_launch();
esp_err_t aux_kill();
void casting_y_escala(int* , float* , float);

#endif