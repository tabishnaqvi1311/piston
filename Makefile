all: piston

piston: main.o huffman.o display.o
	clang++ main.o huffman.o display.o -o piston

main.o:
	clang++ -c src/main.cpp

huffman.o:
	clang++ -c src/huffman.cpp

display.o:
	clang++ -c src/display.cpp

clean:
	@rm -rf main.o display.o huffman.o