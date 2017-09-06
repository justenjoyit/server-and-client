all : TimeServer TimeClient

TimeServer : TimeServer.c
	g++ -o TimeServer TimeServer.c

TimeClient : TimeClient.c
	g++ -o TimeClient TimeClient.c

clean:
	rm -rf TimeServer
	rm -rf TimeClient
