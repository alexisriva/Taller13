#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

double timeProd = 0;
double timeCons = 0;
int queueSize = 0;
int totalItems = 0;
int queue = 0;
int produced = 0;

pthread_cond_t cvcons = PTHREAD_COND_INITIALIZER;
pthread_cond_t cvprod = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
	int exit = 1;
	while (exit) {
		pthread_mutex_lock(&mutex);

		while (queue == queueSize)
			pthread_cond_wait(&cvprod,&mutex);

		usleep(timeProd);

		queue++;
		produced++;

		printf("Productor %d ha producido 1 item, tamaño cola = %d\n",*((int *)arg),queue);

		if (produced == totalItems)
			exit = 0;

		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&cvcons);
	}

	return (void *)0;
}

void *consumer(void *arg) {
	int exit = 1;
	while (exit) {
		pthread_mutex_lock(&mutex);

		while (queue == 0)
			pthread_cond_wait(&cvcons,&mutex);

		usleep(timeCons);

		queue--;

		printf("Consumidor %d ha consumido 1 item, tamaño cola = %d\n",*((int *)arg),queue);

		if (produced == totalItems && queue == 0)
			exit = 0;

		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&cvprod);
	}

	return (void *)0;
}

//Main
int main(int argc, char *argv[]) {
	int numOfThreadsProd = 0;
	int numOfThreadsCons = 0;
	
	if (argc != 7)
		printf("Uso: ./pc <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items>\n");
	else {
		numOfThreadsProd = atoi(argv[1]);
		timeProd = strtod(argv[2], NULL)/1000000;
		numOfThreadsCons = atoi(argv[3]);
		timeCons = strtod(argv[4], NULL)/1000000;
		queueSize = atoi(argv[5]);
		totalItems = atoi(argv[6]);

		printf("Numero de productores: %d\n", numOfThreadsProd);
		printf("Numero de consumidores: %d\n", numOfThreadsCons);
		printf("Tamaño de cola: %d\n", queueSize);
		printf("Tiempo de produccion: %f\n", timeProd);
		printf("Tiempo de consumo: %f\n", timeCons);
		printf("Total de elementos a producir: %d\n", totalItems);

		pthread_t *idsp = (pthread_t *)malloc(numOfThreadsProd*sizeof(pthread_t));
		pthread_t *idsc = (pthread_t *)malloc(numOfThreadsCons*sizeof(pthread_t));

		for (int prod=0;prod<numOfThreadsProd;prod++)
			pthread_create(&idsp[prod],NULL,producer,&prod);

		for (int cons=0;cons<numOfThreadsCons;cons++)
			pthread_create(&idsc[cons],NULL,consumer,&cons);

		for (int prod=0;prod<numOfThreadsProd;prod++)
			pthread_join(idsp[prod],NULL);

		for (int cons=0;cons<numOfThreadsCons;cons++)
			pthread_join(idsc[cons],NULL);
	}
}
