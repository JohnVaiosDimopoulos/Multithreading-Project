#include "Pthread_functions.h"
#include "Thread_data_structs.h"
#include "../Util/Initialization_Data.h"
#include "../Global_structs/Global_Structs.h"
#include "../Util/List.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//==MUTEX/Cond-FUNCTIONS==//
void Lock_on_mutex(pthread_mutex_t *mutex) {

  if (pthread_mutex_lock(mutex)) {
    printf("locking on mutex failed\n");
    exit(-1);
  }
}

void Unlock_on_mutex(pthread_mutex_t* mutex){
  if(pthread_mutex_unlock(mutex)){
    printf("unlocking on mutex failed\n");
    exit(-1);
  }
}

void Wait_on_cond(pthread_cond_t* cond,pthread_mutex_t* mutex){
  if(pthread_cond_wait(cond,mutex)){
    printf("wait on condition failed\n");
    exit(-1);
  }
}


//==Utility functions==//
int Is_Theater_full(){
  // if theater if full return 1 else return 0
  Lock_on_mutex(&mutexes_and_cond.Update_seats);
  for(int i=0;i<global_data.total_num_of_seats;i++){
    if(global_data.seats_array[i].curr_status==FREE) {
      Unlock_on_mutex(&mutexes_and_cond.Update_seats);
      return 0;
    }
  }
  Unlock_on_mutex(&mutexes_and_cond.Update_seats);
  return 1;
}

int Check_if_there_are_enough_seats(int num_of_seats_to_book){

  // if there are enough seats return 0 else return 1
  Lock_on_mutex(&mutexes_and_cond.Update_seats);
  if(num_of_seats_to_book<=global_data.seats_available) {
    Unlock_on_mutex(&mutexes_and_cond.Update_seats);
    return  0;
  }
  Unlock_on_mutex(&mutexes_and_cond.Update_seats);

  return 1;
}

int calculate_random_value(int min, int max){
  return rand()%(max-min+1)+min;
}

double Calc_time_pasted(struct timespec start,struct timespec end){

  int long diff_in_ms;
  diff_in_ms=(end.tv_sec-start.tv_sec)*100000 +(end.tv_nsec-start.tv_nsec)/1000;
  return diff_in_ms;
}

void Print_Exit_message(Server_return_data* transaction_info){


  if(transaction_info->error_num==0){
    printf("=================\n");
    printf("Transaction with id:%d succesfull\n",transaction_info->transaction_id);
    printf("Seats Booked:");
    Print_list(transaction_info->seat_list);
    printf("Total cost:%d\n",transaction_info->transaction_cost);
    printf("=================\n");

  }

  else if(transaction_info->error_num==1){
    printf("=================\n");
    printf("Transaction failed due to credit card error\n");
    printf("=================\n");
  }
  else if(transaction_info->error_num==2){
    printf("=================\n");
    printf("Transaction failed due to lack of seats\n");
    printf("=================\n");
  }
  else if(transaction_info->error_num==3){
    printf("=================\n");
    printf("Trasaction failed because the theater is full\n");
    printf("=================\n");
  }

}

int Check_if_credit_fails(int succes_propabillity){

  int random_number = calculate_random_value(0,100);
  // if the card fails return 1 else return 0
  if(random_number<succes_propabillity)
    return 0;
  return 1;
}

void Update_total_income(int transaction_cost){

  Lock_on_mutex(&mutexes_and_cond.Update_income);
  global_data.total_income +=transaction_cost;
  Unlock_on_mutex(&mutexes_and_cond.Update_income);
}

void Update_total_transactions(){
  Lock_on_mutex(&mutexes_and_cond.Update_transaction_counter);
  global_data.total_transactions++;
  Unlock_on_mutex(&mutexes_and_cond.Update_transaction_counter);
}

void simulate_wait_time(const thread_arg *data) {

  int seconds_to_sleep = calculate_random_value(data->wait_low, data->wait_high);
  sleep(seconds_to_sleep);
}


//==SERVER-FUNCITONS==//
List* Book_Seats(int num_of_seats_to_book,int client_id){

  // we return a list with the seats that we book
  List* seat_list = malloc(sizeof(List));

  Lock_on_mutex(&mutexes_and_cond.Update_seats);
  // keep track of the seats left to find
  int seats_left=num_of_seats_to_book;
  for(int i =0;i<global_data.total_num_of_seats && seats_left!=0 ;i++){
    //if we find a free seat
    if(global_data.seats_array[i].curr_status==FREE){
      // we take it
      global_data.seats_array[i].curr_status=RESERVED;
      global_data.seats_available--;
      global_data.seats_array[i].Client_num=client_id;
      seats_left--;
      Insert_on_front(seat_list,global_data.seats_array[i].Seat_num);
    }
  }
  Unlock_on_mutex(&mutexes_and_cond.Update_seats);

  return seat_list;
}

Server_return_data* Serve_client(thread_arg* data, int num_of_seats_to_book){

  Server_return_data* transaction_info = malloc(sizeof(Server_return_data));
  transaction_info->seat_list=NULL;
  simulate_wait_time(data);

  if(Is_Theater_full()){
    transaction_info->error_num=3;
    return transaction_info;
  }

  if(Check_if_there_are_enough_seats(num_of_seats_to_book)){
    transaction_info->error_num=2;
    return transaction_info;
  }

  if(Check_if_credit_fails(data->success_prob)){
    transaction_info->error_num=1;
    return transaction_info;
  }

  transaction_info->seat_list=Book_Seats(num_of_seats_to_book,data->client_id);
  transaction_info->transaction_cost = num_of_seats_to_book*data->seat_cost;
  Update_total_income(transaction_info->transaction_cost);
  transaction_info->transaction_id=(global_data.total_transactions+1);
  Update_total_transactions();

  return transaction_info;
}


//==Thread-functions==//
void* thread(void *arg){

  thread_arg* data = (thread_arg*)arg;
  struct timespec wait_start,wait_end,throughput_start,throughput_end;

  //start clock for throughput_time;
  clock_gettime(CLOCK_REALTIME,&throughput_start);

  //get a random number of the seats to book
  int num_of_seats_to_book = calculate_random_value(data->S_low, data->S_high);

  //start_clock for wait_time
  clock_gettime(CLOCK_REALTIME,&wait_start);
  Lock_on_mutex(&mutexes_and_cond.Available_telephone);
  while (global_data.telephones_available==0){
    Wait_on_cond(&mutexes_and_cond.Telephone_cond,&mutexes_and_cond.Available_telephone);
  }
  global_data.telephones_available--;
  Unlock_on_mutex(&mutexes_and_cond.Available_telephone);
  clock_gettime(CLOCK_REALTIME,&wait_end);

  Server_return_data* transaction_info = Serve_client(data,num_of_seats_to_book);
  pthread_cond_signal(&mutexes_and_cond.Telephone_cond);
  global_data.telephones_available++;

  //stop clock for throughput time
  clock_gettime(CLOCK_REALTIME,&throughput_end);

  //update total throughput_time;
  Lock_on_mutex(&mutexes_and_cond.Update_throughput_time);
  global_data.total_throughput_time=+Calc_time_pasted(throughput_start,throughput_end);
  Unlock_on_mutex(&mutexes_and_cond.Update_throughput_time);

  //update total wait_time;
  Lock_on_mutex(&mutexes_and_cond.Update_wait_time);
  global_data.total_wait_time=+Calc_time_pasted(wait_start,wait_end);
  Unlock_on_mutex(&mutexes_and_cond.Update_wait_time);

  //print message
  Lock_on_mutex(&mutexes_and_cond.Writing_in_stdout);
  Print_Exit_message(transaction_info);
  Unlock_on_mutex(&mutexes_and_cond.Writing_in_stdout);

  if(transaction_info->seat_list!=NULL){
    free(transaction_info->seat_list);
  }
  free(transaction_info);
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



//==DELETING FUNCTIONS==//
void Destroy_Mutex(pthread_mutex_t* mutex){
  if(pthread_mutex_destroy(mutex)){
    printf("error while destroying mutex\n");
    exit(-1);
  }
}

void Destroy_cond(pthread_cond_t* cond){
  if(pthread_cond_destroy(cond)){
    printf("error while destroying cond\n");
    exit(-1);
  }
}

void Destroy_Mutexes_and_cond(){
  Destroy_Mutex(&mutexes_and_cond.Update_transaction_counter);
  Destroy_Mutex(&mutexes_and_cond.Update_income);
  Destroy_Mutex(&mutexes_and_cond.Update_seats);
  Destroy_Mutex(&mutexes_and_cond.Update_wait_time);
  Destroy_Mutex(&mutexes_and_cond.Update_throughput_time);
  Destroy_Mutex(&mutexes_and_cond.Available_telephone);
  Destroy_Mutex(&mutexes_and_cond.Writing_in_stdout);
  Destroy_cond(&mutexes_and_cond.Telephone_cond);

}
