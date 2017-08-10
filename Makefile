pc: pc.c 
	gcc -Wall -g $^ -lm -o $@ -pthread

.PHONY: clean
clean:
	rm -rf pc
