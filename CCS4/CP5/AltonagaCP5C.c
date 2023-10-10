// Name: John Stanley T. Altonaga
// Date Created: 9/21/2023
// Date Finished: 9/28/2023
/* Description: This program is a BMI calculator implemented with stacks (singly-linked list).
The program can create a stack, add elements, edit elements, delete elements, display top element, and display all elements.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

#define STACKSIZE 10
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

void createStack(node *top, bool *isChecked);
void push(node *top, node data);
node pop(node *top);
node peek(node *top);
bool isEmpty(node *top);

int menu(void);
char *categoryBMI(float bmi);

void dataEntry(node *top);
void dataEditByName(node *top);
void dataDeleteByName(node *top);
void topDisplay(node *top);
void dataDisplay(node *top);

int main(void)
{
    node top = NULL;
    bool isChecked = false;

    int choice;
    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            createStack(&top, &isChecked);
            break;
        case 2:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataEntry(&top);
            break;
        case 3:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataEditByName(&top);
            break;
        case 4:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataDeleteByName(&top);
            break;
        case 5:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            topDisplay(&top);
            break;
        case 6:
            dataDisplay(&top);
            break;
        case 7:
            printf("Exiting the program...\n");
        }
    } while (choice != 7);

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
        printf("[1] Create Stack\n");
        printf("[2] Add element\n");
        printf("[3] Edit element\n");
        printf("[4] Delete element\n");
        printf("[5] Display top element\n");
        printf("[6] Display all elements\n");
        printf("[7] Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 7)
        {
            printf("Invalid option. Please enter a valid option.\n");
            getch();
        }
    } while (choice < 1 || choice > 7);
    return choice;
}

/*  function to create stack
    @param (node *) top
    @param (bool *) isChecked
*/
void createStack(node *top, bool *isChecked)
{
    // check if stack already exists
    if (*top == NULL && *isChecked == true)
    {
        printf("Stack already exists. Press any key to continue.\n");
        getch();
        return;
    }

    // check if stack has elements
    if (*top != NULL && *isChecked == true)
    {
        printf("Stack has existing elements. Do you want to clear the stack? (y/n): ");
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
                *top = NULL;
                printf("Stack has been cleared. Press any key to continue.\n");
                getch();
                return;
            }
            if (choice == 'n')
            {
                printf("Stack has not been cleared. Press any key to continue.\n");
                getch();
                return;
            }
        } while (choice != 'y' && choice != 'n');
    }

    // else if stack does not exist
    *top = NULL;
    *isChecked = true;
    printf("Stack has been created. Press any key to continue.\n");
    getch();
    return;
}

/*  function to push element to stack
    @param (node *) top
*/
void push(node *top, node data)
{
    data->next = *top; // point node next to current top
    *top = data;       // point top to new node
    return;
}

/*  function to pop element from stack
    @param (node *) top
    @returns (node) temp
*/
node pop(node *top)
{
    node temp = *top;
    *top = (*top)->next;
    return temp;
}

/*  function to peek top element of stack
    @param (node *) top
    @returns (node) temp
*/
node peek(node *top)
{
    return *top;
}

/*  function to check if stack is empty
    @param (node *) top
    @returns (bool) isEmpty
*/
bool isEmpty(node *top)
{
    // if top is NULL, return true, else return false
    return *top == NULL ? true : false;
}

void dataEntry(node *top)
{
    node temp = malloc(sizeof(Person));
    // if malloc fails, exit program
    if (temp == NULL)
    {
        printf("Stack overflow. Exiting the program...\n");
        exit(1);
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    fflush(stdin); // clear input buffer
    system("cls");

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

    push(top, temp); // push to stack

    printf("Data has been added. Press any key to continue.\n");
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
}

void dataEditByName(node *top)
{
    // check if stack is empty
    if (isEmpty(top))
    {
        printf("Stack is empty. Press any key to continue.\n");
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

    node t = *top; // temp node to hold top
    node tempStack = NULL;

    // pop element, display returned element from pop, then push element to a temp stack
    while (t != NULL)
    {
        node temp = pop(&t);
        if (strcmp(temp->firstName, tempFirstName) == 0 && strcmp(temp->lastName, tempLastName) == 0)
        {
            printf("Enter new height (in cm): ");
            scanf("%f", &temp->height);

            printf("Enter new weight (in lbs): ");
            scanf("%f", &temp->weight);

            temp->height /= 100;                                      // convert cm to m
            temp->weight *= 0.453592;                                 // convert lbs to kg
            temp->bmi = temp->weight / (temp->height * temp->height); // calculate bmi
            strcpy(temp->category, categoryBMI(temp->bmi));           // get category
        }
        push(&tempStack, temp);
    }

    // push elements back to original stack
    while (tempStack != NULL)
    {
        node temp = pop(&tempStack);
        push(&t, temp);
    }

    printf("Data has been edited. Press any key to continue.\n");
    getch();
    return;
}

/*  function to delete element from stack
    @param (node *) top
*/
void dataDeleteByName(node *top)
{
    // check if stack is empty
    if (isEmpty(top))
    {
        printf("Stack is empty. Press any key to continue.\n");
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

    node t = *top; // temp node to hold top
    node tempStack = NULL;

    // pop element, display returned element from pop, then push element to a temp stack
    while (t != NULL)
    {
        node temp = pop(&t);
        if (strcmp(temp->firstName, tempFirstName) == 0 && strcmp(temp->lastName, tempLastName) == 0)
        {
            printf("Data has been deleted. Press any key to continue.\n");
            getch();
            return;
        }
        push(&tempStack, temp);
    }

    // push elements back to original stack
    while (tempStack != NULL)
    {
        node temp = pop(&tempStack);
        push(&t, temp);
    }

    *top = t; // update top
    printf("Data not found. Press any key to continue.\n");
    getch();
    return;
}

/*  function to display top element in stack
    @param (node *) top
*/
void topDisplay(node *top)
{
    // check if stack is empty
    if (isEmpty(top))
    {
        printf("Stack is empty. Press any key to continue.\n");
        getch();
        return;
    }

    node temp = peek(top);
    system("cls");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);

    printf("\nPress any key to continue.\n");
    getch();
    return;
}

/*  function to display all elements in stack
    @param (node *) top
*/
void dataDisplay(node *top)
{
    // check if stack is empty
    if (isEmpty(top))
    {
        printf("Stack is empty. Press any key to continue.\n");
        getch();
        return;
    }

    // else, display all elements
    node t = *top; // temp node to hold top
    node tempStack = NULL;
    system("cls");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    // pop element, display returned element from pop, then push element to a temp stack
    while (t != NULL)
    {
        node temp = pop(&t);
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);
        push(&tempStack, temp);
    }

    // push elements back to original stack
    while (tempStack != NULL)
    {
        node temp = pop(&tempStack);
        push(&t, temp);
    }

    printf("\nPress any key to continue.\n");
    getch();
    return;
}
