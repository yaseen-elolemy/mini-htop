// Author:  Yaseen Mohamed Kamal
// ID:		20230468
// Task: 	3


#include "lib/lib.h"
#include <ncurses.h>


// !!!Variable to be used by NCURSES: memdata, timedata, usage, procslist[i]


//#define MAX_PROC_LIST 1024
#define interval 1s

Process* procslist = NULL;

void printprocs(int *numprocs)
{
	for(int i = 0; i < *numprocs; ++i)
	{
		mvprintw(11 + i, 2, "%-5d %s", procslist[i].pid, procslist[i].name);
	}
	//printf("====================== END PROCESSES ======================\n");
}


void draw_bar(int row, int col, const char* label, double percentage) {
    int width = 20; 
    int filled = (int)((percentage / 100.0) * width);
	mvprintw(1,1, "press 'q' to quit. ");
    mvprintw(row, col, "%s: [", label);
    
    // decide color based on percentage
    if (percentage > 80) attron(COLOR_PAIR(3));
    else if (percentage > 50) attron(COLOR_PAIR(2));
    else attron(COLOR_PAIR(1));

    for (int i = 0; i < width; i++) {
        if (i < filled) printw("|");
        else printw(" ");
    }
    
    attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
    printw("] %.1f%%", percentage);
}


int main(int argc, char** argv)
{

	int numprocs = 0;
	//procslist = listprocs(&numprocs);

	initscr();          
	noecho();
	curs_set(0);      
	start_color();    
	init_pair(1, COLOR_GREEN, COLOR_BLACK); // Low usage
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Medium usage
	init_pair(3, COLOR_RED, COLOR_BLACK);    // High usage
	timeout(1000);        
	keypad(stdscr, TRUE);  
	
		
	double usage;	
	uptimeData timedata;		//3 items | refactored to C 
	double* memdata = malloc(sizeof(double) * 2);	//2 items
	


	while (true)
	{
		procslist = listprocs(&numprocs);
		memdata = calcmem();
		timedata = uptime();
		usage = calcusage();

		erase();
		draw_bar(3, 2, "CPU", usage); 
		mvprintw(4, 2, "Uptime: %02d:%02d:%02d\n", timedata.hrs, timedata.mins, timedata.secs);
		
		double mem_percent = (memdata[1] / memdata[0]) * 100.0;
		draw_bar(5, 2, "MEMORY", mem_percent);
		mvprintw(6, 2, "Mem: %.2fG/%.2fG\n", memdata[1], memdata[0]);
		mvprintw(7, 2, "Number of processes: %d", numprocs);
		mvhline(8, 0, '=', COLS);
		mvprintw(9, 2, "PID");
		mvprintw(9, 8, "command");
		printprocs(&numprocs);
		
		refresh();

		free(memdata);
		free(procslist);

		int ch = getch(); 
		if (ch == 'q') break;
	}

	endwin();
	return 0;
}
