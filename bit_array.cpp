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

	/* ESTRUCTURA DE DATOS 2: Vector de enteros */
	vector<int> bit_vector_2;

	gettimeofday(&timeMeas, NULL);
	tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);

	for(int i=0; i<nElem; i++) {
		bit_vector_2.push_back(rand() % 2);
		//printf("%d\n", bit_vector_2[i]);
	}

	gettimeofday(&timeMeas, NULL);
	tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Elapsed time 2 (vector<int>): %.6lf s\n", tend - tstart);

	/* ESTRUCTURA DE DATOS 3: Vector booleano */
	vector<bool> bit_vector_3;

	gettimeofday(&timeMeas, NULL);
	tstart = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);

	for(int i=0; i<nElem; i++) {
		if((rand() % 2) == 0)
			bit_vector_3.push_back(false);
		else
			bit_vector_3.push_back(true);

		//cout << ' ' << bit_vector_3.at(i);
  		//cout << '\n';
	}

	gettimeofday(&timeMeas, NULL);
	tend = timeMeas.tv_sec+(timeMeas.tv_usec/1000000.0);
	printf("Elapsed time 3 (vector<bool>): %.6lf s\n", tend - tstart);

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

	return 0;
}
