#include <stdio.h>
#include <./threads/thread.h>
#include <./threads/synch.h>
#include <random.h>

struct semaphore smoker1,smoker2,smoker3,agent;

void smoker1_fun(void *aux){
    while(1){
    sema_down(&smoker1);
    printf("SMOKER-1 is Smoking (agent puts paper)\n");
    sema_up(&agent);
    }
}



void smoker2_fun(void *aux){



            while(1){
    sema_down(&smoker2);
    printf("SMOKER-2 is Smoking (agent puts tobacco)\n");
    sema_up(&agent);
    }

}



void smoker3_fun(void *aux){

        while(1){
    sema_down(&smoker3);
    printf("SMOKER-3 is Smoking (agent puts match)\n");
    sema_up(&agent);
    }
}

void agent_fun(void *aux){
        int i=0;
    while(i<15){
        sema_down(&agent);

        long num=random_ulong()%3;

        switch(num){
            case 0 : sema_up(&smoker1);
                break;
            case 1 : sema_up(&smoker2);
                break;
            case 2 : sema_up(&smoker3);
                break;
        }
        i++;

    }


}



void test_5cs03(void){
    sema_init(&smoker1,0);
    sema_init(&smoker2,0);
    sema_init(&smoker3,0);
    sema_init(&agent,1);
    thread_create("thread1",1,smoker1_fun,NULL);
    thread_create("thread2",2,smoker2_fun,NULL);
    thread_create("thread3",2,smoker3_fun,NULL);
    thread_create("thread4",3,agent_fun,NULL);

}