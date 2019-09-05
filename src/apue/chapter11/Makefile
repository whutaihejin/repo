srcs = pthread_barrier pthread_clean pthread_cond pthread_create pthread_deadlock pthread_deadlock2 pthread_deadlock3 pthread_deadlock4 pthread_exit pthread_join pthread_mutex pthread_ref pthread_rwlock pthread_timedlock
all: $(srcs)

%: %.c
	gcc -g -O0 -std=c99 -o $@ $<

%: %.cc
	g++ -g -O0 -std=c++11 -lpthread -o $@ $<

clean:
	rm -rf $(srcs)
	rm -rf *.dSYM
