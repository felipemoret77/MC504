#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


//Semaphores for ingredient production administration
sem_t production_Administrator;
sem_t production_Tobacco;
sem_t production_Paper;
sem_t production_Match;

//Semaphores for transporters
sem_t transporter_Tobacco;
sem_t transporter_Paper;
sem_t transporter_Match;



//Variables for signaling the presence of ingredients
int isTobacco = 0;
int isPaper = 0;
int isMatch = 0;

void* producting_Tobacco_Match(void *arg){
	while(1){
		sem_wait(&production_Administrator);
		printf("----PRODUCTION OF TOBACCO AND MATCH IS GOING ON----\n");
		sleep(2);
		sem_post(&production_Tobacco);
		sem_post(&production_Match);
	}
}

void* producting_Tobacco_Paper(void *arg){
	while(1){
		sem_wait(&production_Administrator);
		printf("----PRODUCTION OF TOBACCO AND PAPER IS GOING ON----\n");
		sleep(2);
		sem_post(&production_Tobacco);
		sem_post(&production_Paper);
	}
}


void* producting_Paper_Match(void *arg){
	while(1){
		sem_wait(&production_Administrator);
		printf("----PRODUCTION OF PAPER AND MATCH IS GOING ON----\n");
		sleep(2);
		sem_post(&production_Paper);
		sem_post(&production_Match);
	}
}

void* smoking_With_Tobacco(void *arg){
	while(1){
		sem_wait(&transporter_Tobacco);
		printf("----SMOKER WITH TOBACO IS MAKING THE CIGARETTE----\n");
		sleep(2);
		sem_post(&production_Administrator);
		printf("----SMOKER WITH TOBACO IS SMOKING !!! :) ----\n");
		sleep(2);
	}
}

void* smoking_With_Match(void *arg){
	while(1){
		sem_wait(&transporter_Match);
		printf("----SMOKER WITH MATCH IS MAKING THE CIGARETTE----\n");
		sleep(2);
		sem_post(&production_Administrator);
		printf("----SMOKER WITH MATCH IS SMOKING !!! :) ----\n");
		sleep(2);
	}
}


void* smoking_With_Paper(void *arg){
	while(1){
		sem_wait(&transporter_Paper);
		printf("----SMOKER WITH PAPER IS MAKING THE CIGARETTE----\n");
		sleep(2);
		sem_post(&production_Administrator);
		printf("----SMOKER WITH PAPER IS SMOKING !!! :) ----\n");
		sleep(2);
	}
}

int main(){

	pthread_t productor_Tobacco_Match, productor_Tobacco_Paper, productor_Paper_Match;
	pthread_t smoker_With_Tobacco, smoker_With_Match, smoker_With_Paper;
	pthread_t transporter_Tobacco_t, transporter_Match_t, transporter_Paper_t;

	sem_init(&production_Administrator, 0, 1);
	sem_init(&production_Tobacco, 0, 0);
	sem_init(&production_Match, 0, 0);
	sem_init(&production_Paper, 0, 0);

	if (pthread_create(&productor_Tobacco_Match, NULL, &producting_Tobacco_Match, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&productor_Tobacco_Paper, NULL, &producting_Tobacco_Paper, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&productor_Paper_Match, NULL, &producting_Paper_Match, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&smoker_With_Tobacco, NULL, &smoking_With_Tobacco, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&smoker_With_Match, NULL, &smoking_With_Match, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&smoker_With_Paper, NULL, &smoking_With_Paper, NULL) != 0)
		perror("Failed to create thread\n");





	sem_destroy(&production_Administrator);
	sem_destroy(&production_Tobacco);
	sem_destroy(&production_Paper);
	sem_destroy(&production_Match);




	return 0;
}


