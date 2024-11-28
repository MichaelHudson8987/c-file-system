#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

FILE *fPointer;
char FileName[100];
int ch;
int DataOption;
int Loaded = 0;

struct Book {
    char Author[100];
    char LibraryName[100];
    char Publisher[100];
    float ReplacementCost;
    char MaterialSubject[100];
    int IndexNumber;
    char CurrentLoaner[100];
    char DueDate[100];
    struct Book *next;
};

//Function prototypes
struct Book *AddNewEntries(struct Book **);
struct Book *LoadData(struct Book **);
struct Book *ModifyEntries(struct Book **);
struct Book *DeleteEntries(struct Book **);
struct Book *SaveEntry(struct Book **);
struct Book *SearchBook(struct Book **);
struct Book *SearchAuthor(struct Book **);
struct Book *AlphabetSort(struct Book **);
void DisplayOptions(struct Book *);
void BrowseEntries(struct Book *);


int main(){

    struct Book *Start = NULL;

    //Repeats until valid choice is given
    while (1){

        //Prompting user to start with new data or previous data
        puts("\nLibrary Management System");
        puts("-------------------------");
        puts("\nSelect an option: \n\n1. Start with new data \n2. Load previously saved data");

        //Verifies input is valid
        if (scanf("%d", &DataOption) == 1){
            while ((ch = getchar()) != '\n' && ch != EOF);

            //Prompts new list creation if "1" is entered
            if (DataOption == 1){
                AddNewEntries(&Start);
                DisplayOptions(Start);
                break;
            }

            //Prompts loading of data if "2" is entered
            else if (DataOption == 2){
                LoadData(&Start);
                DisplayOptions(Start);
                break;
            }

            else{
                puts("\nInvalid input\n");
            }
        }
        
        //Output error if input is invalid
        else {
            puts("\nInvalid input\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }

    return 0;
}

struct Book *AddNewEntries(struct Book **Start){

    struct Book *Move = NULL, *New = NULL;
    char Repeat = 'Y';

    //Repeats until user no longer wishes to make entries
    while (Repeat == 'y' || Repeat == 'Y'){

        //If no previous list exists
        if (*Start == NULL) {

            //Creating book
            New = (struct Book*)malloc(sizeof(struct Book));

            //Displays error if failed to allocate memory
            if (New == NULL) {
                puts("Memory error!");
                exit(1);
            }

            //Assigns memory of book to start pointer
            *Start = New;

        } 

        //If list already exists
        else {

            //Assigns memory address of start of existing list to move pointer
            Move = *Start;

            //Repeats until move pointer reaches the end of existing list
            while (Move->next != NULL) {
                Move = Move->next;
            }
    
            //Creating new book
            New = (struct Book*)malloc(sizeof(struct Book));

            //Displays error if failed to allocate memory
            if (New == NULL) {
                puts("Memory error!");
                exit(1);
            }
    
            //Placing new book at end of existing list
            Move->next = New;
        }

        //Filling in data of new book
        New->next = NULL;

        puts("\nCreating New Entry");
        puts("------------------");
        puts("\nPlease enter Author Name:"); 
        
        fgets(New->Author, 100, stdin);
        New->Author[strcspn(New->Author, "\n")] = '\0';

        puts("\nPlease enter Library Name:"); 
        fgets(New->LibraryName, 100, stdin);
        New->LibraryName[strcspn(New->LibraryName, "\n")] = '\0';

        puts("\nPlease enter Publisher:"); 
        fgets(New->Publisher, 100, stdin);
        New->Publisher[strcspn(New->Publisher, "\n")] = '\0';
        
        
        //Verifying input is a number
        while (1){

            puts("\nPlease enter Replacement Cost:"); 
            if(scanf("%f", &New->ReplacementCost) == 1){
                while ((ch = getchar()) != '\n' && ch != EOF);
                break;
            }

            else{
                while ((ch = getchar()) != '\n' && ch != EOF);
                puts("Invalid input");
            }
        }
        

        puts("\nPlease enter Material Subject:"); 
        fgets(New->MaterialSubject, 100, stdin);
        New->MaterialSubject[strcspn(New->MaterialSubject, "\n")] = '\0';
        
        //Verifying input is a number
        while (1){

            puts("\nPlease enter Index Number:"); 
            if(scanf("%d", &New->IndexNumber) == 1){
                while ((ch = getchar()) != '\n' && ch != EOF);
                break;
            }

            else{
                while ((ch = getchar()) != '\n' && ch != EOF);
                puts("Invalid input");
            }
        }

        puts("\nPlease enter Current Loaner Name:");
        fgets(New->CurrentLoaner, 100, stdin);
        New->CurrentLoaner[strcspn(New->CurrentLoaner, "\n")] = '\0';

        puts("\nPlease enter Due Date:");
        fgets(New->DueDate, 100, stdin); 
        New->DueDate[strcspn(New->DueDate, "\n")] = '\0';

        //Repeats until valid input is entered
        while (1){
            puts("\nMake another entry? Y/N:");
            scanf("%c", &Repeat);
            while ((ch = getchar()) != '\n' && ch != EOF);

            if (Repeat == 'Y' || Repeat == 'y' || Repeat == 'N' || Repeat == 'n'){
                break;
            }

            //Outputs error if input is invalid
            else{
                while ((ch = getchar()) != '\n' && ch != EOF);
                puts("Invalid input");

            }
        }
       
    }

    //Returns memory address of start of list
    return *Start;
}

void DisplayOptions(struct Book *Start){

    int Choice;

    //Repeats until valid input is entered
    while (1){

        //Prompts user to select an option
        puts("\nPlease select an option:");
        puts("------------------------");
        puts("\n1. Add new entries");
        puts("2. Browse entries");
        puts("3. Modify Entries");
        puts("4. Delete Entries");
        puts("5. Save Data");
        puts("6. Sort into Alphabetical Order");
        puts("7. Search by Book Name");
        puts("8. Search by Author");
        puts("9. Exit Program");

        //If option is valid, call function based on choice
        if (scanf("%d", &Choice) == 1){

            while ((ch = getchar() ) != '\n' && ch != EOF);

            if (Choice == 1){
                AddNewEntries(&Start);  
            }

            else if (Choice == 2) {
                BrowseEntries(Start);
            } 
        
            else if (Choice == 3){
                ModifyEntries(&Start);
            }

            else if (Choice == 4){
                DeleteEntries(&Start);
            }

            else if (Choice == 5){
                SaveEntry(&Start);
            }

            else if (Choice == 6){
                AlphabetSort(&Start);
            }

            else if (Choice == 7){
                SearchBook(&Start);
            }

            else if (Choice == 8){
                SearchAuthor(&Start);
            }

            else if (Choice == 9){
                puts("\nExiting program...");
                exit(0);
            }

            //Output error if choice is out of range
            else{
                puts("\nChoice is out of range");
            }
                    
            //Exit loop if choice is valid
            if (Choice >= 1 && Choice <= 9){
                break;
            }
        }

        //If input is valid, output error
        else {
            puts("\nInvalid input");
            while ((ch = getchar() ) != '\n' && ch != EOF);
        }
    }

    DisplayOptions(Start);
}

void BrowseEntries(struct Book *Start){
    struct Book *Move = Start;

    //If no data, display error
    if (Start == NULL){
        puts("\nNo data available to display");
                        
    }

    else{
        puts("\nDisplaying entries");
        puts("------------------");

        while (Move != NULL){
            printf("\nAuthor Name: %s", Move->Author); 
            printf("\nLibrary Name: %s", Move->LibraryName); 
            printf("\nPublisher: %s", Move->Publisher); 
            printf("\nReplacement Cost: %.2f", Move->ReplacementCost); 
            printf("\nMaterial Subject: %s", Move->MaterialSubject); 
            printf("\nIndex Number: %d", Move->IndexNumber); 
            printf("\nCurrent Loaner Name: %s", Move->CurrentLoaner);
            printf("\nDue Date: %s\n", Move->DueDate);
            Move = Move->next;
        }
    }
}
    
struct Book *LoadData(struct Book **Start){

    struct Book *Move = NULL, *New = NULL;
    char FailPrompt;
    int LoadFail = 0;
    int Repeat = 1;

    //Repeats until valid file name is given
    //or decision to start with new data is made
    while (Repeat == 1){
       
        //Prompting user for file name
        puts("\nPlease enter existing file name:");
        fgets(FileName, sizeof(FileName), stdin);
        FileName[strcspn(FileName, "\n")] = '\0';
        
        //Opens file
        fPointer = fopen(FileName, "r");

        //Exits loop if file exists
        if (fPointer != NULL){
            puts("\nData successfully loaded");
            Loaded = 1;
            Repeat = 0;
        }

        
        else{

            //Outputs error if file is unknown
            //Increases fail count
            puts("\nUnknown file name");
            LoadFail++;

            //If unknown file is entered more than twice
            if (LoadFail > 2){

                //Repeatedly prompts to start with new data
                //until valid choice is made
                while(1){
                    puts("\nStart with new data? Y/N:");
                    scanf("%c", &FailPrompt);
                    while ((ch = getchar()) != '\n' && ch != EOF);

                    //If yes, allow to add new entries
                    if (FailPrompt == 'Y' || FailPrompt == 'y'){
                        AddNewEntries(Start);
                        Repeat = 0;
                        break;
                    }

                    //If no, continue prompting file name
                    else if (FailPrompt == 'N' || FailPrompt == 'n'){
                        break;
                    }

                    //Outputs error if input is invalid
                    else{
                        puts("\nInvalid input");
                    }
                }   
            
            }
        }
    
    }

    //Repeats until entire contents of file are added to list
    while (1){

        //Creating new book
        New = (struct Book*)malloc(sizeof(struct Book));
        
        //If first variable of book is empty, free memory block and exit loop
        if (fgets(New->Author, sizeof(New->Author), fPointer) == NULL){
            free(New);
            break;
        }

        //Adds file contents to list
        New->Author[strcspn(New->Author, "\n")] = '\0';

        fgets(New->LibraryName, sizeof(New->LibraryName), fPointer);
        New->LibraryName[strcspn(New->LibraryName, "\n")] = '\0';

        fgets(New->Publisher, sizeof(New->Publisher), fPointer);
        New->Publisher[strcspn(New->Publisher, "\n")] = '\0';

        fscanf(fPointer, "%f%*c", &New->ReplacementCost);

        fgets(New->MaterialSubject, sizeof(New->MaterialSubject), fPointer);
        New->MaterialSubject[strcspn(New->MaterialSubject, "\n")] = '\0';

        fscanf(fPointer, "%d%*c", &New->IndexNumber);

        fgets(New->CurrentLoaner, sizeof(New->CurrentLoaner), fPointer);
        New->CurrentLoaner[strcspn(New->CurrentLoaner, "\n")] = '\0';

        fgets(New->DueDate, sizeof(New->DueDate), fPointer);
        New->DueDate[strcspn(New->DueDate, "\n")] = '\0';

        New->next = NULL;

        //If beginning of list, assign start to memory of first list
        //Assign move pointer to memory address of first line
        if (*Start == NULL){
            *Start = New;
            Move = New;
        }

        //If list already exists, link book to existing list
        else{
            Move->next = New;
            Move = New;
        }
        
    }

    //Closes file
    fclose(fPointer);

    return *Start;
}

struct Book *ModifyEntries(struct Book **Start){
    int EntryNumber = 1;
    int FieldChoice = 1;
    int Verified = 0;
    int IndexInput;
    char sFieldData[100];
    struct Book *CurrentEntry;
    CurrentEntry = *Start;

    //Fails to execute if no data is available
    if (*Start == NULL){
        puts("\nNo data available to modify");
    }

    else{

        //Repeats until valid entry number is given
        while (1){

            //Prompting user for entry to modify
            puts("\nPlease enter the entry number to modify");

            //If input is a number that's 1 or higher
            if (scanf("%d", &EntryNumber) == 1){

                while ((ch = getchar() ) != '\n' && ch != EOF);
                
                if (EntryNumber >= 1){

                    //Moves through entries up to the number given if data is found
                    for (int Count = 1; CurrentEntry != NULL && Count < EntryNumber; Count++){
                        CurrentEntry = CurrentEntry-> next;
                    }

                    //If no data is found in entry, output invalid entry number error
                    if (CurrentEntry == NULL){
    
                        puts("\nInvalid entry number");

                        //Resets current entry to start of list
                        CurrentEntry = *Start;

                    }

                    else{
                        
                        //Exits loop if number entered is valid
                        break;
                    }
                }
                
                //Outputs error if 0 is entered
                else{
                    puts("\nEntry number is out of range");
                }
            }

            //Outputs error if input is not a number
            else {
                puts("\nInvalid input");
                while ((ch = getchar() ) != '\n' && ch != EOF);
                
            }
        }

        //Repeats until valid field given
        while (1){

            puts("\nPlease select a field to modify:");
            puts("\n1. Author Name"); 
            puts("2. Library Name"); 
            puts("3. Publisher"); 
            puts("4. Replacement Cost"); 
            puts("5. Material Subject"); 
            puts("6. Index Number"); 
            puts("7. Current Loaner Name");
            puts("8. Due Date");
            
            //If input is a number
            if (scanf("%d", &FieldChoice) == 1){

                //If input is a number between 1 and 8, exit loop
                if (FieldChoice >= 1 && FieldChoice <= 8){
                break;
                }

                //Output error if number is out of range
                else{
                    puts("Field choice is out of range");
                }

            }

            //Output error if input is not a number
            else{
                puts("\nInvalid input");
            }
        }

        //Repeats until valid data is entered
        while (1){

            //Assigns float value to chosen field
            if (FieldChoice == 4){
                
                //Verifies number is a float number
                while (Verified == 0){

                    puts("\nPlease enter the new data you would like to enter:");
                    if (scanf("%f", &CurrentEntry->ReplacementCost) == 1){
                        Verified = 1;
                    }

                    //Outputs error if input is not a float number
                    else {
                        while ((ch = getchar() ) != '\n' && ch != EOF);
                        puts("\nInput must be a number");
                    }
                }

                //Exits main loop
                break;
            }

            //Assigns integer value to chosen field
            else if (FieldChoice == 6){

                //Verifies number is an integer number
                while (Verified == 0){

                    puts("\nPlease enter the new data you would like to enter:");
                    if (scanf("%d", &CurrentEntry->IndexNumber) == 1){
                        while ((ch = getchar() ) != '\n' && ch != EOF);
                        Verified = 1;
                    }

                    //Outputs error if input is not an integer number
                    else{
                        while ((ch = getchar() ) != '\n' && ch != EOF);
                        puts("\nInput must be a whole number");
                    }

                }

                //Exits main loop
                break;
            }

            //If any other field, store data into string variable
            else {
                puts("\nPlease enter the new data you would like to enter:");
                while ((ch = getchar() ) != '\n' && ch != EOF);
                fgets(sFieldData, sizeof(sFieldData), stdin);
                sFieldData[strcspn(sFieldData, "\n")] = '\0';

            }

            //Overwrites data field in entry based on choice
            if (FieldChoice == 1){
                strncpy(CurrentEntry->Author, sFieldData, sizeof(CurrentEntry->Author));
                CurrentEntry->Author[strcspn(CurrentEntry->Author, "\n")] = '\0';
                break;
            }

            else if (FieldChoice == 2){
                strncpy(CurrentEntry->LibraryName, sFieldData, sizeof(CurrentEntry->LibraryName));
                CurrentEntry->LibraryName[strcspn(CurrentEntry->LibraryName, "\n")] = '\0';
                break;
            }

            else if (FieldChoice == 3){
                strncpy(CurrentEntry->Publisher, sFieldData, sizeof(CurrentEntry->Publisher));
                CurrentEntry->LibraryName[strcspn(CurrentEntry->LibraryName, "\n")] = '\0';
                break;
            }

            else if (FieldChoice == 5){
                strncpy(CurrentEntry->MaterialSubject, sFieldData, sizeof(CurrentEntry->MaterialSubject));
                CurrentEntry->MaterialSubject[strcspn(CurrentEntry->MaterialSubject, "\n")] = '\0';
                break;
            }

            else if (FieldChoice == 7){
                strncpy(CurrentEntry->CurrentLoaner, sFieldData, sizeof(CurrentEntry->CurrentLoaner));
                CurrentEntry->CurrentLoaner[strcspn(CurrentEntry->CurrentLoaner, "\n")] = '\0';
                break;
            }

            else if (FieldChoice == 8){
                strncpy(CurrentEntry->DueDate, sFieldData, sizeof(CurrentEntry->DueDate));
                CurrentEntry->DueDate[strcspn(CurrentEntry->DueDate, "\n")] = '\0';
                break;
            }

        }
    }

    return *Start;
}

struct Book *DeleteEntries(struct Book **Start){
    int EntryNumber = 1;
    int Deleted = 0;
    char DeleteFile;
    struct Book *CurrentEntry; 
    struct Book *PreviousEntry = NULL;
    CurrentEntry = *Start;

    //Fails to execute if no data is available
    if (*Start == NULL){
        puts("\nNo data available to delete");

        //Prompting user to delete loaded file if contents are empty
        //and file hasn't already been deleted
        if (Loaded == 1 && Deleted == 0){

            while (1){
                puts("\nWould you like to delete the loaded file? Y/N:");
                scanf(" %c", &DeleteFile);
                while ((ch = getchar() ) != '\n' && ch != EOF);

                //Deletes file if yes
                if (DeleteFile == 'Y' || DeleteFile == 'y'){
                    Deleted = 1;
                    Loaded = 0;
                    remove(FileName);
                    printf("\nFile %s has been successfully deleted\n", FileName);
                    break;
                }

                //Exits if no
                else if (DeleteFile == 'N' || DeleteFile == 'n'){
                    break;
                }

                //Outputs error if input is invalid
                else{
                    puts("Invalid input");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                }
            }
        }
        
    }

    else{

        //Repeats until valid entry number is given
        while (1){

            //Prompting user for entry to delete
            puts("\nPlease enter the entry number to delete. Enter 0 to exit");

            //If input is a number that's 1 or higher
            if (scanf("%d", &EntryNumber) == 1){

                while ((ch = getchar() ) != '\n' && ch != EOF);

                if (EntryNumber >= 1){

                    //Moves through entries up to the number given if data is found
                    for (int Count = 1; CurrentEntry != NULL && Count < EntryNumber; Count++){
                        PreviousEntry = CurrentEntry;
                        CurrentEntry = CurrentEntry->next;
                    }
                    
                    if (CurrentEntry != NULL){

                        //If entries exist before current entry, move to after current entry
                        if (PreviousEntry != NULL){
                            PreviousEntry->next = CurrentEntry->next;
                        }

                        //If no entries exist before current entry, move start to after current entry
                        else {
                            *Start = CurrentEntry->next;
                        }

                        //Deletes memory of selected entry
                        free(CurrentEntry);
                        puts("\nThe selected entry has been successfully deleted");
                        break;
                    }

                    //If no data is found in entry, output invalid entry number error
                    else{
                        puts("\nInvalid entry number");

                        //Resets current entry to start of list
                        //Reset previous entry to null
                        CurrentEntry = *Start;
                        PreviousEntry = NULL;
                    }
                }
                

                //Outputs error if 0 is entered
                else{
                    break;
                }
            }

            //Outputs error if input is not a number
            else {
                puts("\nInvalid input");
                while ((ch = getchar() ) != '\n' && ch != EOF);
            }
        }
    }
    
}

struct Book *SaveEntry(struct Book **Start){
   char NewFile[100];
   struct Book *CurrentEntry = *Start;

    //Outputs error if no data found
    if (*Start == NULL){
        puts("\nNo data available to save");
    }

    else{

        //Prompting user to name their file or enter existing file
        puts("\nPlease enter a name for your new save file");
        puts("Or enter an existing file name to overwrite");
        fgets(NewFile, sizeof(NewFile), stdin);
        NewFile[strcspn(NewFile, "\n")] = '\0';
        
        //Opening file to write
        fPointer = fopen(NewFile, "w");

        //Moving through list and printing to file
        while (CurrentEntry != NULL){
            fprintf(fPointer, "%s\n%s\n%s\n%.2f\n%s\n%d\n%s\n%s\n", CurrentEntry->Author, CurrentEntry->LibraryName, CurrentEntry->Publisher,
                                                                    CurrentEntry->ReplacementCost, CurrentEntry->MaterialSubject, CurrentEntry->IndexNumber,
                                                                    CurrentEntry->CurrentLoaner, CurrentEntry-> DueDate);
            CurrentEntry = CurrentEntry->next;
        }

        //File has been saved
        printf("\nFile %s has been successfully saved\n", NewFile);

        //Closing file
        fclose(fPointer);

    }
}

struct Book *SearchAuthor(struct Book **Start){
    char AuthorName[100];
    int Match = 0;
    struct Book *CurrentEntry = *Start;
    struct Book *AuthorEntry = NULL;

    //Outputs error if no data found
    if (*Start == NULL){
        puts("\nNo data available to search");
    }

    else{

        //Prompting user for author name
        puts("\nPlease enter the author name to search for:");
        fgets(AuthorName, sizeof(AuthorName), stdin);
        AuthorName[strcspn(AuthorName, "\n")] = '\0';

        //Searches through linked list
        while(CurrentEntry != NULL){

            //If the author name in entry matches author name entered,
            //author entry pointer is set to the current entry 
            if (strcasecmp(CurrentEntry->Author, AuthorName) == 0){
                AuthorEntry = CurrentEntry;
                Match++;
                
                //Only print header once
                if (Match == 1){
                    puts("\nOne or more entries found:");
                    puts("--------------------------");
                }
                
                //Display contents then move to next entry
                printf("\nAuthor Name: %s", AuthorEntry->Author); 
                printf("\nLibrary Name: %s", AuthorEntry->LibraryName); 
                printf("\nPublisher: %s", AuthorEntry->Publisher); 
                printf("\nReplacement Cost: %.2f", AuthorEntry->ReplacementCost); 
                printf("\nMaterial Subject: %s", AuthorEntry->MaterialSubject); 
                printf("\nIndex Number: %d", AuthorEntry->IndexNumber); 
                printf("\nCurrent Loaner Name: %s", AuthorEntry->CurrentLoaner);
                printf("\nDue Date: %s\n", AuthorEntry->DueDate);

                CurrentEntry = CurrentEntry->next;
            }

            //If no match, move to next entry
            else{
                CurrentEntry = CurrentEntry->next;
            }
        }

        //If the author name was not found, display error
        if (AuthorEntry == NULL){
            printf("\nAn entry with the author name %s was not found\n", AuthorName);
        }
        
        return *Start;
    }
}

struct Book *SearchBook(struct Book **Start){
    char BookName[100];
    int Match = 0;
    struct Book *CurrentEntry = *Start;
    struct Book *BookEntry = NULL;

    //Outputs error if no data found
    if (*Start == NULL){
        puts("\nNo data available to search");
    }

    else{

        //Prompting user for book name
        puts("\nPlease enter the book name (material subject) to search for:");
        fgets(BookName, sizeof(BookName), stdin);
        BookName[strcspn(BookName, "\n")] = '\0';

        //Searches through linked list
        while(CurrentEntry != NULL){

            //If the book name in entry matches book name entered,
            //book entry pointer is set to the current entry 
            if (strcasecmp(CurrentEntry->MaterialSubject, BookName) == 0){
                BookEntry = CurrentEntry;
                Match++;
                
                //Only print header once
                if (Match == 1){
                    puts("\nOne or more entries found:");
                    puts("--------------------------");
                }
                
                //Display contents then move to next entry
                printf("\nAuthor Name: %s", BookEntry->Author); 
                printf("\nLibrary Name: %s", BookEntry->LibraryName); 
                printf("\nPublisher: %s", BookEntry->Publisher); 
                printf("\nReplacement Cost: %.2f", BookEntry->ReplacementCost); 
                printf("\nMaterial Subject: %s", BookEntry->MaterialSubject); 
                printf("\nIndex Number: %d", BookEntry->IndexNumber); 
                printf("\nCurrent Loaner Name: %s", BookEntry->CurrentLoaner);
                printf("\nDue Date: %s\n", BookEntry->DueDate);

                CurrentEntry = CurrentEntry->next;
            }

            //If no match, move to next entry
            else{
                CurrentEntry = CurrentEntry->next;
            }
        }

        //If the book name was not found, display error
        if (BookEntry == NULL){
            printf("\nAn entry with the book name %s was not found\n", BookName);
        }
    }

    return *Start;
}

struct Book *AlphabetSort(struct Book **Start){

    int Switch;

    //Outputs error if no data found
    if (*Start == NULL){
        puts("\nNo data available to sort");
    }

    //Outputs error if only one entry in list
    else if ((*Start)->next == NULL){
        puts("\nList has only one entry, sort is unnecessary");
    }

    else{

        //Repeats until each entry has been sorted alphabetically
        //meaning no more switches can be made
        while (1) {

            //Resets current entry to beginning of list
            //Resets switches made to 0
            struct Book **CurrentEntry = Start;
            Switch = 0;

            //Repeats until whole list has been gone through
            while ((*CurrentEntry) != NULL && (*CurrentEntry)->next != NULL){

                //Compares author of current entry with next entry
                //Swaps position of entries if current entry is higher
                //(i.e higher in alphabet) than the next entry
                if (strcasecmp((*CurrentEntry)->Author, (*CurrentEntry)->next->Author) > 0){
                    struct Book *Temp = (*CurrentEntry)->next;
                    (*CurrentEntry)->next = Temp->next;
                    Temp->next = *CurrentEntry;
                    *CurrentEntry = Temp;

                    //Switch has been made
                    Switch = 1;
                }

                //Move to next entry
                CurrentEntry = &((*CurrentEntry)->next);
            }

            //If no more switches can be made, exit loop
            if (Switch == 0){
               break;
            }
        }

        //Output success message
        puts("\nData has been successfully sorted");

    }

    return *Start;
}