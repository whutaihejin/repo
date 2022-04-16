all: block_http_client stdarg_test attribute

%: %.c
	gcc -Wall -o $@ $<

clean:
	find . -type f -perm /111 -exec rm {} \;
