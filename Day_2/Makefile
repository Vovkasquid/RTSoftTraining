TARGET=thread1
TARGET1=thread2
TARGET2=thread3
TARGET3=HWT
FLAGS=-lpthread
all: $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3)
$(TARGET): thread1.o
	gcc thread1.o -o $(TARGET) $(FLAGS)
thread1.o: thread1.c
	gcc thread1.c -c
$(TARGET1): thread2.o
	gcc thread2.o -o $(TARGET1) $(FLAGS)
thread2.o: thread2.c
	gcc thread2.c -c
$(TARGET2): thread3.o
	gcc thread3.o -o $(TARGET2) $(FLAGS)
thread3.o: thread3.c
	gcc thread3.c -c
$(TARGET3): HomeWorkThreads.o
	gcc HomeWorkThreads.o -o $(TARGET3) $(FLAGS)
HomeWorkThreads.o: HomeWorkThreads.c
	gcc HomeWorkThreads.c -c
clean:
	rm -f *.o $(TARGET)
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f $(TARGET3)
