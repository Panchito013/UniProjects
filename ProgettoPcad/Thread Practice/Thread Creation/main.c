#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_message_function(void* ptr);

typedef char* string;

int main(){

    pthread_t thread1, thread2;
    string message1 = "Thread 1";
    string message2 = "Thread 2";
    int t_err1,t_err2;

    t_err1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    t_err2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", t_err1);
    printf("Thread 2 returns: %d\n", t_err2);
    exit(0);
}

void* print_message_function(void* ptr){
    string message;
    message = (string) ptr;
    printf("%s \n", message);
}