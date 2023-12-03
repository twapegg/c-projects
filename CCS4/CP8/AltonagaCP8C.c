// Name: John Stanley T. Altonaga
// Date Created: 12/3/2023 10:02 AM
// Date Finished: 12/3/2023 9:44 PM 
/* Description: This program is a BMI calculator implemented with a binary search tree (BST).
    It can add, delete, search, and display the elements of the BST. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
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
    node left;
    node right;
} Person;

void createTree(node *root, bool *isCreated);
bool isEmpty(node *root);
void inOrder(node *root);
node insert(node *root, node *newNode);
node delete(node *root, char *lastName);
node search(node *root, char *firstName, char *lastName);
void findMinMax(node *root);

int menu(void);
char *categoryBMI(float bmi);

void dataEntry(node *root);
void dataSearchByName(node *root);
void dataDeleteByName(node *root);
void dataDisplay(node *root);

int main(void)
{
    node root = NULL;
    bool isCreated = false;
    int choice;

    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            createTree(&root, &isCreated);
            break;
        case 2:
            if (!isCreated)
            {
                printf("Tree is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataEntry(&root);
            break;
        case 3:
            if (!isCreated)
            {
                printf("Tree is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataSearchByName(&root);
            break;
        case 4:
            if (!isCreated)
            {
                printf("Tree is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataDeleteByName(&root);
            break;
        case 5:
            if (!isCreated)
            {
                printf("Tree is not created. Press any key to continue.\n");
                getch();
                break;
            }
            dataDisplay(&root);
            break;
        case 6:
            if (!isCreated)
            {
                printf("Tree is not created. Press any key to continue.\n");
                getch();
                break;
            }
            findMinMax(&root);
            break;
        case 7:
            printf("Exiting the program...");
            break;
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
        printf("[1] Create Tree\n");
        printf("[2] Add an element\n");
        printf("[3] Search an element\n");
        printf("[4] Delete an element\n");
        printf("[5] Display all elements\n");
        printf("[6] Find minimum and maximum elements\n");
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

/*  function to create tree
    @param (node *) root
    @param (bool *) isCreated
*/
void createTree(node *root, bool *isCreated)
{
    // if tree is already created and has existing elements
    if (*isCreated && !isEmpty(root))
    {
        printf("Tree has existing elements. Do you want to reset the tree? (y/n): ");

        char choice;
        do
        {
            scanf(" %c", &choice);
            choice = tolower(choice);
            if (choice == 'y')
            {
                *root = NULL;
                printf("The tree has been reset. Press any key to continue.");
                getch();
                return;
            }
            else if (choice == 'n')
            {
                printf("The tree has not been reset. Press any key to continue.");
                getch();
                return;
            }
            else
            {
                printf("Invalid option. Please enter a valid option.\n");
            }
        } while (choice != 'y' && choice != 'n');
    }

    // if tree is already created
    if (*isCreated)
    {
        printf("Tree is already created. Press any key to continue.");
        getch();
        return;
    }

    // else, create tree
    *root = NULL;
    *isCreated = true;
    printf("The tree has been created. Press any key to continue.");
    getch();
    return;
}

/*  function to check if tree is empty
    @param (node *) root
    @returns (bool) isEmpty
*/
bool isEmpty(node *root)
{
    // if root is NULL, then tree is empty
    return (*root == NULL);
}

/*  function to add element to tree, names are capitalized
    @param (node *) root
*/
void dataEntry(node *root)
{
    node temp = *root;
    node newNode = malloc(sizeof(Person));

    // if malloc fails, exit program
    if (newNode == NULL)
    {
        printf("Malloc failed. Exiting program...\n");
        exit(1);
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    system("cls");
    fflush(stdin); // clear input buffer
    bool checkDuplicate = false;

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strcspn(tempFirstName, "\n")] = '\0'; // remove newline character
    strcpy(newNode->firstName, strupr(tempFirstName));

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strcspn(tempLastName, "\n")] = '\0'; // remove newline character
    strcpy(newNode->lastName, strupr(tempLastName));

    if (!isEmpty(&temp))
    {
        node duplicate = search(&temp, newNode->firstName, newNode->lastName);
        if (duplicate != NULL)
        {
            printf("The data already exists. Press any key to continue.");
            getch();
            return;
        }
    }

    printf("Enter height (in cm): ");
    scanf("%f", &newNode->height);

    printf("Enter weight (in lbs): ");
    scanf("%f", &newNode->weight);

    newNode->height /= 100;                                               // convert cm to m
    newNode->weight *= 0.453592;                                          // convert lbs to kg
    newNode->bmi = newNode->weight / (newNode->height * newNode->height); // calculate bmi
    strcpy(newNode->category, categoryBMI(newNode->bmi));                 // get category
    newNode->left = newNode->right = NULL;                                // set pointers to null;

    // add element to tree
    temp = insert(&temp, &newNode);
    *root = temp;

    printf("The data has been added. Press any key to continue.");
    getch();
    return;
}

/*  function to insert element to tree
    @param (node *) root
    @param (node *) newNode
    @returns (node) temp
*/
node insert(node *root, node *newNode)
{
    node temp = *root;
    // if tree is empty, return newNode
    if (temp == NULL)
    {
        temp = *newNode;
        return temp;
    }

    // if tree is not empty, traverse tree
    // compare last names first
    if (strcmp(temp->lastName, (*newNode)->lastName) > 0)
    {
        temp->left = insert(&temp->left, newNode);
    }
    else if (strcmp(temp->lastName, (*newNode)->lastName) < 0)
    {
        temp->right = insert(&temp->right, newNode);
    }
    else
    {
        // if last names are equal, compare first names
        if (strcmp(temp->firstName, (*newNode)->firstName) > 0)
        {
            temp->left = insert(&temp->left, newNode);
        }
        else if (strcmp(temp->firstName, (*newNode)->firstName) < 0)
        {
            temp->right = insert(&temp->right, newNode);
        }
    }
    return temp;
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
    else if (bmi >= 18.5 && bmi < 25)
    {
        return "Normal";
    }
    else if (bmi >= 25 && bmi < 30)
    {
        return "Overweight";
    }
    else
    {
        return "Obese";
    }
}

/*  function to search element in tree
    @param (node *) root
    @param (char *) firstName
    @param (char *) lastName
    @returns (node) temp
*/
node search(node *root, char *firstName, char *lastName)
{
    node temp = *root;
    if (temp == NULL)
    {
        return temp;
    }

    if (strcmpi(temp->lastName, lastName) > 0)
    {
        temp = search(&temp->left, firstName, lastName);
    }
    else if (strcmpi(temp->lastName, lastName) < 0)
    {
        temp = search(&temp->right, firstName, lastName);
    }
    else
    {
        if (strcmpi(temp->firstName, firstName) > 0)
        {
            temp = search(&temp->left, firstName, lastName);
        }
        else if (strcmpi(temp->firstName, firstName) < 0)
        {
            temp = search(&temp->right, firstName, lastName);
        }
    }
    return temp;
}

/*  function to display elements of tree in order
    @param (node *) root
*/
void inOrder(node *root)
{
    node temp = *root;
    if (temp == NULL)
        return;
    // traverse the left subtree
    inOrder(&temp->left);
    // visit the root
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);
    // traverse the right subtree
    inOrder(&temp->right);
}

/*  function to display elements of tree in pre order
    @param (node *) root
*/
void dataDisplay(node *root)
{
    node temp = *root;

    // if tree is empty, display message
    if (isEmpty(&temp))
    {
        printf("The tree is empty. Press any key to continue.");
        getch();
        return;
    }
    // else, display elements
    system("cls");
    printf("Displaying all elements...\n");
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    inOrder(&temp);
    printf("\nPress any key to continue.\n");
    getch();
    return;
}

/*  function to search element in tree
    @param (node *) root
*/
void dataSearchByName(node *root)
{
    node temp = *root;
    if (isEmpty(&temp))
    {
        printf("The tree is empty. Press any key to continue.");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    system("cls");
    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strcspn(tempFirstName, "\n")] = '\0'; // remove newline character

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strcspn(tempLastName, "\n")] = '\0'; // remove newline character

    node found = search(&temp, tempFirstName, tempLastName);
    if (found == NULL)
    {
        printf("The data is not found. Press any key to continue.");
        getch();
        return;
    }

    printf("\nRecord found! Displaying data...\n");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", found->firstName, found->lastName, found->height, found->weight, found->bmi, found->category);

    printf("\nPress any key to continue.\n");
    getch();
    return;
}

/*  function to delete element in tree
    @param (node *) root
    @returns (node) temp
*/
node delete(node *root, char *lastName)
{
    node temp = *root;

    // if tree is empty, return NULL
    if (temp == NULL)
    {
        return temp;
    }

    // if less, go to left subtree
    if (strcmp(temp->lastName, lastName) > 0)
    {
        temp->left = delete (&temp->left, lastName);
        return temp;
    }
    // if greater, go to right subtree
    else if (strcmp(temp->lastName, lastName) < 0)
    {
        temp->right = delete (&temp->right, lastName);
        return temp;
    }

    // if left child is NULL
    if (temp->left == NULL)
    {
        node temp2 = temp->right;
        free(temp);
        return temp2;
    }
    // if right child is NULL
    else if (temp->right == NULL)
    {
        node temp2 = temp->left;
        free(temp);
        return temp2;
    }

    // if both children are not NULL
    else
    {
        node succParent = temp;

        // find in-order successor
        node succ = temp->right;
        while (succ->left != NULL)
        {
            succParent = succ;
            succ = succ->left;
        }

        // delete successor
        if (succParent != temp)
        {
            succParent->left = succ->right;
        }
        else
        {
            succParent->right = succ->right;
        }

        // copy data
        strcpy(temp->firstName, succ->firstName);
        strcpy(temp->lastName, succ->lastName);
        temp->height = succ->height;
        temp->weight = succ->weight;
        temp->bmi = succ->bmi;
        strcpy(temp->category, succ->category);

        free(succ);
        return temp;
    }

    return temp;
}

/*  function to delete element in tree
    @param (node *) root
*/
void dataDeleteByName(node *root)
{
    node temp = *root;
    if (isEmpty(&temp))
    {
        printf("The tree is empty. Press any key to continue.");
        getch();
        return;
    }

    char tempFirstName[TEXTSIZE];
    char tempLastName[TEXTSIZE];

    system("cls");
    fflush(stdin); // clear input buffer

    printf("Enter first name: ");
    fgets(tempFirstName, TEXTSIZE, stdin);
    tempFirstName[strcspn(tempFirstName, "\n")] = '\0'; // remove newline character

    printf("Enter last name: ");
    fgets(tempLastName, TEXTSIZE, stdin);
    tempLastName[strcspn(tempLastName, "\n")] = '\0'; // remove newline character

    node found = search(&temp, tempFirstName, tempLastName);
    if (found == NULL)
    {
        printf("The data is not found. Press any key to continue.");
        getch();
        return;
    }

    printf("\nRecord found! Displaying data...\n");

    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", found->firstName, found->lastName, found->height, found->weight, found->bmi, found->category);

    printf("\nAre you sure you want to delete this data? (y/n): ");
    char choice;
    do
    {
        scanf(" %c", &choice);
        choice = tolower(choice);
        if (choice == 'y')
        {
            temp = delete (&temp, strupr(tempLastName));
            *root = temp;
            printf("The data has been deleted. Press any key to continue.");
            getch();
            break;
        }
        else if (choice == 'n')
        {
            printf("The data has not been deleted. Press any key to continue.");
            getch();
            return;
        }
        else
        {
            printf("Invalid option. Please enter a valid option.\n");
        }
    } while (choice != 'y' && choice != 'n');

    return;
}

/*  function to find minimum and maximum elements in tree
    @param (node *) root
    @param (bool) isCreated
*/
void findMinMax(node *root)
{
    node temp = *root;
    if (isEmpty(&temp))
    {
        printf("The tree is empty. Press any key to continue.");
        getch();
        return;
    }

    system("cls");
    printf("Finding minimum and maximum elements...\n");

    // find minimum
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    printf("\nMinimum element:\n");
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);

    // find maximum
    temp = *root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    printf("\nMaximum element:\n");
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "First Name", "Last Name", "Height (m)", "Weight (kg)", "BMI", "BMI Category");
    printf("%-20s%-20s%-20.2f%-20.2f%-20.2f%-20s\n", temp->firstName, temp->lastName, temp->height, temp->weight, temp->bmi, temp->category);

    printf("\nPress any key to continue.\n");
    getch();
    return;
}