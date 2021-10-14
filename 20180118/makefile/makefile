sources:=$(wildcard *.c)
objs:=$(patsubst %.c,%.o,$(sources))
main:$(objs)
	gcc $^ -o $@
.PHONY:clean
clean:
	rm -f  $(objs)

