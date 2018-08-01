all: echo_server echo_client dns

echo_server:
	g++ -O2 echo_server.cc -o echo_server
	g++ -O2 socket_hostent.cc -o dns

echo_client:
	g++ -O2 echo_client.cc -o echo_client

clean:
	rm echo_server echo_client dns
