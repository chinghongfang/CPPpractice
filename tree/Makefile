cmp: avl_tree.h red_black.h num.txt
	g++ -std=c++11 cmp.cpp -o cmp
num.txt: num.cpp
	g++ -std=c++11 num.cpp -o num
	./num
.PHONY: clean
clean:
	rm num num.txt cmp
