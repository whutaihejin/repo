srcs = limits
all: $(srcs)

%: %.c
	gcc -fno-inline-functions -O0 -std=c99 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
