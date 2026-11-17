# Link compiled object files into the final Windows executable
main.exe: Calculator_Engine.o main.o
	g++ Calculator_Engine.o main.o -o main.exe

# Compile the core calculator engine source into an object file
Calculator_Engine.o: Calculator_Engine.cpp
	g++ Calculator_Engine.cpp -c -o Calculator_Engine.o

# Compile the application entry point into an object file
main.o: main.cpp
	g++ main.cpp -c -o main.o

# Remove generated object files and executable to clean the build directory
clean:
	del *.o *.exe