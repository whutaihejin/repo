# scan all source file with suffix '.cc or .c'
src := $(sort $(wildcard *.cc *.c))

# pattern replacement: '%.cc => % and %.c => %'
target := $(patsubst %.cc, %, $(src:.c=))

all: $(target)
# @echo "target => " $(target)

% : %.cc
	$(CXX) -std=c++17 -g -O0 $< -o $@

% : %.c
	$(CC) -std=c17 -g -O0 $< -o $@

clean:
	rm -rf *.dSYM $(target)
