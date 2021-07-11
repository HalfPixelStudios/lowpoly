
CC=g++
CFLAGS=-Wall -Wno-int-to-pointer-cast
LIBS=-lglfw -lGL -lGLEW
# LIBS=-lglfw -lGL -lX11 -lGLEW -lpthread -lXrandr -lXi -ldl

SRC=shaderutils glutils renderobjects renderer
OBJ=$(addsuffix .cpp,${SRC})

.PHONY: clean

%.o: %.cpp headers/%.h
	$(CC) $(CFLAGS) -c $<

lowpoly: lowpoly.cpp ${OBJ}
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm lowpoly *.o
