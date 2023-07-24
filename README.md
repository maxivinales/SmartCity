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
..
.
.
.
.
.
.
.
.
.
.
.
.

.
.
.

.
.
.

.
.
.
.

.
.
.

.
.
.
.

.
.
.
.
.
.
.

.

## [Especificaciones Técnicas según IRAM4074 y otras IRAM](#ET)
<!-- ## Headline H2
### Headline H3
#### Headline H4 
##### Headline H5
###### Headline H6 -->