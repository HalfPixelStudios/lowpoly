
CC=g++
CFLAGS=-pipe -O2 -Wall -Wno-int-to-pointer-cast -Wno-unused-but-set-variable -Ilib
LIBS=-lglfw -lGL -lGLEW

SRC=shaderutils glutils renderobjects renderer texture
OBJ=$(addsuffix .o,${SRC})
LIBOBJ=lib/stb_image/stb_image.o $(shell ls lib/imgui/*.cpp | sed 's/\.cpp/\.o/')

.PHONY: clean clean-lib

$(LIBSRC)/stb_image/%.cpp: $(LIBSRC)/stb_image/%.h
	$(CC) $(CFLAGS) -c $<

$(LIBSRC)/imgui/%.cpp: $(LIBSRC)/imgui/%.h
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp headers/%.h
	$(CC) $(CFLAGS) -c $<

lowpoly: lowpoly.cpp ${OBJ} ${LIBOBJ}
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm lowpoly *.o

clean-lib:
	find lib -name "*.o" -type f -delete
