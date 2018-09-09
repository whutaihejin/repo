all: fwide

fwide:
	g++ fwide.cc -o $@

clean:
	find . -type f -perm "u=rwx,go=rx" -exec rm {} \;
