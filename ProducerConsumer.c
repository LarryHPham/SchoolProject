#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/* buffer.h */
typedef int buffer_item;
#define BUFFER_SIZE 5

// Declare Global variables
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t full, empty;
int count, in, out;

// Declare Function prototypes
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void *consumer(void *param);
void *producer(void *param);

int main(){
        //declare variables
        int sleep_time, numproducers, numconsumers;
        int i;

        //get user input to set declared variables
        printf("\nHow long before program Stops (Secs): ");
        scanf("%d", &sleep_time);
        printf("\nEnter Number of Producers: ");
        scanf("%d", &numproducers);
        printf("\nEnter Number of Consumers: ");
        scanf("%d", &numconsumers);

        // Initialize synchronization
        srand(time(NULL));
        pthread_mutex_init(&mutex, NULL);
        sem_init(&empty, 0, 5);
        sem_init(&full, 0, 0);

        count = in = out = 0;
        // Create threads for producer and consumer
        pthread_t producers[numproducers];
        pthread_t consumers[numconsumers];
        for(i = 0; i < numproducers; i++){
          pthread_create(&producers[i], NULL, producer, NULL);
        }
        for(i = 0; i < numconsumers; i++){
          pthread_create(&consumers[i], NULL, consumer, NULL);
        }


        // Sleep before terminating
        sleep(sleep_time);
        return 0;
}


//producer function to create item to add into buffer item
void *producer(void *param){
        buffer_item item;
        while(1) {
                sleep(rand() % 5 + 1); // Sleep randomly between 1 and 5 seconds

                item = rand();
                if(insert_item(item)){
                  printf("Error occured\n");
                }else{
                  printf("Producer produced %d\n", item);
                }
        }
}
// Insert item into buffer.
//Returns 0 if successful, -1 indicating error
int insert_item(buffer_item item){
        int success;
        //wait for value to be higher than 0 to continue executing code otherwise thread will wait
        //remove from empty variable
        sem_wait(&empty);

        //block mutex object reference until available
        pthread_mutex_lock(&mutex);

        // Add item to buffer
        if( count != BUFFER_SIZE) {
                buffer[in] = item;
                in = (in + 1) % BUFFER_SIZE;
                count++;
                success = 0;
        }else{
                success = -1;
        }

        //unblock mutex thread to be available for next item
        pthread_mutex_unlock(&mutex);

        //post to increment semaphore value and wake other threads up of greater than 1
        //add to full variable
        sem_post(&full);

        return success;
}


//consumer function to remove item from the buffer  item
void *consumer(void *param){
        buffer_item item;
        while(1) {
                sleep(rand() % 5 + 1); // Sleep randomly between 1 and 5 seconds

                if(remove_item(&item)){
                  printf("Error occured\n");
                }else{
                  printf("Consumer consumed %d\n", item);
                }
        }//end while loop
}
// Remove an object from the buffer, placing it in item.
// Returns 0 if successful, -1 indicating error
int remove_item(buffer_item *item){
        int success;

        //wait for value to be higher than 0 to continue executing code otherwise thread will wait
        //remove from full variable
        sem_wait(&full);

        //block mutex object reference until available
        pthread_mutex_lock(&mutex);

        // Remove item from buffer to item
        if( count != 0) {
                *item = buffer[out];
                out = (out + 1) % BUFFER_SIZE;
                count--;
                success = 0;
        }else{
                success = -1;
        }

        //unblock mutex thread to be available for next item
        pthread_mutex_unlock(&mutex);

        //post to increment semaphore value and wake other threads up of greater than 1
        //add to empty variable
        sem_post(&empty);

        return success;
}
