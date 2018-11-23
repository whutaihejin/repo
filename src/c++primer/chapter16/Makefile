srcs = flexible_array_member rvalue_ref t16.1 t16.2
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
