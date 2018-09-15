all: pipe

%: %.cc
	gcc -o $@ $<

clean:
	find . -type f -perm "u=rwx,go=rx" -exec rm {} \;
