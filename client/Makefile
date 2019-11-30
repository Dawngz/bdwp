SR:=$(wildcard *.c)
OS:=$(SR:%.c=%.o)
ELF:=a.out
CC:=gcc -w
$(ELF):$(OS)
	gcc $^ -o $@ -lcrypt
.PHONY:clean
clean:
	rm $(ELF) $(OS)
