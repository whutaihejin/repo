# scan all source file with suffix '.cc or .c'
src := $(sort $(wildcard *.cc *.c))

# pattern replacement: '%.cc => % and %.c => %'
target := $(patsubst %.cc, %, $(src:.c=))

all: $(target)

% : %.cc
	$(CXX) -std=c++11 -g -O0 $< -o $@

% : %.c
	$(CC) -std=c11 -g -O0 $< -o $@

clean:
	rm -rf *.dSYM $(target)
