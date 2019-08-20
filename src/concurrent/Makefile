srcs = counter counter hanppen_before hanppen_before launch launch launch_thread launch_thread parallel_accu parallel_accu wait wait
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
