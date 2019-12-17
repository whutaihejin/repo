# scan all source file with suffix '.cc'
src := $(sort $(wildcard *.cc *.c))

# pattern replacement: '%.cc => %'
target := $(src:.cc=)
target := $(target:.c=)
# equivalent statement for above
# target := $(patsubst %.cc, %, $(src))

all: $(target)
	@echo "target => " $(target)

% : %.cc
	$(CXX) -std=c++11 -g -O0 $< -o $@

% : %.c
	$(CC) -std=c11 -g -O0 $< -o $@

clean:
	rm -rf $(target)
