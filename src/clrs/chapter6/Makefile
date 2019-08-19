srcs = build_heap heap_sort k_merge_sort less max_heapify min_heapify priority_queue t winner_tree
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
