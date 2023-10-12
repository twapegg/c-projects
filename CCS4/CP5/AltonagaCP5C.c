// Name: John Stanley T. Altonaga
// Date Created: 10/9/2023
// Date Finished: 10/12/2023
/* Description: This program is a BMI calculator implemented with stacks (singly-linked list).
The program can create a stack, add elements (at head), edit elements, delete elements, display top element, and display all elements.
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

void createStack(node *stack, node *top, bool *isChecked);
void push(node *stack, node *top, node data);
node pop(node *stack, node *top);
node peek(node *top);
bool isEmpty(node *top);

int menu(void);
char *categoryBMI(float bmi);

void dataEntry(node *stack, node *top);
void dataEditByName(node *stack, node *top);
void dataDeleteByName(node *stack, node *top);
void topDisplay(node *stack, node *top);
void dataDisplay(node *stack, node *top);

int main(void)
{
    node stack = NULL;
    node top = NULL;
    bool isChecked = false;

    int choice;
    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            createStack(&stack, &top, &isChecked);
            break;
        case 2:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataEntry(&stack, &top);
            break;
        case 3:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataEditByName(&stack, &top);
            break;
        case 4:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataDeleteByName(&stack, &top);
            break;
        case 5:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            topDisplay(&stack, &top);
            break;
        case 6:
            // check if stack exists
            if (top == NULL && isChecked == false)
            {
                printf("Stack does not exist. Press any key to continue.\n");
                getch();
                break;
            }
            dataDisplay(&stack, &top);
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
void createStack(node *stack, node *top, bool *isChecked)
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

/*  function to push element to stack (at head)
    @param (node *) top
*/
void push(node *stack, node *top, node data)
{
    data->next = *top; // point node next to current top
    *top = data;       // point top to new node
    *stack = *top;
    return;
}

/*  function to pop element from stack
    @param (node *) top
    @returns (node) temp
*/
node pop(node *stack, node *top)
{
    node temp = *top;
    *top = (*top)->next;
    *stack = *top;
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

/*  function to get data from user and push to stack
    @param (node *) top
*/
void dataEntry(node *stack, node *top)
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

    push(stack, top, temp); // push to stack

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
}

/*  function to edit element in stack
    @param (node *) top
*/
void dataEditByName(node *stack, node *top)
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
    node tempTop = NULL;  // temp stack top holder
    bool isFound = false; // flag to check if data is found

    // pop element, display returned element from pop, then push element to a temp stack
    while (t != NULL)
    {
        node temp = pop(stack, &t);
        if (stricmp(temp->firstName, tempFirstName) == 0 && stricmp(temp->lastName, tempLastName) == 0)
        {
            isFound = true;
            // display element
            system("cls");
            printf("Record found. Displaying record...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

            char choice;
            printf("\nDo you want to edit this record? (y/n): ");

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
                    // get new data
                    printf("\nEnter new height (in cm): ");
                    scanf("%f", &temp->height);

                    printf("Enter new weight (in lbs): ");
                    scanf("%f", &temp->weight);

                    temp->height /= 100;                                      // convert cm to m
                    temp->weight *= 0.453592;                                 // convert lbs to kg
                    temp->bmi = temp->weight / (temp->height * temp->height); // calculate bmi
                    strcpy(temp->category, categoryBMI(temp->bmi));           // get category

                    // push element back to stack
                    push(stack, &t, temp);
                    printf("\nData has been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
                if (choice == 'n')
                {
                    // push element back to stack
                    push(stack, &t, temp);
                    printf("\nData has not been edited. Press any key to continue.\n");
                    getch();
                    break;
                }
            } while (choice != 'y' && choice != 'n');

            break; // since data is found, break out of loop
        }
        // if data does not match, push element to temp stack
        push(&tempStack, &tempTop, temp);
    }

    // push elements back to original stack
    while (tempStack != NULL)
    {
        node temp = pop(&tempStack, &tempTop);
        push(stack, &t, temp);
    }

    // if data is not found, display message
    if (!isFound)
    {
        printf("\nData not found. Press any key to continue.\n");
        getch();
        return;
    }

    *top = t; // update top
    *stack = *top;
    return;
}

/*  function to delete element from stack
    @param (node *) top
*/
void dataDeleteByName(node *stack, node *top)
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
    node tempTop = NULL;  // temp stack top holder
    bool isFound = false; // flag to check if data is found

    // pop element, display returned element from pop, then push element to a temp stack
    while (t != NULL)
    {
        node temp = pop(stack, &t);
        if (stricmp(temp->firstName, tempFirstName) == 0 && stricmp(temp->lastName, tempLastName) == 0)
        {
            isFound = true;

            // display element
            system("cls");
            printf("Record found. Displaying record...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
            char choice;
            printf("\nDo you want to delete this record? (y/n): ");

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

                    printf("\nData has been deleted. Press any key to continue.\n");
                    getch();
                    break;
                }
                if (choice == 'n')
                {
                    // push element back to stack
                    push(stack, &t, temp);
                    printf("\nData has not been deleted. Press any key to continue.\n");
                    getch();
                    break;
                }
            } while (choice != 'y' && choice != 'n');

            break; // since data is found, break out of loop
        }
        // if data does not match, push element to temp stack
        push(&tempStack, &tempTop, temp);
    }

    // push elements back to original stack
    while (tempStack != NULL)
    {
        node temp = pop(&tempStack, &tempTop);
        push(stack, &t, temp);
    }

    // if data is not found, display message
    if (!isFound)
    {
        printf("\nData not found. Press any key to continue.\n");
        getch();
        return;
    }

    *top = t; // update top
    *stack = *top; 
    return;
}

/*  function to display top element in stack
    @param (node *) top
*/
void topDisplay(node *stack, node *top)
{
    // check if stack is empty
    if (isEmpty(top))
    {
        printf("Stack is empty. Press any key to continue.\n");
        getch();
        return;
    }

    node temp = peek(top); // get top element
    system("cls");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
    printf("\nPress any key to continue.\n");
    getch();
    return;
}

/*  function to display all elements in stack
    @param (node *) top
*/
void dataDisplay(node *stack, node *top)
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
    node tempTop = NULL; // temp stack top holder
    system("cls");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    // pop element, display returned element from pop, then push element to a temp stack
    while (t != NULL)
    {
        node temp = pop(stack, &t); // pop element
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
        push(&tempStack, &tempTop, temp); // push element to temp stack
    }

    // push elements back to original stack
    while (tempStack != NULL)
    {
        node temp = pop(&tempStack, &tempTop);
        push(stack, &t, temp);
    }

    printf("\nPress any key to continue.\n");
    getch();
    return;
}
