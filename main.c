//-----------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//-----------------------------------------------------------------------------------
struct product{
    int id;         // Each product will have an id specified to it for reference
    char *name;     // Name of the product
    float price;    // Price of the product
    char *store;    // Store the product was brought from
    struct product *nextProduct;    // Pointer to next product
};
//-----------------------------------------------------------------------------------
typedef struct product node;  // node
typedef node *nodePtr;     // *nodePtr
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
void deleteItem( nodePtr *root, int id );
//-----------------------------------------------------------------------------------
// Function: main
// Description: Primary source of control
int main( void )
{
    bool on = true;
    int menuChoice = 1;
    int menuChoice1 = 0;
    nodePtr root = NULL;

    int idKey = 0;
    char nameKey[ 20 ];
    float priceKey = 0;
    char storeKey[ 20 ];

    // Main Loop ------------
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
                    case 1:
                        printTitle();
                        printf( "\nPRODUCT ID\n--> " );
                        scanf( "%d", &idKey );

                        printTitle();
                        printf( "\nPRODUCT NAME\n--> " );
                        scanf( "%s", &nameKey );

                        printTitle();
                        printf( "\nPRODUCT PRICE\n--> $" );
                        scanf( "%f", &priceKey );

                        printTitle();
                        printf( "\nPRODUCT STORE\n--> " );
                        scanf( "%s", &storeKey );

                        appendNode( &root, idKey, &nameKey, priceKey, &storeKey );
                        break;
                    case 3:
                        printTitle();
                        printf( "\nPRODUCT ID\n--> " );
                        scanf( "%d", &idKey );
                        deleteItem( &root, idKey );
                        break;
                    case 0:
                        menuChoice = 1;
                        break;
                } // END switch

                break;
            // Insert Sample List
            case 6:
                initializeList( &root );
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
// Function: mainMenu
// Description: Prints the Main Menu and returns the user's choice from the menu
// Inputs: None
// Outputs:
//      - menuChoice  := Users choice to the menu.
// Return:
//      - (int) menuChoice
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
void printTitle( void )
{
    system( "cls" );
    puts( "-----------------------------------------------------------" );
    puts( "                       BUGGY 1.0                           " );
    puts( "-----------------------------------------------------------" );
} // END FUNCTION printTitle
//-----------------------------------------------------------------------------------
void printList( nodePtr root )
{
    printTitle();
    char junk;
    nodePtr x = root;
    if( isEmpty( x ) ){
        puts( "NO DATA" );
    } else {
        puts( "| ID |      NAME       |    PRICE    |        STORE       |" );
        puts( "-----------------------------------------------------------" );
        while( x != NULL ) {
            printf( "%4d\t%15s\t%12.2f\t%19s\n", x->id, x->name, x->price, x->store );
            x = x->nextProduct;
        } // END while
        puts( "-----------------------------------------------------------" );
        printf( "                                             TOTAL : $%.2f", sumList( &root ) );
    } // END if...else
    printf( "\n\nENTER A CHARACTER TO CONTINUE\n--> " );
    scanf( " %c", &junk );
    if( junk == "y" ) { printf( "\n\t\tYESSSSS......\n\n" ); }
} // END FUNCTION printList
//-----------------------------------------------------------------------------------
void appendNode( nodePtr *root, int nid, char *nname, float nprice, char *nstore )
{
    nodePtr currentPtr = *root;
    nodePtr previousPtr;
    nodePtr newPtr = malloc( sizeof( node ) );
    newPtr->name = malloc( strlen( nname ) + 1 );
    newPtr->store = malloc( strlen( nstore ) + 1 );
    newPtr->id = nid;
    newPtr->price = nprice;
    strcpy( newPtr->name, nname );
    strcpy( newPtr->store, nstore );

    if( currentPtr == NULL ) {
        *root = newPtr;
    } else {
        while( currentPtr != NULL ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextProduct;
        }
        previousPtr->nextProduct = newPtr;
        newPtr->nextProduct = currentPtr;
    }
} // END FUNCTION appendNode
//-----------------------------------------------------------------------------------
void initializeList( nodePtr *root )
{
    char junk;

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
int isEmpty( nodePtr root ) { return root == NULL; }
//-----------------------------------------------------------------------------------
float sumList( nodePtr *root )
{
    nodePtr currentPtr = *root;
    float sum = 0;

    while( currentPtr != NULL ) {
        sum += currentPtr->price;
        currentPtr = currentPtr->nextProduct;
    } // END while

    return sum;
} // END FUNCTION sumList
//-----------------------------------------------------------------------------------
void deleteItem( nodePtr *root, int nid )
{
    nodePtr currentPtr;
    nodePtr previousPtr;
    nodePtr tempPtr;

    if( nid == ( *root )->id ) {
        tempPtr = *root;
        *root = ( *root )->nextProduct;
        free( tempPtr );
    } else {

        previousPtr = *root;
        currentPtr = ( *root )->nextProduct;

        while( currentPtr != NULL && currentPtr->id != nid ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextProduct;
        } // END while

        if( currentPtr != NULL ) {
            tempPtr = currentPtr;
            previousPtr->nextProduct = currentPtr->nextProduct;
            free( tempPtr );
            printf( "Deleted...\n" );
        } else {
            printTitle();
            printf( "Object not found...\n" );
        } // END if...else
    } // END if...else
} // END FUNCTION deleteItem
//-----------------------------------------------------------------------------------
