all: fwide temporary_files t5.9 file_lock process_lock

%: %.cc
	g++ -w -o $@ $<

clean:
	find . -type f -perm "u=rwx,go=rx" -exec rm {} \;
