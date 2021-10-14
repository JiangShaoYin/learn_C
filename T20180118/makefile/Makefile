SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
main:$(OBJS)
	gcc $^ -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) main
