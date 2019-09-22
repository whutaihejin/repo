srcs = error_handling itimer my_ls my_shell process_id raw_copy signal_shell std_copy timerfd user_id
all: $(srcs)

%: %.c
	gcc -D_POSIX_C_SOURCE=200809 -fno-inline-functions -std=c99 -O0 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
