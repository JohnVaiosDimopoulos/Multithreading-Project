
#ifndef KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H
#define KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H


struct{
  const int clients_num;
  const int rand_seed;
}typedef Argumet_data;

struct {
  const int Seats_number;
  const int Telephones_number;
  const int S_low;
  const int S_high;
  const int wait_low;
  const int wait_high;
  const int success_prob;
  const int seat_cost;

}typedef Init_file_data;

void check_Arguments_number(int argc);
Argumet_data Get_Arguments(int argc,char** argv);
Init_file_data Get_data_from_file();




#endif //KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H
