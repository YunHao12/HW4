#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node* next;
};

struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

void enqueue(struct Node** head, int data, int priority) {
    struct Node* newNode = createNode(data, priority);

    if (*head == NULL || priority < (*head)->priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int dequeue(struct Node** head) {
    if (*head == NULL) {
        printf("Priority queue is empty.\n");
        return -1;
    }

    int data = (*head)->data;
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return data;
}

int isEmpty(struct Node* head) {
    return head == NULL;
}

int isFull() {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if (temp == NULL)
        return 1;
    free(temp);
    return 0;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("Priority queue is empty.\n");
        return;
    }

    struct Node* current = head;
    printf("Priority queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int choice, data, priority;

    do {
        printf("\nPriority Queue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Is Empty\n");
        printf("4. Is Full\n");
        printf("5. Display\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data: ");
                scanf("%d", &data);
                printf("Enter the priority: ");
                scanf("%d", &priority);
                enqueue(&head, data, priority);
                break;
            case 2:
                data = dequeue(&head);
                if (data != -1)
                    printf("Dequeued element: %d\n", data);
                break;
            case 3:
                if (isEmpty(head))
                    printf("Priority queue is empty.\n");
                else
                    printf("Priority queue is not empty.\n");
                break;
            case 4:
                if (isFull())
                    printf("Priority queue is full.\n");
                else
                    printf("Priority queue is not full.\n");
                break;
            case 5:
                display(head);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid menu option.\n");
        }
    } while (choice != 0);

    // Free the memory
    freeQueue(head);

    return 0;
}
