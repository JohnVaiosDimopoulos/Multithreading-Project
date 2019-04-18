#ifndef KOUVALAME_XATZO_GLOBAL_STRUCTS_H
#define KOUVALAME_XATZO_GLOBAL_STRUCTS_H

#include <pthread.h>

enum status {FREE,RESERVED} typedef status;

struct Seat{
  int Seat_num;
  int Client_num;
  status curr_status;
}typedef Seat;

struct Mutexes_and_cond{
  pthread_mutex_t Available_telephone;
  pthread_mutex_t Bank_account_available;
  pthread_mutex_t Update_transaction_counter;
  pthread_mutex_t Update_wait_time;
  pthread_mutex_t Update_throughput_time;
  pthread_mutex_t Update_seats;
  pthread_mutex_t Writing_in_stdout;
  pthread_cond_t  Telephone_cond;
}typedef  Mutexes_and_cond;

struct Global_data {
  Seat* seats_array;
  int telephones_available;
  int seats_available;
  int S_low;
  int S_high;
  int wait_low;
  int wait_high;
  int Prob_success;
  int Seat_cost;

}typedef Global_data;

Mutexes_and_cond mutexes_and_cond;
Global_data global_data;

#endif //KOUVALAME_XATZO_GLOBAL_STRUCTS_H
