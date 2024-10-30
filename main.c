#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



// declare needed variables
typedef struct {
    int day;
    int month;
    int year;
} Date;

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

int main()
{
    printf("ONE HAND\n");
    printf("Your favorit task manager\n");

    // create a variable named running to keep the uplication running until you stop it
    _Bool running = true;
    _Bool userCheck = true;


    // run the application
    do {
        // create a switch statment to keep track state of the current session if it's create, read delete or update
        switch (appState) {

            case 'H':
                printf("please enter one of these letters (C,B,R,U,D)\n");
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
                printf("Please enter Task ID ");
                scanf("%d", &searchId);
                readTask( searchId );
                break;
            case 'U':
                printf("Please enter Task ID ");
                scanf("%d", &searchId);
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

    return 0;
}


int createTask () {
    printf("*****************************************************\n");
    printf("******************* CREATE TASK *********************\n");
    printf("*****************************************************\n");

    char taskName[50], priority[50], checkAdd;
    int insertCount, day, month, year, status;
    _Bool adding = true;

    // ask the user to enter how many tasks he want to enter
    printf("please enter how many tasks you want to enter ");
    scanf("%d", &insertCount);

    while ( adding ) {
        for ( int i = 0; i < insertCount; i++ ) {
            printf("Please enter task name ");
            scanf("%s", &taskName);

            printf("Please enter priority level ");
            scanf("%s", &priority);

            printf("Please enter status: \n");
            printf("1. Todo\n");
            printf("2. Working\n");
            printf("3. Done\n");
            printf("Make your choice ");
            scanf("%d", &status);

            _Bool statusCheck = true;
            do {
                if ( status == 1 || status == 2 || status == 3 ) {
                    statusCheck = false;
                }
                else {
                    printf("You can only choose (1,2,3)");
                    scanf("%d", &status);
                }
            } while(statusCheck);


            printf("Day: ");
            scanf("%d", &day);

            printf("Month: ");
            scanf("%d", &month);

            printf("Year: ");
            scanf("%d", &year);

            // create an instance
            Task task;
            task.id = currentTaskIdx + 1;
            strcpy(task.taskName, taskName);
            strcpy(task.priority, priority);

            if ( status == 1 ) {
                strcpy(task.status, "todo" );
            }
            else if ( status == 1 ) {
                strcpy(task.status, "working" );
            }
            else if ( status == 1 ) {
                strcpy(task.status, "done" );
            }


            task.date.day = day;
            task.date.month = month;
            task.date.year = year;

            tasks[currentTaskIdx] = task;

            currentTaskIdx++;

        }

        printf("do you want to add more tasks ");
        scanf("%s", &checkAdd);

        if ( checkAdd == 'Y' ) {
            printf("please enter how many tasks you want to add ");
            scanf("%d", &insertCount);
        }
        else {
            printf("task created \n");
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
                printf("TASK: %s\n", tasks[i].taskName);
                printf("PRIORITY: %s\n", tasks[i].priority);
                printf("STATUS: %s\n", tasks[i].status);
                printf("DATE: %d-%d-%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
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

    if ( countedTasks > 0 ) {
        printf("Do you want to apply filters ");
        scanf("%s", &confirmFilter);

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
            for ( int i = 0; i < countedTasks; i++ ) {
                printf("TASK: %s\n", tasks[i].taskName);
                printf("PRIORITY: %s\n", tasks[i].priority);
                printf("STATUS: %s\n", tasks[i].status);
                printf("DATE: %d-%d-%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
            }
        }

        appState = 'H';

    } else {
        printf("To see all tasks you need to create new one \n");
        appState = 'C';
    }
}

int updateTask ( int id ) {
    countedTasks = countTasks();
    int found = 0;
    char taskName[50], priority[50], status[50], checkAdd, date[50];
    int insertCount, day, month, year;

    if (countedTasks > 0) {
        for ( int i = 0; i < countedTasks; i++ ) {
            if ( tasks[i].id == id ) {
                printf("Please enter Task name or enter (E) to keep it as it is ");
                scanf("%s", &taskName);

                if ( strcmp(taskName, "E") != 0 ) {
                    strcpy(tasks[i].taskName, taskName );
                }

                printf("Please enter Task priority or enter (E) to keep it as is ");
                scanf("%s", &priority);
                if ( strcmp( priority, "E" ) != 0 ) {
                    strcpy(tasks[i].priority, priority );
                }

                printf("Please enter Task status or enter (E) to keep it as is Or (M) to modify ");
                scanf("%s", &status);
                if ( strcmp( status, "E" ) != 0 ) {
                    printf("Please choose one of the allowed statuses\n");
                    printf("1. todo\n");
                    printf("2. working\n");
                    printf("3. done\n");
                    printf("make a choice ");

                    int choice;
                    scanf("%d", &choice);

                    // we need to force the user enter only (1,2,3)
                    _Bool checkChoice = true;
                    do {
                        if ( choice == 1 || choice == 2 || choice == 3 ) {
                            checkChoice = false;
                        } else {
                            printf("You should only choose one of these numbers (1,2,3) ");
                            scanf("%d", &choice);
                        }
                    } while( checkChoice );

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

                printf("Please enter Task Date or enter (E) to keep it as is ");
                scanf("%s", &date);
                printf("Compare date => %d \n", strcmp( date, "E" ));

                if ( strcmp( date, "E" ) != 0 ) {
                    printf("Please enter Day");
                    scanf("%d", &day);
                    tasks[i].date.day = day;

                    printf("Please enter Month");
                    scanf("%d", &month);
                    tasks[i].date.month = month;

                    printf("Please enter Year");
                    scanf("%d", &year);
                    tasks[i].date.year = year;
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

    int filterChoice, fieldChoice, filter;
    _Bool fieldCheck = true;
    _Bool choiceCheck = true;
    char choice[50], field[50], choiceValue[50];

    scanf("%d", &fieldChoice);

    do {
        if ( fieldChoice == 1 || fieldChoice == 2 ) {
            fieldCheck = false;
        }
        else {
            printf("Invalid choice, you're allowed to choose only (1,2) ");
            scanf("%d", &filterChoice);
        }
    } while ( fieldCheck );

    if ( fieldChoice == 1 ) {
        // filter by priority
        printf("choose priority level: \n");
        printf("1. low\n");
        printf("2. high\n");
        scanf("%d", &filter);

        strcpy(choice, "priority");

        if ( filter == 1 ) {
            strcpy(choiceValue, "high");
        }
        else if ( filter == 2 ) {
            strcpy(choiceValue, "low");
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

    if ( notFound ) {
        printf("No task with this filter\n");
    }

}

int showFields ( Task task ) {

    printf("ID: %d\n", task.id);
    printf("TASK NAME: %s\n", task.taskName);
    printf("PRIORITY: %s\n", task.priority);
    printf("STATUS: %s\n", task.status);
    printf("DATE: %d-%d-%d\n", task.date.day, task.date.month, task.date.year);

}









