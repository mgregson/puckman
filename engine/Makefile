CC = g++
LD = g++

CFLAGS = -c

all: init contest_engine

contest_engine: build/main.o build/client.o build/world.o build/random.o
	$(LD) -o bin/$@ $^

build/main.o: src/puckman.cc src/defines.h src/World.h src/Client.h src/Random.h
	$(CC) $(CFLAGS) -o $@ $<

build/client.o: src/Client.cc src/defines.h src/World.h src/Client.h
	$(CC) $(CFLAGS) -o $@ $<

build/world.o: src/World.cc src/defines.h src/World.h src/Client.h src/Random.h
	$(CC) $(CFLAGS) -o $@ $<

build/random.o: src/Random.cc src/Random.h
	$(CC) $(CFLAGS) -o $@ $<

init:
	mkdir -p build
	mkdir -p bin

clean:
	rm -rf build
	rm -rf bin

.PHONY: init clean