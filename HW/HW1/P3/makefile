++ = g++  
CFLAGS = -O2 -fsanitize=undefined -fsanitize=address -std=c++17  

target: p3.cpp
	@$(++) $(CFLAGS) p3.cpp -o p3
	./p3 < ./testcase/sample1.txt
	./p3 < ./testcase/sample2.txt
	./p3 < ./testcase/sample3.txt

make clean:
	rm -f p3