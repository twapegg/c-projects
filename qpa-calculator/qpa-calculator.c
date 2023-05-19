#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node *nodeptr;
typedef struct node
{
    char subject[50];
    float units;
    float grade;
    float wgpa;
    nodeptr next;
} node;

int menu();
void addSubject(nodeptr *);
void displaySubjects(nodeptr);
void editSubject(nodeptr *);
void calculateQPA(nodeptr *);

int main()
{
    nodeptr head = NULL;
    char choice;

    do
    {
        choice = menu();
        switch (choice)
        {
        case '1':
            addSubject(&head);
            printf("\nSubject added successfully. ");
            getch();
            break;
        case '2':
            editSubject(&head);
            printf("\nPress any key to continue. ");
            getch();
            break;
        case '4':
            displaySubjects(head);
            printf("\nPress any key to continue. ");
            getch();
            break;
        case '5':
            calculateQPA(&head);
            printf("\nPress any key to continue. ");
            getch();
            break;
        }
    } while (choice != 6);
}

int menu()
{
    char choice;

    system("cls");

    printf("QPA Calculator");
    printf("\nSelect an Option:");
    printf("\n1. Add subject");
    printf("\n2. Edit subject");
    printf("\n3. Remove subject");
    printf("\n4. Display all subjects");
    printf("\n5. Calculate for QPA");

    do
    {
        printf("\nEnter option: ");
        scanf(" %c", &choice);

        if (!isdigit(choice))
        {
            printf("\nInvalid option. Try again.");
        }
        else if (choice < '1' || choice > '5')
        {
            printf("\nInvalid option. Try again.");
        }

    } while (!isdigit(choice) || choice < '1' || choice > '6');

    return choice;
}

void addSubject(nodeptr *h)
{
    nodeptr p = (nodeptr)malloc(sizeof(node));

    char tempStr[50];

    fflush(stdin);

    system("cls");
    printf("Adding Subject... ");
    printf("\n-----------------------");
    do
    {
        printf("\nEnter subject: ");
        gets(tempStr);
        if (strlen(tempStr) <= 0)
        {
            printf("Please add a name for the subject.");
        }
    } while (strlen(tempStr) <= 0);

    strcpy(p->subject, tempStr);

    printf("Enter no. of units: ");
    scanf("%f", &p->units);

    printf("Enter grade: ");
    scanf("%f", &p->grade);

    // Getting the wgpa
    p->wgpa = p->units * p->grade;

    printf("\n-----------------------");
    p->next = *h;
    *h = p;
}

void editSubject(nodeptr *h)
{
    // display subjects labeled with numbers
    system("cls");

    if (h == NULL)
    {
        printf("There are currently no subjects to display.\n");
        return;
    }

    int count = 0;
    nodeptr temp = *h;
    printf("Displaying subjects...");
    printf("\n------------------------------------------------------------");
    printf("\n%-23s %-20s %-20s %-20s\n", "Subjects", "Units", "Grades", "WGPA");
    while (temp != NULL)
    {
        printf("%d. %-20s %-20.2f %-20.2f %-20.f\n", count + 1, temp->subject, temp->units, temp->grade, temp->wgpa);
        count++;

        temp = temp->next;
    }
    printf("\n------------------------------------------------------------");
    // ask which subject to edit
    int choice;
    int traverse;

    printf("\nSelect a subject to edit: ");
    scanf("%d", &choice);
    traverse = choice - 1;

    // ask which part of the subject to edit

    // if user enters 1, then refer to the current head of the list
    // if more than 1, go down the node depending on the
    nodeptr current = *h;
    // traverse to the node of that subject
    for (int i = 0; i < traverse; i++)
    {
        current = current->next;
    }

    // Display subject to be edited
    system("cls");
    printf("Subject to be edited...");
    printf("\n----------------------------------------------------------------------");
    printf("\n%-20s %-20s %-20s \n", "Subject", "Units", "Grade");
    printf("%-20s %-20.2f %-20.2f\n", current->subject, current->units, current->grade);
    printf("\n----------------------------------------------------------------------");

    char tempStr[20];
    fflush(stdin);

    printf("\nUpdate subject name: ");
    gets(tempStr);
    strcpy(current->subject, tempStr);

    printf("Update subject no. of units: ");
    scanf("%f", &current->units);

    printf("Update subject grade: ");
    scanf("%f", &current->grade);

    printf("\nUpdated subject...");
    printf("\n----------------------------------------------------------------------");
    printf("\n%-20s %-20s %-20s \n", "Subject", "Units", "Grade");
    printf("%-20s %-20.2f %-20.2f\n", current->subject, current->units, current->grade);
    printf("\n----------------------------------------------------------------------");

    current->wgpa = current->units * current->grade;
}

void displaySubjects(nodeptr h)
{
    system("cls");

    if (h == NULL)
    {
        printf("There are currently no subjects to display.\n");
        return;
    }

    nodeptr temp = h;
    printf("Displaying subjects...");
    printf("\n----------------------------------------------------------------------");
    printf("\n%-20s %-20s %-20s %-20s\n", "Subjects", "Units", "Grades", "WGPA");
    while (temp != NULL)
    {
        printf("%-20s %-20.2f %-20.2f %-20.2f\n", temp->subject, temp->units, temp->grade, temp->wgpa);
        temp = temp->next;
    }
    printf("\n----------------------------------------------------------------------");
}

void calculateQPA(nodeptr *h)
{
    system("cls");
    // Display subjects first:
    nodeptr temp = *h;
    int count;
    printf("Displaying subjects...");
    printf("\n----------------------------------------------------------------------");
    printf("\n%-20s %-20s %-20s %-20s\n", "Subjects", "Units", "Grades", "WGPA");
    while (temp != NULL)
    {
        printf("%-20s %-20.2f %-20.2f %-20.2f\n", temp->subject, temp->units, temp->grade, temp->wgpa);
        count++;
        temp = temp->next;
    }
    printf("\n----------------------------------------------------------------------");
    // starting from the head:
    nodeptr current = *h;
    float totalUnits = 0;
    float totalGrades = 0;
    float totalWGPA = 0;
    float QPA;
    while (current != NULL)
    {
        // multiply units and grades of each sub to get wgpa
        totalUnits += current->units;
        totalWGPA += current->wgpa;
        totalGrades += current->grade;

        current = current->next;
    }
    // divide total no of units and total wgpa to get qpa
    QPA = totalWGPA / totalUnits;

    printf("\n\nQPA Calculation");
    printf("\n----------------------------------------------------------------------\n");
    printf("%-20s %-20s %-20s %-20s\n", "Total Subjects:", "Total Units:", "Total Grades:", "Total WGPA:");
    printf("%-20d %-20.1f %-20.1f %-20.1f\n", count, totalUnits, totalGrades, totalWGPA);
    printf("\n----------------------------------------------------------------------");
    printf("\nQPA: %.2f\n", QPA);
}
