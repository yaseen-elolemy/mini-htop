#pragma once

#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string.h>



// =============================== PID ==========================================


typedef struct Process Process;

struct Process{
    char name[256];
    int pid;
};


Process* listprocs(int *numprocs);

// =============================== MEM STAT =====================================


double* calcmem();


// =============================== CALC UPTIME ==================================

typedef struct uptimeData uptimeData;

struct uptimeData
{
	int hrs;
	int mins;
	int secs;
};

uptimeData uptime();

// =============================== PROC STAT ====================================

typedef long long ll;

double calcusage();     // returns usage percentage
