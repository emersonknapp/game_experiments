LIBPATH = \
	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
	-L/usr/local/lib \
	-L$$HOME/lib/tinyxml2/lib/

INCLUDE = \
	-I. \
	-I/usr/local/include \
	-I$$HOME/lib/eigen3.2.0 \
	-I$$HOME/lib/tinyxml2
	

FRAMEWORK = \
	-framework OpenGL \
	-framework GLUT \
	-framework CoreFoundation

COMPILERFLAGS = -Wall
CC = clang++
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lGL -lGLU -lSOIL -ltinyxml2

SOURCES= \
	src/main.cpp \
	src/player.cpp \
	src/animation.cpp \
	src/game.cpp
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(OBJECTS): build/%.o : src/%.cpp 
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FRAMEWORK) $(LIBRARIES) $(CFLAGS) -o $@ $(LIBPATH) $(OBJECTS)

clean:
	rm -f build/*.o $(EXECUTABLE)
