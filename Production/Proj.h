#ifndef KOUVALAME_XATZO_PROJ_H
#define KOUVALAME_XATZO_PROJ_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum status {FREE,RESERVED} typedef status;

struct Seat{
  int Seat_num;
  int Client_num;
  status curr_status;
}typedef Seat;

struct Mutexes_and_cond{
  pthread_mutex_t Available_telephone;
  pthread_mutex_t Update_income;
  pthread_mutex_t Update_transaction_counter;
  pthread_mutex_t Update_wait_time;
  pthread_mutex_t Update_throughput_time;
  pthread_mutex_t Update_seats;
  pthread_mutex_t Writing_in_stdout;
  pthread_cond_t  Telephone_cond;
}typedef  Mutexes_and_cond;

struct Global_data {
  Seat* seats_array;
  int total_transactions;
  int total_num_of_seats;
  int telephones_available;
  int total_income;
  int seats_available;
  double total_wait_time;
  double total_throughput_time;

}typedef Global_data;

struct List_node{
  int item;
  struct List_node* next;
}typedef List_node;

struct List{
  List_node* head;
}typedef List;

struct Argument_data{
  const int clients_num;
  const int rand_seed;
}typedef Argument_data;

struct Init_file_data {
  const int Seats_number;
  const int Telephones_number;
  const int S_low;
  const int S_high;
  const int wait_low;
  const int wait_high;
  const int success_prob;
  const int seat_cost;

}typedef Init_file_data;

struct thread_arg{
  int S_low;
  int S_high;
  int wait_low;
  int wait_high;
  int success_prob;
  int seat_cost;
  int client_id;

}typedef thread_arg;

struct Server_return_data{
  struct List* seat_list;
  int transaction_id;
  int transaction_cost;
  int error_num;
}typedef Server_return_data;








Mutexes_and_cond mutexes_and_cond;
Global_data global_data;

#endif //KOUVALAME_XATZO_PROJ_H
