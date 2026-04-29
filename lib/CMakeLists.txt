add_library(mylib
 			lib.c 
			uptime.c
			memspace.c
			procs.c)

target_include_directories(mylib
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR})

