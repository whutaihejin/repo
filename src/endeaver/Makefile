srcs = copy_on_write jump ladder reverse singleton sorted_array_to_bst sorted_list_to_bst test
all: $(srcs)

%: %.cc
	g++ -g -fno-inline-functions -g -O0 -std=c++11 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
