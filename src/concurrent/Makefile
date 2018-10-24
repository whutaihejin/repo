all: wait launch_thread

% : %.cc
	g++ -std=c++11 -pthread -o $@ $<

clean:
	rm -rf wait launch_thread
