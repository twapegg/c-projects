// Name: John Stanley T. Altonaga
// Date Created: 8/17/2023
// Date Finished: 8/20/2023
// Description: This program is a BMI calculator that can store up to 10 records. It can display all records and display records by name.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10

typedef struct person
{
    char firstName[50];
    char lastName[50];
    float weight;
    float height;
    float bmi;
    char category[15];
} Person;

char menu(void);
int dataEntry(Person Records[MAX], int count);
char *categoryBMI(float bmi);
void dataDisplay(Person Records[MAX], int count);
void dataDisplayByName(Person Records[MAX], int count);

int main(void)
{
    int count = 0;
    Person Records[MAX];

    char choice;
    do
    {
        choice = menu(); // display menu and get choice

        switch (choice)
        {
        case 'a':
            if (count == MAX) // check if there is still space for data
            {
                puts("No more space for data. Press any key to continue.");
                getch();
                break;
            }
            count = dataEntry(Records, count);
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
            dataDisplay(Records, count);
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
            dataDisplayByName(Records, count);
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

// function to enter data
int dataEntry(Person Records[MAX], int count)
{
    fflush(stdin); // clear input buffer
    system("cls"); // clear screen

    // ask for data
    printf("Enter first name: ");
    gets(Records[count].firstName);
    strcpy(Records[count].firstName, strupr(Records[count].firstName));

    printf("Enter last name: ");
    gets(Records[count].lastName);
    strcpy(Records[count].lastName, strupr(Records[count].lastName));

    printf("Enter height (in cm): ");
    scanf("%f", &Records[count].height);

    printf("Enter weight (in lbs): ");
    scanf("%f", &Records[count].weight);

    // calculate bmi (convert lbs to kg and centimeters to meters)
    Records[count].bmi = Records[count].weight * 0.453592 / ((Records[count].height / 100) * (Records[count].height / 100));

    // get bmi category
    strcpy(Records[count].category, categoryBMI(Records[count].bmi));

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
void dataDisplay(Person Records[MAX], int count)
{
    system("cls"); // clear screen

    // display data
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (cm)", "Weight (lbs)", "BMI", "BMI Category");

    for (int i = 0; i < count; i++)
    {
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", Records[i].firstName, Records[i].lastName, Records[i].height, Records[i].weight, Records[i].bmi, Records[i].category);
    }
    return;
}

// function to display data by name
void dataDisplayByName(Person Records[MAX], int count)
{

    fflush(stdin); // clear input buffer
    system("cls"); // clear screen

    // temp variable
    char firstName[50];
    char lastName[50];

    // ask for name
    printf("Enter first name: ");
    gets(firstName);

    printf("Enter last name: ");
    gets(lastName);

    int flag = 0;   // flag to check if name is found
    int i;          // will store the index of the record

    // search for name
    for (i = 0; i < count; i++)
    {
        // stricmp is used to compare strings without case sensitivity
        if (stricmp(firstName, Records[i].firstName) == 0 && stricmp(lastName, Records[i].lastName) == 0)
        {
            flag = 1; // set flag to 1 if name is found
            break;
        }
    }

    // display data if name is found
    if (flag == 0)
    {
        printf("\nName not found.\n");
    }
    else
    {
        // the %-20s is used to allot a field width and align the text to the left
        printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (cm)", "Weight (lbs)", "BMI", "BMI Category");
        printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", Records[i].firstName, Records[i].lastName, Records[i].height, Records[i].weight, Records[i].bmi, Records[i].category);
    }
    return;
}
