all: mqcreate mqunlink mqgetattr mqcreate2 mqsend mqreceive

%: %.cc
	g++ -o $@ $< -lrt

clean:
	find . -type f -perm "u=rwx,go=rx" -exec rm {} \;
