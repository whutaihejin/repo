#
CFLAGS=-Wall -DNDEBUG -march=native -ffast-math -std=c++11 -O0 -g -fPIC -Ithird_party/RoutingKit/include

# scan all source file with suffix '.cc or .c'
src := $(sort $(wildcard *.cc *.c))

# pattern replacement: '%.cc => % and %.c => %'
target := $(patsubst %.cc, %, $(src:.c=))

all: $(target)
# @echo "target => " $(target)

% : %.cc
	$(CXX) $(CFLAGS) $< -o $@

% : %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.dSYM $(target)
