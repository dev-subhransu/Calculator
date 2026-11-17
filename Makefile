main.exe: Calculator_Engine.o main.o
	g++ Calculator_Engine.o main.o -o main.exe

Calculator_Engine.o: Calculator_Engine.cpp
	g++ Calculator_Engine.cpp -c -o Calculator_Engine.o

main.o: main.cpp
	g++ main.cpp -c -o main.o

clean:
	del *.o *.exe