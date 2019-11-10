srcs=helloworld
all: $(srcs)

%: %.go
	go build $<
%: %.cc
	echo "hh"

clean:
	rm -rf $(srcs)
