#include "initialization_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *Open_file();

void check_Arguments_number(int argc){

  if(argc!=5){
    printf("Wrong number of arguments\n");
    printf("Correnct format is: -n 'clients_num' -r 'random seed\n");
    exit(-1);
  }
}

Argumet_data Get_Arguments(int argc,char** argv){

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

  Argumet_data data = {clients_num,seed};
  return data;
}

FILE *Open_file() {

  FILE *Initialization_file;
  if ((Initialization_file = fopen("data.txt", "r")) == NULL) {
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

