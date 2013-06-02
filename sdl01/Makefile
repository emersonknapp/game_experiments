# Makefile to build monte_pi_sprng program
# --- macros
CC=gcc
CFLAGS=  -Wall `sdl-config --cflags` -I/opt/X11/include
OBJECTS= main.o
LIBS= `sdl-config --libs` -L/opt/X11/lib -lSDL -lGL -lGLU
EXE= main


# --- targets
all: sdl01
sdl01: $(OBJECTS) 
	$(CC) -o $(EXE) $(OBJECTS) $(LIBS)
        
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp


# --- remove binary and executable files
clean:
	rm -f $(EXE) $(OBJECTS)
	