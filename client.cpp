#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4996)
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include "common.h"
#pragma comment(lib, "Ws2_32.lib")

#define PORT 9000
using namespace std;


int send_data(int n_socket)
{
	char buffer[256] = { 0, };
	cin >> buffer;
	send(n_socket, buffer, 256, 0);
	return 0;
}

int receive_data(int n_socket )
{
	char buffer[256] = { 0, };
	std::cout << n_socket << endl;
	recv(n_socket, buffer, 255, 0);
	std::cout << "Press ENTER to see the reply from Server:  ";
	getchar();
	cout << endl << "Messge: " << buffer << endl; return 0;
}







int main() {
	

	fd_set fr, fw, fe;
	int n_socket = setup();
	char buffer[256] = { 0 };
	
	struct sockaddr_in config_sock;
	config_sock.sin_family = AF_INET;
	config_sock.sin_addr.s_addr = inet_addr("/**Enter your IP address**/");
	config_sock.sin_port = htons(PORT);
	memset(&(config_sock.sin_zero), 0, 8);
	

	int connect_req = connect(n_socket, (sockaddr*)&config_sock, sizeof(config_sock));

	if (connect_req < 0) {
		std::cout << " No connection" << endl;
		WSACleanup();
	}
	else {
		std::cout << "Connection Successful" << endl;
		int opt,p, checker = 0;
		char  buffer1[] = { 0 };
		while (checker==0)
		{
			std::cout << "Select operation: 1. Send Data. 2. Receieve Data 3.Terminate connection.";
			cin >> opt;
			switch (opt)
			{

			case 1: send_data(n_socket);
					receive_data(n_socket);
					break;
				
			case 2: receive_data(n_socket);
				    break;
			
			case 3: closesocket(n_socket); 
				cout << "Socket terminated"; checker++;
				break;
			default: cout << "Invalid Input";
				break;
			}
		
		}
		checker = 0;

	}




	

	return 0;
}