#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <sys/time.h>
#include <sys/resource.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

	if(argc < 2) {
		printf("Uso: %s <Número de genes>\n", argv[0]);
		exit(-1);
	}

	int nGenes = atoi(argv[1]); // Número de elementos (número de genes que componen cada individuo (cromosoma))
	int display = 1; //Poner a 1 si se quiere mostrar por pantalla información adicional de pasos intermedios
	srand (time(NULL)); // initialize random seed

	/****** ESTRUCTURA DE DATOS: Array de enteros ******/
	if(display==1) printf("\n ***** ARRAY DE ENTEROS ***** \n----------------------------\n");
	// Cada cadena de bits representa un cromosoma compuesto por un conjunto de parámetros (genes)
	// Creamos dos individuos padre para poder implementar posteriormente una operación de crossover sobre ellos
	int cromosoma_1[nGenes];
	int cromosoma_2[nGenes];

	// Relleno aleatorio del array de enteros cromosoma_1 con 0 o 1
	if(display==1) printf("POBLACIÓN INICIAL:\ncromosoma_1 original:      ");
	for(int i=0; i<nGenes; i++) {
		cromosoma_1[i] = rand() % 2; 
		if(display==1) printf("%d ", cromosoma_1[i]);
	}
	if(display==1) printf("\n");

	// Relleno aleatorio del array de enteros cromosoma_2 con 0 o 1
	if(display==1) printf("cromosoma_2 original:      ");
	for(int i=0; i<nGenes; i++) {
		cromosoma_2[i] = rand() % 2; 
		if(display==1) printf("%d ", cromosoma_2[i]);
	}
	if(display==1) printf("\n");


	/*** MUTACIÓN ***/
	/* Alteración aleatoria (normalmente con probabilidad pequeña) de cada gen componente del cromosoma 
	de forma que obtengamos un individuo mutado. Mutaremos, por ejemplo, el cromosoma_1 */
	bool mutar;
	if(display==1) printf("\nMUTACIÓN:\ncromosoma_1 tras mutación: ");
	for(int i=0; i<nGenes; i++) {
		// Determinamos la probabilidad de que un gen mute (cambie de 0 a 1 o de 1 a 0). Por ejemplo: 10% de probabilidad
		mutar = (rand() % 100) < 10; // rand() % 100 nos da un nº aleatorio entre 0 y 100.
					     // La probabilidad de que sea menor de 10 es precisamente el 10%...	
		if(mutar == true) {
			cromosoma_1[i]=~cromosoma_1[i]+2; // Cambia a 1 si era 0 y viceversa
			if(display==1) printf("%d ", cromosoma_1[i]);
		}
		else if(display==1) printf("%d ", cromosoma_1[i]);	
	}
	if(display==1) printf("(Probabilidad de mutación p=0.1) \ncromosoma_2 tras mutación: ");
	for(int i=0; i<nGenes; i++) {
		// Determinamos la probabilidad de que un gen mute (cambie de 0 a 1 o de 1 a 0). Por ejemplo: 10% de probabilidad
		mutar = (rand() % 100) < 10; // rand() % 100 nos da un nº aleatorio entre 0 y 100.
					     // La probabilidad de que sea menor de 10 es precisamente el 10%...	
		if(mutar == true) {
			cromosoma_2[i]=~cromosoma_2[i]+2; // Cambia a 1 si era 0 y viceversa
			if(display==1) printf("%d ", cromosoma_2[i]);
		}
		else if(display==1) printf("%d ", cromosoma_2[i]);	
	}
	if(display==1) printf("(Probabilidad de mutación p=0.1) \n");


	/*** CROSSOVER ***/
	/* El operador de cruce coge dos padres e intercambia los genes comprendidos entre dos puntos de cruce escogidos al azar, 
	obteniendo por tanto dos individuos hijos */

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
	if(display==1) {
		printf("cromosoma_1 tras crossover: ");
		for(int i=0; i<nGenes; i++) printf("%d ", cromosoma_1[i]);
		printf("\ncromosoma_2 tras crossover: ");
		for(int i=0; i<nGenes; i++) printf("%d ", cromosoma_2[i]);
		printf("\n");
	}


//------------------------------------------------------------------------------------------------------------------------


	/****** ESTRUCTURA DE DATOS: Vector de char ******/
	if(display==1) printf("\n ***** VECTOR DE CHAR ***** \n----------------------------\n");
	vector<char> cromosoma_padre_1;
	vector<char> cromosoma_padre_2;

	// Inicialización aleatoria del vector cromosoma_padre_1 con 0 o 1
	if(display==1) printf("POBLACIÓN INICIAL:\ncromosoma_padre_1 original:      ");
	for(int i=0; i<nGenes; i++) {
		cromosoma_padre_1.push_back(rand() % 2);
		if(display==1) printf("%d ", cromosoma_padre_1[i]);
	}
	if(display==1) printf("\n");
	
	// Inicialización aleatoria del vector cromosoma_padre_2 con 0 o 1
	if(display==1) printf("cromosoma_padre_2 original:      ");
	for(int i=0; i<nGenes; i++) {
		cromosoma_padre_2.push_back(rand() % 2);
		if(display==1) printf("%d ", cromosoma_padre_2[i]);
	}
	if(display==1) printf("\n");

	/*** MUTACIÓN ***/
	vector<char>::iterator it;
	if(display==1) printf("\nMUTACIÓN:\ncromosoma_padre_1 tras mutación: ");
	for(it = cromosoma_padre_1.begin(); it != cromosoma_padre_1.end(); ++it) {
		mutar = (rand() % 100) < 10;
		if(mutar==true) {
			*it=~*it+2;
			if(display==1) printf("%d ", *it);
		}
		else if(display==1) printf("%d ", *it);
	}
	if(display==1) printf("(Probabilidad de mutación p=0.1) \ncromosoma_padre_2 tras mutación: ");
	for(it = cromosoma_padre_2.begin(); it != cromosoma_padre_2.end(); ++it) {
		mutar = (rand() % 100) < 10;
		if(mutar==true) {
			*it=~*it+2;
			if(display==1) printf("%d ", *it);
		}
		else if(display==1) printf("%d ", *it);
	}
	if(display==1) printf("(Probabilidad de mutación p=0.1) \n");

	/*** CROSSOVER ***/
	// Utilizamos nuevos puntos de cruce
	p1 = rand() % nGenes;
	p2 = rand() % nGenes;
	if(display==1) printf("\nCROSSOVER:\nPuntos aleatorios de la cadena: p1=%d y p2=%d\n", p1, p2);
	// Los puntos anteriores pueden no haber salido ordenados. Necesitamos pc1 (punto de cruce 1) < pc2 (punto de cruce 2)
	pc1 = (p1<p2) ? p1 : p2;
	pc2 = (p1>p2) ? p1 : p2;
	if(display==1) printf("Punto de cruce 1 (pc1): %d\nPunto de cruce 2 (pc2): %d\n", pc1, pc2);

	// Creamos dos vectores hijos donde copiamos los vectores padre
	vector<char> cromosoma_hijo_1(cromosoma_padre_1);
	vector<char> cromosoma_hijo_2(cromosoma_padre_2);

	// Realizamos el crossover basado en dos puntos
	for(int i=pc1; i<=pc2; i++) {
		cromosoma_hijo_1[i]=cromosoma_padre_2[i];
		cromosoma_hijo_2[i]=cromosoma_padre_1[i];
	}
	if(display==1) {
		printf("cromosoma_hijo_1 tras crossover: ");
		for(it = cromosoma_hijo_1.begin(); it != cromosoma_hijo_1.end(); ++it)	printf("%d ", *it);
		printf("\ncromosoma_hijo_2 tras crossover: ");
		for(it = cromosoma_hijo_2.begin(); it != cromosoma_hijo_2.end(); ++it)	printf("%d ", *it);
		printf("\n");
	}
	
}












