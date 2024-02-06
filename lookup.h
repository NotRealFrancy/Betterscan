#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include <cstring>

using namespace std;

inline string hostnamebyip(const string& ip)
{
	struct sockaddr_in sa;
	inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));

	char host[NI_MAXHOST];
	int result = getnameinfo(reinterpret_cast<struct sockaddr*>(&sa), sizeof(sa), host, NI_MAXHOST, nullptr, 0, NI_NAMEREQD);

	if (result == 0)
	{
		return host;
	}
	else
	{
		return "Unknown";
	}
}

#ifdef _WIN32
inline void lookupDomain(const string& domain)
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		return;
	}

	addrinfo* result = nullptr;
	if (getaddrinfo(domain.c_str(), nullptr, nullptr, &result) != 0)
	{
		WSACleanup();
		return;
	}

	for (auto ptr = result; ptr != nullptr; ptr = ptr->ai_next)
	{
		if (ptr->ai_family == AF_INET)
		{
			sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
			char ip[INET_ADDRSTRLEN];
			if (inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ip, INET_ADDRSTRLEN) != nullptr)
			{
				cout << endl
					<< "[+] IP Address: " << ip << endl
					<< endl;
			}
		}
	}

	freeaddrinfo(result);
	WSACleanup();
}
#else
inline void lookupDomain(const string& domain)
{
	hostent* host = gethostbyname(domain.c_str());

	if (host == nullptr)
	{
		return nullptr;
	}

	in_addr** addrlist = reinterpret_cast<in_addr**>(host->h_addr_list);

	for (int i = 0; addrlist[i] != nullptr; ++i)
	{
		string ip = inet_ntoa(*addrlist[i]);
		cout << endl
			<< "[+] IP Address: " << ip << endl
			<< endl;
	}
}
#endif