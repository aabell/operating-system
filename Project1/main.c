//
//  main.c
//  Project1
//
//  Created by Abel Tilahun on 4/17/18.
//  Copyright © 2018 Abel Tilahun. All rights reserved.
//

#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <unistd.h>

int main()
{
    char *ptr;
    
    int ShareMemory;
    
    key_t key;
    
    key = 500;
    
    //create shared memory
    ShareMemory = shmget(key,20*sizeof(char),IPC_CREAT|0666);
    
    if(ShareMemory < 0 )
    {
        perror("Error creating shared memory: ");
        
        return -1;
    }
    
    
    //allocate memory
    ptr = (char*)shmat(ShareMemory,(char*)0,0);
    
    //child process
     pid_t pid = fork();
    
    if( pid == 0 )
    {
        
        strcpy(ptr,"Assigment Project one");
        
        printf("Child with pid %d writes %s word into shared memory\n",getpid(),ptr);
    
    }
    
    else
    //parent process
    {
        wait(0);
        
        printf("Parent with pid %d reads from shared memory: %s\n",getpid(),ptr);
    }
    
    //delete pid_t shared memory
    shmctl(ShareMemory,IPC_RMID,0);
    
    return 0;
}
