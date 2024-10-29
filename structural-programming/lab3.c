#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int v1;
    int v2;
    struct Node* next;
} Node;

void printList(Node* n) {
    while (n->next != NULL) {
        printf("v1=%d, v2=%d -> ", n->v1, n->v2);
        n = n->next;
    }
    printf("v1=%d, v2=%d \n", n->v1, n->v2);
}

void insert(struct Node** head_ref, int v1, int v2) {

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->v1 = v1;
    new_node->v2 = v2;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    }
	else{
		Node* tmp = *head_ref;
   		while (tmp->next != NULL) {
    	    tmp = tmp->next;
    	}

    	tmp->next = new_node;
	}
    
}

int compare_by_v1(Node* Node1, Node* Node2) {
    
	if(Node1->v1 == Node2->v1){
		return 1;
	}
	else{
		return 0;
	}
	
}

int compare_by_v2(Node* Node1, Node* Node2) {
    if(Node1->v2 == Node2->v2){
		return 1;
	}
	else{
		return 0;
	}
}

Node* intersection(Node* start1, Node* start2, int (*reduce_f)(Node*, Node*)) {
    Node* result = NULL; 
    Node* tmp = start2;

    while (start1 != NULL) {
        while (start2 != NULL) {
            if ((*reduce_f)(start1, start2)) { 
                insert(&result, start1->v1, start1->v2);
            }
            start2 = start2->next;
        }
        start2 = tmp; 
        start1 = start1->next;
    }

    return result;
}




int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    //list1'in sonuna ekler
    insert(&list1, 1, 10);
    insert(&list1, 2, 20);
    insert(&list1, 3, 5);

    //list2'nin sonuna ekler
    insert(&list2, 2, 5);
    insert(&list2, 1, 25);
    insert(&list2, 4, 20);

	//linked listleri yazdirma
    printf("Linked list 1: ");
    printList(list1);

    printf("Linked list 2: ");
    printList(list2);

	//karsilastirma sonucunu yazdirma
    Node* result_v1 = intersection(list1, list2, compare_by_v1);
    printf("v1'e gore karsilastirma sonucu: ");
    printList(result_v1);


    Node* result_v2 = intersection(list1, list2, compare_by_v2);
    printf("v2'ye gore karsilastirma sonucu: ");
    printList(result_v2);

    return 0;
}

