/*
  Name: Nagham Maali
  ID: 1212312
  Sec.: 2
*/

//libraries:
/*1*/#include <stdio.h>
/*2*/#include <stdlib.h>
/*3*/#include <string.h>

/*(:)*/#define MaxSize 1000

struct QNode
{
    char word[20] ;
    struct QNode *Next ;
};

struct Queue
{
    struct QNode *front ;
    struct QNode *rear ;
};

struct SNode
{
    char word[20] ;
    char operation[20] ;  //Insert / Remove
    int index ;  //-1: insert / 32: remove
    struct SNode *Next ;
};

struct Stack
{
    struct SNode *Top ;
};

//function Definition:
/*1*/struct Queue *createQueue() ;
/*2*/struct Stack *createStack() ;
/*3*/void displayMainMenu() ;
/*4*/char *open_and_load() ;
/*5*/void split_and_load(struct Queue *AddQueue , char *inititial_text) ;
/*6*/void enqueue(struct Queue *AddQueue , char *token) ;
/*7*/void dequeue(struct Queue *AddQueue , char *remS) ;
/*8*///void print(struct Queue *AddQueue) ; to check the insert(enqueue) and remove(dequeue) functions
/*9*/void split_and_loadto_undo(struct Stack *UndoStack , char *newText , char *op , int ix) ;
/*10*/void push(struct Stack *UndoStack , char *token , char *op , int ix) ;
/*11*/void Undo(struct Stack *UndoStack , struct Stack *RedoStack , struct Queue *AddQueue) ;
/*12*/void Redo(struct Stack *UndoStack , struct Stack *RedoStack , struct Queue *AddQueue) ;
/*13*/void printustack(struct Stack *UndoStack) ;
/*14*/void printrstack(struct Stack *RedoStack) ;
/*15*/void save_to_file(struct Queue *AddQueue) ;
/*16*/void freeS(struct Stack *s) ;
/*17*/void freeQ(struct Queue *AddQueue) ;




int main()
{
    printf("Hi!\n") ;

    int x ;  //user choice
    int condition = 1 ;

    struct Queue *AddQueue ;  //Stores the words for the added string, then these words are added from the queue to both text and the undo stack.
    struct Stack *UndoStack ;  //stores the differential changes (insert/remove) made to the text, including the word, operation type, and position (starting index).
    struct Stack *RedoStack ;  //stores changes undone by the user, allowing for redo operations (involves the text involved, the operation type, and the index

    char *inititial_text = NULL ;

    char newText[MaxSize] ;  //the text that will be added to the initial text

    char remS[MaxSize] ;  //the string that will be removed

    AddQueue = createQueue() ;
    UndoStack = createStack() ;
    RedoStack = createStack() ;

    while(condition == 1)
    {
        displayMainMenu() ;
        scanf("%d" , &x) ;

        if(x == 1)
        {
            inititial_text = open_and_load() ;
            if(inititial_text != NULL)
            {
                printf("\t\t\t\tdone loading.\n") ;
            }
            else  //if no initial text
            {
                printf("\t\t\t\tError!!!\n") ;
            }
        }
        else if(x == 2)
        {
            if(inititial_text == NULL)
            {
                printf("No text to print!\n") ;
                return ;
            }

            printf("the loaded initial text: %s\n" , inititial_text) ;  //option 2 : print the initial text

        }
        else if(x == 3)
        {
            //option3: enqueue
            if(inititial_text == NULL)
            {
                printf("no initial text!!!\n") ;
                return ;
            }

            split_and_load(AddQueue , inititial_text) ;

            if(AddQueue == NULL)
            {
                printf("No text!\n") ;
                return ;
            }

            printf("enter the new text u wanna add...\n") ;
            getchar() ;
            fgets(newText , MaxSize , stdin) ;  //read the new text
            strtok(newText , "\n") ;  //remove new line character
            split_and_load(AddQueue , newText) ;
            printf("done adding new text.\n") ;

            /*
              printf("and the text now:\n") ;
              print(AddQueue) ;
              printf("\n") ;
              to check the insert process
            */

            split_and_loadto_undo(UndoStack , newText , "Insert" , -1) ;
        }
        else if(x == 4)
        {
            //option4: dequeue
            if(AddQueue == NULL)
            {
                printf("No text!\n") ;
                return ;
            }

            printf("what part of the text u wanna remove?\n") ;
            getchar() ;
            fgets(remS , MaxSize , stdin) ;  //read the string to remove
            strtok(remS , "\n") ;  //remove new line character
            dequeue(AddQueue , remS) ;
            push(UndoStack , remS , "Remove" , 32) ;

            /*
              printf("and the text now:\n") ;
              print(AddQueue) ;
              printf("\n") ;
              to check the remove process
            */
        }
        else if(x == 5)
        {
            Undo(UndoStack , RedoStack , AddQueue) ;
        }
        else if(x == 6)
        {
            Redo(UndoStack , RedoStack , AddQueue) ;
        }
        else if(x == 7)
        {
            printustack(UndoStack) ;
            printf("\n") ;
            printrstack(RedoStack) ;
        }
        else if(x == 8)
        {
            save_to_file(AddQueue) ;
        }
        else if(x == 9)
        {
            printf("Bye!\n") ;
            break ;
        }
        else
        {
            printf("invalid option!!!\n") ;
            printf("try again :)\n") ;
        }
    }

    //free allocated memory:
    freeS(UndoStack) ;
    freeS(RedoStack) ;
    freeQ(AddQueue) ;
    free(inititial_text) ;

    return 0 ;
}

struct Queue *createQueue()
{
    struct Queue *Aq ;

    Aq = (struct Queue *)malloc(sizeof(struct Queue)) ;  //allocate memory for the queue structure

    if(Aq == NULL)
    {
        printf("Error!!\n") ;
        return NULL ;
    }

    Aq -> front = NULL ;  //set the front pointer of the queue to NULL
    Aq -> rear = NULL ;  //set the rear pointer of the queue to NULL

    return Aq ;  //return the created queue
}

struct Stack *createStack()
{
    struct Stack *S ;

    S = (struct Stack *)malloc(sizeof(struct Stack)) ;  //allocate memory for the stack structure

    if(S == NULL)
    {
        printf("Error!!\n") ;
        return NULL ;
    }

    S -> Top = NULL ;  //set the top pointer of the stack to NULL

    return S ;  //return the created stack
}

void displayMainMenu()
{
    printf("please select an option(1-14):\n") ;
    printf("1. Load the input file which contains the initial text.\n") ;
    printf("2. Print the loaded text.\n") ;
    printf("3. Insert strings to the text.\n") ;
    printf("4. Remove strings from the text.\n") ;
    printf("5. Perform Undo operation\n") ;
    printf("6. Perform Redo operation.\n") ;
    printf("7. Print the Undo Stack and the Redo stack.\n") ;
    printf("8. Save the updated text to the output file. \n") ;
    printf("9. Exit.\n") ;
}

char *open_and_load()
{
    FILE *input_file ;
    char *Line ;

    Line = (char *)malloc(MaxSize * sizeof(char)) ;

    input_file = fopen("initial_text.txt" , "r") ;  //open input file

    if(input_file == NULL)  //check if the file exists and can be opened
    {
        printf("No file with such a name!\n") ;
        return NULL ;
    }

    printf("loading initial text started...\n") ;

    if(fgets(Line , MaxSize , input_file) == NULL)  //read line from the file
    {
        printf("can't read the file!\n") ;
        free(Line) ;  //free allocated memory for Line
        fclose(input_file) ;  //close file
        return NULL ;
    }

    fclose(input_file) ;  //close file

    return Line ;  //return the loaded text
}

void split_and_load(struct Queue *AddQueue , char *inititial_text)
{
    char *token ;
    token = strtok(inititial_text , " ") ;  //split the text into tokens using space as delimiter
    if(token == NULL)
    {
        printf("invalid input format!\n") ;
        return ;
    }

    while(token != NULL)  //loop through each token(word)
    {
        enqueue(AddQueue , token) ;  //insert the token(word) into the queue(each word is a separate node)
        token = strtok(NULL , " ") ;  //get the next tokenn
    }
}

void enqueue(struct Queue *AddQueue , char *token)
{
    struct QNode *n ;  //new node

    n = (struct QNode *)malloc(sizeof(struct QNode)) ;  //allocate memory for the new node
    if(n == NULL)
    {
        printf("Error!!!\n") ;
        return ;
    }

    strcpy(n -> word , token) ;  //copy the token into the word field of the new node
    n -> Next = NULL ;  //set the Next pointer of the new node to NULL

    if(AddQueue -> rear == NULL)  //if the queue is empty,
    {
        //set both front and rear pointer to the new node
        AddQueue -> front = n ;
        AddQueue -> rear = n ;
    }
    else
    {
        AddQueue -> rear -> Next = n ;  //linki the new node to the end of the queue
        AddQueue -> rear = n ;  //update the rear pointer to the new node
    }
}

void dequeue(struct Queue *AddQueue , char *remS)
{
    if(AddQueue -> front == NULL)  //if the queue is empty,
    {
        printf("Error!!!\n") ;
        return ;
    }

    struct QNode *temp = AddQueue -> front ;  //declare a temporary pointer and initialize it to the front of the queue
    struct QNode *ptr = NULL ;  //declare a pointer to keep track of the previous node

    while(temp != NULL)
    {
        if(strcmp (temp -> word , remS) == 0)  //search for the word to remove
        {
            if(ptr == NULL)  //if the node to remove is the front node,
            {
                AddQueue -> front = temp -> Next ;  //update the front poiinter
                if(AddQueue -> front== NULL)  //if the queue becomes empty after removal
                {
                    AddQueue -> rear = NULL ;  //update the rear pointer
                }
            }
            else
            {
                ptr -> Next = temp -> Next ;  //link the previous node to the next node
                if(temp -> Next == NULL)  //if the node to remove is the rear node
                {
                    AddQueue -> rear = ptr ;  //update the rear node
                }
            }
            free(temp) ;  //free memory allocated for the node to remove
            printf("string '%s' is found and removed from the text.\n" , remS) ;
            return ;
        }
        ptr = temp ;  //update the previous pointer
        temp = temp -> Next ;  //move to the next node
    }
    printf("string '%s' is not found in the text!\n" , remS) ;
}

/*
void print(struct Queue *AddQueue)
{
    if(AddQueue -> front == NULL)  //if the queue is empty,
    {
        printf("Error!!!\n") ;
        return ;
    }

    struct QNode *n ;  //declare a pointer to traverse the queue
    n = AddQueue -> front ;  //initialize the pointer to the front of the queue
    while(n != NULL)  //traverse the queue and print each word
    {
        printf("%s " , n -> word) ;
        n = n -> Next ;  //move to the next node
    }
    printf("\n") ;  //print new line
}
*/

void split_and_loadto_undo(struct Stack *UndoStack , char *newText , char *op , int ix)
{
    char *token ;
    token = strtok(newText , " ") ;  //split the text into tokens using space as delimiter
    if(token == NULL)
    {
        printf("invalid input format!\n") ;
        return ;
    }

    while(token != NULL)  //loop through each token
    {
        push(UndoStack , token , op , ix) ;  //push the token into UndoStack with specified operation and index
        token = strtok(NULL , " ") ;  //get the next token
    }
}

void push(struct Stack *UndoStack , char *token , char *op , int ix)
{
    struct SNode *s ;  //new stack node

    s = (struct SNode *)malloc(sizeof(struct SNode)) ;  //allocate memory for the new stack node
    if(s == NULL)
    {
        printf("Error!!!\n") ;
        return ;
    }

    strcpy(s -> word , token) ;  //copy the token into the word field of the new node
    strcpy(s -> operation , op) ;  //copy the operation into the operation field of the new node
    s -> index = ix ;  //set the index field of the new node

    s -> Next = UndoStack -> Top ;  //link the new node to the top of the stack
    UndoStack -> Top = s ;  //update the top pointer of the stack
}

void Undo(struct Stack *UndoStack , struct Stack *RedoStack , struct Queue *AddQueue)
{
    if(UndoStack -> Top == NULL)
    {
        printf("can't perform undo operation!\n") ;
        return ;
    }

    struct SNode *un ;  //declare a pointer to store the top node of the UndoStack

    un = UndoStack -> Top ;  //store the top node of the UndoStack
    UndoStack -> Top = un -> Next ;  //update the top pointer of the UndoStack to point to the next node

    push(RedoStack , un -> word , un -> operation , un -> index) ;  //push the undone operation into RedoStack

    if(strcmp(un -> operation , "Insert") == 0)  //if the undone operation is Insert
    {
        enqueue(AddQueue , un -> word) ;  //enqueue the word into the AddQueue
    }
    else if(strcmp(un -> operation , "Remove") == 0)  //if the undone operation is Remove
    {
        push(RedoStack , un -> word , un -> operation , un -> index) ;  //push the undone operation again into the RedoStack
    }

    free(un) ;  //free memory Allocated for the undone operation node

    printf("undo operation performed successfully.\n") ;
}

void Redo(struct Stack *UndoStack , struct Stack *RedoStack , struct Queue *AddQueue)
{
    if(RedoStack -> Top == NULL)  //if the RedoStack is empty,
    {
        printf("can't perform redo operation!\n") ;
        return ;
    }

    struct SNode *re ;  //declare a pointer to store the top node of of the RedoStack

    re = RedoStack -> Top ;  //store the top node of the RedoStack
    RedoStack -> Top = re -> Next ;  //update the top pointer of RedoStack to point to the next node

    push(UndoStack , re -> word , re -> operation , re -> index) ;  //push the redone operation into the UndoStack

    if(strcmp(re -> operation , "Insert") == 0)  //if the redone operation is Insert
    {
        enqueue(AddQueue , re -> word) ;  //enqueue the word into the AddQueue
    }
    else if(strcmp(re -> operation , "Remove") == 0)  //if the redone operation is Remove
    {
        enqueue(AddQueue , re -> word) ;  //enqueue the word into the AddQueue
    }

    free(re) ;  //free memory allocated for the redone operation node

    printf("redo operation performed successfully.\n") ;
}

void printustack(struct Stack *UndoStack)
{
    if(UndoStack -> Top == NULL)  //if the UndoStack is empty,
    {
        printf("Error!!!\n") ;
        return ;
    }

    printf("undo stack:\n") ;
    printf("%-15s %-10s %-6s\n" , "token" , "operation" , "index") ;  //print column headers

    struct SNode *us ;

    us = UndoStack -> Top ;  //initialize the pointer to the top of the UndoStack
    while(us != NULL)
    {
        printf("%-15s %-10s %-6d\n" , us -> word , us -> operation , us -> index) ;
        us = us -> Next ;  //move to the next node
    }
    printf("\n") ;  //new empty line
}

void printrstack(struct Stack *RedoStack)
{
    if(RedoStack -> Top == NULL)  //if the RedoStack is empty,
    {
        printf("Error!!!\n") ;
        return ;
    }

    printf("redo stack:\n") ;
    printf("%-15s %-10s %-6s\n" , "token" , "operation" , "index") ;  //print column headers

    struct SNode *rs ;

    rs = RedoStack -> Top ;  //initialize the pointer to the top of the RedoStack
    while(rs != NULL)
    {
        printf("%-15s %-10s %-6d\n" , rs -> word , rs -> operation , rs -> index) ;
        rs = rs -> Next ;  //move to the next node
    }
    printf("\n") ;  //new empty line
}

void save_to_file(struct Queue *AddQueue)
{
    if(AddQueue == NULL || AddQueue -> front == NULL)  //if the queue is empty,
    {
        printf("No text to save!\n") ;
        return ;
    }

    FILE *outpt_file ;
    outpt_file = fopen("saveText.txt" , "w") ;  //open file
    if(outpt_file == NULL)  //check if the file exists and can be opened
    {
        printf("Error!!!\n") ;
        return ;
    }

    struct QNode *Aq ;

    Aq = AddQueue -> front ;  //initialize the pointer to the front of the AddQueue
    while(Aq != NULL)
    {
        fprintf(outpt_file , "%s " , Aq -> word) ;
        Aq = Aq -> Next ;  //move to the next node
    }

    fclose(outpt_file) ;  //close file

    printf("the text is saved to the file.\n") ;
}

void freeS(struct Stack *s)
{
    struct SNode *c ;  //pointer to traverse the stack
    struct SNode *temp ;  //temporary pointer to store the current node

    c = s -> Top ;  //initialize the pointer to the top of the stack
    while(c != NULL)
    {
        temp = c ;  //store the current node in temp
        c = c -> Next ;  //move to the next node
        free(temp) ;  //free memory allocated for the current node
    }
    free(s) ;  //free memory allocated for the stack structure
}

void freeQ(struct Queue *AddQueue)
{
    struct QNode *c ;  //pointer to traverse the queue
    struct QNode *temp ;  //temporary pointer to store the current node

    c = AddQueue -> front ;  //initialize the pointer to the front of the queue
    while(c != NULL)
    {
        temp = c ;  //store the current node in temp
        c = c -> Next ;  //move to the next node
        free(temp) ;  //free memory allocated for the current node
    }
    free(AddQueue) ;  //free memory allocated for the queue structure
}
