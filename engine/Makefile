CC = g++
LD = g++ -g

CFLAGS = -c -g

all: init contest_engine

contest_engine: build/main.o build/client.o build/world.o build/random.o build/visualizer.o build/logger.o
	@echo "Linking [$@]..."
	@$(LD) -o bin/$@ $^
	@echo
	@echo "---------------------------------------"
	@echo
	@echo "Run with bin/$@"

build/main.o: src/puckman.cc src/defines.h src/World.h src/Client.h src/Random.h src/Visualizer.cc src/Visualizer.h src/Logger.cc src/Logger.h
	@echo "Building [$@]..."
	@$(CC) $(CFLAGS) -o $@ $<

build/logger.o: src/Logger.cc src/Logger.h
	@echo "Building [$@]..."
	@$(CC) $(CFLAGS) -o $@ $<

build/client.o: src/Client.cc src/defines.h src/World.h src/Client.h
	@echo "Building [$@]..."
	@$(CC) $(CFLAGS) -o $@ $<

build/world.o: src/World.cc src/defines.h src/World.h src/Client.h src/Random.h
	@echo "Building [$@]..."
	@$(CC) $(CFLAGS) -o $@ $<

build/random.o: src/Random.cc src/Random.h
	@echo "Building [$@]..."
	@$(CC) $(CFLAGS) -o $@ $<

build/visualizer.o: src/Visualizer.cc src/Visualizer.h
	@echo "Building [$@]..."
	@$(CC) $(CFLAGS) -o $@ $<


init:
	@echo "Configuring build environment..."
	@mkdir -p build
	@mkdir -p bin

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf build bin


.PHONY: init clean