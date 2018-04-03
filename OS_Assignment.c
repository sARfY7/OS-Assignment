#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

char Game[] = "Playing Game";

sem_t stud, tech, staff, game,tgame,stgame,stud_lock,tech_lock,staff_lock;

int timeStart = 6, timeEnd = 7;

int studentCount = 0;
void *student(void *n)
{
    int studentN = (int) n;

    sem_wait(&game);
    sem_wait(&stud);
    int flag = 0;
    if ((timeStart >= 6) && (timeEnd <= 22))
    {
        studentCount++;
        if (studentCount == 1)
        {
            sem_wait(&tech);
            sem_wait(&staff);
            flag = 1;
        }
        else
        {
            flag=1;
        }
    }
    printf("Student %d Process Started\n", studentN);
    if (flag == 1)
    {
        //critical section add game
        printf("Student %d %s\n", studentN, Game);
        sleep(2);
        printf("Student %d Game Ended\n", studentN);
    }

    studentCount--;
    if (studentCount == 0)
    {
        sem_post(&tech);
        sem_post(&staff);
    }
    sem_post(&stud);
    sem_post(&game);
   
    pthread_exit(NULL);
}

int teacherCount = 0;
void *teacher(void *n)
{
    int teacherN = (int) n;

    sem_wait(&game);
    
    sem_wait(&tech);
    int flag = 0;
    if ((timeStart >= 8) && (timeEnd <= 17))
    {
        printf("hello\n");
        teacherCount++;
        if (teacherCount == 1)
        {
            sem_wait(&stud);
            sem_wait(&staff);
            flag = 1;
        }
        else
        {
            flag = 1;
        }
    }
    printf("Teacher %d Process Started\n", teacherN);
    if (flag == 1)
        {
        //critical section add game
        printf("Teacher %d %s\n", teacherN, Game);
        sleep(2);
        printf("Teacher %d Game Ended\n", teacherN);
    }
    teacherCount--;
    if (teacherCount == 0)
    {
        sem_post(&stud);
        sem_post(&staff);
    }
    sem_post(&tech);
   
    sem_post(&game);
    pthread_exit(NULL);
}

int techStaffCount = 0;
void *tech_staff(void *n)
{
    int techStaffN = (int) n;
    sem_wait(&game);
    
    sem_wait(&staff);
    int flag = 0;
    techStaffCount++;
    //printf("hello");
    if (techStaffCount == 1)
    {
        sem_wait(&stud);
        sem_wait(&tech);
        flag = 1;
    }
    else
    {
       
        flag = 1;
    }

    
    printf("TechStaff %d Process Started\n", techStaffN);
    if (flag == 1)
    {
        //critical section add game
        printf("TechStaff %d %s\n", techStaffN, Game);
        sleep(2);
        printf("TechStaff %d Game Ended\n", techStaffN);
    }

    techStaffCount--;
    if (techStaffCount == 0)
    {
        sem_post(&stud);
        sem_post(&tech);
    }
    sem_post(&staff);
   sem_post(&game);
    
    pthread_exit(NULL);
}

int main()
{
    pthread_t st, st1, th, th1, sf, sf1;
    sem_init(&stud, 0, 1);
    sem_init(&tech, 0, 1);
    sem_init(&staff, 0, 1);
    sem_init(&game, 0, 1);
    sem_init(&tgame, 0, 1);
    sem_init(&stgame, 0, 1);
    int a=1;
    pthread_create(&st, NULL, student, (void *) a);
    pthread_create(&th, NULL, teacher, (void *) a);
    a++;
     pthread_create(&sf, NULL, tech_staff, (void *) 1);
    pthread_create(&st1, NULL, student, (void *) a);
    pthread_create(&th1, NULL, teacher, (void *)a);
     pthread_create(&sf1, NULL, tech_staff, (void *) 2);
    pthread_join(st, NULL);
    pthread_join(th, NULL);
     pthread_join(sf, NULL);
    pthread_join(st1, NULL);
    pthread_join(th1, NULL);
     pthread_join(sf1, NULL);
}
