srcs = alarm itimer nanosleep timed_read timerfd
all: $(srcs)

%: %.c
	gcc -D_POSIX_C_SOURCE=200809 -fno-inline-functions -std=c99 -O0 -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
