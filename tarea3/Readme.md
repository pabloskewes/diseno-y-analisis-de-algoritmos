# Tarea 3 - Closest pair of points

## Integrantes

- [Pablo Skewes](https://github.com/pabloskewes/)
- [Tomás Alvarado](https://github.com/TomasAlvarado21)
- [Sebastián Brzovic](https://github.com/sebabrzovic)

## Instrucciones de instalación

Para instalar las dependencias del proyecto, se debe disponer de un sistema operativo Linux y ejecutar el siguiente comando en la terminal:

```bash
$ sudo apt-get install make cmake g++
```

## Instrucciones de ejecución

Para ejecutar el proyecto, idealmente se puede usar el Makefile que se encuentra en la carpeta raíz del proyecto.

Para compilar el proyecto, se debe ejecutar el siguiente comando en la terminal:

```bash
$ make build
```

Para ejecutar el proyecto, se debe ejecutar el siguiente comando en la terminal:

```bash
$ make run
```

## Estructura del proyecto

El proyecto se divide en 3 carpetas principales:

- **src**: Contiene el código fuente del proyecto.
- **include**: Contiene los headers del proyecto.
- **build**: Contiene los archivos compilados del proyecto (generados al ejecutar el comando `make build`, estos archivos son ignorados por git).


## Indicaciones

En el archivo main está indicado cómo generar los inputs (usando la función bulkGeneration).
Luego, se pueden usar las funciones runExperiments... para correr los experimentos y generar los archivos de salida.
Es importante que en la raiz del proyecto exista una carpeta llamada data, que contenga las carpetas grids y results.
Y que dentro de results existan las carpetas divideAndConquer, randomized y HashingFunction, que corresponden a los resultados de los experimentos. randomized corresponde al algoritmo aleatorizado usando el hashing normal mientras que HashingFunction corresponde al algoritmo aleatorizado usando la función de hashing que optimiza la operación modulo usando un primo de Mersenne.