FLAGS=-lpthread
TARGET=main
TARGET1=HMD3
all: $(TARGET) $(TARGET1)
$(TARGET): main.o
	gcc main.o -o $(TARGET) $(FLAGS)
main.o: main.c
	gcc main.c -c
$(TARGET1): HWMutCond.o
	gcc HWMutCond.o -o $(TARGET1) $(FLAGS)
HWMutCond.o: HWMutCond.c
	gcc HWMutCond.c -c
clean:
	rm -f *.o $(TARGET)
	rm -f $(TARGET1)
