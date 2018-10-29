all: wait launch_thread parallel_accu

% : %.cc
	g++ -g -std=c++11 -pthread -o $@ $<

clean:
	rm -rf wait launch_thread parallel_accu
