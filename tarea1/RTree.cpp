// Inicio tarea R-Tree
// Alumno: Jaime Alvarado - Sebastian Brzovic - Pablo Skewes

// Librerias
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include <algorithm>
#include <functional>


// constructor de la clase RTree

RTree::RTree() {
    root = new Node();
    root->isLeaf = true;
    root->level = 0;
    root->num_entries = 0;
}

// destructor de la clase RTree