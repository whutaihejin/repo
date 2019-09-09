srcs = abs_int t14.2.1 t14.2.2 t14.9.2
all: $(srcs)

%: %.c
	gcc -g -O0 -std=c99 -o $@ $<

%: %.cc
	g++ -g -O0 -std=c++11 -lpthread -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
