
#ifndef KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H
#define KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H




/*forward declarations of data in Global_Structs.h*/
struct Mutexes_and_cond;
struct Global_data;
struct Seat;
enum status;

/*forward declare from Initialization Data*/
struct Argument_data;
struct Init_file_data;


struct Argument_data Get_Arguments(int argc,char** argv);
struct Init_file_data Get_data_from_file();
void Initialize_mutexes(struct Mutexes_and_cond* mutexes_and_cond);
void Initialize_global_data(struct Global_data* global_data,struct Init_file_data file_data);


#endif //KOUVALAME_XATZO_INITIALIZATION_FUNCTIONS_H
