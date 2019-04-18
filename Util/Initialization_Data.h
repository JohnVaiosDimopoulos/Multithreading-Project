#ifndef KOUVALAME_XATZO_INITIALIZATION_DATA_H
#define KOUVALAME_XATZO_INITIALIZATION_DATA_H

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


#endif //KOUVALAME_XATZO_INITIALIZATION_DATA_H
