srcs = abort mask reentrant sig_global_val sig_set sigaction sigcld siglongjmp signal sigpenging sigsuspend
all: $(srcs)

%: %.c
	gcc -g -O0 -std=c99 -o $@ $<

%: %.cc
	g++ -g -O0 -std=c++11 -lpthread -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
