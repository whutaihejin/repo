srcs = call_order counter hanppen_before launch launch_thread parallel_accu wait
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
