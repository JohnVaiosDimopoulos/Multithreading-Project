#include "initialization_functions.h"
#include "../Global_structs/Global_Structs.h"
#include "Initialization_Data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *Open_file();

void Initialize_seat_array(const struct Global_data *global_data, Init_file_data *file_data);

void check_Arguments_number(int argc){

  if(argc!=5){
    printf("Wrong number of arguments\n");
    printf("Correnct format is: -n 'clients_num' -r 'random seed\n");
    exit(-1);
  }
}

Argument_data Get_Arguments(int argc,char** argv){

  check_Arguments_number(argc);
  int clients_num;
  int seed;

  for(int i =1;i<argc;i++){

    if(!strcmp("-n",argv[i])){
      i++;
      clients_num=atoi(argv[i]);
    }

    else if(!strcmp("-r",argv[i])){
      i++;
      seed=atoi(argv[i]);
    }

    else{
      printf("WRONG ARGUMET FORMAT\n");
      printf("Correnct format is: -n 'clients_num' -r 'random seed\n");
      exit(-1);
    }
  }

  Argument_data data = {clients_num,seed};
  return data;
}

FILE *Open_file() {

  FILE *Initialization_file;
  if ((Initialization_file = fopen("./Data_file/data.txt", "r")) == NULL) {
    printf("error at file opening");
    exit(-1);
  }
  return Initialization_file;
}

Init_file_data Read_data_from_file(FILE* Initialization_file){

  int Seats_number;
  int Telephones_number;
  int S_low;
  int S_high;
  int wait_low;
  int wait_high;
  int success_prob;
  int seat_cost;

  fscanf(Initialization_file,"seat_num = %d\n "
                             "tel_num = %d\n"
                             "seat_low = %d\n"
                             "seat_high = %d\n"
                             "wait_low = %d\n"
                             "wait_high = %d\n"
                             "success_prob = %d\n"
                             "cost = %d",&Seats_number,&Telephones_number,&S_low,&S_high,&wait_low,&wait_high,&success_prob,&seat_cost);

  Init_file_data file_data ={Seats_number,Telephones_number,S_low,S_high,wait_low,wait_high,success_prob,seat_cost};
  return file_data;
}

Init_file_data Get_data_from_file(){
  FILE* Initialization_file = Open_file();
  return Read_data_from_file(Initialization_file);



}

void Init_mutex_and_check(pthread_mutex_t mutex){
  if(pthread_mutex_init(&mutex,NULL)){
    printf("Mutex init error");
    exit(-1);
  }

}

void Init_cond_and_check(pthread_cond_t cond){
  if(pthread_cond_init(&cond,NULL)){
    printf("condition initialization error");
    exit(-1);
  }
}

void Initialize_mutexes(struct Mutexes_and_cond* mutexes_and_cond){

  Init_mutex_and_check(mutexes_and_cond->Available_telephone);
  Init_mutex_and_check(mutexes_and_cond->Update_income);
  Init_mutex_and_check(mutexes_and_cond->Update_transaction_counter);
  Init_mutex_and_check(mutexes_and_cond->Update_wait_time);
  Init_mutex_and_check(mutexes_and_cond->Update_throughput_time);
  Init_mutex_and_check(mutexes_and_cond->Update_seats);
  Init_mutex_and_check(mutexes_and_cond->Writing_in_stdout);
  Init_cond_and_check(mutexes_and_cond->Telephone_cond);
}


void Initialize_seat_array(const struct Global_data *global_data, Init_file_data *file_data) {
  for (int i = 0; i < (*file_data).Seats_number; i++) {
    global_data->seats_array[i].Client_num = -1;
    global_data->seats_array[i].curr_status = FREE;
    global_data->seats_array[i].Seat_num = i + 1;
  }
}


void Initialize_global_data(struct Global_data* global_data,Init_file_data file_data){

  global_data->seats_array=malloc(file_data.Seats_number* sizeof(Seat));
  Initialize_seat_array(global_data, &file_data);
  global_data->telephones_available=file_data.Telephones_number;
  global_data->seats_available=file_data.Seats_number;
  global_data->total_wait_time=0.0;
  global_data->total_throughput_time=0.0;
  global_data->total_num_of_seats=file_data.Seats_number;
  global_data->total_transactions=0;
}


