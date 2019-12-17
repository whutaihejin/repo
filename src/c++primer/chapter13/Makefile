src := $(sort $(wildcard *.cc))

target := $(patsubst %.cc, %, $(src))

all: $(target)
	@echo "target => " $(target)

% : %.cc
	g++ -std=c++11 -g -O0 $< -o $@

clean:
	rm -rf $(target)
