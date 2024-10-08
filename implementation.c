#include "flist.h"
#include <stdlib.h>

enum {
	SUCCESS,
	INV_PTR,
} errors;

int list_init(List *this) {
	if (this == NULL) {
		return INV_PTR;
	}

	this->head = NULL;
	return SUCCESS;
}

int list_init_size(List *this, size_t size) {
	if (this == NULL) {
		return INV_PTR;
	}

	this->head = (Node*)calloc(1, sizeof(Node));
	
	for (int i = 1; i < size; ++i) {
		this->head->next =
	}

	return SUCCESS;
}


