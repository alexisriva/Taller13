#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

//Main
int main(int argc, char *argv[]) {

	double timeProd = 0;
	double timeCons = 0;
	int numOfThreadsProd = 0;
	int numOfThreadsCons = 0;
	int queueSize = 0;
	int totalItems = 0;

	if (argc != 7)
		printf("Uso: ./pc <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items>\n");
	else {
		numOfThreadsProd = atoi(argv[1]);
		timeProd = strtod(argv[2], NULL);
		numOfThreadsCons = atoi(argv[3]);
		timeCons = strtod(argv[4], NULL);
		queueSize = atoi(argv[5]);
		totalItems = atoi(argv[6]);

		printf("Numero de productores: %d\n", numOfThreadsProd);
		printf("Numero de consumidores: %d\n", numOfThreadsCons);
		printf("Tamaño de cola: %d\n", queueSize);
		printf("Tiempo de produccion: %f\n", timeProd);
		printf("Tiempo de consumo: %f\n", timeCons);
		printf("Total de elementos a producir: %d\n", totalItems);
	}
}
