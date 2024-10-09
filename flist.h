#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stddef.h>
typedef enum err{
	SUCCESS,
	INV_PTR,
    INV_DATA,
	SAM_DATA,
	INV_POS,
    INV_ELEM,
} errors;


typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct ForwardList {
    Node* head;
} List;

// ctor
int list_init(List* this);
int list_init_size(List* this, size_t size);
int list_init_fill(List* this, size_t size, int val);
int list_copy(List* this, const List* other);
int list_assign(List* this, const List* other);

// dtor
int destroy_list(List* this);

// modifiers
int list_insert(List* this, size_t count, int value);
int list_erase(List* this, int value);
int list_push_front(List* this, int value);
int list_pop_front(List* this);
int find_in_list(const List* this, int value);
int list_reverse(List* this);
int clear_list(List* this);
size_t list_size(const List* this);

// additional functionality
int list_sort(List* this);
int list_unique(List* this); //for sorted list
int list_merge(List *this, List *other); //for sorted list

int print_list(const List* this);

#endif // FORWARD_LIST_H
