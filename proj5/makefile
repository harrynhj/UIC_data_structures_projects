build:
	rm -f tests.exe
	g++ -g -Wall tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	
run:
	./tests.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes -s ./tests.exe

gdb:
	gdb ./tests.exe

clean:
	rm -f tests.exe
	rm -rf build