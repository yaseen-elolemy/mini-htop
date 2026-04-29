#include "lib.h"

int extractVal(const char *stat)
{
    int val;
    sscanf(stat, "%*s %d", &val);
    return val;
}

double* calcmem()      //mem to show  Used = MemTotal − MemFree − Buffers − Cached − SReclaimable
{
    int total, free, buffers, cached, sreclaimable;
    double dT, used;
    char line[256];
    char memTotal[256], memFree[256], memBuff[256], memCache[256], sRec[256];
    double *rVal = (double*)malloc(2 * sizeof(double));

    FILE *memf = fopen("/proc/meminfo", "r");
    if (memf == NULL)
    {
        return NULL;
    }

    fgets(memTotal, sizeof(memTotal), memf);
    fgets(memFree, sizeof(memFree), memf);
    fgets(line, sizeof(line), memf);    //exactly how much available
    fgets(memBuff, sizeof(memBuff), memf);
    fgets(memCache, sizeof(memCache), memf);

    for(int i = 0; i < 19; ++i)
    {
        fgets(line, sizeof(line), memf);
        if(i == 18)
        {
            strcpy(sRec, line);
        }
    }

    fclose(memf);

    total        = extractVal(memTotal);
    free         = extractVal(memFree);
    buffers      = extractVal(memBuff);
    cached       = extractVal(memCache);
    sreclaimable = extractVal(sRec);

    //Kibibyte to Gibibyte
    dT = (double) total / pow(2, 20);  
    used = (double) (total - free - buffers - cached - sreclaimable) / pow(2, 20);
    
    rVal[0] = dT;
    rVal[1] = used;

    return rVal;
}
