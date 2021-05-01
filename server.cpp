#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "common.h"
#pragma comment(lib, "Ws2_32.lib")

#define PORT 9000

using namespace std;
	



int send_data(int client_socket)
{
	char buffer[256] = { 0, };
	std::cin >> buffer;
	send(client_socket, buffer, 256, 0); return 0;	
}

int receive_data(int client_socket)
{
	char buffer[256] = { 0, };
	std::cout << client_socket << endl;
	recv(client_socket, buffer, 255, 0);
	cout << "Press ENTER to see the message from client:  ";
	getchar();
	cout << endl << "Messge: " << buffer << endl;


	std::stringstream buf; char buffer1[20] = "_AppendedMessage";
	buf << buffer << buffer1;
	buf >> buffer;
	std::cout << buffer;
	
	send(client_socket, buffer, 256, 0); return 0;
}

void ProcessTheNewRequest(int n_socket,fd_set* f_read) {
	
	if (FD_ISSET(n_socket, f_read)) {
		int nLen = sizeof(struct sockaddr);
		int client_socket = accept(n_socket, NULL, &nLen);
		char buffer[] = {0,};
		

		if (client_socket > 0) {
			int opt,p, checker = 0;
			
			while (checker==0) 
			{
				std::cout << "\nSelect operation: 1. Send Data. 2. Receieve Data 3.Terminate connection.";
				std::cin >> opt;
				switch(opt)
				{
				case 1:	send_data(client_socket);
					break;
				case 2: receive_data(client_socket);
					break; 
				
				case 3:	closesocket(client_socket); cout << "Socket terminated"; checker++;
					break;
					
				}

			}
			
		}
	}

}





int main() {

	fd_set f_read, f_write, f_exception;
	int p=0;
	while (p==0)
	{

		int listen_value;
		int n_socket = setup();


		struct sockaddr_in config_sock;
		config_sock.sin_family = AF_INET;
		config_sock.sin_addr.S_un.S_addr = INADDR_ANY;
		config_sock.sin_port = htons(PORT);
		memset(&(config_sock.sin_zero), 0, 8);


		int bind_value = bind(n_socket, (sockaddr*)&config_sock, sizeof(sockaddr));
		listen_value = listen(n_socket, 5);
		if (listen_value < 0) {
			std::cout << "Listening mode off" << endl;
		}
		else {
			std::cout << "Listening mode ON" << endl;
		}
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		int maxFat = n_socket;
		int q = 0;
		
		while (q == 0) {
			FD_ZERO(&f_read);
			FD_ZERO(&f_write);
			FD_ZERO(&f_exception);
			FD_SET(n_socket, &f_read);
			FD_SET(n_socket, &f_exception);

			int select_value = select(maxFat + 1, &f_read, &f_write, &f_exception, &tv);
			cout << "Waiting for client..\n";
			if (select_value > 0) {

				ProcessTheNewRequest(n_socket,&f_read);
				q = 1;

			}


		}
		
	}
	return 0;
}


