/*	Programmer: Rusyl Anne D. Espina
    Started on: September 23, 2023
    Finished on: September 28, 2023

    Program Summary: THIS PROGRAM ASKS A USER FOR DETAILS SUCH AS THE FIRST NAME, LAST NAME, WEIGHT, AND HEIGHT. IT WILL THEN STORE THE ELEMENTS INTO A STACK.
                    THE PROGRAM WILL CALCULATE FOR ITS BMI AND GIVE THE BMI RANGE. IT ALSO ALLOWS THE USER TO EDIT AND DELETE AN ELEMENT, AND PEEK INTO THE TOPMOST ELEMENT OF A STACK.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>

#define SIZE 10

// STRUCTURE
typedef struct person
{
    char fname[100];
    char lname[100];
    float height;
    float weight;
    float m;
    float kg;
    float BMI;
    char range[100];
} PERSON;

// FUNCTION DECLARATIONS
bool isFull(int top);
bool isEmpty(int top);
void Push(PERSON stack[], PERSON element, int *top);
PERSON Pop(PERSON stack[], int *top);
PERSON Peek(PERSON stack[], int *top);
void ShowMostTOP(PERSON stack[], int top, bool stackCreated);
void Create(PERSON stack[], int *top);
void CreateStack(PERSON stack[], int *top, bool *stackCreated);
void AddElement(PERSON stack[], int *top, bool stackCreated);
void DisplayStack(PERSON stack[], int top, bool stackCreated);
void CalculatorAndRange(PERSON stack[], int top);
void SearchAndDelete(PERSON stack[], int *top, bool stackCreated);
void SearchAndEdit(PERSON stack[], int *top, bool stackCreated);

// MAIN MENU
int Menu(void)
{
    char choice;
    printf("\nMenu:\n");
    printf("[A]. CREATE THE STACK\n");
    printf("[B]. ADD AN ELEMENT INTO THE STACK\n");
    printf("[C]. SEARCH AND EDIT AN ELEMENT\n");
    printf("[D]. SEARCH AND DELETE AN ELEMENT\n");
    printf("[E]. TAKE A PEEK AT THE TOP OF THE STACK\n");
    printf("[F]. DISPLAY ALL ELEMENTS\n");
    printf("[G]. EXIT PROGRAM\n");
    printf("\n\nEnter your choice: ");
    scanf(" %c", &choice);

    return choice;
}

int main()
{
    int choice;
    PERSON stack[SIZE];
    int top = -1;
    bool stackCreated = false;

    do
    {
        system("cls");
        fflush(stdin);
        choice = Menu();

        switch (choice)
        {
        case 'a':
        case 'A':
            CreateStack(stack, &top, &stackCreated);
            break;
        case 'b':
        case 'B':
            AddElement(stack, &top, stackCreated);
            break;
        case 'c':
        case 'C':
            SearchAndEdit(stack, &top, stackCreated);
            break;
        case 'd':
        case 'D':
            SearchAndDelete(stack, &top, stackCreated);
            break;
        case 'e':
        case 'E':
            ShowMostTOP(stack, top, stackCreated);
            break;
        case 'f':
        case 'F':
            DisplayStack(stack, top, stackCreated);
            break;
        case 'g':
        case 'G':
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    } while (choice != 'g' && choice != 'G');

    return 0;
}

// CHECKS IF A STACK IS FULL
bool isFull(int top)
{
    if (top == SIZE - 1)
        return true;
    else
        return false;
}

// CHECKS IF A STACK IS EMPTY
bool isEmpty(int top)
{
    if (top == -1)
        return true;
    else
        return false;
}

// PUSHES AN ELEMENT TO ITS DESIRED STACK
void Push(PERSON stack[SIZE], PERSON element, int *top)
{
    int t = *top;
    t++;
    stack[t] = element;
    *top = t;
}

// POPS AN ELEMENT FROM A STACK
PERSON Pop(PERSON stack[], int *top)
{
    int t = *top;
    PERSON element;

    element = stack[t];
    t--;
    *top = t;
    return element;
}

// FUNCTION THAT DISPLAYS THE TOP ELEMENT
void ShowMostTOP(PERSON stack[], int top, bool stackCreated)
{
    PERSON element;

    if (stackCreated == false)
    {
        printf("\nError: Stack has not been created. Please create the stack first (Option A).\n");
        printf("Press any key to return to the main menu.");
        getch();
        return;
    }

    if (isEmpty(top))
    {
        printf("\nStack is empty. No elements to peek.\n");
        printf("Press any key to continue...");
        getch();
    }
    else
    {
        element = Peek(stack, &top);
        printf("\nFirst Name\t\tLast Name\tHeight (cm)\tWeight (kg)\tBMI\t\tInterpretation\n");
        printf("%-24s%-16s%-16.2f%-16.1f%-16.1f%-16s\n", strupr(element.fname), strupr(element.lname), element.height, element.kg, element.BMI, element.range);
        printf("\n\nPress any key to continue...");
        getch();
    }
}

// CHECKS THE TOP ELEMENT
PERSON Peek(PERSON stack[], int *top)
{
    int t = *top;
    PERSON element;

    element = stack[t];
    *top = t;
    return element;
}

void Create(PERSON stack[], int *top)
{
    int i, t = *top;

    for (i = 0; i < SIZE; i++)
    {
        strcpy(stack[i].fname, "");
        strcpy(stack[i].lname, "");
        stack[i].height = 0.0;
        stack[i].weight = 0.0;
        stack[i].m = 0.0;
        stack[i].kg = 0.0;
        stack[i].BMI = 0.0;
        strcpy(stack[i].range, "");
    }

    printf("\nStack created.");
    printf("\nPress any key to continue...");
    getch();
    t = -1;
    *top = t;
}

void CreateStack(PERSON stack[], int *top, bool *stackCreated)
{
    int t = *top;
    bool crt = *stackCreated;
    char confirm;

    if (t != -1)
    {
        printf("\nWarning: The stack already has elements.");
        do
        {
            printf("\nDo you want to delete the elements of the stack and create a new stack? (Y/N): ");
            scanf(" %c", &confirm);

            if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
            {
                printf("\nInvalid input. Please enter 'Y' or 'N'.");
            }

            else if (confirm == 'Y' || confirm == 'y')
            {
                Create(stack, &t);
            }
            else
            {
                printf("\nStack creation canceled.");
                printf("\nPress any key to return to the main menu.");
                getch();
            }
        } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');
    }
    else
    {
        Create(stack, &t);
    }
    *top = t;
    crt = true;
    *stackCreated = crt;
}

// THIS FUNCTION ALLOWS A USER TO ADD AN ELEMENT TO THE STACK.
void AddElement(PERSON stack[], int *top, bool stackCreated)
{
    int t = *top;
    char Fname[100];
    char Lname[100];
    float hgt;
    float wgt;
    bool Full;
    PERSON newElement;

    if (stackCreated == false)
    {
        printf("\nError: Stack has not been created. Please create the stack first (Option A).");
        printf("\nPress any key to return to the main menu.");
        getch();
        return;
    }

    Full = isFull(t);
    if (Full)
    {
        printf("\nError: Stack is full. Cannot add more elements.");
        printf("\nPress any key to return to the main menu.");
        getch();
        return;
    }
    else
    {
        system("cls");
        fflush(stdin);
        printf("Enter First Name: ");
        gets(Fname);
        strcpy(newElement.fname, Fname);
        printf("Enter Last Name: ");
        gets(Lname);
        strcpy(newElement.lname, Lname);
        printf("Enter Height (in cm): ");
        scanf("%f", &hgt);
        newElement.height = hgt;
        printf("Enter Weight (in pounds): ");
        scanf("%f", &wgt);
        newElement.weight = wgt;

        Push(stack, newElement, &t);
        *top = t;

        CalculatorAndRange(stack, *top);
        printf("\nElement added to the stack.");
        printf("\nPress any key to continue...");
        getch();
    }
}

// THIS FUNCTION CONVERTS CENTIMETERS TO METERS AND POUNDS TO KILOGRAMS. IT THEN CALCULATES THE BMI AND DETERMINE THE BMI RANGE OF THE USER BASE ON ITS BMI.
void CalculatorAndRange(PERSON stack[], int top)
{
    stack[top].kg = stack[top].weight * 0.4535927;
    stack[top].m = stack[top].height * 0.01;
    stack[top].BMI = stack[top].kg / (stack[top].m * stack[top].m);

    if (stack[top].BMI < 18.5)
    {
        strcpy(stack[top].range, "Underweight");
    }
    else if (stack[top].BMI >= 18.5 && stack[top].BMI < 24.9)
    {
        strcpy(stack[top].range, "Normal weight");
    }
    else if (stack[top].BMI >= 25 && stack[top].BMI < 29.9)
    {
        strcpy(stack[top].range, "Overweight");
    }
    else
    {
        strcpy(stack[top].range, "Obese");
    }
}

// THIS FUNCTION DISPLAYS THE ELEMENTS OF THE STACK.
void DisplayStack(PERSON stack[], int top, bool stackCreated)
{
    if (stackCreated == false)
    {
        printf("\nError: Stack has not been created. Please create the stack first (Option A).");
        printf("\nPress any key to return to the main menu.");
        getch();
        return;
    }

    if (isEmpty(top))
    {
        printf("\nStack is empty. No elements to display.");
        printf("\nPress any key to continue...");
        getch();
    }
    else
    {
        PERSON tempStack[SIZE];
        int tempTop = -1;

        printf("\nFirst Name\t\tLast Name\tHeight (cm)\tWeight (kg)\tBMI\t\tInterpretation\n");

        while (!isEmpty(top))
        {
            PERSON element = Pop(stack, &top);
            Push(tempStack, element, &tempTop);

            printf("%-24s%-16s%-16.2f%-16.1f%-16.1f%-16s\n", strupr(element.fname), strupr(element.lname), element.m, element.kg, element.BMI, element.range);
        }

        while (!isEmpty(tempTop))
        {
            PERSON element = Pop(tempStack, &tempTop);
            Push(stack, element, &top);
        }

        printf("\n\nPress any key to continue...");
        getch();
    }
}

// THIS FUNCTION ALLOWS THE USER TO SEARCH FOR AN ELEMENT AND IF FOUND, THE PROGRAM WILL ASK WHETHER THE USER WILL EDIT THE HEIGHT AND WEIGHT OF THE ELEMENT.
void SearchAndEdit(PERSON stack[], int *top, bool stackCreated)
{
    int t = *top;
    char FN[100];
    char LN[100];
    bool found = false;
    int tempTop = -1;
    PERSON tempStack[SIZE];
    char choice;

    if (stackCreated == false)
    {
        printf("\nError: Stack has not been created. Please create the stack first (Option A).\n");
        printf("Press any key to return to the main menu.");
        getch();
        return;
    }

    if (isEmpty(*top))
    {
        printf("\nStack is empty. No elements to edit.");
        printf("\nPress any key to continue...");
        getch();
        return;
    }

    system("cls");
    fflush(stdin);
    printf("Input the following details to search:\n\n");
    printf("Enter first name: ");
    gets(FN);
    printf("Enter last name: ");
    gets(LN);

    while (!isEmpty(*top))
    {
        PERSON element = Pop(stack, top);

        if (strcmpi(element.fname, FN) == 0 && strcmpi(element.lname, LN) == 0)
        {
            found = true;
            printf("\n\nName: %s %s\n", strupr(element.fname), strupr(element.lname));
            printf("Height: %.2f meters\n", element.m);
            printf("Weight: %.1f kilograms\n", element.kg);
            printf("Your BMI is %.2f and you are %s.\n", element.BMI, element.range);

            do
            {
                printf("\nDo you want to edit the height and weight? [Y/N]: ");
                scanf(" %c", &choice);

                if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                {
                    printf("\nInvalid input. Please enter 'Y' or 'N'.\n");
                }
                else if (choice == 'Y' || choice == 'y')
                {
                    system("cls");
                    fflush(stdin);
                    printf("\nEnter new Height (in cm): ");
                    scanf("%f", &element.height);
                    printf("Enter new Weight (in pounds): ");
                    scanf("%f", &element.weight);

                    CalculatorAndRange(&element, *top);
                    printf("\nElement edited.\n");

                    Push(stack, element, &top);
                    *top = t;
                }
                else
                {
                    printf("\nThe height and weight will remain unchanged.\n");
                }
            } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
        }
        else
        {
            Push(tempStack, element, &tempTop);
        }
    }

    while (!isEmpty(tempTop))
    {
        PERSON element = Pop(tempStack, &tempTop);
        Push(stack, element, top);
    }

    if (!found)
    {
        printf("\nPerson not found.");
    }

    printf("\nPress any key to return to the main menu.");
    getch();
}

// THIS FUNCTION ALLOWS THE USER TO SEARCH FOR AN ELEMENT AND IF FOUND, THE PROGRAM WILL ASK WHETHER THE USER WILL DELETE THE ELEMENT OF THE STACK.
void SearchAndDelete(PERSON stack[], int *top, bool stackCreated)
{
    char FN[100];
    char LN[100];
    bool found = false;
    PERSON tempStack[SIZE];
    int tempTop = -1;
    char choice;

    if (stackCreated == false)
    {
        printf("\nError: Stack has not been created. Please create the stack first (Option A).\n");
        printf("Press any key to return to the main menu.");
        getch();
        return;
    }

    if (isEmpty(*top))
    {
        printf("\nStack is empty. No elements to delete.");
        printf("\nPress any key to return to the main menu.");
        getch();
        return;
    }

    system("cls");
    fflush(stdin);
    printf("Input the following details to search:\n\n");
    printf("Enter first name: ");
    gets(FN);
    printf("Enter last name: ");
    gets(LN);

    while (!isEmpty(*top))
    {
        PERSON element = Pop(stack, top);

        if (strcmpi(element.fname, FN) == 0 && strcmpi(element.lname, LN) == 0)
        {
            found = true;
            printf("\n\nName: %s %s\n", strupr(element.fname), strupr(element.lname));
            printf("Height: %.2f meters\n", element.m);
            printf("Weight: %.1f kilograms\n", element.kg);
            printf("Your BMI is %.2f and you are %s.\n", element.BMI, strupr(element.range));

            do
            {
                printf("\nDo you want to delete this element? [Y/N]: ");
                scanf(" %c", &choice);

                if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                {
                    printf("\nInvalid input. Please enter 'Y' or 'N'.");
                }
                else if (choice == 'Y' || choice == 'y')
                {
                    printf("\nElement successfully deleted.");
                }

            } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
        }
        else
        {
            Push(tempStack, element, &tempTop);
        }
    }

    while (!isEmpty(tempTop))
    {
        PERSON element = Pop(tempStack, &tempTop);
        Push(stack, element, top);
    }

    if (!found)
    {
        printf("\nPerson not found.\n");
    }

    printf("\nPress any key to return to the main menu.");
    getch();
}

// END OF PROGRAM