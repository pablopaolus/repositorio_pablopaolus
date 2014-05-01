Documentación de seleccion.cpp
============================

El código se encuentra en [seleccion.cpp] (https://github.com/pablopaolus/repositorio_pablopaolus/blob/master/seleccion.cpp). 
En primer lugar, debo aclarar dos puntos importantes:

1. He optado por seguir adelante con el ejercicio utilizando la clase `<vector>`, dejando de lado la implementación que he mantenido hasta el ejercicio anterior utilizando array de enteros debido a las menores medidas de tiempo. La justificación radica en la disponibilidad de funciones en esta clase `<vector>` que, además de facilitarnos la vida, ahorrarán mucho tiempo. Por ejemplo: ordenar el vector de fitness de forma eficiente. 
2. También he modificado el código que he venido haciendo hasta ahora para poder implementar fácilmente una población de individuos, creando un vector de vectores, de forma que cada elemento del vector (de tamaño `nPob` será un cromosoma con `nGenes`. Ambos parámetros se especifican, en ese orden, al ejecutar el código. 

```cpp
vector< vector<char> > poblacion(nPob, vector<char>(nGenes)); 
```

A lo largo de la documentación se irá mostrando también, en cada apartado, la información que se imprime por pantalla (para ello: `display = 1`) en la ejecución del programa con una población de tamaño 5 y un número de genes igual a 10, para una mejor comprensión y seguimiento del ejercicio:

```bash
./seleccion 5 10
```

#####Población Inicial:

En primer lugar llevamos a cabo la inicialización aleatoria de cada vector cromosoma (habrá nPob vectores) con 0 o 1:

```cpp
// Inicialización aleatoria de cada vector cromosoma (habrá nPob vectores) con 0 o 1
for(itPoblacion = poblacion.begin(); itPoblacion != poblacion.end(); ++itPoblacion) {
	for(itCrom = (*itPoblacion).begin(); itCrom != (*itPoblacion).end(); ++itCrom) {
		*itCrom = rand() % 2;
		if(display==1) printf("%d ", *itCrom);
	}
	if(display==1) printf("\n");
}
```
La salida por pantalla correspondiente a esta inicialización sería:

```bash
POBLACIÓN INICIAL:
1 0 1 0 1 0 1 1 1 1 
0 1 0 0 1 0 0 0 1 0 
0 1 1 0 0 0 0 0 1 0 
0 1 1 0 1 0 0 0 1 0 
1 0 1 1 0 0 0 1 0 1  
```

#####Fitness:

Para evaluar el fitness cuento el número de 1s de cada cromosoma del vector de vectores `poblacion`, y lo almaceno en el vector `fitness`. Este vector será de tipo `pair` para poder almacenar pares de (índice vector cromosoma , fitness asociado):

```cpp
vector< pair<int,int> > fitness(nPob); // Almaceno indice de individuo y su fitness (nº de unos)
long ones = 0; // Variable para almacenar el número de unos contados en cada cromosoma
long int total_ones = 0; // Variable para almacenar el número total de unos de todos los cromosomas de la población
double average = 0; 
if(display==1) printf("\nFITNESS:\n");
for(int i = 0; i < nPob; i++) {
	ones = 0;
	for(int j = 0; j < nGenes; j++) {
		if(poblacion[i][j] == 1)
			ones++;
	}
fitness[i] = make_pair(i, ones);
total_ones += ones;
if(display==1) printf("Cromosoma %d --> Fitness: %d\n", fitness[i].first, fitness[i].second);
}
average = ((double) total_ones / (double) nPob);	
if(display==1) printf("Fitness total: %ld\nAverage Fitness: %f\n", total_ones, average);	

// Ordenamos el vector fitness según el número de ones (de mayor a menor) para ver qué cromosomas tienen mejor fitness
qsort(&fitness[0], nPob, sizeof(pair<int,int>), compare);
if(display==1) {
	printf("\nVector de fitness ordenado:\n");
	for(int i = 0; i < nPob; i++) 
		printf("Cromosoma %d --> Fitness: %d\n", fitness[i].first, fitness[i].second);
	}
```

Tras la ejecución de esta parte, obtenemos por pantalla la siguiente información:

```bash
FITNESS:
Cromosoma 0 --> Fitness: 7
Cromosoma 1 --> Fitness: 3
Cromosoma 2 --> Fitness: 3
Cromosoma 3 --> Fitness: 4
Cromosoma 4 --> Fitness: 5
Fitness total: 22
Average Fitness: 4.400000

Vector de fitness ordenado:
Cromosoma 0 --> Fitness: 7
Cromosoma 4 --> Fitness: 5
Cromosoma 3 --> Fitness: 4
Cromosoma 1 --> Fitness: 3
Cromosoma 2 --> Fitness: 3
```

#####Selección: Rueda de Ruleta:

Se crea un pool genético formado por cromosomas de la generación actual, en una cantidad proporcional a su fitness. En el vector `ruleta` almacenamos los índices de los cromosomas en proporción a su fitness (más copias cuanto mayor sea su fitness).
Para realizar estos cálculos me he basado en [este documento] (http://www.uobabylon.edu.iq/eprints/paper_2_27286_124.pdf)

```cpp
vector<int> ruleta(nPob);
int copias=0;
int indice_ruleta=0;
for(int i = 0; i < nPob; i++) {
	copias=	((double) fitness[i].second / (double) average);	
	if(display==1) printf("Copias de cromosoma %d = %d\n", fitness[i].first, copias); 
	for(int j = indice_ruleta; j < copias + indice_ruleta; j++) {
		ruleta[j] = fitness[i].first;
		//printf("ruleta[%d] = %d\n", j, ruleta[j]); 
	}
	indice_ruleta += copias;
	//printf("indice_ruleta: %d\n", indice_ruleta); 
}
```
Puede ocurrir que el número de copias no llegue a `nPob` (`indice_ruleta` < `nPob`), en cuyo caso rellenamos lo restante con una copia extra de cada cromosoma, respetando la prioridad según su fitness:

```cpp
if(indice_ruleta < nPob) {
	int indice_fitness=0;
	for(int i = indice_ruleta; i < nPob; i++) {
		ruleta[i] = fitness[indice_fitness].first;
		indice_fitness++;
	}
}
```
La salida por pantalla correspondiente a la parte de selección es la siguiente:

```bash
SELECCIÓN:
Copias de cromosoma 0 = 1
Copias de cromosoma 4 = 1
Copias de cromosoma 3 = 0
Copias de cromosoma 1 = 0
Copias de cromosoma 2 = 0
Indices de cromosomas en la ruleta: 0 4 0 4 3
```

Como se puede observar, en el vector `fitness` ya no tenemos los índices de los cromosomas 1 y 2, dado que no se ha creado ninguna copia de ellos debido a su bajo fitness. Sin embargo, del cromosoma 4 tenemos el mayor número de copias (2 en este caso), ya que es el que mejor fitness tiene (mayor número de unos, según el criterio escogido). 

#####Cruce:
El operador de cruce coge dos padres e intercambia los genes comprendidos entre dos puntos de cruce escogidos al azar, obteniendo por tanto dos individuos hijos. Dado que hay que coger parejas aleatorias de cromosomas para cruzarlas, el número de cruces será igual al tamaño de la población dividido entre 2, lo cual podemos calcular simplemente desplazando `nPob` un bit a la derecha.

En primer lugar elijo aleatoriamente dos individuos de la poblacion. Sus índices dentro del vector de vectores poblacion son crom1 y crom2. A continuación elijo aleatoriamente los puntos de corte para el cruce de cadenas entre los dos vectores con índices crom1 y crom. Los puntos anteriores pueden no haber salido ordenados. Necesitamos `pc1` (punto de cruce 1) < `pc2` (punto de cruce 2), por lo que es necesario ordenarlos. Posteriormente, copiamos dos cromosomas padre (los que haya en el vector ruleta en los índices crom1 y crom2) en sendos cromosomas hijos. Dado que en el vector ruleta hay más índices de los cromosomas con más fitness, habra más probabilidad de que el índice seleccionado pertenezca a cromosomas con más fitness. Finalmente realizamos el crossover basado en dos puntos.

Todo lo anterior se traduce al siguiente código:

```cpp
int nCruces = nPob >> 1; // Número de cruces a realizar
if(display == 1) printf("\nCROSSOVER:\nNúmero de cruces: %d\n", nCruces);
// Creamos un vector de hijos (vector de vectores) de tamaño nPob
vector< vector<char> > hijos(nPob);
// Bucle para realizar los nCruces
for(int i = 0; i < nCruces; ++i) {
	if(display==1) printf("\nCRUCE Nº %d\n",i+1);
	// Primero elijo aleatoriamente dos individuos de la poblacion. Sus índices dentro del vector de vectores poblacion son crom1 y crom2
	int crom1 = rand() % nPob;
	int crom2 = rand() % nPob;
	// Ahora elijo aleatoriamente los puntos de corte para el cruce de cadenas entre los dos vectores con índices crom1 y crom2
	int p1 = rand() % nGenes;
	int p2 = rand() % nGenes;
	// Los puntos anteriores pueden no haber salido ordenados. Necesitamos pc1 (punto de cruce 1) < pc2 (punto de cruce 2)
	int pc1 = (p1<p2) ? p1 : p2;
	int pc2 = (p1>p2) ? p1 : p2;
	if(display==1) printf("Puntos de cruce: pc1=%d y pc2=%d\n", pc1, pc2);
	// Copiamos dos cromosomas padre (los que haya en el vector ruleta en los índices crom1 y crom2) en sendos cromosomas hijos.
	// Dado que en el vector ruleta hay más índices de los cromosomas con más fitness, habra más probabilidad 
	// de que el índice seleccionado pertenezca a cromosomas con más fitness. 
	hijos[i<<1] = poblacion[ruleta[crom1]];
	hijos[(i<<1)+1] = poblacion[ruleta[crom2]];
	if(display==1) printf("Índices de los cromosomas que se cruzarán: %d y %d\n", ruleta[crom1], ruleta[crom2]);
	// Realizamos el crossover basado en dos puntos
	for(int k=pc1; k<=pc2; k++) {
		hijos[(i<<1)][k] = poblacion[ruleta[crom2]][k];
		hijos[(i<<1)+1][k] = poblacion[ruleta[crom1]][k];
	}
```

En este caso, al ser `nPob` igual a 5, se realizarán 2 cruces, y la información por pantalla será la siguiente:

```bash
CROSSOVER:
Número de cruces: 2

CRUCE Nº 1
Puntos de cruce: pc1=1 y pc2=2
Índices de los cromosomas que se cruzarán: 4 y 0

Población (hijos) tras cruce nº 1:
1 0 1 1 0 0 0 1 0 1 
1 0 1 0 1 0 1 1 1 1 
---------------------

CRUCE Nº 2
Puntos de cruce: pc1=0 y pc2=5
Índices de los cromosomas que se cruzarán: 3 y 4

Población (hijos) tras cruce nº 2:
1 0 1 1 0 0 0 1 0 1 
1 0 1 0 1 0 1 1 1 1 
1 0 1 1 0 0 0 0 1 0 
0 1 1 0 1 0 0 1 0 1 
```

Se puede apreciar que la población tras el cruce es de 4 hijos, no 5 (como debería ser). Esto es debido a que `nPob` es impar. Lo tendremos en cuenta y lo arreglaremos más adelante, en el apartado de Inserción, donde se especifica la población de la nueva generación. 

#####Mutación:
Como sabemos, se trata de la alteración aleatoria (normalmente con probabilidad pequeña) de cada gen componente del cromosoma de forma que obtengamos un individuo mutado. Mutamos pues la población de hijos obtenida tras el cruce:

```cpp
bool mutar;
if(display==1) printf("\nMUTACIÓN:\nPoblación tras mutación:\n");
for(itPoblacion = hijos.begin(); itPoblacion != hijos.end(); ++itPoblacion) {
	for(itCrom = (*itPoblacion).begin(); itCrom != (*itPoblacion).end(); ++itCrom) {
		mutar = (rand() % 100) < 10;
		if(mutar==true) {
			*itCrom=~*itCrom+2;
			if(display==1) printf("%d ", *itCrom);
		}
		else if(display==1) printf("%d ", *itCrom);
	}
	if(display==1) printf("\n");
}
```

La población de individuos tras la mutación será la siguiente, en este ejemplo:

```bash
MUTACIÓN:
Población tras mutación:
1 0 1 1 1 0 0 1 0 1 
1 0 1 0 1 0 1 1 1 0 
1 0 1 0 0 0 0 0 0 1 
0 1 1 0 1 0 0 1 0 1 
```

#####Inserción:

Por último, se insertan los nuevos individuos en la población, sustituyendo la población anterior. Como hemos comentado antes, si `nPob` es impar (como en el caso del ejemplo que estamos siguiendo), el nº de hijos generados es uno menos, ya que el número de cruces se ha calculado como la parte entera de la división entre 2 de `nPob`.Para completar la población, añadimos al cromosoma padre con mas fitness al vector `hijos` de la población de la nueva generación:

```cpp
if(nPob % 2 == 1)
	hijos[nPob-1] = poblacion[fitness[0].first]; // El vector fitness lo tenemos ya ordenado

// Población final
if(display == 1) {
	printf("\nINSERCIÓN:\nNueva Población:\n");
	for(itPoblacion = hijos.begin(); itPoblacion != hijos.end(); ++itPoblacion) {
		for(itCrom = (*itPoblacion).begin(); itCrom != (*itPoblacion).end(); ++itCrom)
			printf("%d ", *itCrom);	
		printf("\n");
	}
}
```

En el ejemplo que estamos siguiendo, la nueva población será:

```bash
INSERCIÓN:
Nueva Población:
1 0 1 1 1 0 0 1 0 1 
1 0 1 0 1 0 1 1 1 0 
1 0 1 0 0 0 0 0 0 1 
0 1 1 0 1 0 0 1 0 1 
1 0 1 0 1 0 1 1 1 1 
```

Donde se puede observar que el último individuo es el cromosoma padre de la población inicial que tenía mayor número de unos (mejor fitness). 


Medida de tiempos
----------------------

Para la medidicón de los tiempos ponemos la variable `display` a 0, evitando así las impresiones por pantalla. Como se ha venido haciendo, se han seleccionado los mejores tiempos para cada caso entre 10 ejecuciones del programa.

En primer lugar, mantengo fijo el tamaño de la población a 100 cromosomas, y varío el número de genes de cada cromosoma, obteniendo los siguientes resultados: 


  Tam. Población (Nº Cromosomas)  |   Nº Genes   | Tiempo de Ejecución
----------------------------------|--------------|---------------------
      	       100                |      128     |      0.001216 s 
     	       100                |      256     |      0.002397 s 
     	       100                |      512     |      0.004671 s
     	       100                |      1024    |      0.010266 s
     	       100                |     65536    |      0.641004 s


Como segundo experimento, mantengo fijo el número de genes a 128, y varío en este caso el tamaño de la población:


  Tam. Población (Nº Cromosomas)  |   Nº Genes   | Tiempo de Ejecución
----------------------------------|--------------|---------------------
      	       100                |      128     |      0.001216 s 
     	       200                |      128     |      0.002549 s 
     	       500                |      128     |      0.006277 s
     	       1000               |      128     |      0.012580 s
               10000              |      128     |      0.139305 s

Los tiempos obtenidos son regulares, pero estoy contendo de que al menos funcione... y me esté poco a poco enterando de algo a base de tiempo y cabezazos.
Quiero agradecer a rotty11 por la documentación de sus ejercicios, que me ha ayudado enormemente a entender e implementar el algoritmo genético.  







