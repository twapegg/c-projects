// Name: John Stanley T. Altonaga
// Date Created: 9/4/2023
// Date Finished: 9/4/2023
// Description: This program is a BMI calculator implemented with a singly-linked list that can store up to 10 records. It can display all records and display records by name.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct person *node;
struct person
{
    char firstName[50];
    char lastName[50];
    float weight;
    float height;
    float bmi;
    char category[15];
    node next;
} Person;

char menu(void);
int dataEntry(node *head, int count);
char *categoryBMI(float bmi);
void dataDisplay(node *head);
void dataDisplayByName(node *head);

int main(void)
{
    node head = NULL;
    int count = 0;

    char choice;
    do
    {
        choice = menu(); // display menu and get choice

        switch (choice)
        {
        case 'a':
            count = dataEntry(&head, count);
            puts("Data entry successful. Press any key to continue.");
            getch();
            break;
        case 'b':
            if (count == 0) // check if there is data to display
            {
                puts("No data to display. Press any key to continue.");
                getch();
                break;
            }
            dataDisplay(&head);
            puts("\nPress any key to continue.");
            getch();
            break;

        case 'c':
            if (count == 0) // check if there is data to display
            {
                puts("No data to display. Press any key to continue.");
                getch();
                break;
            }
            dataDisplayByName(&head);
            puts("\nPress any key to continue.");
            getch();
            break;
        }
    } while (choice != 'd');

    return 0;
}

// function to display menu
char menu(void)
{
    char choice;
    do
    {
        system("cls");
        printf("BMI Calculator\n");
        printf("a. Enter data\n");
        printf("b. Retrieve all data\n");
        printf("c. Retrieve data by name\n");
        printf("d. Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        choice = tolower(choice); // convert to lowercase

        // trap invalid input
        if (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
        {
            printf("Invalid option. Please enter a valid option.\n");
            getch();
        }
    } while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd');

    return choice;
}

// function to add a node and input data at the end of the list
int dataEntry(node *head, int count)
{
    // Create a new node
    node newNode = (node)malloc(sizeof(Person));

    // check if memory allocation failed
    if (newNode == NULL)
    {
        printf("Memory allocation failed. Exiting program.\n");
        exit(1);
    }

    node tail = *head; // tail pointer
    int flag;          // flag to check if name already exists

    fflush(stdin); // clear input buffer

    // ask for data
    do
    {
        flag = 0;
        system("cls"); // clear screen

        printf("Enter first name: ");
        gets(newNode->firstName);
        strcpy(newNode->firstName, strupr(newNode->firstName));

        printf("Enter last name: ");
        gets(newNode->lastName);
        strcpy(newNode->lastName, strupr(newNode->lastName));

        // check if name already exists
        node temp = *head;
        while (temp != NULL)
        {
            if (strcmp(newNode->firstName, temp->firstName) == 0 && strcmp(newNode->lastName, temp->lastName) == 0)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            printf("Name already exists. Please enter a different name.\n");
            printf("Press any key to continue.");
            getch();
        }
    } while (flag == 1);

    printf("Enter height (in cm): ");
    scanf("%f", &newNode->height);

    printf("Enter weight (in lbs): ");
    scanf("%f", &newNode->weight);

    // convert pounds to kg
    newNode->weight = newNode->weight * 0.453592;

    // convert cm to m
    newNode->height = newNode->height / 100;

    // calculate bmi
    newNode->bmi = newNode->weight / (newNode->height * newNode->height);

    // get bmi category
    strcpy(newNode->category, categoryBMI(newNode->bmi));

    // insert node at the end of the list
    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = NULL;
    }
    else
    {
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = newNode;
        newNode->next = NULL;
    }

    // increment count
    return count + 1;
}

// function to get category
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

// function to display data in tabular form
void dataDisplay(node *head)
{
    system("cls"); // clear screen

    // display data
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    node temp = *head;
    while (temp != NULL)
    {
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);
        temp = temp->next;
    }

    return;
}

// function to display data by name
void dataDisplayByName(node *head)
{
    char firstName[50];
    char lastName[50];
    int flag = 0;

    fflush(stdin); // clear input buffer

    // ask for name
    do
    {
        flag = 0;
        system("cls"); // clear screen

        printf("Enter first name: ");
        gets(firstName);
        strcpy(firstName, strupr(firstName));

        printf("Enter last name: ");
        gets(lastName);
        strcpy(lastName, strupr(lastName));

        // check if name exists
        node temp = *head;
        while (temp != NULL)
        {
            if (strcmp(firstName, temp->firstName) == 0 && strcmp(lastName, temp->lastName) == 0)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 0)
        {
            printf("Name does not exist. Please enter a different name.\n");
            printf("Press any key to continue.");
            getch();
        }
    } while (flag == 0);

    system("cls"); // clear screen

    // display data
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    node temp = *head;

    while (temp != NULL)
    {
        if (strcmp(firstName, temp->firstName) == 0 && strcmp(lastName, temp->lastName) == 0)
        {
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);
        }
        temp = temp->next;
    }

    return;
}