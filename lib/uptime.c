#include "lib.h"


uptimeData uptime()		//extract uptime as double
{
	uptimeData ret;
	FILE *fptr = fopen("/proc/uptime", "r");
	char contents[256];
	fgets(contents, 256, fptr);
	double itime;
	itime = atof(contents);


	double hrs, mins, secs;
	hrs = itime / 3600;
	ret.hrs = (int) hrs;

	hrs = fmod(hrs, 1.0);
	mins = hrs * 60;
	ret.mins = (int) mins;

	mins = fmod(mins, 1.0);
	secs = mins*60;
	ret.secs = (int) secs;


	return ret;
}