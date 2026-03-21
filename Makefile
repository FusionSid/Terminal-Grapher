all: graph

graph: main.c screen.c
	@clang -o graph.out main.c screen.c

clean:
	rm graph