srcs = acquire_release acquire_release2 call_order counter hanppen_before launch launch_thread memory_barriers non_atomic_order parallel_accu relaxed_order relaxed_order_2 release_consume release_sequence sequential_consistent transitive_acquire_release transitive_acquire_release2 wait
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
