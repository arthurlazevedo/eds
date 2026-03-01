.PHONY: all run ra rl
all: arrayl linked
run: ra rl

# run arrayl
ra: arrayl
	./arrayl/arrayl

arrayl: arrayl/arrayl.c
	gcc -o arrayl/arrayl arrayl/arrayl.c

# run linked
rl: linked
	./linked/linked

linked: linked/linked.c
	gcc -o linked/linked linked/linked.c