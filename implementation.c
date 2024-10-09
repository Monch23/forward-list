#include "flist.h"
#include <stdlib.h>

enum {
	SUCCESS,
	INV_PTR,
	SAM_DATA,
	INV_POS,
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
	this->head->value = other->head->value;
	Node *tmp = this->head;
	Node *otherTmp = other->head;
	
	while (otherTmp->next) {
		tmp->next = (Node*)malloc(sizeof(Node));
		tmp->next->value = otherTmp->next->value;
		tmp = tmp->next;
		otherTmp = otherTmp->next;
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

	if (this->head == NULL && pos == 0) {
		list_init_fill(this, 1, val);
		return SUCCESS;
	}
	if (!pos) {
		Node *saveHead = this->head;
		Node *newNode = (Node*)malloc(sizeof(Node));
		this->head = newNode;
		newNode->next = saveHead;
		return SUCCESS;
	}

	Node *tmp = this->head;
	
	while (--pos) {
		if (tmp->next == NULL && pos) {
			return INV_POS;
		}
		tmp = tmp->next;
	}

	Node *saveNext = tmp->next;
	tmp->next = (Node*)malloc(sizeof(Node));
	tmp->next->value = val;
	tmp = tmp->next;
	tmp->next = saveNext;

	return SUCCESS;
}

int list_erase(List *this, int val) {
	if (this == NULL) {
		return INV_PTR;
	}
	
	Node *prev = NULL;
	Node *nxt = this->head;
	
	while (nxt) {
		if (nxt->value == val) {
			if (prev == NULL) {
				nxt = nxt->next;
				free(this->head);
				this->head = nxt;
			} else {
				prev = nxt->next;
				free(nxt);
				nxt = prev->next;
			}
		} else {
			prev = nxt;
			nxt = nxt->next;
		}
	}

	return SUCCESS;
}


