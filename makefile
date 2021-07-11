
CC=g++
CFLAGS=-pipe -O2 -Wall -Wno-int-to-pointer-cast -Wno-unused-but-set-variable
LIBS=-lglfw -lGL -lGLEW

SRC=shaderutils glutils renderobjects renderer texture
LIBSRC=stb_image.cpp
OBJ=$(addsuffix .o,${SRC})

.PHONY: clean

%.o: %.cpp headers/%.h
	$(CC) $(CFLAGS) -c $<

lowpoly: lowpoly.cpp ${OBJ} lib/${LIBSRC}
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm lowpoly *.o
