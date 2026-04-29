#include "lib.h"

#define MAX_PROCS 1024   //assume maximum size of process list of 512, not optimal but easier

FILE *fptr;


bool is_string_numeric(const char* str) {       //function to find out if string is only digits
    if (str == NULL || *str == '\0') return false;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

Process *proclist;  // like that its global

Process* listprocs(int *numprocs)    //define header as pointer
{

    proclist = (Process*)calloc(sizeof(Process), MAX_PROCS);
    Process p;
    char delimiter[] = " ";
	char *token;
    DIR *d;
    char fname[128];
    char fcontent[2048];
    struct dirent *dir;
    d = opendir("/proc");
    int i = 0;
    if (d)
    {
        while((dir = readdir(d)) != NULL)
        {
            if(is_string_numeric(dir -> d_name))   //if it is only digits, go into it, open /stat, get first two words. place into proclist then iterate i
            {
                snprintf(fname, sizeof(fname), "/proc/%s/stat", dir->d_name);
                fptr = fopen(fname, "r");
                fgets(fcontent, 2048, fptr);    //now fcontent contains file content as string
                    // This reads the PID and then specifically looks for characters inside ( )
                if (sscanf(fcontent, "%d (%[^)])", &proclist[i].pid, proclist[i].name) == 2) 
                {
                    i++;
                }
                fclose(fptr);
            }
        }
    }
    else{
        closedir(d);
    }

    *numprocs = i;
    return proclist;           //return address of first element
}