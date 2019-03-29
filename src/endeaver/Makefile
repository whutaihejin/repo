srcs = modular_arithmetic multiply robbery test unit_set
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
