#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DATA {
    int id;
    char depcity[50];
    char arrcity[50];
    char time[6];
    int domestic;
    int runway;
    struct DATA *next;
} DATA;

DATA *createData(int id, char *depcity, char *arrcity, char *time, int domestic, int runway) {
    DATA *newData = (DATA*)malloc(sizeof(DATA));
    newData->id = id;
    strcpy(newData->depcity, depcity);
    strcpy(newData->arrcity, arrcity);
    strcpy(newData->time, time);
    newData->domestic = domestic;
    newData->runway = runway;
    newData->next = NULL;
    return newData;
}

void sortData(DATA **head, DATA *newData) {
    if (*head == NULL || (*head)->id > newData->id) {
        newData->next = *head;
        *head = newData;
    } 
	else {
        DATA *current = *head;
        while (current->next != NULL && current->next->id < newData->id) {
            current = current->next;
        }
        newData->next = current->next;
        current->next = newData;
    }
}

void printDataList(DATA *head) {
    DATA *current = head;
    while (current != NULL) {
        printf("%d %s %s %s %d %d\n", current->id, current->depcity, current->arrcity, current->time, current->domestic, current->runway);
        current = current->next;
    }
}

void createFiles(DATA *head) {
    DATA *current = head;
    while (current != NULL) {
        char filename[20];
        sprintf(filename, "pist%d.txt", current->runway);
        FILE *file = fopen(filename, "a");
        if (file != NULL) {
            fprintf(file, "%d %s %s %s %d %d\n", current->id, current->depcity, current->arrcity, current->time, current->domestic, current->runway);
            fclose(file);
        } else {
            printf("Error opening file %s\n", filename);
        }
        current = current->next;
    }
}

int main() {
    DATA *head = NULL;

    FILE *file = fopen("ucusBilgi.txt", "r");
    if (file == NULL) {
        printf("Error opening input file.\n");
        return 0;
    }
    
    int id, domestic, runway;
    char depcity[50], arrcity[50], time[6];
    
    while (fscanf(file, "%d %s %s %s %d %d", &id, depcity, arrcity, time, &domestic, &runway) != EOF) {
        DATA *newData = createData(id, depcity, arrcity, time, domestic, runway);
        sortData(&head, newData);
    }
    
    fclose(file);
    
    printDataList(head);
    createFiles(head);
    
    DATA *current = head;
    while (current != NULL) {
        DATA *next = current->next;
        free(current);
        current = next;
    }
    
    return 0;
}

