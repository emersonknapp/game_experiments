#Space invaders makefile
CC=g++
cc=gcc

OPT = -g -Wall
#OPT += -O3

UNAME := $(shell uname)

#-LIBRARIES AND INCLUDES
FRAMEWORK = -framework GLUT -framework OpenGL
LIBS = -lGL -lGLU -lm -lstdc++ -lfreetype -lftgl
INCS = -I.
INCS += -I./include

#Mac specific includes
ifeq ($(UNAME), Darwin)
#LIBS += -L"/System/Library/Frameworks/OpenGL.framework/Libraries" 
LIBS += -L"/usr/X11/lib"
LIBS += -L"/usr/local/Cellar/ftgl/2.1.3-rc5/lib"

#INCS += -I"/System/Library/Frameworks/OpenGL.framework/Headers"
#INCS += -I"/System/Library/Frameworks/GLUT.framework/Headers"
INCS += -I"/usr/X11/include/GL"
INCS += -I"/usr/local/Cellar/ftgl/2.1.3-rc5/include"
INCS += -I"/usr/X11/include/freetype2"
INCS += -I"/usr/local/Cellar/eigen/3.0.5/include/eigen3"
endif


#FLAGS
CCOPTS = $(OPT) $(INCS) -c
LDOPTS = $(OPT) $(INCS) $(LIBS)

#USEFUL INFORMATION
SOURCES=renderer.cpp renderable.cpp quits.cpp input.cpp viewport.cpp state.cpp si_states.cpp si_game.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

#RULES
all: $(SOURCES) $(EXECUTABLE)

clean:
	/bin/rm -f *.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FRAMEWORK) $(OBJECTS) $(LDOPTS) -o $@

.cpp.o:
	$(CC) $(CCOPTS) $< -o $@
