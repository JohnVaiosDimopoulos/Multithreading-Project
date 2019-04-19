#ifndef KOUVALAME_XATZO_PTHREAD_FUNCTIONS_H
#define KOUVALAME_XATZO_PTHREAD_FUNCTIONS_H
#include <pthread.h>

struct Init_file_data;
void Start_Clients(pthread_t* clients_array,int num_of_clients, struct Init_file_data file_data);
void Wait_for_clients_to_finish(pthread_t* clients_array,int num_of_clients);
void Destroy_Mutexes_and_cond();

#endif //KOUVALAME_XATZO_PTHREAD_FUNCTIONS_H
