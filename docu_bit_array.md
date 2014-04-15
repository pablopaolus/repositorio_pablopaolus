Documentación de bit_array.cpp
============================

Mi implementación de un vector de bits o cadena binaria es [bit_array.cpp] (https://github.com/pablopaolus/repositorio_pablopaolus/blob/master/bit_array.cpp). He escrito el programa en C++ utilizando 4 estructuras de datos diferentes:

 1. Un array de enteros
 2. Un vector de enteros (utilizando la clase `<vector>`)
 3. Un vector de booleanos (utilizando la clase `<vector>`)
 4. Un vector de char (utilizando la clase `<vector>`)

Expresándolo en forma de código:

  ```c++
  int bit_vector_1[nElem];
  vector<int> bit_vector_2;
  vector<bool> bit_vector_3;
  vector<char> bit_vector_4;
  ```
Donde `nElem` es el tamaño de los vectores, común en todos los casos. Excepto en el primer caso (array de enteros), cuando utilizo la clase `<vector>` lo que hago para rellenar aleatoriamente los vectores con 0 o 1 es ir añadiendo elementos al vector (mediante un bucle desde 0 hasta `nElem` utilizando la función `push_back`, que añade un elemento al final del vector.

Para ejecutar el programa hay que pasar como argumento el tamaño deseado para los vectores:

  ```bash
  ./bit_array <Número de elementos>
  ```
Si especificamos diferentes valores al número de elementos se obtienen los siguientes valores de tiempo (se mide tan solo el tiempo consumido en la generación inicial de cada vector con valores 0 o 1 aleatoriamente). Cabe mencionar que se han seleccionado los mejores tiempos para cada caso entre 10 ejecuciones del programa:

  Nº elementos  | Array de int | Vector de int | Vector de bool | Vector de char
----------------|--------------|---------------|----------------|-----------------
     100        |  0.000002 s  |   0.000064 s  |   0.000008 s   |    0.000005 s
     1000       |  0.000015 s  |   0.000086 s  |   0.000047 s   |    0.000029 s
     10000      |  0.000239 s  |   0.000438 s  |   0.000493 s   |    0.000239 s
     100000     |  0.001753 s  |   0.003006 s  |   0.004220 s   |    0.002323 s
     1000000    |  0.017068 s  |   0.027062 s  |   0.043753 s   |    0.025058 s

Se puede observar que los menores tiempos siempre se dan para el caso de un array de int. Habrá que ver si en las operaciones de mutación y crossover sigue manteniendo el mejor tiempo.
De entre las estructuras de datos implementadas con la clase `<vector>`, se obtienen mejores tiempos en el caso de vector de char. 


