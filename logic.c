#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for each task in the to-do list
struct node {
    char task[100];          // Task description
    int status;              // 0 for pending, 1 for completed
    int date;                // Date in YYYYMMDD format
    struct node* link;       // Link to the next node
};

// Global pointer to head
struct node* head = NULL;

// Function to convert date string (in DD/MM/YYYY format) to an integer (YYYYMMDD)
int convertDate(char* dateStr) {
    int day, month, year;
    if (sscanf(dateStr, "%d/%d/%d", &day, &month, &year) != 3 || day < 1 || day > 31 || month < 1 || month > 12) {
        printf("Invalid date format or value! Please use DD/MM/YYYY.\n");
        return -1; // Error code for invalid date
    }
    return year * 10000 + month * 100 + day;
}

// Display all tasks
void display() {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }
    struct node* ptr = head;
    do {
        printf("Task: %s | Date: %08d | Status: %s\n", 
               ptr->task, ptr->date, 
               (ptr->status == 0) ? "Pending" : "Completed");
        ptr = ptr->link;
    } while (ptr != head);
}

// Add a task based on date
void InsertByDate(char* task, char* dateStr) {
    int date = convertDate(dateStr);
    if (date == -1) return;  // Abort if date is invalid

    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed! Unable to add task.\n");
        return;
    }

    strcpy(newNode->task, task);
    newNode->status = 0;  // Task is pending when added
    newNode->date = date;

    // If the list is empty, make the new task the head
    if (head == NULL) {
        head = newNode;
        head->link = head;
    } else {
        struct node* ptr = head;
        struct node* prev = NULL;

        // Find the correct position based on date
        do {
            if (newNode->date < ptr->date) break;
            prev = ptr;
            ptr = ptr->link;
        } while (ptr != head);

        // Insert the new node at the correct position
        if (prev == NULL) { 
            // Insert at head
            while (ptr->link != head) {
                ptr = ptr->link;
            }
            newNode->link = head;
            head = newNode;
            ptr->link = head;
        } else {
            // Insert in middle or end
            prev->link = newNode;
            newNode->link = ptr;
        }
    }

    printf("Task '%s' added successfully.\n", task);
}

// Mark a task as completed by task name
void markCompleted(char* task) {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }
    struct node* ptr = head;
    do {
        if (strcmp(ptr->task, task) == 0) {
            ptr->status = 1;  // Mark as completed
            printf("Task '%s' marked as completed.\n", task);
            return;
        }
        ptr = ptr->link;
    } while (ptr != head);
    printf("Task '%s' not found.\n", task);
}

// Delete a task by name
void deleteTask(char* task) {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }

    struct node *curr = head, *prev = NULL;

    do {
        if (strcmp(curr->task, task) == 0) {
            if (prev == NULL) {
                // Deleting head
                struct node* last = head;
                while (last->link != head) last = last->link;
                if (head == head->link) { 
                    // Only one node
                    free(head);
                    head = NULL;
                } else {
                    last->link = head->link;
                    free(head);
                    head = last->link;
                }
            } else {
                prev->link = curr->link;
                free(curr);
            }
            printf("Task '%s' deleted.\n", task);
            return;
        }
        prev = curr;
        curr = curr->link;
    } while (curr != head);

    printf("Task '%s' not found.\n", task);
}

// Search for a task by name
void searchTask(char* task) {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }

    struct node* ptr = head;
    do {
        if (strcmp(ptr->task, task) == 0) {
            printf("Task: %s | Date: %08d | Status: %s\n", 
                   ptr->task, ptr->date, 
                   (ptr->status == 0) ? "Pending" : "Completed");
            return;
        }
        ptr = ptr->link;
    } while (ptr != head);

    printf("Task '%s' not found.\n", task);
}

// Main function to handle menu
int main() {
    int choice;
    char task[100];
    char date[11];  // To store date in DD/MM/YYYY format

    while (1) {
        printf("\n--- To-Do List Menu ---\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete a Task\n");
        printf("5. Search for a Task\n");
        printf("6. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Enter a number.\n");
            while (getchar() != '\n');  // Clear buffer
            continue;
        }
        getchar();  // Consume leftover newline

        switch (choice) {
            case 1:
                printf("Enter the task: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;  // Remove newline

                printf("Enter the date (DD/MM/YYYY): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = 0;  // Remove newline

                InsertByDate(task, date);
                break;

            case 2:
                display();
                break;

            case 3:
                printf("Enter the task to mark as completed: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;  // Remove newline
                markCompleted(task);
                break;

            case 4:
                printf("Enter the task to delete: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;  // Remove newline
                deleteTask(task);
                break;

            case 5:
                printf("Enter the task to search: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;  // Remove newline
                searchTask(task);
                break;

            case 6:
                printf("Exiting. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
