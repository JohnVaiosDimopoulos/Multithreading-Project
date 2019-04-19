#include <stdio.h>
#include <stdlib.h>
#include "../Util/initialization_functions.h"
#include "../Util/Statistics.h"
#include "../Global_structs/Global_Structs.h"
#include "../Util/Initialization_Data.h"
#include "../Pthread_functions/Pthread_functions.h"




int main(int argc,char** argv) {

  //Initialization phase
  Argument_data data = Get_Arguments(argc,argv);
  srand(data.rand_seed);
  Init_file_data file_data =Get_data_from_file();
  Initialize_mutexes(&mutexes_and_cond);
  Initialize_global_data(&global_data,file_data);

  //Main pahse
  pthread_t clients[data.clients_num];
  Start_Clients(clients,data.clients_num,file_data);
  Wait_for_clients_to_finish(clients,data.clients_num);

  //Ending phsase
  Print_Stats(data,file_data);
  Destroy_Mutexes_and_cond();
}