#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#ifndef LINUX_OS
	#include <dispatch/dispatch.h>
#endif

// Constants to define state matrix size
#define PERSON_QTD		3+1	// 3 smokers + Admnistrator
#define RESOURCES_QTD 	3+1	// 3 Ingredients + IsSmoking

#define M_MATCH_INDEX		0
#define M_TOBACCO_INDEX		1
#define M_PAPER_INDEX		2
#define M_IS_SMOKING_INDEX	3

#define M_ADM_INDEX				0
#define M_SMOKER_MATCH_INDEX	1
#define M_SMOKER_TOBACCO_INDEX	2
#define M_SMOKER_PAPER_INDEX	3

int global_State_Matrix[PERSON_QTD][RESOURCES_QTD] = {0};


#ifdef LINUX_OS
//Semaphores for ingredient production administration
	sem_t production_Administrator;
	sem_t production_Tobacco;
	sem_t production_Paper;
	sem_t production_Match;
	//Semaphores for transporters
	sem_t transporter_Tobacco;
	sem_t transporter_Paper;
	sem_t transporter_Match;
#else
	dispatch_semaphore_t production_Administrator;
	dispatch_semaphore_t production_Tobacco;
	dispatch_semaphore_t production_Paper;
	dispatch_semaphore_t production_Match;
	dispatch_semaphore_t transporter_Tobacco;
	dispatch_semaphore_t transporter_Paper;
	dispatch_semaphore_t transporter_Match;
#endif

//Mutex for controlling transporters access to availability variables
pthread_mutex_t mutex;

//Variables for signaling the presence of ingredients (availability variables)
int isTobacco = 0;
int isPaper = 0;
int isMatch = 0;

void print_actual_state(){
	system("clear");
	printf("		|| M | T | P || S |\n");
	printf("________________||___|___|___||___|\n");
	for(int person=0; person<PERSON_QTD; person++){
		if (person == 0)
			printf("Agent 		||");
		if (person == 1)
			printf("Smoker Match	||");
		if (person == 2)
			printf("Smoker Tobacco	||");
		if (person == 3)
			printf("Smoker Paper	||");
		for (int resource=0; resource<RESOURCES_QTD; resource++){
			printf(" %d |", global_State_Matrix[person][resource]);
			if (resource == 2)
				printf("|");
		}
		printf("\n");
	}
}

void* producting_Tobacco_Match(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&production_Administrator);
#else
		dispatch_semaphore_wait(production_Administrator, DISPATCH_TIME_FOREVER);
#endif
		global_State_Matrix[M_ADM_INDEX][M_TOBACCO_INDEX] = 1;
		global_State_Matrix[M_ADM_INDEX][M_MATCH_INDEX] = 1;
		global_State_Matrix[M_ADM_INDEX][M_PAPER_INDEX] = 0;

		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_IS_SMOKING_INDEX] = 0;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_IS_SMOKING_INDEX] = 0;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_IS_SMOKING_INDEX] = 0;

		print_actual_state();
		printf("----PRODUCTION OF TOBACCO AND MATCH IS GOING ON----\n");
		sleep(2);
#ifdef LINUX_OS
		sem_post(&production_Tobacco);
		sem_post(&production_Match);
#else
		dispatch_semaphore_signal(production_Tobacco);
		dispatch_semaphore_signal(production_Match);
#endif
	}
}

void* producting_Tobacco_Paper(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&production_Administrator);
#else
		dispatch_semaphore_wait(production_Administrator, DISPATCH_TIME_FOREVER);
#endif
		global_State_Matrix[M_ADM_INDEX][M_TOBACCO_INDEX] = 1;
		global_State_Matrix[M_ADM_INDEX][M_MATCH_INDEX] = 0;
		global_State_Matrix[M_ADM_INDEX][M_PAPER_INDEX] = 1;

		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_IS_SMOKING_INDEX] = 0;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_IS_SMOKING_INDEX] = 0;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_IS_SMOKING_INDEX] = 0;

		print_actual_state();
		printf("----PRODUCTION OF TOBACCO AND PAPER IS GOING ON----\n");
		sleep(2);
#ifdef LINUX_OS
		sem_post(&production_Tobacco);
		sem_post(&production_Paper);
#else
		dispatch_semaphore_signal(production_Tobacco);
		dispatch_semaphore_signal(production_Paper);
#endif
	}
}

void* producting_Paper_Match(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&production_Administrator);
#else
		dispatch_semaphore_wait(production_Administrator, DISPATCH_TIME_FOREVER);
#endif

		global_State_Matrix[M_ADM_INDEX][M_TOBACCO_INDEX] = 0;
		global_State_Matrix[M_ADM_INDEX][M_MATCH_INDEX] = 1;
		global_State_Matrix[M_ADM_INDEX][M_PAPER_INDEX] = 1;

		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_IS_SMOKING_INDEX] = 0;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_IS_SMOKING_INDEX] = 0;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_IS_SMOKING_INDEX] = 0;

		print_actual_state();
		printf("----PRODUCTION OF PAPER AND MATCH IS GOING ON----\n");
		sleep(2);
#ifdef LINUX_OS
		sem_post(&production_Paper);
		sem_post(&production_Match);
#else
		dispatch_semaphore_signal(production_Paper);
		dispatch_semaphore_signal(production_Match);
#endif
	}
}


void* smoking_With_Tobacco(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&transporter_Tobacco);
#else
		dispatch_semaphore_wait(transporter_Tobacco, DISPATCH_TIME_FOREVER);
#endif
		global_State_Matrix[M_ADM_INDEX][M_MATCH_INDEX] = 0;
		global_State_Matrix[M_ADM_INDEX][M_PAPER_INDEX] = 0;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_MATCH_INDEX] = 1;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_PAPER_INDEX] = 1;
		print_actual_state();
		printf("----SMOKER WITH TOBACCO IS MAKING THE CIGARETTE----\n");
		sleep(2);

		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_MATCH_INDEX] = 0;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_PAPER_INDEX] = 0;
		global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_IS_SMOKING_INDEX] = 1;
		print_actual_state();
		printf("----SMOKER WITH TOBACCO IS SMOKING !!! :) ----\n");
		sleep(2);

#ifdef LINUX_OS
		sem_post(&production_Administrator);
#else
		dispatch_semaphore_signal(production_Administrator);
#endif
	}
}

void* smoking_With_Match(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&transporter_Match);
#else
		dispatch_semaphore_wait(transporter_Match, DISPATCH_TIME_FOREVER);
#endif

		global_State_Matrix[M_ADM_INDEX][M_TOBACCO_INDEX] = 0;
		global_State_Matrix[M_ADM_INDEX][M_PAPER_INDEX] = 0;
		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_TOBACCO_INDEX] = 1;
		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_PAPER_INDEX] = 1;
		print_actual_state();
		printf("----SMOKER WITH MATCH IS MAKING THE CIGARETTE----\n");
		sleep(2);

		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_TOBACCO_INDEX] = 0;
		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_PAPER_INDEX] = 0;
		global_State_Matrix[M_SMOKER_MATCH_INDEX][M_IS_SMOKING_INDEX] = 1;
		print_actual_state();
		printf("----SMOKER WITH MATCH IS SMOKING !!! :) ----\n");
		sleep(2);

#ifdef LINUX_OS
		sem_post(&production_Administrator);
#else
		dispatch_semaphore_signal(production_Administrator);
#endif
	}
}

void* smoking_With_Paper(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&transporter_Paper);
#else
		dispatch_semaphore_wait(transporter_Paper, DISPATCH_TIME_FOREVER);
#endif

		global_State_Matrix[M_ADM_INDEX][M_TOBACCO_INDEX] = 0;
		global_State_Matrix[M_ADM_INDEX][M_MATCH_INDEX] = 0;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_TOBACCO_INDEX] = 1;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_MATCH_INDEX] = 1;
		print_actual_state();
		printf("----SMOKER WITH PAPER IS MAKING THE CIGARETTE----\n");
		sleep(2);

		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_TOBACCO_INDEX] = 0;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_MATCH_INDEX] = 0;
		global_State_Matrix[M_SMOKER_PAPER_INDEX][M_IS_SMOKING_INDEX] = 1;
		print_actual_state();
		printf("----SMOKER WITH PAPER IS SMOKING !!! :) ----\n");
		sleep(2);

#ifdef LINUX_OS
		sem_post(&production_Administrator);
#else
		dispatch_semaphore_signal(production_Administrator);
#endif
	}
}


void* transporting_Tobacco(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&production_Tobacco);
#else
		dispatch_semaphore_wait(production_Tobacco, DISPATCH_TIME_FOREVER);
#endif
		pthread_mutex_lock(&mutex);
		if(isPaper){
			isPaper = 0;
#ifdef LINUX_OS
			sem_post(&transporter_Match);
#else
			dispatch_semaphore_signal(transporter_Match);
#endif
		}
		else if(isMatch){
			isMatch = 0;
#ifdef LINUX_OS
			sem_post(&transporter_Paper);
#else
			dispatch_semaphore_signal(transporter_Paper);
#endif
		}
		else{
			isTobacco = 1;
		}

		pthread_mutex_unlock(&mutex);
	}
}

void* transporting_Match(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&production_Match);
#else
		dispatch_semaphore_wait(production_Match, DISPATCH_TIME_FOREVER);
#endif
		pthread_mutex_lock(&mutex);
		if(isPaper){
			isPaper = 0;
#ifdef LINUX_OS
			sem_post(&transporter_Tobacco);
#else
			dispatch_semaphore_signal(transporter_Tobacco);
#endif
		}
		else if(isTobacco){
			isTobacco = 0;
#ifdef LINUX_OS
			sem_post(&transporter_Paper);
#else
			dispatch_semaphore_signal(transporter_Paper);
#endif
		}
		else{
			isMatch = 1;
		}

		pthread_mutex_unlock(&mutex);
	}
}

void* transporting_Paper(void *arg){
	while(1){
#ifdef LINUX_OS
		sem_wait(&production_Paper);
#else
		dispatch_semaphore_wait(production_Paper, DISPATCH_TIME_FOREVER);
#endif
		pthread_mutex_lock(&mutex);
		if(isTobacco){
			isTobacco = 0;
#ifdef LINUX_OS
			sem_post(&transporter_Match);
#else
			dispatch_semaphore_signal(transporter_Match);
#endif
		}
		else if(isMatch){
			isMatch = 0;
#ifdef LINUX_OS
			sem_post(&transporter_Tobacco);
#else
			dispatch_semaphore_signal(transporter_Tobacco);
#endif
		}
		else{
			isPaper = 1;
		}

		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	global_State_Matrix[M_SMOKER_MATCH_INDEX][M_MATCH_INDEX] = 1;
	global_State_Matrix[M_SMOKER_TOBACCO_INDEX][M_TOBACCO_INDEX] = 1;
	global_State_Matrix[M_SMOKER_PAPER_INDEX][M_PAPER_INDEX] = 1;

	pthread_t productor_Tobacco_Match, productor_Tobacco_Paper, productor_Paper_Match;
	pthread_t smoker_With_Tobacco, smoker_With_Match, smoker_With_Paper;
	pthread_t transporter_Tobacco_t, transporter_Match_t, transporter_Paper_t;

#ifdef LINUX_OS
	sem_init(&production_Administrator, 0, 1);
	sem_init(&production_Tobacco, 0, 0);
	sem_init(&production_Match, 0, 0);
	sem_init(&production_Paper, 0, 0);

	sem_init(&transporter_Tobacco, 0, 0);
	sem_init(&transporter_Match, 0, 0);
	sem_init(&transporter_Paper, 0, 0);
#else
	production_Administrator = dispatch_semaphore_create(1);
	production_Tobacco = dispatch_semaphore_create(0);
	production_Match = dispatch_semaphore_create(0);
	production_Paper = dispatch_semaphore_create(0);

	transporter_Tobacco = dispatch_semaphore_create(0);
	transporter_Match = dispatch_semaphore_create(0);
	transporter_Paper = dispatch_semaphore_create(0);
#endif

	pthread_mutex_init(&mutex, NULL);

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

	if (pthread_create(&transporter_Tobacco_t, NULL, &transporting_Tobacco, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&transporter_Match_t, NULL, &transporting_Match, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&transporter_Paper_t, NULL, &transporting_Paper, NULL) != 0)
		perror("Failed to create thread\n");

	if (pthread_join(productor_Tobacco_Match, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(productor_Tobacco_Paper, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(productor_Paper_Match, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(smoker_With_Tobacco, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(smoker_With_Match, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(smoker_With_Paper, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(transporter_Tobacco_t, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(transporter_Match_t, NULL) != 0)
		perror("Failed to join thread\n");

	if (pthread_join(transporter_Paper_t, NULL) != 0)
		perror("Failed to join thread\n");


	pthread_mutex_destroy(&mutex);

#ifdef LINUX_OS
	sem_destroy(&production_Administrator);
	sem_destroy(&production_Tobacco);
	sem_destroy(&production_Paper);
	sem_destroy(&production_Match);

	sem_destroy(&transporter_Tobacco);
	sem_destroy(&transporter_Match);
	sem_destroy(&transporter_Paper);
#else
	dispatch_release(production_Administrator);
	dispatch_release(production_Tobacco);
	dispatch_release(production_Paper);
	dispatch_release(production_Match);

	dispatch_release(transporter_Tobacco);
	dispatch_release(transporter_Match);
	dispatch_release(transporter_Paper);
#endif
	return 0;
}
