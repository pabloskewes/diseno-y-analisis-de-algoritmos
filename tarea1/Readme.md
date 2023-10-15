# Tarea 1 - Rtree

## Integrantes
- [Pablo Skewes](https://github.com/pabloskewes/)
- [Tomás Alvarado]()
- [Sebastián Brzovic]()

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

Para limpiar los archivos compilados del proyecto, se debe ejecutar el siguiente comando en la terminal:
```bash
$ make clean
```

Para ver el uso de memoria cache, se puede ejecutar:
```bash
$ make cache-usage
```

Para borrar el caché, se puede ejecutar:
```bash
$ make free-cache
```

## Estructura del proyecto
El proyecto se divide en 3 carpetas principales:
- **src**: Contiene el código fuente del proyecto.
- **include**: Contiene los headers del proyecto.
- **build**: Contiene los archivos compilados del proyecto (generados al ejecutar el comando `make build`, estos archivos son ignorados por git).