srcs = echo_all exec1 fork fork_buf fork_with_thread pid race_condition race_condition_child race_condition_parent twice_fork vfork wait
all: $(srcs)

%: %.c
	gcc -g -O0 -std=c99 -o $@ $<

%: %.cc
	g++ -g -O0 -std=c++11 -lpthread -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
