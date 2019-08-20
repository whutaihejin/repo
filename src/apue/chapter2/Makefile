srcs = env limits
all: $(srcs)

%: %.c
	gcc -O0 -std=c99 -o $@ $<

%: %.cc
	g++ -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
