// Name: John Stanley T. Altonaga
// Date Created: 9/10/2023
// Date Finished: 9/14/2023
// Description: This program is a BMI calculator implemented with a doubly-linked list. It can insert, search, display, and delete records.

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
    node prev;
    node next;
} Person;

char menu(void);
void dataEntry(node *head);
int duplicateNameCheck(node *head, char *firstName, char *lastName);
char *categoryBMI(float bmi);
void dataDisplay(node *head);
void dataDisplayByName(node *head);
void dataEditByName(node *head);
void dataDeleteByName(node *head);

int main(void)
{
    node head = NULL;
    char choice;

    do
    {
        choice = menu(); // display menu and get choice

        switch (choice)
        {
        case 'a':
            dataEntry(&head);
            puts("Data entry successful. Press any key to continue.");
            getch();
            break;
        case 'b':
            if (head == NULL) // check if there is data to display
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
            if (head == NULL) // check if there is data to display
            {
                puts("No data to display. Press any key to continue.");
                getch();
                break;
            }
            dataDisplayByName(&head);
            puts("\nPress any key to continue.");
            getch();
            break;
        case 'd':
            if (head == NULL) // check if there is data to edit
            {
                puts("No data to edit. Press any key to continue.");
                getch();
                break;
            }
            dataEditByName(&head);
            puts("\nPress any key to continue.");
            getch();
            break;
        case 'e':
            if (head == NULL) // check if there is data to delete
            {
                puts("No data to delete. Press any key to continue.");
                getch();
                break;
            }
            dataDeleteByName(&head);
            puts("\nPress any key to continue.");
            getch();
            break;
        case 'f':
            puts("Exiting program...");
            break;
        default:
            puts("Invalid input. Please try again.");
            puts("Press any key to continue.");
            getch();
            break;
        }

    } while (choice != 'f');
    return 0;
}

/*  function to display menu and get choice
    @returns user's choice (via input)
*/
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
        printf("d. Edit data by name\n");
        printf("e. Delete data by name\n");
        printf("f. Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        choice = tolower(choice); // convert to lowercase

        // trap invalid input
        if (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd' && choice != 'e' && choice != 'f')
        {
            printf("Invalid input. Please try again.\n");
            printf("Press any key to continue.");
            getch();
        }
    } while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd' && choice != 'e' && choice != 'f');

    return choice;
}

/*  function to add a node and input data at the END of the linked list
    @param {*head} pointer to the head node
*/
void dataEntry(node *head)
{
    // Create a new node
    node newNode = (node)malloc(sizeof(Person));

    // check if memory allocation failed
    if (newNode == NULL)
    {
        printf("Memory allocation failed. Exiting program.\n");
        exit(1);
    }

    int flag; // flag to check if name already exists

    fflush(stdin); // clear input buffer

    // ask for data, will loop if name already exists
    do
    {
        flag = 0;
        system("cls"); // clear screen

        printf("Enter first name: ");
        gets(newNode->firstName);

        printf("Enter last name: ");
        gets(newNode->lastName);

        // check if list is not empty
        if (*head != NULL)
        {
            // function call will return 1 if name already exists, else 0
            flag = duplicateNameCheck(head, newNode->firstName, newNode->lastName);
            if (flag == 1)
            {
                printf("Name already exists. Please enter a different name.\n");
                printf("Press any key to continue.");
                getch();
            }
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

    // make next of new node as NULL
    newNode->next = NULL;

    // if list is empty, make new node as head
    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    // else, traverse till the last node
    node tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    tail->next = newNode; // change next of last node to new node
    newNode->prev = tail; // make last node as previous of new node

    return;
}

/*  function to check for existing names
    @param {*head} pointer to head node
    @param {*firstName} string pointer to first name
    @param {*lastName} string pointer to last name
    @return 1 if duplicate is found, else 0
 */
int duplicateNameCheck(node *head, char *firstName, char *lastName)
{
    node temp = *head;

    while (temp != NULL)
    {
        // compare first and last name
        if (strcmpi(firstName, temp->firstName) == 0 && strcmpi(lastName, temp->lastName) == 0)
        {
            return 1; // duplicate is found
        }
        temp = temp->next;
    }

    return 0; // no duplicate
}

/*  function to get BMI category
    @param {bmi} BMI value
    @return (string) BMI category
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

/*  function to display data
    @param {*head} pointer to head node
*/
void dataDisplay(node *head)
{
    system("cls"); // clear screen

    int count = 0; // counter for number of records

    // display data in ascending order
    printf("Displaying data in ascending order...\n");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    node temp = *head;
    node tail; // pointer to tail node
    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            // stores tail node for descending order
            tail = temp;
        }
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
        count++;
        temp = temp->next;
    }

    // display data in descending order
    printf("\nDisplaying data in descending order...\n");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");

    temp = tail;
    while (temp != NULL)
    {
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
        temp = temp->prev;
    }

    printf("\nNumber of records: %d\n", count);

    return;
}

/*  function to search and display data by name
    @param {*head} pointer to head node
*/
void dataDisplayByName(node *head)
{
    char tempFirstName[50];
    char tempLastName[50];
    int flag = 0;

    fflush(stdin); // clear input buffer

    system("cls"); // clear screen

    // ask for name
    printf("Enter first name: ");
    gets(tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);

    node temp = *head;
    // traverse list
    while (temp != NULL)
    {
        // if name is found, display data
        if (strcmpi(tempFirstName, temp->firstName) == 0 && strcmpi(tempLastName, temp->lastName) == 0)
        {
            system("cls"); // clear screen
            printf("Record found! Displaying data...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

            // display neighboring data
            if (temp->prev != NULL)
            {
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->prev->firstName), strupr(temp->prev->lastName), temp->prev->height, temp->prev->weight, temp->prev->bmi, temp->prev->category);
            }
            else
            {
                printf("No previous record.\n");
            }
            if (temp->next != NULL)
            {
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->next->firstName), strupr(temp->next->lastName), temp->next->height, temp->next->weight, temp->next->bmi, temp->next->category);
            }
            else
            {
                printf("No next record.\n");
            }

            return;
        }
        temp = temp->next;
    }

    // if name is not found, display error message
    printf("\nName does not exist. Returning to main menu...\n");

    return;
}

/*  function to search and edit data by name
    @param {*head} pointer to head node
*/
void dataEditByName(node *head)
{
    char tempFirstName[50];
    char tempLastName[50];
    int flag = 0;

    fflush(stdin); // clear input buffer

    system("cls"); // clear screen

    // ask for name
    printf("Enter first name: ");
    gets(tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);

    node temp = *head;
    // traverse list
    while (temp != NULL)
    {
        // if name is found, display data
        if (strcmpi(tempFirstName, temp->firstName) == 0 && strcmpi(tempLastName, temp->lastName) == 0)
        {
            system("cls"); // clear screen
            printf("Record found! Displaying data...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

            char choice;

            do
            {
                printf("\nDo you want to edit this record? (y/n): ");
                scanf(" %c", &choice);

                choice = tolower(choice); // convert to lowercase

                // trap invalid input
                if (choice != 'y' && choice != 'n')
                {
                    printf("Invalid input. Please try again.\n");
                    printf("Press any key to continue.");
                    getch();
                }
            } while (choice != 'y' && choice != 'n');

            switch (choice)
            {
            case 'y':
                // ask for data
                printf("Enter new height (in cm): ");
                scanf("%f", &temp->height);

                printf("Enter new weight (in lbs): ");
                scanf("%f", &temp->weight);

                // convert pounds to kg
                temp->weight = temp->weight * 0.453592;

                // convert cm to m
                temp->height = temp->height / 100;

                // calculate bmi
                temp->bmi = temp->weight / (temp->height * temp->height);

                // get bmi category
                strcpy(temp->category, categoryBMI(temp->bmi));

                system("cls"); // clear screen
                printf("Record updated successfully. Displaying record...\n");
                printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
                break;

            case 'n':
                system("cls"); // clear screen
                printf("Record not updated. Displaying record...\n");
                printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
                break;
            }

            return;
        }
        temp = temp->next;
    }

    // if name is not found, display error message
    printf("\nName does not exist. Returning to main menu...\n");
    return;
}

/*  function to search and delete data by name
    @param {*head} pointer to head node
*/
void dataDeleteByName(node *head)
{
    char tempFirstName[50];
    char tempLastName[50];
    int flag = 0;

    fflush(stdin); // clear input buffer

    system("cls"); // clear screen

    // ask for name
    printf("Enter first name: ");
    gets(tempFirstName);

    printf("Enter last name: ");
    gets(tempLastName);

    node temp = *head;
    // traverse list
    while (temp != NULL)
    {
        // if name is found, display data
        if (strcmpi(tempFirstName, temp->firstName) == 0 && strcmpi(tempLastName, temp->lastName) == 0)
        {
            system("cls"); // clear screen
            printf("Record found! Displaying data...\n");
            printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
            printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);

            char choice;

            do
            {
                printf("\nDo you want to delete this record? (y/n): ");
                scanf(" %c", &choice);

                choice = tolower(choice); // convert to lowercase

                // trap invalid input
                if (choice != 'y' && choice != 'n')
                {
                    printf("Invalid input. Please try again.\n");
                    printf("Press any key to continue.");
                    getch();
                }
            } while (choice != 'y' && choice != 'n');

            switch (choice)
            {
            case 'y':
                // if node to be deleted is head node
                if (*head == temp)
                {
                    *head = temp->next; // change head
                }

                // if node to be deleted is not last node
                if (temp->next != NULL)
                {
                    temp->next->prev = temp->prev; // change next node's previous
                }

                // if node to be deleted is not first node
                if (temp->prev != NULL)
                {
                    temp->prev->next = temp->next; // change previous node's next
                }

                // point left and right pointers to NULL
                temp->prev = NULL;
                temp->next = NULL;

                free(temp); // free memory

                system("cls"); // clear screen
                printf("Record deleted successfully.");
                break;

            case 'n':
                system("cls"); // clear screen

                printf("Record not deleted. Displaying record...\n");
                printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
                printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", strupr(temp->firstName), strupr(temp->lastName), temp->height, temp->weight, temp->bmi, temp->category);
                break;
            }

            return;
        }

        temp = temp->next;
    }

    // if name is not found, display error message
    printf("\nName does not exist. Returning to main menu...\n");
    return;
}
