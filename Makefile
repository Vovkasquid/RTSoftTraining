all: 
	make --directory=Day_1
	make --directory=Day_2
	make --directory=Day_3
clean:
	make clean --directory=Day_1
	make clean --directory=Day_2
	make clean --directory=Day_3

