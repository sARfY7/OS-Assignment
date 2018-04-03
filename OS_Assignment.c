#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

struct tm * timeinfo;

sem_t stud,tech,staff,scommon,tscommon,tcommon;

void gettime()
{
    time_t rawtime;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

}

int scount=0;
void *student()
{
    sem_wait(&stud);
    sem_wait(&scommon);
    int flag=0;
    //printf("%d\n",timeinfo->tm_hour);
    if(timeinfo->tm_hour>=22||(timeinfo->tm_hour<6))
    {
         //printf("hello");
        scount++;
        if(scount==2)
        {
            sem_wait(&tech);
            sem_wait(&staff);
            flag=1;
        }
        else
        {
            printf("student Need 1 more player\n");
            flag=0;
        }

    }
    sem_post(&scommon);
    printf("student process\n");
    if(flag==1)
    {
        //critical section add game
        printf("student lets start the match\n");
        sleep(5);
    }

    sem_wait(&scommon);
        if(scount==2)
        {
            sem_post(&tech);
            sem_post(&staff);
            scount=0;
        }
    sem_post(&scommon);
    sem_post(&stud);

    

pthread_exit(NULL);
}

int tcount=0;
void *teacher()
{

    sem_wait(&tech);
    sem_wait(&tcommon);
    int flag=0;
    if((timeinfo->tm_hour>=17)||(timeinfo->tm_hour<8))
    {
        printf("hello");
        tcount++;
        if(tcount==2)
        {
            sem_wait(&stud);
            sem_wait(&staff);
            flag=1;
        }
        else
        {
            printf("techer Need 1 more player\n");
            flag=0;
        }

    }
    sem_post(&tcommon);

    printf("teacher process\n");
    if(flag==1)
    {
        //critical section add game
        printf("teacher lets start the match\n");
        sleep(5);
    }

    sem_wait(&tcommon);
        if(tcount==2)
        {
            sem_post(&stud);
            sem_post(&staff);
            scount=0;
        }
    sem_post(&tcommon);
    sem_post(&tech);

pthread_exit(NULL);
}

int tscount=0;
void *tech_staff()
{

    sem_wait(&staff);
    sem_wait(&tscommon);
    int flag=0;
    tscount++;
     //printf("hello");
        if(tscount==2)
        {
            sem_wait(&stud);
            sem_wait(&tech);
            flag=1;
        }
        else
        {
            printf("staff Need 1 more player\n");
            flag=0;
        }

    sem_post(&tscommon);

    printf("tech staff process\n");
    if(flag==1)
    {
        //critical section add game
        printf("staff lets start the match\n");
        sleep(5);
    }

    sem_wait(&tscommon);
        if(tcount==2)
        {
            sem_post(&stud);
            sem_post(&tech);
            scount=0;
        }
    sem_post(&tscommon);
    sem_post(&staff);

pthread_exit(NULL);
}

int main()
{
    pthread_t st,st1,th,th1,sf,sf1;
    sem_init(&stud,0,2);
    sem_init(&tech,0,2);
    sem_init(&staff,0,2);
    sem_init(&scommon,0,1);
    sem_init(&tcommon,0,1);
    sem_init(&tscommon,0,1);
    gettime();
    pthread_create(&st,NULL,student,NULL);
    pthread_create(&th,NULL,teacher,NULL);
    pthread_create(&sf,NULL,tech_staff,NULL);
    pthread_create(&st1,NULL,student,NULL);
    pthread_create(&th1,NULL,teacher,NULL);
    pthread_create(&sf1,NULL,tech_staff,NULL);
    pthread_join(st,NULL);
    pthread_join(th,NULL);
    pthread_join(sf,NULL);
    pthread_join(st1,NULL);
    pthread_join(th1,NULL);
    pthread_join(sf1,NULL);

}
