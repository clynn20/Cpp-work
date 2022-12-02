CC = g++ -std=c++11
exe_file = program
$(exe_file): prog.o budget_buddy.o
	     $(CC) prog.o budget_buddy.o -o $(exe_file)
budget_buddy.o: budget_buddy.cpp
	     $(CC) -c budget_buddy.cpp
prog.o: prog.cpp
	     $(CC) -c prog.cpp
clean:	 
	rm -f *.out *.o $(exe_file)