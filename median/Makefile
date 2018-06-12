all: functional basicops execution

functional:
	gcc -o functional_test functional_test.c algorithms.c data.c -lm

basicops:
	gcc -o basic_operations basic_operations.c algorithms_ops.c data.c -lm

execution:
	gcc -o execution_time execution_time.c algorithms.c data.c -lm

clean:
	rm -f functional_test basic_operations execution_time memcpy_test
