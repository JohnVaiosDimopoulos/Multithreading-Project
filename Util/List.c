#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int Is_empty(List* list){
  if(list->head==NULL)
    return 1;
  return 0;
}

List_node* Allocate_new_node(int item){
  List_node* temp = malloc(sizeof(List_node));
  temp->item=item;
  return temp;
}

void Insert_on_front(List *list, int item){

  List_node* new_node = Allocate_new_node(item);
  new_node->next=NULL;
  if(list->head==NULL)
    list->head=new_node;
  else{
    new_node->next=list->head;
    list->head=new_node;
  }

}

void Print_list(List *list){
  if(Is_empty(list))
    return;

  List_node* temp = list->head;
  while (temp!=NULL){
    printf("%d->",temp->item);
    temp=temp->next;
  }
  printf("\n");
}


