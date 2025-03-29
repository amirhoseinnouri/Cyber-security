CC=g++
CFLAGS=-fPIC -shared -ldl

all: rootkit hook

rootkit: src/main.cpp src/utils.cpp
	$(CC) -o rootkit src/main.cpp src/utils.cpp

hook: src/hook.cpp
	$(CC) $(CFLAGS) -o hook.so src/hook.cpp

clean:
	rm -f rootkit hook.so
