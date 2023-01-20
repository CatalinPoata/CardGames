.PHONY: clean
build:
	gcc -o tema1 ./tema1.c

run: 
	./tema1


clean: 
	rm -rf ./tema1 ./in ./out