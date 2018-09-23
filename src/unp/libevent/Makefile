all: block_http_client

%: %.c
	gcc -o $@ $<

clean:
	find . -type f -perm /111 -exec rm {} \;
