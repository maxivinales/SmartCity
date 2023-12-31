<!-- | Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# _Sample project_

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)



## How to use example
We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py. -->

# Sonometro IoT
***
Este es el firmware para uno de los sensores Smart City enmarcados en el ANR denominado ***Desarrollo De Sensores IOT-Ciudades Inteligentes para Implementación en el Municipio de Oberá-Misiones en áreas Urbanas, Rurales, Reservas Naturales e Industriales con investigación y análisis de aspectos integrales de Ciudad Inteligentes para mejora de procesos de Gobernanza y modernización tecnológica*** enmarcado en el PFIP2022.
La idea es obtener un sonómetro de clase 2 o superior que sea certificable por IRAM y el INTI.
Se decidió utilizar en este proyecto el IDE ***ESP IDF*** provisto por el mismo Espressif, el cual cuenta con muchos mas recursos para manejar el hardware del  los microcontroladores ESP32 y ESP8266, programandose en C y Assembler.
El microcontrolador a utilizarse es la ESP32, la hoja de datos del mismo está en (introducir enlace) y el set de introducciones en (introducir enlace).

(hablar algo de RTOS)
## Tabla de contenidos

- **Especificaciones Técnicas según IRAM4074 y otras IRAM**
- **Estructura del proyecto de firmware**
    - **RTOS**
    - **main**
    - **config**
    - **logica_control**
    - **audio_task**

***
## Especificaciones Técnicas según IRAM4074 y otras IRAM

Debe ser de clase 2, para lo cual debe cumplir con las siguientes especificaciones:
1. Medir mínimamente con ponderaciones A y C (ubicaciones de polos y ceros en IRAM 4074 - 1 pág 12 y 13), y lineal (sin filtro).
1. Mínimamente ponderaciones tem
1. Rango de linealidad de 50 dB (Tabla 2 IRAM 4074 - 3)
1. Tolerancia ±1 dB (Tabla 2 IRAM 4074 - 3)
1. Demás valores de la Tabla 2 IRAM 4074 - 3 (ensayos de pulsos).
1. Sensibilidad entre 20 Hz y 20 kHz
1. Omnidireccional
1. Cambio máximo en medición durante 1 h de 0,5 dB (según Tabla 1 IRAM 4074 - 3)
1. Debe tener indicador de sobrecarga (overload)
1. Debe tener una tolerancia con respecto al factor de cresta menor a los de la Tabla 3 IRAM 4074 - 3
1. Frecuencia de muestreo de 48 kHz
1. Micrófono analógico, desmontable para sustituirlo por una señal eléctrica
1. Debe detectar picos (en dB)
1. Deberá tener una resolución de 0,1 dB o mayor
1. Para una variación de ±10% en la presión estática, debe variar como mucho ±0,5 dB en la medición.
1. Debe cumplir con el ensayo “Tone Burst”, que es detectar “trenes de pulsos” de ondas senoidales, es decir, una serie de periodos de ondas senoidales (que arrancan y terminan en 0). frecuencia de las ondas senoidales debe ser de 2000 Hz, y debe repetirse a 2 Hz. Por las dudas probemos a muchas frecuencias y períodos.
1. Se debe indicar en el manual com afectan las vibraciones al dispositivo. Para determinar esto se debe realizar un ensayo a aceleración de 1 m/s² entre 20 y 1000 Hz.
1. Deberá ser inmune a ruido electromagnético (ver punto 8.4 de IRAM 4074 - 1)
1. Se debe especificar el rango de temperatura de operación del equipo, según norma debe ser al menos de -10 a 50°C.
1. La frecuencia de referencia del dispositivo debe ser de 1 kHz (ver 3.7 de IRAM 4074 - 1)
1. Deberá tener la función de calibración a 94 y 114 dB.
1. Debe cumplir con el inciso 5 de la IRAM 4074 - 1, y las tablas II y III (direccionalidad).
1. Debe poder calibrarse para campo difuso y campo libre.
1. Antes de realizar la ponderación en frecuencia se debería corregir la curva del micrófono en frecuencia (si es necesario).
1. Debe ser de tipo integrador, con tiempo de integración seteable. Esto se puede hacer en el servidor. Se recomiendan las opciones: 10 s, 1 min, 5 min, 10 min, 1 h, 8 h, 24 h.
1. Tiempo de estabilización de la medición menor a 1 min.
1. Debe cumplir con el ensayo de promediación temporal definido en la 9.3.2 de la IRAM 4074 - 3.
1. Rango de linealidad y de pulsos (ver 9.3 de la IRAM 4074 - 3)
1. Opcional: análisis con filtros de octavas, adaptativo mediante FFT.

#### En el manual de instrucciones se debe indicar:
1. El tipo de micrófono y el método de montaje necesario para lograr las tolerancias requeridas para esa clase particular de medidor de nivel sonoro integrador
1. La dirección de incidencia y la respuesta en frecuencia a campo libre en esa dirección para instrumentos calibrados en campo difuso
1. Rango del instrumento para cada ponderación en frecuencia.
1. Precisión del instrumento
1. Nivel de presión de referencia según 3.8 de la IRAM 4074 - 1. Se entiende que sería de 94 dB para la mayoría de los calibradores.
1. Tipos de ponderación en frecuencia (A, C, Z)
1. Tipos de ponderación temporal (S, F, I), con descripción.
1. Efecto de las vibraciones sobre el dispositivo.
1. Efectos de los campos magnéticos sobre el dispositivo
1. Efectos de la temperatura sobre el dispositivo (8.5 IRAM 4074 - 1)
1. Efecto de la presencia del observador en una medición en campo libre
1. Efectos de la humedad sobre el dispositivo (8.6 IRAM 4074 - 1)
1. Límites de temperatura y humedad admisibles.
1. Efectos de utilizar accesorios tales como protectores de viento.
1. Procedimiento de calibración (4.2 IRAM 4074 - 1), para campo libre y campo difuso.
1. Ubicación del observador con respecto al dispositivo para minimizar los efectos del mismo sobre la medición.
1. Frecuencia de referencia (1 kHz) (3.9 IRAM 4074 - 1)
1. Tiempo de estabilización después del cual se pueden tomar lecturas válidad (4.9 IRAM 4074 - 1)la dirección de referencia. en función de la frecuencia. Según tabla IV IRAM 
1. Información para corregir sensibilidad en un campo difuso y la sensibilidad en 4074 - 1 y Apéndice B de la misma norma. Ver 9.1 IRAM 4074 - 3. Al menos hasta 8 kHz.
1. Si mide en campo libre y difuso. Creo que se especifica con R en el modelo si es campo difuso.
1. Respuesta direccional del dispositivo, a varias frecuencias. Se debe incluir 1 kHz.
1. Ancho de banda (donde la medición es lineal)
1. Tiempos prefijados de integracion (si los usamos).
1. Duración nominal de la batería.
1. Impedancia del micrófono
1. Forma de montaje del instrumento
1. Configuración para modo normal de funcionamiento
1. Efectos de recibir una descarga eléctrica
1. etc.

Si es posible:
1. Sensibilidad del dispositivo en función de la frecuencia
1. Comportamiento del medidor cuando se lo prueba con trenes de pulsos (“tone burst”), ver 7.2 y 7.3 de IRAM 4074 - 1

***
## Estructura del proyecto de firmware
En el presente proyecto se utiliza [Free RTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html), y se decide separar las tareas en archivos separados por una cuestión de buenas prácticas, para no tener demasiadas lineas en pocos scrips. Se presenta a continuación una descripción de cada archivo y sus funciones principales, así como el funcionamiento de RTOS.
### Cosas básicas de RTOS
Cada tarea debe tener al menos 2 métodos:
- <sub>task_launch()</sup>: No necesariamente debe llamarse así, toma el nombre dependiendo de la tarea que lancemos. Generalmente tiene la siguiente estructura:
```c
task_launch(){
    xTaskCreatePinnedToCore(    // comando que crea la tarea
        func_task,               // llama a la funcion que será el bucle de la tarea
        "func_task",             // nombre de la tarea dentro de RTOS a findes de debug
        100000,                 // tamaño del stack, depende de la cantidad de variables que maneja mi tarea
        NULL,                   // Parameter to pass (generalmente no se usa)
        2,                      // TPrioridad de la tarea (de menor a mayor, creo que va hasta 15)
        &TaskHandle_task,        // Task handle, es como un puntero que apunta a la tarea en memoria
        APP_CORE);              // Indica que nucleo usaremos
}
```
Depende de la tarea, también se pueden crear colas (qeue) en el task launch, en ese caso vayan a fijarse al script :)
- <sub>task_kill()</sup>: Es para matar la tarea, a fin de liberar memoria si la misma ya no se usa. También se pueden matar colas, eso fijense en el código, no acá.
```c
task_kill(){
    if (TaskHandle_task != NULL)
    {
        vTaskDelete(TaskHandle_task);
        TaskHandle_task = NULL;
    }
}
```
(ver si agregar algo de colas mas adelante).
Las tareas generalmente tienen 2 archivos:
- *task.h*: en el header se llaman a las dependencias de la tarea y se definen los métodos de la misma. También se definen constantes y lo que uno quiera definir y no tenga que estar dentro de una función de la tarea.
- *task.c*: aca está el cuerpo de los métodos y la tarea principal que tiene el bucle. Esta es la que se llama desde donde se quiera lanzar la tarea.

### ***main***
aca simplemente se debería llamar a *config.c* y *logica_control.c*, quedando sin loop infinito, ya que de esto se encargarán las tareas.

### ***config***
Esta no es una tarea de RTOS propiamente dicha, en ella están los métodos:
- *loadconfig()*: trae la información guardada en la spiffs (dcredenciales, calibraciones, datos de versionado, etc.) y actualiza los datos en RAM.
- *saveconfig()*: guarda los datos importantes en la memoria spiffs.

### ***logica_control***
Lanza las demás tareas, y se encarga de recibir las peticiones del usuario y hacer en consecuencia lo que se necesite.

### ***audio_task***
Se encarga de calcular el nivel sonoro equivalente. También tiene implementado el test unitario del filtro de audio según la norma IRAM4074-1.

### Archivos en Assembler
#### Cast_and_scale.S
Se encarga de recibir la muestra de audio en veces (numero entero sin signo generalmente) y pasarlo a unidades de presión. Para utilizarlo se lo encluye en el script.c, globalmente de la siguiente forma:
```c
extern void casting_y_escala(int muestra_cuentas, float* muestra_p, float* k_veces_to_p);
```
donde:
- *muestra_cuentas*: es la muestra de audio en veces
- *muestra_p*: puntero que apunta a la dirección de memoria donde se guardará la muestra en unidades de presión.
- *k_veces_to_p*: puntero que apunta a la dirección de memoria donde está la constante de conversión de veces a unidades de presion.

#### filtro.S
Contiene un algoritmo correspondiente a un filtro IIR de grado 2 según la forma directa tipo I. Para utilizarlo se lo encluye en el script.c, globalmente de la siguiente forma:
```c
extern void filtro_II_d_I(float* muestra_p, float* _x, float* _y, float* _SOS);
```
donde:
- *muestra_p*: puntero que apunta a la dirección de memoria donde se guardará la muestra en unidades de presión.
- *_x*: apunta al primer elemento de un stack de 3 elementos correspondientes a x[n], x[n-1] y x[n-2], dicho stack es una pila FIFO.
- *_y*: apunta al primer elemento de un stack de 3 elementos correspondientes a y[n], y[n-1] y y[n-2], dicho stack es una pila FIFO.
- *_SOS*: apunta al primer elemento de array que contiene los parámetros del filtro a implementar. La disposición de los parámetros es la siguiente:
    - *(_sos + 0) = b0
    - *(_sos + 1) = b1
    - *(_sos + 2) = b2
    - *(_sos + 3) = a1
    - *(_sos + 4) = a2
    
Si se pretende aplicar un filtro de grado mayor a 2 se debe implementar como una cascada de filtros de grado 2 según forma directa tipo I.

#### product_and_acu.S
Se encarga de realizar unqa escala a la salida de la etapa de filtrado y de realizar el acumulado del cuadrado de la presión. Para utilizarlo se lo encluye en el script.c, globalmente de la siguiente forma:
```c
extern void producto_y_acumulacion(float *_y, float *_acu, float *_k);
```
donde:
- *_y*: apunta a la salida de la etapa de filtrado.
- *_acu*: apunta a la direccion de memoria donde se guardará el acumulado de los cuadrados de la salida del filtro para calcular luego el Leq.
- *_k*: constante a la que se multiplica *_y antes de realizar el cuadrado. Generalmente se especifica en el diseño del filtro.