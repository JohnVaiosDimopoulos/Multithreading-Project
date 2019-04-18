#include "Pthread_functions.h"
#include "Thread_input_data.h"
#include "../Util/Initialization_Data.h"
#include "../Global_structs/Global_Structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread(void *arg){
  //start clock for through_put;
  thread_arg* data = (thread_arg*)arg;
  pthread_mutex_lock(&mutexes_and_cond.Writing_in_stdout);
  printf("I'am thread: %d and will sleep\n",data->client_id);
  pthread_mutex_unlock(&mutexes_and_cond.Writing_in_stdout);

  //1.get number of seats to ask for
  //2.tart timer for wait
  //3.lock_for_telephone
  //4.while(avail_teleph)
    //wait_on_cond
  //5.stop timer for  wait
  //6.tel_avail--
  //7.call function
  //8.end_clock for thtouput
  //9.calc_time
    //lock_thorouput_time_mutex
    //update_time
    //unlock_thoroughput_time_mutex
  //10.same for wait time
  //11.lock_stdin
  //12.print_message
  //13.unlock_stdin
  free(data);
  pthread_exit(NULL);
}

thread_arg* Create_thread_argumet(int client_id,struct Init_file_data file_data){
  thread_arg* argument = malloc(sizeof(thread_arg));
  argument->client_id=client_id;
  argument->S_low=file_data.S_low;
  argument->S_high=file_data.S_high;
  argument->wait_low=file_data.wait_low;
  argument->wait_high=file_data.wait_high;
  argument->success_prob=file_data.success_prob;
  argument->seat_cost=file_data.seat_cost;

  return argument;
}

void Start_Clients(pthread_t* clients_array,int num_of_clients, struct Init_file_data file_data){

  for(int i =0;i<num_of_clients;i++){
    thread_arg* arg = Create_thread_argumet(i,file_data);
    if(pthread_create(&(clients_array[i]),NULL,thread,(void*)arg)){
      printf("thread error");
      exit(-1);
    }
  }
}

void Wait_for_clients_to_finish(pthread_t* clients_array,int num_of_clients){

  for (int i = 0; i<num_of_clients ;i++) {
    if(pthread_join(clients_array[i],NULL)){
      printf("thread error");
      exit(-1);
    }
  }
}


