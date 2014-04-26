Documentación de fitness.cpp
============================

El código se encuentra en [fitness.cpp] (https://github.com/pablopaolus/repositorio_pablopaolus/blob/master/fitness.cpp). En este caso, de entre las implementaciones de cadenas de bits del primer ejercicio me he quedado con las dos que menor tiempo requerían para su generación inicial: array de int y vector de char. 

En la presentación del ejercicio dice que "el fitness es usualmente uno de los elementos críticos de un algoritmo evolutivo", y que "conviene usar todas las técnicas de implementación que se conozcan para hacerlo lo más rápido posible". Como yo es la primera vez que escucho hablar sobre algoritmos evolutivos (o, mejor dicho, leo algo sobre ello, ya que hablar... poco se ha hablado), no conozco ninguna técnica de implementación de fitness. Así que como benchmark he optado por usar el más sencillo: count-ones. Si no lo he entendido mal, se trata simplemente de contar el número de 1s de la cadena binaria. 

Para ello accedo a las cadenas de bits como a una tabla de consulta. En el caso del array de enteros:

```cpp
// Cuento el número de 1s de la cadena de bits
int count_ones = 0;
	if(bit_vector_1[i] == 1)
		++count_ones;
```

Para el caso del vector de char, podemos utilizar las funciones propias de la clase `<vector>` para acceder a las diferentes posiciones:

```cpp
vector<char>::iterator it;
// Cuento el número de 1s del vector
count_ones = 0; // Reiniciamos el contador
	for(it = bit_vector_4.begin(); it != bit_vector_4.end(); ++it)
		if(*it == 1)
			++count_ones;
```

A continuación se muestran las mediciones de los tiempos para diferentes tamaños de cadena: 128, 256, 512 y 1024, es decir, para diferente número de parámetros de un cromosoma (cada cromosoma está compuesto por una cadena binaria). Al igual que en el primer ejercicio, se han seleccionado los mejores tiempos para cada caso entre 10 ejecuciones del programa. Los resultados para cada ejecución se pueden consultar en [medidas_tiempo_fitness] (https://github.com/pablopaolus/repositorio_pablopaolus/blob/master/medidas_tiempo_fitness.txt).

  Tam. Cadena   | Array de int | Vector de char
----------------|--------------|---------------
     128        |  0.000001 s  |   0.000004 s 
     256        |  0.000002 s  |   0.000007 s 
     512        |  0.000004 s  |   0.000013 s
     1024       |  0.000008 s  |   0.000027 s

Como se puede observar en la tabla, el tiempo necesario para realizar el cómputo del número de unos de la cadena se incrementa de forma lineal con el tamaño para las dos estructuras, consiguiendo menores tiempos en el caso del array de enteros.  
 


