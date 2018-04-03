#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

char Game[] = "Playing Game";

sem_t stud, tech, staff, game;

int timeStart = 6, timeEnd = 7;

int studentCount = 0;
void *student(void *n)
{
    int studentN = (int) n;
    sem_wait(&stud);
    sem_wait(&game);
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
            printf("Student %d Need one more player\n", studentN);
            flag = 0;
        }
    }
    sem_post(&game);
    sem_post(&stud);
    printf("Student %d Process Started\n", studentN);
    if (flag == 1)
    {
        //critical section add game
        printf("Student %d %s\n", studentN, Game);
        sleep(2);
    }

    sem_wait(&game);
    if (studentCount == 1)
    {
        sem_post(&tech);
        sem_post(&staff);
        studentCount = 0;
    }
    sem_post(&game);
    sem_post(&stud);

    pthread_exit(NULL);
}

int teacherCount = 0;
void *teacher(void *n)
{
    int teacherN = (int) n;
    sem_wait(&tech);
    sem_wait(&game);
    int flag = 0;
    if ((timeStart >= 8) && (timeEnd <= 17))
    {
        //printf("hello");
        teacherCount++;
        if (teacherCount == 2)
        {
            sem_wait(&stud);
            sem_wait(&staff);
            flag = 1;
        }
        else
        {
            printf("techer Need 1 more player\n");
            flag = 0;
        }
    }
    sem_post(&game);
    sem_post(&tech);
    printf("Teacher %d Process Started\n", teacherN);
    if (flag == 1)
    {
        //critical section add game
        printf("Teacher %d %s\n", teacherN, Game);
        sleep(2);
    }

    sem_wait(&game);
    if (teacherCount == 2)
    {
        sem_post(&stud);
        sem_post(&staff);
        studentCount = 0;
    }
    sem_post(&game);
    sem_post(&tech);

    pthread_exit(NULL);
}

int techStaffCount = 0;
void *tech_staff(void *n)
{
    int techStaffN = (int) n;
    sem_wait(&staff);
    sem_wait(&game);
    int flag = 0;
    techStaffCount++;
    //printf("hello");
    if (techStaffCount == 2)
    {
        sem_wait(&stud);
        sem_wait(&tech);
        flag = 1;
    }
    else
    {
        printf("staff Need 1 more player\n");
        flag = 0;
    }

    sem_post(&game);

    printf("TechStaff %d Process Started\n", techStaffN);
    if (flag == 1)
    {
        //critical section add game
        printf("TechStaff %d %s\n", techStaffN, Game);
        sleep(2);
    }

    sem_wait(&game);
    if (teacherCount == 2)
    {
        sem_post(&stud);
        sem_post(&tech);
        studentCount = 0;
    }
    sem_post(&game);
    sem_post(&staff);

    pthread_exit(NULL);
}

int main()
{
    pthread_t st, st1, th, th1, sf, sf1;
    sem_init(&stud, 0, 2);
    sem_init(&tech, 0, 2);
    sem_init(&staff, 0, 2);
    sem_init(&game, 0, 1);
    pthread_create(&st, NULL, student, (void *) 1);
    pthread_create(&th, NULL, teacher, (void *) 1);
    // pthread_create(&sf, NULL, tech_staff, (void *) 1);
    pthread_create(&st1, NULL, student, (void *) 2);
    pthread_create(&th1, NULL, teacher, (void *) 2);
    // pthread_create(&sf1, NULL, tech_staff, (void *) 2);
    pthread_join(st, NULL);
    pthread_join(th, NULL);
    // pthread_join(sf, NULL);
    pthread_join(st1, NULL);
    pthread_join(th1, NULL);
    // pthread_join(sf1, NULL);
}
