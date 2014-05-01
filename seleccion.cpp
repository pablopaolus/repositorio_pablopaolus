#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <sys/time.h>
#include <sys/resource.h>
#include <vector>

using namespace std;

// Funcion usada por qsort para ordenar por fitness a los individuos en el torneo (gracias Juanjo)
int compare(const void *ind1, const void *ind2) {

	return ( ((pair<int,int>*)ind2)->second - ((pair<int,int>*)ind1)->second );
}

int main(int argc, char *argv[]) {

	if(argc < 3) {
		printf("Uso: %s <Población cromosomas> <Número de genes>\n", argv[0]);
		exit(-1);
	}

	int nPob = atoi(argv[1]); // Población (número de cromosomas)
	int nGenes = atoi(argv[2]); // Número de elementos (número de genes que componen cada individuo (cromosoma))

	int display = 0; //Poner a 1 si se quiere mostrar por pantalla información adicional de pasos intermedios
	srand (time(NULL)); // initialize random seed
	struct timeval timeMeas;

	// Vector de vectores con la población. Cada vector es un cromosoma con nGenes
	vector< vector<char> > poblacion(nPob, vector<char>(nGenes)); 
	vector< vector<char> >::iterator itPoblacion;
	vector<char>::iterator itCrom; 

	gettimeofday(&timeMeas, NULL);
	double tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);

	/*** POBLACIÓN INICIAL***/
	// Inicialización aleatoria de cada vector cromosoma (habrá nPob vectores) con 0 o 1
	if(display==1) printf("\nPOBLACIÓN INICIAL:\n");
	for(itPoblacion = poblacion.begin(); itPoblacion != poblacion.end(); ++itPoblacion) {
		for(itCrom = (*itPoblacion).begin(); itCrom != (*itPoblacion).end(); ++itCrom) {
			*itCrom = rand() % 2;
			if(display==1) printf("%d ", *itCrom);
		}
		if(display==1) printf("\n");
	}

	/*** FITNESS ***/
	// Cuento el número de 1s de cada cromosoma del vector de vectores poblacion, y lo almaceno en el vector fitness
	// Este vector será de tipo pair para poder almacenar pares de índice vector cromosoma - fitness
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

	/*** SELECCIÓN: RUEDA DE RULETA ***/
	// Se crea un pool genético formado por cromosomas de la generación actual, en una cantidad proporcional a su fitness.
	// Vector ruleta donde almacenamos los índices de los cromosomas en proporción a su fitness (más copias cuanto mayor sea su fitness)
	if(display==1) printf("\nSELECCIÓN:\n");
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
	
	/*
	// VERSIÓN ALTERNATIVA EQUIVALENTE RUEDA DE RULETA 	
	// Sale lo mismo que antes pero, en vez de calcular la media del fitness total (average), calculamos la probabilidad de cada cromosoma según su fitness
	vector<double> prob(nPob);
	for(int i = 0; i < nPob; i++) {
		prob[i] = ((double) fitness[i].second / (double) total_ones);	
		printf("prob[cromosoma[%d]] = %f\n", fitness[i].first, prob[i]);
	}
	for(int i = 0; i < nPob; i++) {
		copias=((double) nPob * (double) prob[i]);	
		printf("copias de cromosoma %d = %d\n", fitness[i].first, copias); 
		for(int j = indice_ruleta; j < copias + indice_ruleta; j++) {
			ruleta[j] = fitness[i].first;
			printf("ruleta[%d] = %d\n", j, ruleta[j]); 
		}
		indice_ruleta += copias;
		printf("indice_ruleta: %d\n", indice_ruleta); 
	}
	*/

	// Si el número de copias no llega a nPob (indice_ruleta < nPob), rellenamos lo restante con una copia extra de cada cromosoma
	// respetando la prioridad según su fitness. 
	if(indice_ruleta < nPob) {
		int indice_fitness=0;
		for(int i = indice_ruleta; i < nPob; i++) {
			ruleta[i] = fitness[indice_fitness].first;
			indice_fitness++;
		}
	}
	
	if(display==1) {	
		printf("Indices de cromosomas en la ruleta: ");
		for(int i = 0; i < nPob; ++i)
			printf("%d ", ruleta[i]);
		printf("\n");
	}
	
	/*** CROSSOVER ***/
	/* El operador de cruce coge dos padres e intercambia los genes comprendidos entre dos puntos de cruce escogidos al azar, obteniendo por tanto dos individuos hijos */
	// Dado que hay que coger parejas aleatorias de cromosomas para cruzarlas, el número de cruces será igual al tamaño de la población dividido entre 2, lo cual podemos calcular simplemente desplazando un bit a la derecha:
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

		if(display==1) {
			printf("\nPoblación (hijos) tras cruce nº %d:\n", i+1);
			for(itPoblacion = hijos.begin(); itPoblacion != hijos.end(); ++itPoblacion) {
				for(itCrom = (*itPoblacion).begin(); itCrom != (*itPoblacion).end(); ++itCrom) {
					printf("%d ", *itCrom);
				}
				printf("\n");
			}
		printf("\n---------------------\n");
		}
	}

	/*** MUTACIÓN ***/
	/* Alteración aleatoria (normalmente con probabilidad pequeña) de cada gen componente del cromosoma 
	de forma que obtengamos un individuo mutado. */
	// Mutamos la población de hijos obtenida tras el cruce
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

	/*** INSERCIÓN ***/
	// se insertan los nuevos individuos en la población, sustituyendo la población anterior
	// Si nPob es impar, el nº de hijos generados es uno menos, ya que el nº de cruces se ha calculado como la parte entera de la división entre 2 de nPob.Para completar la población, añadimos al cromosoma padre con mas fitness 
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

	gettimeofday(&timeMeas, NULL);
	double tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Tiempo Algoritmo Genético: %.6lf s\n", tend - tstart);	
}
