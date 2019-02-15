srcs = matrix_chain robbery test
all: $(srcs)

%: %.cc
	g++ -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
