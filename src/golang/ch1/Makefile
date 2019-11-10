srcs= dup1 dup2 dup3 echo1 echo2 echo3 fetch fetchall helloworld lissajous
all: $(srcs)

%: %.go
	go build $<

%: %.cc
	gcc -O0 -o $@ $<

clean:
	rm -rf $(srcs)
