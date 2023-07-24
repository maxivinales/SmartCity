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
1. [Especificaciones Técnicas según IRAM4074 y otras IRAM](#ET)
2. [RTOS](#technologies)
3. [Filtro](#installation)
4. [Comunicacion](#collaboration)
5. [Sarasa](#faqs)

## Especificaciones Técnicas según IRAM4074 y otras IRAM
***
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
***
En el manual de instrucciones se debe indicar:
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
***
Si es posible:
1. Sensibilidad del dispositivo en función de la frecuencia
1. Comportamiento del medidor cuando se lo prueba con trenes de pulsos (“tone burst”), ver 7.2 y 7.3 de IRAM 4074 - 1

<!-- ## Headline H2
### Headline H3
#### Headline H4 
##### Headline H5
###### Headline H6 -->