srcs = binary_add bit_add bubble_sort construct_tree construct_tree_postorder insertion_sort linear_search merge_sort selection_sort shell_sort
all: $(srcs)

%: %.cc
	g++ -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
