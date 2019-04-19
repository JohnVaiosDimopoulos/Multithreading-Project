#ifndef KOUVALAME_XATZO_THREAD_DATA_STRUCTS_H
#define KOUVALAME_XATZO_THREAD_DATA_STRUCTS_H

struct List;

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

#endif //KOUVALAME_XATZO_THREAD_DATA_STRUCTS_H
