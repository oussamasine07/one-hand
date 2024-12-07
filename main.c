#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>



// declare needed variables
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int isValide;
    int message[50];
} ValideDate;

typedef struct {
    int id;
    char taskName[50];
    char priority[50];
    char status[50];
    Date date;
} Task;

// create an array where we can store intstances of person
Task tasks[30];

char appState = 'H';
int currentTaskIdx = 0;
int countedTasks = 0;
int searchId;
char inputId[20];

// Declare needed functions
// create a new task
int createTask ();

// read one single task
int readTask (int id );

// read bulk of taskes
int readBulkTasks ();

// update task
int updateTask ( int id );

// delete task
int deleteTask ( int id );

int countTasks ();

int filterTasks ();

int applyFiler ( char choice[50], char filter[50] );

int validateInts ( char chars[50] );

char validateFields ();

ValideDate validateDate ( int day, int month, int year );

int saveFile ( Task tasks[30] );

int readTaskFile ();

int showHeader ( char header[50] );

int test ( int nums[4] );

int main()
{
    int nums[4] = {1,2,3,4};
    test( nums );
    for ( int i = 0; i < 4; i++ ) {
        printf("%d ", nums[i] );
    }

    /*
    printf("ONE HAND\n");
    printf("Your favorit task manager\n");

    // create a variable named running to keep the uplication running until you stop it
    _Bool running = true;
    _Bool userCheck = true;
    _Bool inputCheck;


    // run the application
    do {
        // create a switch statment to keep track state of the current session if it's create, read delete or update
        switch (appState) {

            case 'H':
                printf("please enter one of these letters (C,B,R,U,D,Q)\n");
                printf("C => create a new task\n");
                printf("R => read single task by ID\n");
                printf("B => read all tasks\n");
                printf("U => update a task\n");
                printf("D => delete a task \n");
                printf("Q => to quite the application\n");
                printf("Your choice: ");
                scanf("%s", &appState);

                do {
                    if (appState == 'C' || appState == 'R' || appState == 'B' || appState == 'U' || appState == 'D' || appState == 'F' || appState == 'Q') {
                        userCheck = false;
                    }
                    else {
                        printf("invalide charachter, you should type only (C,R,B,U,D,F,Q) \n");
                        scanf("%s", &appState);
                    }
                } while (userCheck);

                break;
            case 'B':
                readBulkTasks();
                break;
            case 'C':
                createTask();
                break;
            case 'R':
                inputCheck = true;
                printf("Please enter Task ID ");
                scanf("%s", &inputId);

                do {
                    if ( validateInts( inputId ) ) {
                        inputCheck = false;
                        searchId = validateInts( inputId );
                    }
                    else {
                        printf("please inter a valide ID, we accept only integers ");
                        scanf("%s", inputId);
                    }
                } while( inputCheck );

                readTask( searchId );
                break;
            case 'U':
                inputCheck = true;
                printf("Please enter Task ID ");
                scanf("%s", &inputId);

                do {
                    if ( validateInts( inputId ) ) {
                        inputCheck = false;
                        searchId = validateInts( inputId );
                    }
                    else {
                        printf("please inter a valide ID, we accept only integers ");
                        scanf("%s", inputId);
                    }
                } while( inputCheck );

                updateTask( searchId );
                break;
            case 'D':
                printf("Please enter Task ID you want to delete ");
                scanf("%d", &searchId);
                deleteTask( searchId );
                break;
            case 'Q':
                printf("Have a good time!!\n");
                running = false;
                break;
        }

    } while (running);
    */
    return 0;
}

int showHeader ( char header[50] ) {
    printf("*******************************************************\n");
    printf("********************* %s **********************\n", header);
    printf("*******************************************************\n");
}

int createTask () {
    showHeader("CREATE TASK");

    char taskName[50], checkAdd, userInputCount[20];
    int insertCount, day, month, year, status, priority;
    _Bool adding = true, validating = true;

    // ask the user to enter how many tasks he want to enter
    printf("please enter how many tasks you want to enter ");
    scanf("%s", &userInputCount);

    do {
        if ( validateInts( userInputCount ) ) {
            validating = false;
            insertCount = validateInts( userInputCount );
        }
        else {
            printf("Invalid number please enter valide integer ");
            scanf("%s", &userInputCount);
        }
    } while ( validating );


    while ( adding ) {
        for ( int i = 0; i < insertCount; i++ ) {
            printf("Please enter task name ");
            scanf(" %[^\n]", &taskName);

            printf("Please enter Priority \n");
            printf("1. low\n");
            printf("2. high\n");
            scanf("%d", &priority);

            // validate priority field
            validating = true;
            do {
                if ( priority == 1 || priority == 2 ) {
                    validating = false;
                }
                else {
                    printf("You can only choose a valid priority (1,2,3)");
                    scanf("%d", &priority);
                }
            } while ( validating );

            printf("Please enter status: \n");
            printf("1. Todo\n");
            printf("2. Working\n");
            printf("3. Done\n");
            printf("Make your choice ");
            scanf("%d", &status);

            // validate status field, force the user user to inter only (1,2,3)
            validating = true;
            do {
                if ( status == 1 || status == 2 || status == 3 ) {
                    validating = false;
                }
                else {
                    printf("You can only choose a valid status (1,2,3)");
                    scanf("%d", &status);
                }
            } while(validating);

            printf("Please enter a valide date it should be like so (dd-mm-yyyy) ");
            scanf("%d-%d-%d", &day, &month, &year); // user input 12-11-2024

            // validate date formate
            validating = true;
            ValideDate result;
            result = validateDate(day, month, year);

            do {
                if ( result.isValide ) {
                    validating = false;
                }
                else {
                    printf("%s", result.message);
                    printf("Please re-enter a valide date dd-mm-yyyy ");
                    scanf("%d-%d-%d", &day, &month, &year);
                }
            } while ( validating );

            // create an instance
            Task task;
            task.id = currentTaskIdx + 1;
            strcpy(task.taskName, taskName);


            switch ( priority ) {
                case 1:
                    strcpy(task.priority, "low" );
                    break;
                case 2:
                    strcpy(task.priority, "high" );
                    break;
            }

            switch ( status ) {
                case 1:
                    strcpy(task.status, "todo" );
                    break;
                case 2:
                    strcpy(task.status, "working" );
                    break;
                case 3:
                    strcpy(task.status, "done" );
            }

            task.date.day = day;
            task.date.month = month;
            task.date.year = year;

            tasks[currentTaskIdx] = task;

            currentTaskIdx++;

            saveFile(tasks);

        }

        printf("do you want to add more tasks ");
        scanf("%s", &checkAdd);

        if ( checkAdd == 'Y' ) {
            printf("please enter how many tasks you want to add ");
            scanf("%d", &insertCount);
        }
        else {
            printf("=============== TASK CREATED ==============\n");
            printf("\n");
            appState = 'H';
            adding = false;
        }
    }
}

int readTask ( int id ) {
    countedTasks = countTasks();
    int found = 0;

    if (countedTasks > 0) {
        for ( int i = 0; i < countedTasks; i++ ) {
            if ( tasks[i].id == id ) {
                // call the function that shows  task fields
                showFields( tasks[i] );
                found = 1;
                break;
            }
        }
        if ( !found ) {
            printf("This task does not exists\n");
        }
        appState = 'H';
    }
    else {
        printf("the list of tasks is empty, you new create task at first\n");
        appState = 'C';
    }
}

int readBulkTasks () {
    countedTasks = countTasks();
    char confirmFilter;

    _Bool filtering = true;
    // check if the list of tasks is empty, than redirect user to create a new task
    if ( countedTasks > 0 ) {
        // ask user if he want to filter tasks
        printf("Do you want to apply filters ");
        scanf("%s", &confirmFilter);
        // force the user to enter one of (Y/N)
        do {
            if ( confirmFilter == 'Y' || confirmFilter == 'N' ) {
                filtering = false;
            }
            else {
                printf("Invalid character to confirm enter (Y) to cancel enter (N)");
                scanf("%s", &confirmFilter);
            }
        } while (filtering);

        if ( confirmFilter == 'Y' ) {
            filterTasks();
        }
        else {
            printf("\n");
            printf("================== ALL TASKS ==================\n");
            for ( int i = 0; i < countedTasks; i++ ) {
                showFields( tasks[i] );
            }
            printf("===============================================\n");
            printf("\n");
        }
        // return the app to it's initial state
        appState = 'H';

    } else {
        printf("To see all tasks you need to create new one \n");
        appState = 'C';
    }
}

int updateTask ( int id ) {
    countedTasks = countTasks();
    int found = 0, idx = 0, i, fields[4] = {0}, choice, day, month, year;
    char taskName[50], date[50], fieldsInputs[20];

    _Bool checkChoice, dateCheck, validating = true;


    // check if the list is empty then redirect user to create new tasks
    if (countedTasks > 0) {

        printf("Please choose the fields you want to update\n");
        printf("1. task name\n");
        printf("2. task priority\n");
        printf("3. task status\n");
        printf("4. task date\n");
        printf("To choose enter number of fields like ex:142 ");
        scanf("%s", &fieldsInputs);

        // check if all chars are integrs
        do {
            idx = 0;

            if ( validateInts( fieldsInputs ) ) {
                //validating = false;
                for ( i = 0; i < strlen(fieldsInputs); i++ ) {
                    fields[idx] = fieldsInputs[i] - '0';
                    // check if integers are included in (1,2,3,4)
                    if ( fields[idx] == 1 || fields[idx] == 2 || fields[idx] == 3 || fields[idx] == 4 ) {
                        validating = false;
                    }
                    else {
                        printf("the spesified fields don't exist, please enter one of these\n");
                        printf("1. task name\n");
                        printf("2. task priority\n");
                        printf("3. task status\n");
                        printf("4. task date\n");
                        printf("make your choice ");
                        scanf("%s", &fieldsInputs);
                    }
                    idx++;
                }
            }
            else {
                printf("invalide characters please enter a valide numbers ");
                scanf("%s", &fieldsInputs);
            }
        } while( validating );

        // loop through all tasks
        for ( int i = 0; i < countedTasks; i++ ) {
            // get task by id
            if ( tasks[i].id == id ) {
                // loop through the fields, that the user intered to update
                for ( int j = 0; j < 4; j++ ) {

                    if ( fields[j] == 1 ) {
                        printf("edit task name ");
                        scanf(" %[^\n]", &taskName);
                        strcpy(tasks[i].taskName, taskName );
                    }
                    else if ( fields[j] == 2 ) {
                        printf("Please choose one of the allowed priorities\n");
                        printf("1. low\n");
                        printf("2. high\n");
                        printf("make a choice ");
                        scanf("%d", &choice);
                        // for the user to enter 1 or 2
                        validating = true;
                        do {
                            if ( choice == 1 || choice == 2 ) {
                                validating = false;
                            }
                            else {
                                printf("please you can only enter (1,2)");
                                scanf("%d", &choice);
                            }
                        } while ( validating );
                        // update priority based on user choice
                        if ( choice == 1 ) {
                            strcpy(tasks[i].priority, "low" );
                        }
                        else if ( choice == 2 ) {
                            strcpy(tasks[i].priority, "high" );
                        }
                    }
                    else if ( fields[j] == 3 ) {
                        printf("Please choose one of the allowed statuses\n");
                        printf("1. todo\n");
                        printf("2. working\n");
                        printf("3. done\n");
                        printf("make a choice ");

                        scanf("%d", &choice);
                        // we need to force the user enter only (1,2,3)
                        validating = true;
                        do {
                            if ( choice == 1 || choice == 2 || choice == 3 ) {
                                validating = false;
                            } else {
                                printf("You should only choose one of these numbers (1,2,3) ");
                                scanf("%d", &choice);
                            }
                        } while( validating );

                        if ( choice == 1 ) {
                            strcpy(tasks[i].status, "todo");
                        }
                        else if ( choice == 2 ) {
                            strcpy( tasks[i].status, "working" );
                        }
                        else if ( choice == 3 ) {
                            strcpy( tasks[i].status, "done" );
                        }
                    }
                    else if ( fields[j] == 4 ) {
                        printf("Please enter a valide date it should be like so (dd-mm-yyyy) ");
                        scanf("%d-%d-%d", &day, &month, &year);

                        ValideDate result;
                        result = validateDate(day, month, year);
                        validating = true;

                        do {
                            if ( result.isValide ) {
                                validating = false;
                            }
                            else {
                                printf("%s", result.message);
                                printf("Please re-enter a valide date dd-mm-yyyy ");
                                scanf("%d-%d-%d", &day, &month, &year);
                            }
                        } while ( validating );

                        tasks[i].date.day = day;
                        tasks[i].date.month = month;
                        tasks[i].date.year = year;
                    }

                }

                found = 1;
                break;
            }
        }
        if ( !found ) {
            printf("This task does not exists\n");
        }

        appState = 'H';
    }
    else {
        printf("the list of tasks is empty, you new create task at first\n");
        appState = 'C';
    }
}

int deleteTask ( int id ) {
    // find the task;
    int countedTasks = countTasks();
    int found = 0,  idx = -1;
    char name[50], confirm;

    if ( countedTasks > 0) {
        // do this code
        for ( int i = 0; i < countedTasks; i++ ) {
            if ( tasks[i].id == id ) {
                // get the user you want to delete
                idx = i;
                strcpy(name, tasks[i].taskName);
                found = 1;
            }
        }

        // check if the task exists
        if (!found) {
            printf("This task is NOT FOUND!!");
        }
        else {
            printf("Are you sure you want to delete <<<%s>>> ?, Type (Y/N)", name);
            scanf("%s", &confirm);
            if ( confirm == 'Y' ) {
                if ( idx != -1 ) {
                    for ( int i = idx; i < countedTasks; i++ ) {
                        tasks[i] = tasks[i+1];
                    }
                }
            }
            else {
                printf("Deleting Canceled!!");
            }
            appState = 'H';
        }
    }
    else {
        printf("Task list is empty, you need to create one at first\n");
        appState = 'C';
    }
}

int countTasks () {
    int count = 0;

    for ( int i = 0; i < 30; i++) {
        if ( strlen( tasks[i].taskName  ) > 0 ) {
                count++;
        }
    }

    return count;
}

int filterTasks () {

    countedTasks = countTasks();

    printf("please select how you want to filter your tasks\n");
    printf("1. Priority\n");
    printf("2. Status\n");

    int fieldChoice, filter;
    _Bool validating = true;
    char choice[50], field[50], choiceValue[50];

    scanf("%d", &fieldChoice);

    do {
        if ( fieldChoice == 1 || fieldChoice == 2 ) {
            validating = false;
        }
        else {
            printf("Invalid choice, you're allowed to choose only (1,2) ");
            scanf("%d", &fieldChoice);
        }
    } while ( validating );

    if ( fieldChoice == 1 ) {
        // filter by priority
        printf("choose priority level: \n");
        printf("1. low\n");
        printf("2. high\n");
        scanf("%d", &filter);

        strcpy(choice, "priority");

        if ( filter == 1 ) {
            strcpy(choiceValue, "low");
        }
        else if ( filter == 2 ) {
            strcpy(choiceValue, "high");
        }
    }
    else if ( fieldChoice == 2 ) {
        // filter statuse
        printf("choose status type: \n");
        printf("1. todo\n");
        printf("2. working\n");
        printf("3. done\n");

        scanf("%d", &filter);

        strcpy( choice, "status" );
        if ( filter == 1 ) {
            strcpy(choiceValue, "todo");
        }
        else if ( filter == 2 ) {
            strcpy(choiceValue, "working");
        }
        else if ( filter == 3 ) {
            strcpy(choiceValue, "done");
        }
    }

    applyFiler( choice, choiceValue );
    appState = 'H';
}

int applyFiler ( char choice[50], char filter[50] ) {
    int notFound = 0;
    printf("\n");
    printf("================== FILTERED TASKS ==================\n");
    for ( int i = 0; i < countedTasks; i++ ) {
        // apply filter, to filter by priority or status
        if ( strcmp( choice, "priority" ) == 0 ) {
            if ( strcmp(tasks[i].priority, filter) == 0 ) {
                showFields( tasks[i] );
            }
            else {
                notFound = 1;
            }
        }
        else if ( strcmp( choice, "status") == 0 ) {
            if ( strcmp(tasks[i].status, filter) == 0 ) {
                showFields( tasks[i] );
            }
            else {
                notFound = 1;
            }
        }
    }
    printf("===============================================\n");
    printf("\n");
    if ( notFound ) {
        printf("No task with this filter\n");
    }

}

int showFields ( Task task ) {
    printf("================== TASK ID: %d =================\n", task.id );
    printf("TASK NAME: %s\n", task.taskName);
    printf("PRIORITY: %s\n", task.priority);
    printf("STATUS: %s\n", task.status);
    printf("DATE: %d-%d-%d\n", task.date.day, task.date.month, task.date.year);
}

int validateInts ( char input[50] ) {
    int isValid = 1;

    // Check if all characters in the input are digits
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            isValid = 0;
            break;
        }
    }

    if (isValid) {
        int number = atoi(input);  // Convert string to integer if valid
        return number;
    } else {
        return 0;
    }
}

ValideDate validateDate ( int day, int month, int year ) {

    // get current date
    struct tm newDate = {0};
    time_t newTime;
    time(&newTime);
    struct tm *currentDate = localtime( &newTime );

    ValideDate validate;

    if ( year < currentDate->tm_year + 1900 ) {
        validate.isValide = 0;
        strcpy(validate.message, "The year you have entered is out dated\n");
        return validate;
    }
    else {
        // check if month is valide
        if ( month > 12 ) {
            validate.isValide = 0;
            strcpy(validate.message, "Invalide month\n");
            return validate;
        }
        else {
            // check if month is out dated
            if ( month >= currentDate->tm_mon + 1 ) {

                // force the user to enter a valid day for a specific month ( ex: febrerary => no more than 29 days )
                switch (month) {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        if ( day >= 32) {
                            validate.isValide = 0;
                            strcpy(validate.message, "Invalide day, you can enter only up to 31\n");
                            return validate;
                        }
                        else {
                            // check if the day is out dated
                            if ( month == currentDate->tm_mon + 1 && day < currentDate->tm_mday ) {
                                validate.isValide = 0;
                                strcpy(validate.message, "the day you have entered is out dated\n");
                                return validate;
                            }
                            else {
                                validate.isValide = 1;
                                return validate;
                            }
                        }
                        break;

                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        if ( day >= 31 ) {
                            validate.isValide = 0;
                            strcpy(validate.message, "Invalide day, you can enter only up to 30\n");
                            return validate;
                        }
                        else {
                            // check if the day is out dated
                            if ( month == currentDate->tm_mon + 1 && day < currentDate->tm_mday ) {
                                validate.isValide = 0;
                                strcpy(validate.message, "the day you have entered is out dated\n");
                                return validate;
                            }
                            else {
                                validate.isValide = 1;
                                return validate;
                            }
                        }
                        break;
                    case 2:
                        if ( day >= 30 ) {
                            validate.isValide = 0;
                            strcpy(validate.message, "Invalide day, you can enter only up to 29\n");
                            return validate;
                        }
                        else {
                            // check if the day is out dated
                            if ( month == currentDate->tm_mon + 1 && day < currentDate->tm_mday ) {
                                validate.isValide = 0;
                                strcpy(validate.message, "the day you have entered is out dated\n");
                                return validate;
                            }
                            else {
                                validate.isValide = 1;
                                return validate;
                            }
                        }
                        break;
                }

            }
            else {
                validate.isValide = 0;
                strcpy(validate.message, "the month you have entered is outdated\n");
                return validate;
            }
        }
    }
}

int saveFile ( Task tasks[30] ) {
    countedTasks = countTasks();
    int countedTasks = countTasks();
    FILE *file = fopen("tasks.xml", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return an error code
    }

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<tasks>\n");

    for (int i = 0; i < countedTasks; i++) {
        fprintf(file, "    <task>\n");
        fprintf(file, "        <taskName>%d</taskName>\n", tasks[i].id);
        fprintf(file, "        <taskName>%s</taskName>\n", tasks[i].taskName);
        fprintf(file, "        <taskName>%s</taskName>\n", tasks[i].priority);
        fprintf(file, "        <taskName>%s</taskName>\n", tasks[i].status);
        fprintf(file, "        <taskName>%d-%d-%d</taskName>\n", tasks[i].date);
        fprintf(file, "    </task>\n");
    }

    fprintf(file, "</tasks>\n");

    fclose(file);
    return 0; // Indicate success
}

int readTaskFile () {

    countedTasks = countTasks();
    int countedTasks = countTasks();
    FILE *file = fopen("tasks.xml", "r");

    if ( file == NULL ) {
        printf("this does not exists yet\n");
    }

}

int test ( int nums[4] ) {

    for ( int i = 0; i < 4 / 2; i++ ) {
        int temp = nums[4 - i - 1];
        nums[4 - i - 1] = nums[i];
        nums[i] = temp;
    }

    return 0;

}

