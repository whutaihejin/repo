all: block_http_client stdarg_test

%: %.c
	gcc -o $@ $<

clean:
	find . -type f -perm /111 -exec rm {} \;
