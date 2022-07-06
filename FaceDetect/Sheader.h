/*
* RECEIVER
*/

#pragma once
#pragma comment(lib, "ws2_32.lib")

#define PKT 1024
#define FILEMAX 100000

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
using namespace std;
const int MasterPort = 4321;
int BasePort = 8080, clientcnt = 0, pddcnt = 0;

class stream {
private:
	WSADATA wsa;
	SOCKET server, client;
	SOCKADDR_IN addr = { 0 }, clientaddr = { 0 };
	int clientsize;

public:
	stream() { }
	stream(SOCKET s, int port) {
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return;

		server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server == INVALID_SOCKET) return;

		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;

		if (:: bind(server, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) return;
		if (listen(server, SOMAXCONN) == SOCKET_ERROR) return;

		send(s, "adds", PKT, 0);

		cout << "Listening from client... " << port - BasePort << endl;

		clientsize = sizeof(clientaddr);
		client = accept(server, (SOCKADDR*)&clientaddr, &clientsize);
		if (client == INVALID_SOCKET) return;

		cout << "Joined a client number " << port - BasePort << endl;
	}
	SOCKET& GetClient() { return this->client; }
}; vector<stream>streams;

typedef struct __data_T {
	char filepath[PKT] = { 0 },
		filename[PKT] = { 0 };
	int number;
	__data_T() { }
	__data_T(const char* f1, const char* f2) {
		strcpy_s(filepath, f1);
		strcpy_s(filename, f2);
	}
}Pdata; vector<Pdata>pdd;
