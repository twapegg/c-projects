// Name: John Stanley T. Altonaga
// Date Created: 9/21/2023
// Date Finished: 9/28/2023
/* Description: This program is a BMI calculator implemented with stacks (arrays of structures).
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
void createStack(Person stack[STACKSIZE], int *top, bool *isChecked);
void initStack(Person stack[STACKSIZE], int *top);
bool isEmpty(int top);
bool isFull(int top);
void push(Person stack[STACKSIZE], int *top, Person data);
Person pop(Person stack[STACKSIZE], int *top);
Person peek(Person stack[STACKSIZE], int *top);
void dataEntry(Person stack[STACKSIZE], int *top);
char *categoryBMI(float bmi);
void dataEditByName(Person stack[STACKSIZE], int *top);
void dataDeleteByName(Person stack[STACKSIZE], int *top);
void topDisplay(Person stack[STACKSIZE], int *top);
void dataDisplay(Person stack[STACKSIZE], int *top);

int main(void)
{
    Person stack[STACKSIZE];
    int top = -1;
    bool isChecked = false;

    int choice;

    do
    {
        choice = menu(); // display menu and get choice

        switch (choice)
        {
        case 1:
            createStack(stack, &top, &isChecked);
            printf("Press any key to continue.");
            getch();
            break;
        case 2:
            // Check if stack is created
            if (!isChecked)
            {
                printf("Stack is not created. Press any key to continue.");
                getch();
                break;
            }

            dataEntry(stack, &top);
            printf("Press any key to continue.");
            getch();
            break;
        case 3:
            // Check if stack is created
            if (!isChecked)
            {
                printf("Stack is not created. Press any key to continue.");
                getch();
                break;
            }

            dataEditByName(stack, &top);
            printf("Press any key to continue.");
            getch();
            break;
        case 4:
            // Check if stack is created
            if (!isChecked)
            {
                printf("Stack is not created. Press any key to continue.");
                getch();
                break;
            }

            dataDeleteByName(stack, &top);
            printf("Press any key to continue.");
            getch();
            break;
        case 5:
            // Check if stack is created
            if (!isChecked)
            {
                printf("Stack is not created. Press any key to continue.");
                getch();
                break;
            }

            topDisplay(stack, &top);
            printf("\nPress any key to continue.");
            getch();
            break;
        case 6:
            // Check if stack is created
            if (!isChecked)
            {
                printf("Stack is not created. Press any key to continue.");
                getch();
                break;
            }

            dataDisplay(stack, &top);
            printf("\nPress any key to continue.");
            getch();
            break;
        case 7:
            printf("Exiting program...");
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

/* function to create stack
    @param (Person) stack
    @param (int) top
    @param (bool) isChecked
 */
void createStack(Person stack[STACKSIZE], int *top, bool *isChecked)
{
    int t = *top;
    bool check = *isChecked;
    char choice;

    do
    {
        // check if stack is already created and is empty
        if (isEmpty(t) && check)
        {
            printf("Stack is already created. ");
            return;
        }

        // check if stack contains data
        if (!isEmpty(t))
        {
            printf("Stack contains data. Do you want to clear the stack? (y/n): ");
        }
        else
        {
            printf("Stack is empty. Do you want to initialize the stack? (y/n): ");
        }
        scanf(" %c", &choice);
        choice = tolower(choice);

        // trap invalid input
        if (choice != 'y' && choice != 'n')
        {
            printf("Invalid option. Please enter a valid option.\n");
        }
    } while (choice != 'y' && choice != 'n');

    switch (choice)
    {
    case 'n':
        printf("Stack has not been created. ");
        break;
    case 'y':
        initStack(stack, &t); // initialize stack
        check = true;
        printf("Stack has been created. ");
        break;
    }

    // update top and isChecked pointers
    *top = t;
    *isChecked = check;

    return;
}

/* function to initialize stack elements
    @param (Person) stack
    @param (int) top
 */
void initStack(Person stack[STACKSIZE], int *top)
{
    int i, t = *top;

    // loop to initialize stack elements to null values
    for (i = 0; i < STACKSIZE; i++)
    {
        stack[i].firstName[0] = '\0';
        stack[i].lastName[0] = '\0';
        stack[i].weight = 0;
        stack[i].height = 0;
        stack[i].bmi = 0;
        stack[i].category[0] = '\0';
    };
    t = -1;   // set top to -1
    *top = t; // update top pointer
    return;
}
/* function to check if stack is empty
    @param (int) top
    @returns (bool) true if stack is empty, false if stack is not empty
 */
bool isEmpty(int top)
{
    if (top == -1)
        return true;
    else
        return false;
}

/* function to check if stack is full
    @param (int) top
    @returns (bool) true if stack is full, false if stack is not full
 */
bool isFull(int top)
{
    if (top == STACKSIZE - 1)
        return true;
    else
        return false;
}

/* function to push data to stack
    @param (Person) stack
    @param (int) top
    @param (Person) data
 */
void push(Person stack[STACKSIZE], int *top, Person data)
{
    int t = *top;
    t++;
    stack[t] = data; // push data to stack
    *top = t;
    return;
}

/* function to pop data from stack
    @param (Person) stack
    @param (int) top
    @returns (Person) data
 */
Person pop(Person stack[STACKSIZE], int *top)
{
    int t = *top;
    Person data = stack[t]; // pop data from stack
    t--;
    *top = t;
    return data; // return popped data
}

/* function to peek top element of the stack
    @param (Person) stack
    @param (int) top
    @returns (Person) data
 */
Person peek(Person stack[STACKSIZE], int *top)
{
    int t = *top;
    return stack[t]; // return top element of the stack
}

/* function to enter data to stack
    @param (Person) stack
    @param (int) top
 */
void dataEntry(Person stack[STACKSIZE], int *top)
{
    int t = *top;
    bool check = isFull(t);

    // check if stack is full
    if (check)
    {
        printf("Stack is full. Press any key to continue.");
        getch();
        return;
    }

    Person data; // data holder

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];
    float tempHeight;
    float tempWeight;

    fflush(stdin); // clear input buffer
    system("cls");

    printf("Enter first name: ");
    gets(tempFirstName);
    strcpy(data.firstName, tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);
    strcpy(data.lastName, tempLastName);

    printf("Enter height (in cm): ");
    scanf("%f", &tempHeight);

    printf("Enter weight (in lbs): ");
    scanf("%f", &tempWeight);

    data.height = tempHeight / 100;                       // convert cm to m
    data.weight = tempWeight * 0.453592;                  // convert lbs to kg
    data.bmi = data.weight / (data.height * data.height); // calculate bmi
    strcpy(data.category, categoryBMI(data.bmi));         // calculate bmi category

    push(stack, &t, data); // push data to stack
    *top = t;              // update top
    printf("Data has been added. ");
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

/* function to edit data by name
    @param (Person) stack
    @param (int) top
 */
void dataEditByName(Person stack[STACKSIZE], int *top)
{
    int t = *top;
    bool check = isEmpty(t);

    system("cls");

    // check if stack is empty
    if (check)
    {
        printf("Stack is empty. ");
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    gets(tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);

    Person tempStack[STACKSIZE]; // temporary stack

    int tempTop = -1;
    int flag = 0; // flag to check if data is found
    int i;

    // search for data
    for (i = t; i >= 0; i--)
    {
        // pop data from stack
        Person temp = pop(stack, &t);

        // check if data is found
        if (strcmpi(temp.firstName, tempFirstName) == 0 && strcmpi(temp.lastName, tempLastName) == 0)
        {
            flag = 1;
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
                if (choice != 'y' && choice != 'n')
                {
                    printf("Invalid option. Please enter a valid option.\n");
                }
            } while (choice != 'y' && choice != 'n');

            switch (choice)
            {
            case 'n':
                system("cls");
                printf("Record has not been edited. Displaying record...\n\n");
                printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);
                push(stack, &t, temp); // push data back to stack
                break;
            case 'y':

                printf("Enter new height (in cm): ");
                scanf("%f", &temp.height);

                printf("Enter new weight (in lbs): ");
                scanf("%f", &temp.weight);

                temp.height = temp.height / 100;                      // convert cm to m
                temp.weight = temp.weight * 0.453592;                 // convert lbs to kg
                temp.bmi = temp.weight / (temp.height * temp.height); // get bmi
                strcpy(temp.category, categoryBMI(temp.bmi));         // get bmi category

                push(stack, &t, temp); // push data to stack

                system("cls");
                printf("Record has been edited. Displaying record...\n\n");
                printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);

                break;
            }

            break; // since data is found, break loop
        }

        // if data doesn't match, push to temporary stack
        push(tempStack, &tempTop, temp);
    }

    // push back to original stack
    for (i = tempTop; i >= 0; i--)
    {
        Person temp = pop(tempStack, &tempTop);
        push(stack, &t, temp);
    }

    // check if data is not found
    if (flag == 0)
    {
        printf("\nRecord not found. ");
    }

    return;
}

/* function to delete data by name
    @param (Person) stack
    @param (int) top
 */
void dataDeleteByName(Person stack[STACKSIZE], int *top)
{

    int t = *top;
    bool check = isEmpty(t);

    system("cls");

    // check if stack is empty
    if (check)
    {
        printf("Stack is empty. ");
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    gets(tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);

    Person tempStack[STACKSIZE]; // temporary stack

    int tempTop = -1;
    int flag = 0; // flag to check if data is found
    int i;

    // search for data
    for (i = t; i >= 0; i--)
    {
        // pop data from stack
        Person temp = pop(stack, &t);

        // check if data is found
        if (strcmpi(temp.firstName, tempFirstName) == 0 && strcmpi(temp.lastName, tempLastName) == 0)
        {
            flag = 1;
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
                if (choice != 'y' && choice != 'n')
                {
                    printf("Invalid option. Please enter a valid option.\n");
                }
            } while (choice != 'y' && choice != 'n');

            switch (choice)
            {
            case 'n':
                system("cls");
                printf("Record has not been deleted. Displaying record...\n\n");
                printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);
                push(stack, &t, temp); // push data back to stack
                break;
            case 'y':
                system("cls");
                printf("Record has been deleted. ");
                break;
            }

            break; // since data is found, break loop
        }
        // if data doesn't match, push to temporary stack
        push(tempStack, &tempTop, temp);
    }

    // push back to original stack
    for (i = tempTop; i >= 0; i--)
    {
        Person temp = pop(tempStack, &tempTop);
        push(stack, &t, temp);
    }

    // check if data is not found
    if (flag == 0)
    {
        printf("\nRecord not found. ");
    }

    *top = t; // update top
    return;
}

/* function to display top element of the stack
    @param (Person) stack
    @param (int) top
 */
void topDisplay(Person stack[STACKSIZE], int *top)
{
    int t = *top;
    bool check = isEmpty(t); // returns true if stack is empty

    system("cls");

    // check if stack is empty
    if (check)
    {
        printf("Stack is empty. ");
        return;
    }

    // else, display top element
    Person temp = peek(stack, &t); // get top element

    // display element
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);

    return;
}

/* function to display all elements of the stack (top to bottom)
    @param (Person) stack
    @param (int) top
 */
void dataDisplay(Person stack[STACKSIZE], int *top)
{
    int t = *top;
    bool check = isEmpty(t); // returns true if stack is empty

    system("cls");

    // check if stack is empty
    if (check)
    {
        printf("Stack is empty. ");
        return;
    }

    // else, display all elements
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    Person tempStack[STACKSIZE]; // temporary stack
    int tempTop = -1;

    for (int i = t; i >= 0; i--)
    {
        Person temp = pop(stack, &t); // pop element
        // display element
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp.firstName), strupr(temp.lastName), temp.height, temp.weight, temp.bmi, temp.category);
        push(tempStack, &tempTop, temp); // push element to temporary stack
    }

    // push back to original stack
    for (int i = tempTop; i >= 0; i--)
    {
        Person temp = pop(tempStack, &tempTop);
        push(stack, &t, temp);
    }
    return;
}