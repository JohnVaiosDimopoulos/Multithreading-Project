#include "Statistics.h"
#include "Initialization_Data.h"
#include "../Global_structs/Global_Structs.h"
#include <stdio.h>

void Prit_seats_array(Seat* seat_array,int num_of_seats){

  for(int i =0;i<num_of_seats;i++){
    printf("===SEAT:%d ",seat_array[i].Seat_num);
    if(seat_array[i].Client_num==-1)
      printf("CLIENT: SEAT_EMPTY");
    else
      printf("CLEINT:%d ",seat_array[i].Client_num);
    printf("===\n");
  }
}

double Calculate_average_wait_time(int num_of_clients){
  return global_data.total_wait_time/num_of_clients;
}

double Calculate_average_throughput_time(int num_of_clients){
  return global_data.total_throughput_time/num_of_clients;
}

void Print_Stats(struct Argument_data data, struct Init_file_data file_data){
  Prit_seats_array(global_data.seats_array,file_data.Seats_number);
  printf("Total_income: %d\n",global_data.total_income);
  printf("Average client wait_time in milliseconds: %lf \n",Calculate_average_wait_time(data.clients_num));
  printf("Average client throughput time in milliseconds: %lf \n",Calculate_average_throughput_time(data.clients_num));
}

