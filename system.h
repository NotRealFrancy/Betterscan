#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

inline const std::string hostname()
{
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) == 0)
	{
		return std::string(hostname);
	}
	else
	{
		return "Unknown";
	}
}
inline const std::string ip()
{
	std::string ipaddress = "Unknown";
#ifdef _WIN32
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) == 0)
	{
		char hostname[256];
		if (gethostname(hostname, sizeof(hostname)) == 0)
		{
			struct addrinfo* result = nullptr;
			struct addrinfo* ptr = nullptr;
			struct addrinfo hints;

			std::memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_INET;

			if (getaddrinfo(hostname, nullptr, &hints, &result) == 0)
			{
				for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
				{
					if (ptr->ai_family == AF_INET)
					{
						struct sockaddr_in* sockaddr_ipv4 = reinterpret_cast<struct sockaddr_in*>(ptr->ai_addr);
						char ip[INET_ADDRSTRLEN];
						if (inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ip, INET_ADDRSTRLEN) != nullptr)
						{
							ipaddress = ip;
							break;
						}
					}
				}

				freeaddrinfo(result);
			}
		}

		WSACleanup();
	}
#else
	struct ifaddrs* ifaddrstruct = nullptr;
	if (getifaddrs(&ifaddrstruct) == 0)
	{
		for (struct ifaddrs* ifa = ifaddrstruct; ifa != nullptr; ifa = ifa->ifa_next)
		{
			if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET)
			{
				struct sockaddr_in* sockaddr_ipv4 = reinterpret_cast<struct sockaddr_in*>(fa->fa_addr);
				char ip[INET_ADDRSTRLEN];
				if (inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr)))
				{
					ipaddress = ip;
					break;
				}
			}
		}

		freeifaddrs(ifaddrstruct);
	}
#endif
	return ipaddress;
}