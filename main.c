//-----------------------------------------------------------------------------------
//                                    BUGGY
//-----------------------------------------------------------------------------------
/*
File: main.c

Description:
    - This program allows for grocery shopping data to be created, stored, and used
      by the user.

To Do List:
    - Add 'Quantity' to product characteristics.
    - Store environment in data file.
    - Load environment from data file.
    - Make grocery list.
    - Save grocery list.
    - Load grocery list.
*/
//-----------------------------------------------------------------------------------
// Imported Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//-----------------------------------------------------------------------------------
// Structures
struct product{
    int id;         // Each product will have an id specified to it for reference
    char *name;     // Name of the product
    float price;    // Price of the product
    char *store;    // Store the product was brought from
    struct product *nextProduct;    // Pointer to next product
};
//-----------------------------------------------------------------------------------
// Type Definitions
typedef struct product node;    // node
typedef node *nodePtr;          // *nodePtr
//-----------------------------------------------------------------------------------
// Function Prototypes
void printTitle( void );
int mainMenu( void );
int editMenu( void );
void printList( nodePtr root );
void appendNode( nodePtr *root, int nid, char *nname, float nprice, char *nstore );
void initializeList( nodePtr *root );
int isEmpty( nodePtr root );
float sumList( nodePtr *root );
void deleteNode( nodePtr *root, int id );
void changeNode( nodePtr *root, int nid, char *nname, float nprice, char *nstore );
void saveEnvironment( nodePtr *root );
void loadEnvironment( nodePtr *root );
//-----------------------------------------------------------------------------------
/*
Function: main

Description:
    - Primary source of control

Things to Do:
    - Error check input parameters from user.
    - Allow for space input in strings.
*/
int main( void )
{
    bool on = true;         // Switch to false to end state machine and program
    int menuChoice = 1;     // Variable in which user interacts with main menu
    int menuChoice1 = 0;    // Variable in which user interacts with edit menu
    nodePtr root = NULL;    // Linked List root pointer

    // Used to allow the user to set structure parameters
    int idKey = 0;
    char nameKey[ 20 ];
    float priceKey = 0;
    char storeKey[ 20 ];

    // Main Loop / State Machine ------------
    while( on  == true ) {
        switch( menuChoice ) {
        // Main Menu
        case 1:
            menuChoice = mainMenu();
            switch( menuChoice ) {
            // View List
            case 1:
                printList( root );
                break;
            // Edit Item
            case 2:
                menuChoice1 = editMenu();
                switch( menuChoice1 ) {
                    // Add Item
                    case 1:
                        printTitle();
                        printf( "\nPRODUCT ID\n--> " );
                        scanf( "%d", &idKey );

                        printTitle();
                        printf( "\nPRODUCT NAME\n--> " );
                        scanf( "%s", nameKey );

                        printTitle();
                        printf( "\nPRODUCT PRICE\n--> $" );
                        scanf( "%f", &priceKey );

                        printTitle();
                        printf( "\nPRODUCT STORE\n--> " );
                        scanf( "%s", storeKey );

                        appendNode( &root, idKey, nameKey, priceKey, storeKey );
                        menuChoice = 1;
                        break;
                    // Change Item
                    case 2:
                        printTitle();
                        printf( "\nPRODUCT ID\n--> " );
                        scanf( "%d", &idKey );

                        printTitle();
                        printf( "\nPRODUCT NAME\n--> " );
                        scanf( "%s", nameKey );

                        printTitle();
                        printf( "\nPRODUCT PRICE\n--> $" );
                        scanf( "%f", &priceKey );

                        printTitle();
                        printf( "\nPRODUCT STORE\n--> " );
                        scanf( "%s", storeKey );

                        changeNode( &root, idKey, nameKey, priceKey, storeKey );
                        menuChoice = 1;
                        break;
                    // Delete Item
                    case 3:
                        printTitle();
                        printf( "\nPRODUCT ID\n--> " );
                        scanf( "%d", &idKey );
                        deleteNode( &root, idKey );
                        menuChoice = 1;
                        break;
                    // Back to Main Menu
                    case 0:
                        menuChoice = 1;
                        break;
                } // END switch
                break;
            // Save Environment
            case 3:
                saveEnvironment( &root );
                menuChoice = 1;
                break;
            // Load Environment
            case 4:
                loadEnvironment( &root );
                menuChoice = 1;
                break;
            // Insert Sample List
            case 6:
                initializeList( &root );
                menuChoice = 1;
                break;
            // Exit Program
            case 0:
                on = false;
                break;
            default:
                menuChoice = 1;
            } // END switch
            break;
        // Exit Program
        case 0:
            on = false;
            break;
        default:
            // The main menu is the default menu choice
            menuChoice = 1;
        } // END switch
    } // END while

    return 0;
}
//-----------------------------------------------------------------------------------
/*
Function: mainMenu
Description: Prints the Main Menu and returns the user's choice from the menu
Input Variables: None
Intermediate Variables:
    - menuChoice  := User's choice to the menu.
Return:
    - (int) menuChoice
*/
int mainMenu( void )
{
    int menuChoice;
    printTitle();
    puts( "MAIN MENU" );
    puts( "\t1 >> VIEW LIST" );
    puts( "\t2 >> EDIT ITEM" );
    puts( "\t3 >> SAVE ENVIRONMENT" );
    puts( "\t4 >> LOAD ENVIRONMENT" );
    puts( "\t5 >> GROCERY LIST" );
    puts( "\t6 >> TEST LIST" );
    puts( "\t0 >> EXIT" );
    printf( "--> " );
    scanf( "%d", &menuChoice );
    return menuChoice;
} // END FUNCTION printMainMenu
//-----------------------------------------------------------------------------------
/*
Function: editMenu
Description: Prints edit menu and returns the user's choice.
Input Variables: None
Intermediate Variables:
    - menuChoice    := User's choice to the menu
Return:
    - (int) menuChoice
*/
int editMenu( void )
{
    int menuChoice;
    printTitle();
    puts( "EDIT MENU" );
    puts( "\t1 >> ADD ITEM" );
    puts( "\t2 >> CHANGE ITEM" );
    puts( "\t3 >> DELETE ITEM" );
    puts( "\t0 >> BACK TO MAIN MENU" );
    printf( "--> " );
    scanf( "%d", &menuChoice );
    return menuChoice;
} // END FUNCTION editMenu
//-----------------------------------------------------------------------------------
/*
Function: printTitle
Description:
    - Clears screen and prints the buggy title at the top of the screen.
Variables: None
Return: None
*/
void printTitle( void )
{
    // Windows: "cls"
    // Linux: "clear"
    system( "cls" );
    puts( "-----------------------------------------------------------" );
    puts( "                       BUGGY 1.0                           " );
    puts( "-----------------------------------------------------------" );
} // END FUNCTION printTitle
//-----------------------------------------------------------------------------------
/*
Function: printList

Description:
    - Prints the information from each node in the linked list connected to the
      input <root>.

Input Variables:
    - Root to linked list

Intermediate Variables:
    - junk  := Throw away string, used to pause program execution.
*/
void printList( nodePtr root )
{
    printTitle();
    char junk;
    nodePtr x = root;
    if( isEmpty( x ) ){     // If the list connected to <root> is empty.
        puts( "NO DATA" );
    } else {                // If there is one or more nodes connected to <root>.
        // Table Labels
        puts( "| ID |      NAME       |    PRICE    |        STORE       |" );
        puts( "-----------------------------------------------------------" );

        // Prints each elements in the list connected to <root>.
        while( x != NULL ) {
            printf( "%4d\t%15s\t%12.2f\t%19s\n", x->id, x->name, x->price, x->store );
            x = x->nextProduct;
        } // END while

        // Closes table and prints the sum of the price of all the elements.
        puts( "-----------------------------------------------------------" );
        // printf( "                                             TOTAL : $%.2f", sumList( &root ) );
    } // END if...else
    printf( "\n\nENTER A CHARACTER TO CONTINUE\n--> " );
    scanf( " %c", &junk );
    if( junk == "y" ) { printf( "\n\t\tYESSSSS......\n\n" ); }
} // END FUNCTION printList
//-----------------------------------------------------------------------------------
/*
Function: appendNode

Description:
    - Appends a new node to the end of the list connected to <root>. The new node
      shall have the characteristics as passed in the input variables: <nid>, <nname>,
      <nprice>, and <nstore>.

Inputs Variables:
    - root      := Pointer to root of linked list to be changed.
    - nid       := Id of new product.
    - nname     := Name of new product.
    - nprice    := Price of new product.
    - nstore    := Store in which the new product was brought.

Intermediate Variables:
    - currentPtr    := Primary node of linked list to be operated upon. Will eventually
                       point to the end of the list, and will serve as an insertion
                       point for the newly created node.
    - previousPtr   := Points to the node before the one pointed to by currentPtr.
                       Will allow for the final node in the list to be adjusted to
                       point to the newly created node.
    - newPtr        := Newly created node to be appended to the end of the list.

Things to do:
    - Handle the case, if there is no memory available to allocate for the new node.
*/
void appendNode( nodePtr *root, int nid, char *nname, float nprice, char *nstore )
{
    // Creates pointers to be operated upon.
    nodePtr currentPtr = *root;
    nodePtr previousPtr;
    // Allocates the memory for the newly created node.
    nodePtr newPtr = malloc( sizeof( node ) );

    // Initialize the characteristics of the newly created node.
    newPtr->id = nid;
    newPtr->price = nprice;
    newPtr->name = malloc( strlen( nname ) + 1 );
    newPtr->store = malloc( strlen( nstore ) + 1 );
    strcpy( newPtr->name, nname );
    strcpy( newPtr->store, nstore );

    if( currentPtr == NULL ) {          // If there is no nodes in the list.
        *root = newPtr;
    } else {                            // If there are nodes in the list.
        // While current pointer does not point to the end of the list
        while( currentPtr != NULL ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextProduct;
        } // END while

        // Points the last node in the list towards the newly created node.
        previousPtr->nextProduct = newPtr;
        // Points the newly created node towards the NULL pointed to by the
        // current pointer.
        newPtr->nextProduct = NULL;
    } // END if...else
} // END FUNCTION appendNode
//-----------------------------------------------------------------------------------
void initializeList( nodePtr *root )
{
    nodePtr a = malloc( sizeof( node ) );
    nodePtr b = malloc( sizeof( node ) );
    nodePtr c = malloc( sizeof( node ) );
    nodePtr d = malloc( sizeof( node ) );

    a->id = 100;
    a->name = "Milk";
    a->price = 3.45;
    a->store = "Wal-Mart";
    a->nextProduct = b;

    b->id = 200;
    b->name = "Eggs";
    b->price = 1.28;
    b->store = "Wal-Mart";
    b->nextProduct = c;

    c->id = 300;
    c->name = "Butter";
    c->price = 4.54;
    c->store = "Lucky's Market";
    c->nextProduct = d;

    d->id = 400;
    d->name = "Bread";
    d->price = 2.11;
    d->store = "Aldis";
    d->nextProduct = NULL;

    *root = a;

} // END FUNCTION initializeList
//-----------------------------------------------------------------------------------
/*
Function: isEmpty

Description:
    - Returns true (1) if there are no nodes connected to <root>. Returns false (0)
      if there are elements connected to <root>.
*/
int isEmpty( nodePtr root ) { return root == NULL; }
//-----------------------------------------------------------------------------------
/*
Function: sumList

Description:
    - Returns the sum of the prices in each and every element connected to <root>.

Input Variables:
    - root      := Pointer to the root of the list to be summed.

Intermediate Variables:
    - currentPtr    := Present location of the list being operated upon.
    - sum           := Sum of all of the prices in the list.

Return:
    - (float) sum
*/
float sumList( nodePtr *root )
{
    nodePtr currentPtr = *root;
    float sum = 0;

    // Sums every element in the list pointed to by <root>.
    while( currentPtr != NULL ) {
        sum += currentPtr->price;
        currentPtr = currentPtr->nextProduct;
    } // END while

    return sum;
} // END FUNCTION sumList
//-----------------------------------------------------------------------------------
/*
Function: deleteNode

Description:
    - Deletes the node with id = nid.
    - If there exists two nodes with the same id, the first will be deleted.

Input Variables:
    - root  := Pointer to the root of the list to be operated upon.
    - nid   := Id of the node to be deleted.

Intermediate Variables:
    - currentPtr    := Current node to be deleted. Will eventually point to the
                       node to be deleted.
    - previousPtr   := Points to the node before the current pointer.
    - tempPtr       := Will point to the node to be deleted, and free the memory
                       pointed to by that node.

Return: None
*/
void deleteNode( nodePtr *root, int nid )
{
    // Creation of pointers used in operation.
    nodePtr currentPtr;
    nodePtr previousPtr;
    nodePtr tempPtr;

    // If the first node in the list has an id equal to the target id (nid).
    if( nid == ( *root )->id ) {
        tempPtr = *root;
        *root = ( *root )->nextProduct;
        free( tempPtr );
    // If the first node does not have an id equal to the target id (nid)
    } else {

        // Initialization of algorithm
        previousPtr = *root;
        currentPtr = ( *root )->nextProduct;

        // While the current pointer does not point to the end of the list or
        // have an id equal to that of the target id (nid).
        while( currentPtr != NULL && currentPtr->id != nid ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextProduct;
        } // END while

        //
        if( currentPtr != NULL ) {
            tempPtr = currentPtr;
            previousPtr->nextProduct = currentPtr->nextProduct;
            free( tempPtr );
        } // END if
    } // END if...else
} // END FUNCTION deleteItem
//-----------------------------------------------------------------------------------
void changeNode( nodePtr *root, int nid, char *nname, float nprice, char *nstore )
{
    nodePtr currentPtr;

    if( nid == ( *root )->id ) {
        ( *root )->name = malloc( strlen( nname ) + 1 );
        ( *root )->price = nprice;
        ( *root )->store = malloc( strlen( nstore ) + 1 );
        strcpy( ( *root )->name, nname );
        strcpy( ( *root )->store, nstore );
    } else {
        currentPtr = ( *root )->nextProduct;

        while( currentPtr != NULL && currentPtr->id != nid ) {
            currentPtr = currentPtr->nextProduct;
        } // END while

        if( currentPtr != NULL ) {
            currentPtr->name = malloc( strlen( nname ) + 1 );
            strcpy( currentPtr->name, nname );
            currentPtr->price = nprice;
            currentPtr->store = malloc( strlen( nstore ) + 1 );
            strcpy( currentPtr->store, nstore );
        } // END if
    } // END if...else

} // END FUNCTION changeNode
//-----------------------------------------------------------------------------------
void saveEnvironment( nodePtr *root )
{
    FILE *fPtr;
    fPtr = fopen( "data.dat", "w" );

    nodePtr currentPtr = *root;

    while( currentPtr != NULL ) {
        fprintf( fPtr, "%d%20s%f%20s\n", currentPtr->id, currentPtr->name, currentPtr->price, currentPtr->store  );
        currentPtr = currentPtr->nextProduct;
    } // END while

    fprintf( fPtr, "%d\t%20s\t%f\t%20s\n", -1, "END", 0.00, "END" );
    fclose( fPtr );
} // END FUNCTION saveEnvironment
//-----------------------------------------------------------------------------------
void loadEnvironment( nodePtr *root )
{
    FILE *fPtr;
    fPtr = fopen( "data.dat", "r" );

    int id = 0;
    char name[ 20 ];
    float price = 0.000;
    char store[ 20 ];

    while( id != -1 ) {
        fscanf( fPtr, "%d\t%20s\t%f\t%20s", &id, name, &price, store );
        appendNode( &root, id, name, price, store );
    } // END while

    fclose( fPtr );
} // END FUNCTION loadEnvironment
//-----------------------------------------------------------------------------------
