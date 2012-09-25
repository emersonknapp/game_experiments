#Space invaders makefile
CC=g++
cc=gcc

OPT = -g -Wall
#OPT += -O3

UNAME := $(shell uname)

#-LIBRARIES AND INCLUDES
FRAMEWORK = -framework GLUT -framework OpenGL -framework Accelerate
LIBS = -lGL -lGLU -lm -lstdc++ -larmadillo
INCS = -I./include

#Mac specific includes
ifeq ($(UNAME), Darwin)
LIBS += -L"/System/Library/Frameworks/OpenGL.framework/Libraries" 
#LIBS += -L"/System/Library/Frameworks/GLUT.framework/Libraries"

INCS += -I"/System/Library/Frameworks/OpenGL.framework/Headers"
INCS += -I"/System/Library/Frameworks/GLUT.framework/Headers"
endif


#FLAGS
CCOPTS = $(OPT) $(INCS) -c
LDOPTS = $(OPT) $(INCS) $(LIBS)

#USEFUL INFORMATION
SOURCES=classes.cpp entity.cpp main.cpp mesh.cpp scene.cpp
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
