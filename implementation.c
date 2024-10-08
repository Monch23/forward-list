#include "flist.h"
#include <stdlib.h>

enum {
	SUCCESS,
	INV_PTR,
	SAM_DATA,
} errors;

// destructor

int destroy_list(List *this) {
	if (this == NULL) {
		return INV_PTR;
	}
	if (this->head == NULL) {
		return SUCCESS;
	}

	Node *tmp = this->head->next;
	
	while (tmp) {
		free(this->head);
		this->head = tmp;
		tmp = tmp->next;
	}

	return SUCCESS;
}

// constructors

int list_init(List *this) {
	if (this == NULL) {
		return INV_PTR;
	}

	this->head = NULL;
	return SUCCESS;
}

int list_init_fill(List *this, size_t size, int val) {
	if (this == NULL) {
		return INV_PTR;
	}

	this->head = (Node*)malloc(sizeof(Node));
	this->head->value = val;
	Node *tmp = this->head;
	
	while (--size) {
		tmp->next = (Node*)malloc(sizeof(Node));
		tmp->next->value = val;
		tmp = tmp->next;
	}

	tmp->next = NULL;
	
	return SUCCESS;
}

int list_copy(List *this, const List *other) {
	if (this == NULL || other == NULL) {
		return INV_PTR;
	}
	if (this == other) {
		return SAM_DATA;
	}

	this->head = (Node*)malloc(sizeof(Node));
	this->head->value = val;
	Node *tmp = this->head;
	Node *tmp2 = other->head;
	
	while (tmp2->next) {
		tmp->next = (Node*)malloc(sizeof(Node));
		tmp->next->value = tmp2->next->value;
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}

	tmp->next = NULL;

	return SUCCESS;
}

int list_assign(List *this, const List *other) {
	if (this == NULL || other == NULL) {
		return INV_PTR;
	}
	if (this == other) {
		return SAM_DATA;
	}

	if (this->head != NULL) {
		destroy_list(this);
	}
	this->head = (Node*)malloc(sizeof(Node));
	this->head->value = val;
	Node *tmp = this->head;
	Node *tmp2 = other->head;

	while (tmp2->next) {
		tmp->next = (Node*)malloc(sizeof(Node));
		tmp->next->value = tmp2->next->value;
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}

	return SUCCESS;
}

// modifiers

int list_insert(List *this, size_t pos, int val) {
	if (this == NULL) {
		return INV_PTR;
	}

	if (this->head == NULL) {
		this->head = (Node*)malloc(sizeof(Node));
		Node *tmp = this->head;
		
		while (--pos) {
			tmp = tmp->next;
		}
		tmp->next
		tmp->next->value = val;
		return SUCCESS;
	}

	Node *saveHead = this->head;
	
	while (count--) {
		
	}
}




