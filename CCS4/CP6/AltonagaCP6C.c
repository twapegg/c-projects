// Name: John Stanley T. Altonaga
// Date Created: 10/15/2023
// Date Finished: 10/16/2023
/* Description: This program is a BMI calculator implemented with a circular queue (arrays of structures).
The program can create a queue, enqueue, edit, dequeue, and display the queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

#define QUEUESIZE 5
#define TEXTSIZE 50

typedef struct person
{
    char firstName[TEXTSIZE];
    char lastName[TEXTSIZE];
    float weight;
    float height;
    float bmi;
    char category[TEXTSIZE];
} Person;

int menu(void);
void createQueue(Person queue[QUEUESIZE], int *head, int *tail, bool *isChecked);
void initQueue(Person queue[QUEUESIZE], int *head, int *tail);
bool emptyQueue(int head, int tail);
bool fullQueue(int head, int tail);
void enqueue(Person queue[QUEUESIZE], int *tail, Person data);
Person dequeue(Person queue[QUEUESIZE], int *head);
char *categoryBMI(float bmi);

void dataEntry(Person queue[QUEUESIZE], int *head, int *tail);
void dataDisplay(Person queue[QUEUESIZE], int *head, int *tail);
void dataEditByName(Person queue[QUEUESIZE], int *head, int *tail);
void dataDeleteByName(Person queue[QUEUESIZE], int *head, int *tail);

/*  function to display menu and get choice
    @returns (int) choice
*/
int main(void)
{
    Person queue[QUEUESIZE];
    int head;
    int tail;
    bool isChecked = false;

    int choice;

    do
    {
        choice = menu(); // display menu and get choice

        switch (choice)
        {
        case 1:
            createQueue(queue, &head, &tail, &isChecked);
            break;
        case 2:
            // check if queue is created
            if (isChecked == false)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            // check if queue is full
            if (fullQueue(head, tail))
            {
                printf("Queue is full. Press any key to continue.\n");
                getch();
                break;
            }
            // else, add element
            dataEntry(queue, &head, &tail);
            break;
        case 3:
            // check if queue is created
            if (isChecked == false)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            // else, edit element
            dataEditByName(queue, &head, &tail);
            break;
        case 4:
            // check if queue is created
            if (isChecked == false)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            // else, delete element
            dataDeleteByName(queue, &head, &tail);
            break;
        case 5:
            // check if queue is created
            if (isChecked == false)
            {
                printf("Queue is not created. Press any key to continue.\n");
                getch();
                break;
            }
            // else, display all elements
            dataDisplay(queue, &head, &tail);
            break;
        case 6:
        }
    } while (choice != 6);
    return 0;
}

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

void createQueue(Person queue[QUEUESIZE], int *head, int *tail, bool *isChecked)
{

    // check if queue is already created and has elements
    if (*isChecked == true && *head != *tail)
    {
        printf("Queue has existing elements. Do you want to clear the queue? (y/n): ");
        getch();

        char choice;
        do
        {
            scanf(" %c", &choice);
            choice = tolower(choice);

            if (choice == 'y')
            {
                *head = 0;
                *tail = 0;
                initQueue(queue, head, tail);
                printf("Queue has been cleared.\n");
                getch();
                return;
            }

            if (choice == 'n')
            {
                printf("Queue has been not cleared.\n");
                getch();
                return;
            }
        } while (choice != 'y' && choice != 'n');
    }

    // check if queue is already created
    if (*isChecked == true)
    {
        printf("Queue already created.\n");
        getch();
        return;
    }
    // else, create queue
    *head = 0;
    *tail = -1;
    *isChecked = true;
    initQueue(queue, head, tail);
    printf("Queue created.\n");
    getch();
}

void initQueue(Person queue[QUEUESIZE], int *head, int *tail)
{
    for (int i = 0; i < QUEUESIZE; i++)
    {
        strcpy(queue[i].firstName, "");
        strcpy(queue[i].lastName, "");
        queue[i].weight = 0;
        queue[i].height = 0;
        queue[i].bmi = 0;
        strcpy(queue[i].category, "");
    }
}

bool emptyQueue(int head, int tail)
{
    // if tail is -1 and head is 0, queue is empty
    return (tail == -1 && head == 0) ? true : false;
}

bool fullQueue(int head, int tail)
{
    // if tail is QUEUESIZE - 1 and head is 0, queue is full
    return (tail == QUEUESIZE - 1 && head == 0) ? true : false;
}

void enqueue(Person queue[QUEUESIZE], int *tail, Person data)
{
    int t = *tail;
    t++;
    queue[t] = data;
    *tail = t;
    return;
}

Person dequeue(Person queue[QUEUESIZE], int *head)
{
    int h = *head;
    Person data = queue[h];
    h++;
    *head = h;
    return data;
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
}

void dataEntry(Person queue[QUEUESIZE], int *head, int *tail)
{
    int h = *head;
    int t = *tail;

    Person data; // data holder

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];
    float tempWeight;
    float tempHeight;

    fflush(stdin); // clear input buffer
    system("cls");

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strlen(tempFirstName) - 1] = '\0'; // remove newline character
    strcpy(data.firstName, strupr(tempFirstName));

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strlen(tempLastName) - 1] = '\0'; // remove newline character
    strcpy(data.lastName, strupr(tempLastName));

    printf("Enter height (in cm): ");
    scanf("%f", &tempHeight);

    printf("Enter weight (in lbs): ");
    scanf("%f", &tempWeight);

    data.height = tempHeight / 100;                       // convert cm to m
    data.weight = tempWeight * 0.453592;                  // convert lbs to kg
    data.bmi = data.weight / (data.height * data.height); // calculate bmi
    strcpy(data.category, categoryBMI(data.bmi));         // calculate bmi category

    enqueue(queue, &t, data); // add data to queue
    *head = h;
    *tail = t;
    printf("Data added. Press any key to continue.\n");
    getch();
    return;
}

void dataEditByName(Person queue[QUEUESIZE], int *head, int *tail)
{
    int h = *head;
    int t = *tail;

    // check if queue is empty
    if (emptyQueue(h, t))
    {
        printf("Queue is empty. Press any key to continue.\n");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    system("cls");
    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strlen(tempFirstName) - 1] = '\0'; // remove newline character

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strlen(tempLastName) - 1] = '\0'; // remove newline character

    Person tempQueue[QUEUESIZE];
    int tempHead = 0;
    int tempTail = -1;
    bool isFound = false;

    // check if name exists
    while (h != t + 1)
    {
        Person temp = dequeue(queue, &h); // dequeue element
        if (stricmp(temp.firstName, tempFirstName) == 0 && stricmp(temp.lastName, tempLastName) == 0)
        {
            isFound = true;

            system("cls");
            printf("Record found! Displaying data...\n\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);

            char choice;
            do
            {
                printf("\nDo you want to edit this record? (y/n): ");
                scanf(" %c", &choice);
                choice = tolower(choice);

                // trap invalid input
                if (choice == 'y')
                {
                    printf("Enter new height (in cm): ");
                    scanf("%f", &temp.height);

                    printf("Enter new weight (in lbs): ");
                    scanf("%f", &temp.weight);

                    temp.height = temp.height / 100;                      // convert cm to m
                    temp.weight = temp.weight * 0.453592;                 // convert lbs to kg
                    temp.bmi = temp.weight / (temp.height * temp.height); // get bmi
                    strcpy(temp.category, categoryBMI(temp.bmi));

                    enqueue(queue, &t, temp); // enqueue element to temp queue
                    printf("Record has been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
                else if (choice == 'n')
                {
                    // enqueue element to temp queue
                    enqueue(queue, &t, temp);
                    printf("Record has not been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
                else
                {
                    printf("Invalid option. Please enter a valid option.\n");
                }
            } while (choice != 'y' && choice != 'n');
            break; // since data is found, break loop
        }
        // if data doesn't match, enqueue element to temp queue
        enqueue(tempQueue, &tempTail, temp);
    }

    // enqueue elements back to original queue
    while (tempHead != tempTail + 1)
    {
        Person temp = dequeue(tempQueue, &tempHead);
        enqueue(queue, &t, temp);
    }

    // if data is not found, display message
    if (isFound == false)
    {
        printf("Record not found. Press any key to continue.\n");
        getch();
    }

    return;
}

void dataDeleteByName(Person queue[QUEUESIZE], int *head, int *tail)
{
    int h = *head;
    int t = *tail;

    // check if queue is empty
    if (emptyQueue(h, t))
    {
        printf("Queue is empty. Press any key to continue.\n");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    system("cls");
    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strlen(tempFirstName) - 1] = '\0'; // remove newline character

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strlen(tempLastName) - 1] = '\0'; // remove newline character

    Person tempQueue[QUEUESIZE];
    int tempHead = 0;
    int tempTail = -1;
    bool isFound = false;

    // check if name exists
    while (h != t + 1)
    {
        Person temp = dequeue(queue, &h); // dequeue element

        if (stricmp(temp.firstName, tempFirstName) == 0 && stricmp(temp.lastName, tempLastName) == 0)
        {
            isFound = true;
            system("cls");
            printf("Record found! Displaying data...\n\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);

            char choice;
            do
            {
                printf("\nDo you want to delete this record? (y/n): ");
                scanf(" %c", &choice);
                choice = tolower(choice);

                // trap invalid input
                if (choice == 'y')
                {
                    printf("Record has been deleted. Press any key to continue.\n");
                    getch();
                    break;
                }
                else if (choice == 'n')
                {
                    // enqueue element to temp queue
                    enqueue(queue, &t, temp);
                    printf("Record has not been edited. Press any key to continue.\n");
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
            // if data doesn't match, enqueue element to temp queue
            enqueue(tempQueue, &tempTail, temp);
        }
    }

    // reset head and tail
    h = 0;
    t = -1;

    // enqueue elements back to original queue
    while (tempHead != tempTail + 1)
    {
        Person temp = dequeue(tempQueue, &tempHead);
        enqueue(queue, &t, temp);
    }

    // if data is not found, display message
    if (isFound == false)
    {
        printf("Record not found. Press any key to continue.\n");
        getch();
    }

    *head = h;
    *tail = t;
    return;
}

void dataDisplay(Person queue[QUEUESIZE], int *head, int *tail)
{
    int h = *head;
    int t = *tail;

    // check if queue is empty
    if (emptyQueue(h, t))
    {
        printf("Queue is empty. Press any key to continue.\n");
        getch();
        return;
    }

    // else, display all elements
    Person tempQueue[QUEUESIZE];
    int tempHead = 0;
    int tempTail = -1;

    system("cls");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    while (h != t + 1)
    {
        Person temp = dequeue(queue, &h); // dequeue element
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp.firstName, temp.lastName, temp.height, temp.weight, temp.bmi, temp.category);
        enqueue(tempQueue, &tempTail, temp); // enqueue element to temp queue
    }

    // reset head and tail
    h = 0;
    t = -1;

    // enqueue elements back to original queue
    while (tempHead != tempTail + 1)
    {
        Person temp = dequeue(tempQueue, &tempHead);
        enqueue(queue, &t, temp);
    }

    printf("\nPress any key to continue.\n");
    getch();
    return;
}