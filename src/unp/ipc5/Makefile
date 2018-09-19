all: mqcreate mqunlink 

%: %.cc
	g++ -o $@ $< -lrt

clean:
	find . -type f -perm "u=rwx,go=rx" -exec rm {} \;
