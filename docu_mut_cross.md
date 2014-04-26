Documentación de mut_cross.cpp
============================

El código se encuentra en [mut_cross.cpp] (https://github.com/pablopaolus/repositorio_pablopaolus/blob/master/mut_cross.cpp). En primer lugar se realizan los operadores de mutación para la estructura de datos array de enteros, ya que es la que menor tiempo consumía en las pruebas realizadas anteriormente. 

Cada cadena de bits representa un cromosoma compuesto por un conjunto de parámetros (que denominaremos genes)

#####Mutación:

El operador de mutación se aplica a una cadena de genes y consiste en la alteración aleatoria (normalmente con probabilidad pequeña) de cada gen componente del cromosoma, de forma que obtengamos un individuo mutado.

```cpp
bool mutar;
if(display==1) printf("\nMUTACIÓN:\ncromosoma_1 tras mutación: ");
for(int i=0; i<nGenes; i++) {
	mutar = (rand() % 100) < 10; 
	if(mutar == true) {
		cromosoma_1[i]=~cromosoma_1[i]+2; // Cambia a 1 si era 0 y viceversa
		if(display==1) printf("%d ", cromosoma_1[i]);
	}
	else if(display==1) printf("%d ", cromosoma_1[i]);	
}
```

Con la variable booleana `mutar` determinamos la probabilidad de que un gen mute (cambie de 0 a 1 o de 1 a 0). Por ejemplo, en este caso se ha elegido una probabilidad del 10%. El comando `rand() % 100` nos da un número aleatorio entre 0 y 100. Si hacemos `(rand() % 100) < 10`, la probabilidad de que ese número sea menor que 10 es, precisamente, del 10%.
La variable `display` sirve simplemente para mostrar por pantalla información adicional de pasos intermedios de la ejecución. Se puede poner a 0 al inicio del programa si no se quiere imprimir por pantalla. 

Si ejecutamos el programa con un tamaño de cadena de 20, por pantalla podemos observar los genes antes y después de la mutación:

```bash
 ***** ARRAY DE ENTEROS ***** 
----------------------------
POBLACIÓN INICIAL:
cromosoma_1 original:      1 1 1 1 0 1 0 1 0 0 1 1 1 1 0 0 0 1 0 0 
cromosoma_2 original:      1 0 0 0 0 0 1 1 1 1 1 0 0 0 1 0 0 1 1 0 

MUTACIÓN:
cromosoma_1 tras mutación: 1 0 1 1 0 1 0 1 0 0 1 0 1 1 0 0 0 1 0 0 (Probabilidad de mutación p=0.1) 
cromosoma_2 tras mutación: 1 0 0 0 0 0 0 1 0 0 1 0 0 0 1 0 0 1 1 0 (Probabilidad de mutación p=0.1) 
```

Vemos que, en este ejemplo en concreto, en el cromosoma_1 han mutado los genes 1 y 11; mientras que en cromosoma_2 han mutado los genes 6, 8 y 9.

#####Crossover:

El operador de cruce coge dos padres e intercambia los genes comprendidos entre dos puntos de cruce escogidos al azar, obteniendo por tanto dos individuos hijos. La implementación realizada es la siguiente:

```cpp
// Puntos aleatorios de la cadena por donde cortaremos
int p1 = rand() % nGenes;
int p2 = rand() % nGenes;
if(display==1) printf("\nCROSSOVER:\nPuntos aleatorios de la cadena: p1=%d y p2=%d\n", p1, p2);
// Los puntos anteriores pueden no haber salido ordenados. Necesitamos pc1 (punto de cruce 1) < pc2 (punto de cruce 2)
int pc1 = (p1<p2) ? p1 : p2;
int pc2 = (p1>p2) ? p1 : p2;
if(display==1) printf("Punto de cruce 1 (pc1): %d\nPunto de cruce 2 (pc2): %d\n", pc1, pc2);
// Realizamos el crossover basado en dos puntos sobre los cromosomas 1 y 2
int gen;
for(int i=pc1; i<=pc2; i++) {
	gen = cromosoma_1[i]; // Variable intermedia para no perder el valor
	cromosoma_1[i] = cromosoma_2[i];
	cromosoma_2[i] = gen;
}
```

Lo que se ha hecho es definir dos puntos de cruce aleatorios `pc1` y `pc2` entre los cuales se encuentra la cadena de bits que se intercambiará de un padre a otro. En esta implementación, para realizar el cruce se ha necesitado de una variable intermedia (`gen`) para almacenar temporalmente el gen de uno de los padres para que no se perdiese en el intercambio. 

Si se observa el crossover realizado sobre las cadenas de bits del mismo ejemplo anterior, los genes comprendidos entre los puntos de cruce 12 y 18 se han intercambiado entre los dos padres, obteniendo dos nuevos hijos:

```bash
CROSSOVER:
Puntos aleatorios de la cadena: p1=18 y p2=12
Punto de cruce 1 (pc1): 12
Punto de cruce 2 (pc2): 18
cromosoma_1 tras crossover: 1 0 1 1 0 1 0 1 0 0 1 0 0 0 1 0 0 1 1 0 
cromosoma_2 tras crossover: 1 0 0 0 0 0 0 1 0 0 1 0 1 1 0 0 0 1 0 0 
```

No obstante, la implementación escogida mediante cadenas de enteros no me ha convencido del todo, por lo que he decidido implementarlo todo de nuevo utilizando vector de char, que también ha demostrado ser de las mejores en los ejercicios previos. La ventaja es que la clase `<vector>` nos permite utilizar algunas funciones ya implementadas y que nos facilitarán la vida. 

Si bien el operador de mutación se realiza de forma similar al caso anterior (ver [mut_cross.cpp] (https://github.com/pablopaolus/repositorio_pablopaolus/blob/master/mut_cross.cpp)), en el caso del operador de cruce (crossover) lo que hacemos ahora es copiar los vectores padre a nuevos vectores hijo (de forma que ya no perdemos los progenitores, como antes), y además la tarea del intercambio de cadenas no necesita de una variable intermedia:

```cpp
// Creamos dos vectores hijos donde copiamos los vectores padre
vector<char> cromosoma_hijo_1(cromosoma_padre_1);
vector<char> cromosoma_hijo_2(cromosoma_padre_2);

// Realizamos el crossover basado en dos puntos
for(int i=pc1; i<=pc2; i++) {
	cromosoma_hijo_1[i]=cromosoma_padre_2[i];
	cromosoma_hijo_2[i]=cromosoma_padre_1[i];
```

Por lo demás, los códigos son parecidos. 
Un ejemplo de salida del programa para la ejecución con 20 genes por cromosoma y utilización de esta estructura de datos es:

```bash
 ***** VECTOR DE CHAR ***** 
----------------------------
POBLACIÓN INICIAL:
cromosoma_padre_1 original:      0 0 1 1 1 0 1 1 0 1 1 0 1 1 0 1 1 1 1 1 
cromosoma_padre_2 original:      1 0 0 0 1 0 0 1 1 0 1 1 0 1 0 0 1 1 1 0 

MUTACIÓN:
cromosoma_padre_1 tras mutación: 0 0 1 1 1 0 1 0 0 1 1 0 1 1 0 0 1 0 0 1 (Probabilidad de mutación p=0.1) 
cromosoma_padre_2 tras mutación: 1 0 0 0 1 0 1 1 1 0 0 1 0 1 0 0 1 1 1 0 (Probabilidad de mutación p=0.1) 

CROSSOVER:
Puntos aleatorios de la cadena: p1=1 y p2=3
Punto de cruce 1 (pc1): 1
Punto de cruce 2 (pc2): 3
cromosoma_hijo_1 tras crossover: 0 0 0 0 1 0 1 0 0 1 1 0 1 1 0 0 1 0 0 1 
cromosoma_hijo_2 tras crossover: 1 0 1 1 1 0 1 1 1 0 0 1 0 1 0 0 1 1 1 0 
```

Donde se observa que, tras la mutación (con probabilidad del 10%), el cromosoma_padre_1 ha mutado sus genes 7, 15, 17 y 18, mientras que el cromosoma_padre_2 ha mutado sus genes 6 y 10.

Por su parte, el crossover se ha producido con las cadenas que incluyen los genes del 1 al 3 (sobre los cromosomas padre ya mutados), obteniendo dos nuevos individuos hijos. 


