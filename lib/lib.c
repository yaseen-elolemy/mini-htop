#include "lib.h"

#define SLEEP_TIME 1

typedef long long ll;

// TODO: THIS CONTAINS A MATHEMATICAL BUG IN THE CALCULATION INTERVAL

typedef struct {
    ll idle;
    ll total;
} CpuData;


double domath(ll idle1, ll idle2, ll total1, ll total2)
{
    double deltaIdle  = (double)(idle2 - idle1);
    double deltaTotal = (double)(total2 - total1);
    return (1.0 - (deltaIdle / deltaTotal)) * 100.0;
}


// Extract idle (col 4) and sum all numeric columns from a /proc/stat line
CpuData sumline(const char *stat)
{
    CpuData data = {0, 0};
    char buf[256];
    strncpy(buf, stat, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    int i = 0;
    char *token = strtok(buf, " \t\n");
    while (token != NULL) {
        if (i == 4)
            data.idle = atoll(token);   // 5th token (0-idx) is idle
        if (i >= 1)
            data.total += atoll(token); // skip the leading "cpu" label
        i++;
        token = strtok(NULL, " \t\n");
    }
    return data;
}


double calcusage()
{
    char   stat[256];
    CpuData data1, data2;
    FILE  *procstat;

    procstat = fopen("/proc/stat", "r");
    fgets(stat, sizeof(stat), procstat);
    fclose(procstat);
    data1 = sumline(stat);

    sleep(SLEEP_TIME);

    procstat = fopen("/proc/stat", "r");
    fgets(stat, sizeof(stat), procstat);
    fclose(procstat);
    data2 = sumline(stat);

    return domath(data1.idle, data2.idle, data1.total, data2.total);
}