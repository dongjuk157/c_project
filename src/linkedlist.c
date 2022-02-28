#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int create_linked_list(LinkedList* list){
    list -> size = 0;
    list -> head = NULL;
    list -> tail = NULL;
    list->magicCode = LIST_MAGIC_CODE;
    return ERR_LIST_OK;
}
LinkedList* create_linked_list_ptr(){
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    create_linked_list(list);
    return list;
}


int list_push_front(LinkedList* list, LPDATA data){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->prev = NULL;
    if(list->head == NULL){
        temp->next = NULL;
        list->tail = list->head = temp;
    }
    else{
        list->head->prev = temp;
        temp->next = list->head;
        list->head = temp;
    }
    list->size += 1;
    return ERR_LIST_OK;
}

int list_push_back(LinkedList* list, LPDATA data){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    if(list->head == NULL){
        temp->prev = NULL;
        list->tail = list->head = temp;
    }
    else{
        list->tail->next = temp;
        temp->prev = list->tail;
        list->tail = temp;
    }
    list->size += 1;
    return ERR_LIST_OK;
}

int list_pop_front(LinkedList* list){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    if(list->size == 0){
        return ERR_LIST_POSITION;
    }
    Node* temp = list->head;
    list->size -= 1;
    if(list->head == list->tail){
        free(temp);
        list->head = list->tail = NULL;
    }
    else{
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
    }
   
    return ERR_LIST_OK;
}
int list_pop_back(LinkedList* list){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    if(list->size == 0){
        return ERR_LIST_POSITION;
    }
    Node* temp = list->tail;
    list->size -= 1;
    if(list->head == list->tail){
        free(temp);
        list->head = list->tail = NULL;
    }
    else{
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
    }
    
    return ERR_LIST_OK;
}

int list_size(LinkedList* list){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    return list->size;
}

int list_get_at(LinkedList* list, int nPos, LPDATA* lpValue){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    if(nPos < 0 || nPos > list_size(list)){
        return ERR_LIST_POSITION;
    }

    Node *temp = list -> head;
    for (int i = 0; i < nPos; i++){
        temp = temp->next;
    }
    *lpValue = (temp->data);
    return ERR_LIST_OK;
}

int list_set_at(LinkedList* list, int nPos, const LPDATA lpValue){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    if(nPos < 0 || nPos > list_size(list)){
        return ERR_LIST_POSITION;
    }

    Node *temp = list -> head;
    for (int i = 0; i < nPos; i++)
    {
        temp = temp -> next;
    }
    temp ->data = lpValue;

    return ERR_LIST_OK;
}

int list_clear(LinkedList* list){
    if (LIST_MAGIC_CODE != list->magicCode) {
        //magic 코드가 오류 코드 리턴합니다
        return ERR_LIST_MAGICCODE;
    }
    Node* temp = list->head;
    Node* next;
    while(temp){
        next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = list->tail = NULL;
    return ERR_LIST_OK;
}

