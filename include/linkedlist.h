#if !defined(__LINKED_LIST_H__)
#define __LINKED_LIST_H__

/*메직 코드 상수로 선언한다*/
#define LIST_MAGIC_CODE        0x43218765

#define ERR_LIST_OK              0     /*성공시 상수값*/
#define ERR_LIST_CREATE        -3000 /*메모리 할당시 오류 코드 */
#define ERR_LIST_MAGICCODE     -3001 /*구조체 포인터가 가리키는 메모리의 선두에 존재해야 하는 매직 코드가 없을 때 발생하는 오류 코드 */
#define ERR_LIST_POSITION      -3002 /*배열의 범위를 벗어났을 때 발생하는 오류 코드 */

typedef void* LPDATA;


typedef struct Node{
    LPDATA data;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct LinkedList{
    int magicCode;
    int size;
    Node *head;
    Node *tail;
}LinkedList;

int create_linked_list(LinkedList* list);
LinkedList* create_linked_list_ptr();

int list_push_front(LinkedList* list, LPDATA data);
int list_push_back(LinkedList* list, LPDATA data);
int list_insert(LinkedList* list, LPDATA data, int nPos);


int list_pop_front(LinkedList* list);
int list_pop_back(LinkedList* list);
int list_remove(LinkedList* list, int nPos);


int list_size(LinkedList* list);
int list_get_at(LinkedList* list, int nPos, LPDATA* lpValue);
int list_set_at(LinkedList* list, int nPos, const LPDATA lpValue);

int list_clear(LinkedList* list);


#endif // __LINKED_LIST_H__
