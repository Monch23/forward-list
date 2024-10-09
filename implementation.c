#include "flist.h"
#include <stdlib.h>
#include <stdio.h>

/*typedef enum err{
	SUCCESS,
	INV_PTR,
    INV_DATA,
	SAM_DATA,
	INV_POS,
    INV_ELEM,
} errors;
*/
// destructors

int clear_list(List *this) {
    if (this == NULL) {
        return INV_PTR;
    }
    if (this->head == NULL) {
        return SUCCESS;
    }
    if (this->head->next == NULL) {
        list_pop_front(this);
        return SUCCESS;
    }

    Node *nxt = this->head->next;

    while (nxt) {
        free(this->head);
        this->head = nxt;
        nxt = nxt->next;
    }

    this->head = NULL;
    return SUCCESS;
}

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
	this->head->value = other->head->value;
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

int list_push_front(List *this, int val) {
    if (this == NULL) {
        return INV_PTR;
    }
    
    Node *saveHead = this->head;
    this->head = (Node*)malloc(sizeof(Node));
    this->head->value = val;
    this->head->next = saveHead;

    return SUCCESS;
}

int list_pop_front(List *this) {
    if (this == NULL) {
        return INV_PTR;
    }
    if (this->head == NULL) {
        return INV_DATA;
    }
    if (this->head->next == NULL) {
        free(this->head);
        this->head = NULL;
        return SUCCESS;
    }

    Node *tmp = this->head->next;
    free(this->head);
    this->head = tmp;
    tmp = NULL;
    
    return SUCCESS;
}

int list_insert(List *this, size_t pos, int val) {
	if (this == NULL) {
		return INV_PTR;
	}

	if (this->head == NULL && pos == 0) {
		this->head = (Node*)malloc(sizeof(Node));
        this->head->value = val;
		return SUCCESS;
	}
	if (!pos) {
		list_push_front(this, val);
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
				prev->next = nxt->next;
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

int find_in_list(const List* this, int val) {
    if (this == NULL) {
        return INV_PTR;
    }

    Node *find = this->head;
    int index = 0;

    while (find) {
        if (find->value == val) {
            printf("value finded in %d index \n", index);
            return SUCCESS;
        }
        find = find->next;
        ++index;
    }

    return INV_ELEM;
}

size_t list_size(const List *this) {
    if (this == NULL) {
        return INV_PTR;
    }
    if (this->head == NULL) {
        return 0;
    }

    size_t size = 0;
    Node *tmp = this->head;

    while (tmp) {
        ++size;
        tmp = tmp->next;
    }

    return size;
}

int print_list(const List *this) {
    if (this == NULL) {
        return INV_PTR;
    }
    if (this->head == NULL) {
        return INV_DATA;
    }

    Node *tmp = this->head;

    while (tmp) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    
    putchar(10);
    return SUCCESS;
}
