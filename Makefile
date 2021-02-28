
target: golomb_coder 

golomb_coder: golomb_coder.c encode.c
	gcc -Wall -o $@ $^ -lz -lm
