srcs = error_handling my_ls my_shell process_id raw_copy signal_shell std_copy user_id
all: $(srcs)

%: %.c
	gcc -fno-inline-functions -O0 -std=c99 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
