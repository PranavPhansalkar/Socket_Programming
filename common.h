#pragma once
#pragma once
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
#define PORT 9000
#pragma comment(lib, "Ws2_32.lib")




	int setup() {

		WSADATA ws;
		if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
		{
			std::cout << "WSA is not set\n"; exit(0);
		}
		else
		{
			std::cout << "WSA initiated.\n";
			int n_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (n_socket < 0) {
				std::cout << "Socket is not open\n"; exit(0);
			}
			else
			{
				std::cout << "Socket initiated...\n";

			}

			u_long block = 0;
			int check_block = ioctlsocket(n_socket, FIONBIO, &block);
			if (check_block != 0)
			{
				std::cout<< "Blocking failed.\n";
				return -1;
			}
			else
			{
				std::cout << "Socket in blocking mode.\n";
			}


			return n_socket;
		}
	}

