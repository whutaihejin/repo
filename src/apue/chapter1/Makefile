srcs = my_ls
all: $(srcs)

%: %.c
	gcc -g -fno-inline-functions -g -O0 -std=c99 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
