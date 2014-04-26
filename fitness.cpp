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
		printf("Uso: %s <Número de elementos>\n", argv[0]);
		exit(-1);
	}

	srand(time(NULL));

	int nElem = atoi(argv[1]); // Número de elementos (común para todas las estructuras de datos)
	struct timeval timeMeas;

	printf("--------------------------------\n");

	/* ESTRUCTURA DE DATOS 1: Array de enteros de toda la vida */
	int bit_vector_1[nElem];

  	srand (time(NULL)); // initialize random seed

	gettimeofday(&timeMeas, NULL);
	double tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);

	// Relleno aleatorio del array de enteros con 0 o 1
	for(int i=0; i<nElem; i++) {
		bit_vector_1[i] = rand() % 2; 
		//printf("%d\n", bit_vector_1[i]);
	}

	gettimeofday(&timeMeas, NULL);
	double tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Elapsed time 1 (int array): %.6lf s\n", tend - tstart);	

	/* Fitness Count-Ones*/

	gettimeofday(&timeMeas, NULL);
	tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);

	// Cuento el número de 1s de la cadena de bits
	int count_ones = 0;
	for(int i=0; i<nElem; i++)
		if(bit_vector_1[i] == 1)
			++count_ones;

	gettimeofday(&timeMeas, NULL);
	tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Count ones (int array): %d\n", count_ones);
	printf("Elapsed time count-ones (int array): %.6lf s\n", tend - tstart);	
	printf("--------------------------------\n");

	/* ESTRUCTURA DE DATOS 4: Vector de caracteres */
	vector<char> bit_vector_4;

	gettimeofday(&timeMeas, NULL);
	tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	
	for(int i=0; i<nElem; i++) {
		bit_vector_4.push_back(rand() % 2);
	}

	gettimeofday(&timeMeas, NULL);
	tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Elapsed time 4 (vector<char>): %.6lf s\n", tend - tstart);

	/* Fitness Count-Ones*/

	vector<char>::iterator it;

	gettimeofday(&timeMeas, NULL);
	tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);

	
	// Cuento el número de 1s del vector
	count_ones = 0; // Reiniciamos el contador
	for(it = bit_vector_4.begin(); it != bit_vector_4.end(); ++it)
		if(*it == 1)
			++count_ones;

	gettimeofday(&timeMeas, NULL);
	tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Count ones (vector<char>): %d\n", count_ones);
	printf("Elapsed time count-ones (vector<char>): %.6lf s\n", tend - tstart);	
	printf("--------------------------------\n");

	return 0;
}
