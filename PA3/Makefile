all:
	gcc -std=c99 -o vmm ./vmm_main.c

run:
	./vmm < ./input/linear-access.txt > your-linear-stat-result.txt 2> your-linear-result.txt
	./vmm < ./input/random-access.txt > your-random-stat-result.txt 2> your-random-result.txt

clean:
	rm vmm your-linear-result.txt your-linear-stat-result.txt your-random-result.txt your-random-stat-result.txt
