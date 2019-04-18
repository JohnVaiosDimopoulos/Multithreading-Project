
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


/*forward declarations of data in Global_Structs.h*/
struct Mutexes_and_cond;
struct Global_data;
struct Seat;
enum status;

Argumet_data Get_Arguments(int argc,char** argv);
Init_file_data Get_data_from_file();
void Initialize_mutexes(struct Mutexes_and_cond* mutexes_and_cond);
void Initialize_global_data(struct Global_data* global_data,Init_file_data file_data);



#endif //KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H
