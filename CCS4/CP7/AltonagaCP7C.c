// Name: John Stanley T. Altonaga
// Date Created: 10/9/2023
// Date Finished: 11/9/2023
/* Description: This program is a BMI calculator implemented with queues (singly-linked list).
It can create a queue, add elements (at tail) to the queue, edit elements, delete elements, and display all elements in the queue. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

#define TEXTSIZE 50

typedef struct person *node;
struct person
{
    char firstName[TEXTSIZE];
    char lastName[TEXTSIZE];
    float weight;
    float height;
    float bmi;
    char category[TEXTSIZE];
    node next;
} Person;

void createQueue(node *queue, node *front, node *rear, bool *isChecked);
void enqueue(node *queue, node *front, node *rear, node data);
node dequeue(node *queue, node *front);
bool emptyQueue(node *queue);

int menu(void);
char *categoryBMI(float bmi);

void dataEntry(node *queue, node *front, node *rear);
void dataEditByName(node *queue, node *front, node *rear);
void dataDeleteByName(node *queue, node *front, node *rear);
void dataDisplay(node *queue, node *front, node *rear);

int main(void)
{
    node queue = NULL;
    node front = NULL;
    node rear = NULL;
    bool isChecked = false;

    int choice;
    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            createQueue(&queue, &front, &rear, &isChecked);
            break;
        case 2:
            // if queue is not created, display message
            if (!isChecked)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataEntry(&queue, &front, &rear);
            break;
        case 3:
            // if queue is not created, display message
            if (!isChecked)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataEditByName(&queue, &front, &rear);
            break;
        case 4:
            // if queue is not created, display message
            if (!isChecked)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataDeleteByName(&queue, &front, &rear);
            break;
        case 5:
            // if queue is not created, display message
            if (!isChecked)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataDisplay(&queue, &front, &rear);
            break;
        case 6:
            printf("Exiting the program...\n");
        }
    } while (choice != 6);

    return 0;
}

/*  function to display menu and get choice
    @returns (int) choice
*/
int menu(void)
{
    int choice;
    do
    {
        system("cls");
        printf("BMI Calculator\n");
        printf("[1] Create Queue\n");
        printf("[2] Add element\n");
        printf("[3] Edit element\n");
        printf("[4] Delete element\n");
        printf("[5] Display all elements\n");
        printf("[6] Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 6)
        {
            printf("Invalid option. Please enter a valid option.\n");
            getch();
        }
    } while (choice < 1 || choice > 6);
    return choice;
}

/*  function to create queue
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
    @param (bool *) isChecked
*/
void createQueue(node *queue, node *front, node *rear, bool *isChecked)
{
    // check if queue is already created and has existing elements
    if (*isChecked && !emptyQueue(queue))
    {
        printf("Queue has existing elements. Do you want to clear the queue? (y/n): ");

        char choice;
        do
        {
            scanf(" %c", &choice);
            choice = tolower(choice);
            if (choice != 'y' && choice != 'n')
            {
                printf("Invalid option. Please enter a valid option.\n");
            }
            if (choice == 'y')
            {
                // free all elements
                while (!emptyQueue(queue))
                {
                    node temp = dequeue(queue, front);
                    free(temp);
                }

                // reset queue
                *queue = NULL;
                *front = NULL;
                *rear = NULL;

                printf("Queue has been cleared. Press any key to continue.\n");
                getch();
                return;
            }
            if (choice == 'n')
            {
                printf("Queue has not been cleared. Press any key to continue.\n");
                getch();
                return;
            }
        } while (choice != 'y' && choice != 'n');
    }

    // check if queue is already created
    if (*isChecked)
    {
        printf("Queue is already created. Press any key to continue.\n");
        getch();
        return;
    }

    // else, initialize queue
    *queue = NULL;
    *front = NULL;
    *rear = NULL;
    *isChecked = true;
    printf("Queue has been created. Press any key to continue.\n");
    getch();
    return;
}

/*  function to enqueue element to queue
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
    @param (node) data
*/
void enqueue(node *queue, node *front, node *rear, node data)
{
    // if empty, add at head
    if (emptyQueue(queue))
    {
        *front = data;
        (*front)->next = NULL;
        *queue = *front;
        *rear = data;
        return;
    }
    // else, add at tail
    (*rear)->next = data;
    *rear = data;
    (*rear)->next = NULL;
    return;
}

/*  function to dequeue element from queue
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
    @returns (node) temp
*/
node dequeue(node *queue, node *front)
{
    node temp = *front;
    *front = (*front)->next;
    *queue = *front;
    return temp;
}

/*  function to check if queue is empty
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
    @returns (bool) isEmpty
*/
bool emptyQueue(node *queue)
{
    // if front is NULL, return true, else return false
    return *queue == NULL ? true : false;
}

/*  function to add element to queue (at tail)
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
*/
void dataEntry(node *queue, node *front, node *rear)
{
    node temp = malloc(sizeof(Person));

    // if malloc fails, exit program
    if (temp == NULL)
    {
        printf("Malloc failed. Exiting program...\n");
        exit(1);
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    system("cls");
    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strcspn(tempFirstName, "\n")] = '\0'; // remove newline character
    strcpy(temp->firstName, tempFirstName);

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strcspn(tempLastName, "\n")] = '\0'; // remove newline character
    strcpy(temp->lastName, tempLastName);

    printf("Enter height (in cm): ");
    scanf("%f", &temp->height);

    printf("Enter weight (in lbs): ");
    scanf("%f", &temp->weight);

    temp->height /= 100;                                      // convert cm to m
    temp->weight *= 0.453592;                                 // convert lbs to kg
    temp->bmi = temp->weight / (temp->height * temp->height); // calculate bmi
    strcpy(temp->category, categoryBMI(temp->bmi));           // get category

    // add element to queue
    enqueue(queue, front, rear, temp);

    printf("\nData has been added. Press any key to continue.\n");
    getch();
    return;
}

/* function to get bmi category
    @param (float) bmi
    @returns (string) category
 */
char *categoryBMI(float bmi)
{
    if (bmi < 18.5)
    {
        return "Underweight";
    }
    else if (bmi >= 18.5 && bmi <= 24.9)
    {
        return "Normal";
    }
    else if (bmi >= 25 && bmi <= 29.9)
    {
        return "Overweight";
    }
    else if (bmi >= 30)
    {
        return "Obese";
    }
    else
    {
        return "Unknown";
    }
}

/*  function to edit an element in queue
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
*/
void dataEditByName(node *queue, node *front, node *rear)
{
    // check if queue is empty
    if (emptyQueue(queue))
    {
        printf("Queue is empty. Press any key to continue.\n");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    fflush(stdin); // clear input buffer
    system("cls");

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strcspn(tempFirstName, "\n")] = '\0'; // remove newline character

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strcspn(tempLastName, "\n")] = '\0'; // remove newline character

    node f = *front; // temp node to hold front
    node tempQueue = NULL;
    node tempFront = NULL;
    node tempRear = NULL;
    bool isFound = false; // flag to check if data is found

    while (f != NULL)
    {
        node temp = dequeue(queue, &f);
        if (stricmp(temp->firstName, tempFirstName) == 0 && stricmp(temp->lastName, tempLastName) == 0)
        {
            isFound = true;
            // display element
            system("cls");
            printf("Record found. Displaying record...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

            char choice;
            do
            {
                printf("\nDo you want to edit this record? (y/n): ");
                scanf(" %c", &choice);
                choice = tolower(choice);
                if (choice == 'y')
                {
                    // get new data
                    printf("\nEnter new height (in cm): ");
                    scanf("%f", &temp->height);

                    printf("Enter new weight (in lbs): ");
                    scanf("%f", &temp->weight);

                    temp->height /= 100;                                      // convert cm to m
                    temp->weight *= 0.453592;                                 // convert lbs to kg
                    temp->bmi = temp->weight / (temp->height * temp->height); // calculate bmi
                    strcpy(temp->category, categoryBMI(temp->bmi));           // get category

                    // enqueue element to temp queue
                    enqueue(&tempQueue, &tempFront, &tempRear, temp);
                    printf("\nData has been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
                if (choice == 'n')
                {
                    // enqueue element to temp queue
                    enqueue(&tempQueue, &tempFront, &tempRear, temp);
                    printf("\nData has not been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
                else
                {
                    printf("Invalid option. Please enter a valid option.\n");
                }
            } while (choice != 'y' && choice != 'n');
        }
        else
        {
            enqueue(&tempQueue, &tempFront, &tempRear, temp);
        }
    }

    // enqueue elements back to original queue
    while (tempQueue != NULL)
    {
        node temp = dequeue(&tempQueue, &tempFront);
        enqueue(queue, &f, rear, temp);
    }

    // if data is not found, display message
    if (!isFound)
    {
        printf("\nData not found. Press any key to continue.\n");
        getch();
        return;
    }

    *front = *queue = f; // update front and queue
    return;
}

/*  function to delete an element in queue
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
*/
void dataDeleteByName(node *queue, node *front, node *rear)
{
    // check if queue is empty
    if (emptyQueue(queue))
    {
        printf("Queue is empty. Press any key to continue.\n");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    fflush(stdin); // clear input buffer
    system("cls");

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strcspn(tempFirstName, "\n")] = '\0'; // remove newline character

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strcspn(tempLastName, "\n")] = '\0'; // remove newline character

    node f = *front; // temp node to hold front
    node tempQueue = NULL;
    node tempFront = NULL;
    node tempRear = NULL;
    bool isFound = false; // flag to check if data is found

    while (f != NULL)
    {
        node temp = dequeue(queue, &f);
        if (stricmp(temp->firstName, tempFirstName) == 0 && stricmp(temp->lastName, tempLastName) == 0)
        {
            isFound = true;
            // display element
            system("cls");
            printf("Record found. Displaying record...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

            char choice;

            do
            {
                printf("\nDo you want to delete this record? (y/n): ");
                scanf(" %c", &choice);
                choice = tolower(choice);
                if (choice == 'y')
                {
                    // free element
                    free(temp);
                    printf("\nData has been deleted. Press any key to continue.\n");
                    getch();
                    break;
                }
                if (choice == 'n')
                {
                    // enqueue element to temp queue
                    enqueue(&tempQueue, &tempFront, &tempRear, temp);
                    printf("\nData has not been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
                else
                {
                    printf("Invalid option. Please enter a valid option.\n");
                }
            } while (choice != 'y' && choice != 'n');
        }
        else
        {
            enqueue(&tempQueue, &tempFront, &tempRear, temp);
        }
    }

    // enqueue elements back to original queue
    while (tempQueue != NULL)
    {
        node temp = dequeue(&tempQueue, &tempFront);
        enqueue(queue, &f, rear, temp);
    }

    // if data is not found, display message
    if (!isFound)
    {
        printf("\nData not found. Press any key to continue.\n");
        getch();
        return;
    }

    *front = *queue = f; // update front and queue
    return;
}

/*  function to display all elements in queue
    @param (node *) queue
    @param (node *) front
    @param (node *) rear
*/
void dataDisplay(node *queue, node *front, node *rear)
{
    // check if queue is empty
    if (emptyQueue(queue))
    {
        printf("Queue is empty. Press any key to continue.\n");
        getch();
        return;
    }

    // else, display all elements
    node f = *front; // temp node to hold front
    node tempQueue = NULL;
    node tempFront = NULL;
    node tempRear = NULL;

    system("cls");
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    while (f != NULL)
    {
        node temp = dequeue(queue, &f); // dequeue element
        // display element
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

        enqueue(&tempQueue, &tempFront, &tempRear, temp);
    }

    // enqueue elements back to original queue
    while (tempQueue != NULL)
    {
        node temp = dequeue(&tempQueue, &tempFront);
        enqueue(queue, front, rear, temp);
    }

    printf("\nPress any key to continue.\n");
    getch();
    return;
}