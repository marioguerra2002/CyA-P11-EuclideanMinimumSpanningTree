# CyA-P11-EuclideanMinimumSpanningTree

## Descripción
Implementación de un algoritmo que calcula el árbol de expansión mínima de un grafo ponderado no dirigido usando la distancia euclídea entre los nodos.

## Comandos de compilación
```bash
g++ src/main.cc src/point_set.cc src/point_types.cc src/sub_tree.cc -o program -std=c++17 -lm
```
Este comando compila el programa y genera un ejecutable llamado `program`.

## Comandos de ejecución
```bash
./program ./test/nombre_test.txt salida.txt

o 

./program ./test/nombre_test.txt salida.txt -d # en caso de que se quiera generar .dot  para visualizar el árbol de expansión mínima
```
## Comando para generar pdf
```bash
dot -Tpdf salida.dot -o salida.pdf
```
Este comando genera un archivo pdf a partir de un archivo .dot.

## Autores
- [Mario Guerra Pérez](alu0101395036@ull.edu.es)
- [Jorge Riera](jriera@ull.es)
- [Jose Luis González](jlgavila@ull.es)

## Enlace al repositorio
[CyA-P11-EuclideanMinimumSpanningTree](https://github.com/marioguerra2002/CyA-P11-EuclideanMinimumSpanningTree.git)