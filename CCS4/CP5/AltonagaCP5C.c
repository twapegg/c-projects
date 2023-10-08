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
    node *next;
} Person;

typedef struct stack
{
    node *top;
    bool isChecked;
} Stack;

void createStack(Stack *stack);
void push(node *top, node data);
bool isEmpty(node *top);
bool isFull(node *top);
// void pop(node *top);
// void displayTop(node *top);
// void edit(node *top);
// void delete(node *top);
// void clear(node *top);
int menu(void);

char *categoryBMI(float bmi);
void dataEntry(node *top);
void dataDisplay(node *top);

int main(void)
{
    Stack stack;
    stack.isChecked = false;
    stack.top = NULL;

    int choice;
    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            createStack(&stack);
            break;
        case 2:
            dataEntry(&stack.top);
            break;

        // case 3:
        //     edit(&top);
        //     break;
        // case 4:
        //     delete (&top);
        //     break;
        // case 5:
        //     displayTop(&top);
        //     break;
        case 6:
            dataDisplay(&stack.top);
            break;
            // case 7:
            //     clear(&top);
            //     break;
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
*/
void createStack(Stack *stack)
{
    // test cases:
    // 1. stack already created
    // 2. stack already created but has elements
    // 3. stack created but not empty

    if (stack->isChecked == true)
    {
        printf("Stack already created.\n");
        getch();
        return;
    }

    stack->top = NULL;
    stack->isChecked = true;
    printf("Stack created.\n");
    return;
}

/*  function to push element to stack
    @param (node *) top
*/
void push(node *top, node data)
{
    data->next = *top;
    *top = data;
    return;
}

/*  function to check if stack is empty
    @param (node *) top
    @returns (bool) isEmpty
*/
bool isEmpty(node *top)
{
    return *top == NULL ? true : false;
}

/*  function to check if stack is full
    @param (node *) top
    @returns (bool) isFull
*/
bool isFull(node *top)
{
    node temp = malloc(sizeof(Person));
    if (temp == NULL)
    {
        return true;
    }
    else
    {
        free(temp);
        return false;
    }
}

void dataEntry(node *top)
{

    node temp = malloc(sizeof(Person));
    if (temp == NULL)
    {
        printf("Stack is full.\n");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    fflush(stdin); // clear input buffer
    system("cls");

    printf("Enter first name: ");
    gets(tempFirstName);
    strcpy(temp->firstName, tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);
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

    printf("Data has been added.\n");
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

/*  function to display all elements in stack
    @param (node *) top
*/
void dataDisplay(node *top)
{
    if (*top == NULL)
    {
        printf("Stack is empty.\n");
        getch();
        return;
    }

    node temp = *top;
    while (temp != NULL)
    {
        printf("Name: %s %s\n", temp->firstName, temp->lastName);
        printf("Weight: %.2f\n", temp->weight);
        printf("Height: %.2f\n", temp->height);
        printf("BMI: %.2f\n", temp->bmi);
        printf("Category: %s\n", temp->category);
        printf("\n");
        temp = temp->next;
    }
    getch();
    return;
}