#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



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
int deleteTask ();

int countTasks ();

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
            case 'Q':
                printf("Have a good time!!\n");
                running = false;
                break;
        }

    } while (running);

    return 0;
}

int readBulkTasks () {
    countedTasks = countTasks();
    if ( countedTasks > 0 ) {
        for ( int i = 0; i < countedTasks; i++ ) {
            printf("TASK: %s\n", tasks[i].taskName);
            printf("PRIORITY: %s\n", tasks[i].priority);
            printf("STATUS: %s\n", tasks[i].status);
            printf("DATE: %d-%d-%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
        }
        appState = 'H';

    } else {
        printf("To see all tasks you need to create new one \n");
        appState = 'C';
    }
}

int createTask () {
    printf("*****************************************************\n");
    printf("******************* CREATE TASK *********************\n");
    printf("*****************************************************\n");

    char taskName[50], priority[50], status[50], checkAdd;
    int insertCount, day, month, year;
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
            strcpy(task.status, status);

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

int countTasks () {
    int count = 0;

    for ( int i = 0; i < 30; i++) {
        if ( strlen( tasks[i].taskName  ) > 0 ) {
                count++;
        }
    }

    return count;
}













