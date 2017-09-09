CC:=clang++
CFLAGS:=-Wall -c -g -std=c++11
LDFLAGS:=-Wall -lgmp -lgmpxx -pthread
SOURCES:=$(wildcard *.cpp)
EXECUTABLE=task_1 task_2 task_3 task_4 task_5

all: $(SOURCES) $(EXECUTABLE)

task_1: task_1.o
	$(CC) task_1.o -o $@ $(LDFLAGS) 

task_2: task_2.o
	$(CC) task_2.o -o $@ $(LDFLAGS)

task_3: task_3.o
	$(CC) task_3.o -o $@ $(LDFLAGS)

task_4: task_4.o
	$(CC) task_4.o -o $@ $(LDFLAGS)

task_5: task_5.o
	$(CC) task_5.o -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(EXECUTABLE) *.o

