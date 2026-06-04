# Shikaku

Solucionador y jugador interactivo del rompecabezas Shikaku.

**Autor:** Sofia Guerra Jiménez  
**Institución:** Pontificia Universidad Javeriana, Facultad de Ingeniería, Departamento de Ingeniería de Sistemas

---

## Estructura del proyecto

```
shikaku/
├── src/                        código fuente (.cxx)
├── include/                    headers (.h)
├── tableros/                   tableros de entrada (.txt)
├── Makefile
├── Shikaku.pdf
└── README.md
```

## Compilar

```bash
make
```

Genera el ejecutable `shikaku` en la raíz del proyecto.
Los archivos objeto intermedios quedan en `build/` (se crea automáticamente).

```bash
make clean   # elimina build/ y el ejecutable
```

## Formato de los tableros

Los tableros se guardan como archivos `.txt` en `tableros/`.
La primera línea tiene las dimensiones; las siguientes forman la matriz,
donde `0` indica celda vacía y cualquier entero positivo es un número del tablero.

```
4 4
4 0 0 2
0 0 0 0
0 0 6 0
0 4 0 0
```

La suma de todos los números positivos debe ser igual a filas × columnas.

## Correr el programa

### Modo interactivo (jugador humano)

```bash
./shikaku tableros/in_00.txt
```

Abre el tablero y espera comandos. Escribe `h` para ver la ayuda.

| Comando               | Acción                                         |
|-----------------------|------------------------------------------------|
| `c <archivo>`         | Cargar un tablero desde archivo                |
| `p <f> <c> <h> <w>`   | Colocar un rectángulo (fila, col, alto, ancho) |
| `u`                   | Deshacer el último rectángulo                  |
| `l`                   | Limpiar todos los rectángulos                  |
| `v`                   | Verificar si la solución es correcta           |
| `m`                   | Mostrar el tablero                             |
| `i`                   | Ver información de los rectángulos colocados   |
| `h`                   | Mostrar esta ayuda                             |
| `q`                   | Salir                                          |

### Modo automático - fuerza bruta

```bash
./shikaku tableros/in_00.txt fb
```

Resuelve el tablero usando backtracking puro. Imprime la solución y la verifica.

### Modo automático - heurística MRV

```bash
./shikaku tableros/in_00.txt h
```

Resuelve el tablero usando backtracking con heurística MRV (*Minimum Remaining Values*).
En cada paso elige el número con menos rectángulos válidos disponibles en el estado actual del tablero.

## Ejemplo de uso

```
> c tableros/in_00.txt
Tablero cargado (4x4).
> p 0 0 2 2
Rectangulo colocado (id=0)
> v
El tablero no es valido
> u
Ultimo rectangulo deshecho.
> q
Saliendo del juego...
```

## Documentación

En este repositorio se encuentran el documento **`Shikaku.pdf`** con el diseño de la interfaz (descripción de la interfaz interactiva y diagrama del flujo del juego) y la escritura formal del algoritmo (análisis del problema, clasificación de complejidad, diseño de entradas y salidas, pseudocódigo de los algoritmos, análisis de complejidad e invariante).