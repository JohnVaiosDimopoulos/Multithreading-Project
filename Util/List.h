
#ifndef KOUVALAME_XATZO_LIST_H
#define KOUVALAME_XATZO_LIST_H

struct List_node{
  int item;
  struct List_node* next;
}typedef List_node;

struct List{
  List_node* head;
}typedef List;

void Insert_on_front(List *list, int item);
void Print_list(List *list);
void Free_list(List *list);


#endif //KOUVALAME_XATZO_LIST_H
