#include <stdio.h>
#include "../Initialization/initialization_functions.h"
#include "../Global_structs/Global_Structs.h"

int main(int argc,char** argv) {

  Argumet_data data = Get_Arguments(argc,argv);
  Init_file_data file_data =Get_data_from_file();
  Initialize_mutexes(&mutexes_and_cond);
  Initialize_global_data(&global_data,file_data);


}