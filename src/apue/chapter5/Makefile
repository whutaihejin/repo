all: fwide temporary_files t5.9

%: %.cc
	g++ -w -o $@ $<

clean:
	find . -type f -perm "u=rwx,go=rx" -exec rm {} \;
