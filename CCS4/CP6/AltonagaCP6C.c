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
            // if (fullQueue(head, tail))
            // {
            //     printf("Queue is full. Press any key to continue.\n");
            //     getch();
            //     break;
            // }
            // else, add element
            dataEntry(queue, &head, &tail);
            break;
        case 3:
        case 4:
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
        printf("[1] Create Stack\n");
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
    if ((head == 0 && tail == QUEUESIZE - 1) ||
        ((tail + 1) % QUEUESIZE == head))
    {
        return true;
    }
    else
    {
        // queue is not full
        return false;
    }
}

void enqueue(Person queue[QUEUESIZE], int *tail, Person data)
{
    // if tail is at the end of the array, set tail to 0
    if (*tail == QUEUESIZE - 1)
    {
        *tail = 0;
        queue[*tail] = data;
        return;
    }
    // else, increment tail
    *tail = (*tail + 1) % QUEUESIZE;
    queue[*tail] = data;
    return;
}

Person dequeue(Person queue[QUEUESIZE], int *head)
{
    // data holder
    Person data = queue[*head];
    *head = (*head + 1) % QUEUESIZE; // increment head
    return data;                     // return data
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
    int tempTail = 0;

    system("cls");

    printf("%d %d", h, t);
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    do
    {
        Person temp = dequeue(queue, &h);
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp.firstName, temp.lastName, temp.height, temp.weight, temp.bmi, temp.category);
        enqueue(tempQueue, &tempTail, temp);
    } while (h != t);

    // enqueue elements back to original queue
    do
    {

        Person temp = dequeue(tempQueue, &tempHead);
        enqueue(queue, &t, temp);
    } while (tempHead != tempTail);

    printf("\nPress any key to continue.\n");
    getch();
    return;
}