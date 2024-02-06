#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "inputs.h"
#include "getos.h"
#include <cstdlib>
#include "env.h"
#include "system.h"
#include "lookup.h"

void printtitle()
{
	cout
		<< endl
		<< "                BetterScan 1.0" << endl
		<< "               ________________" << endl
		<< " Made by Francesco Piantone (@NotRealFrancy_)" << endl
		<< "  http://github.com/NotRealFrancy/Betterscan" << endl
		<< "         https://t.me/notrealfrancy" << endl
		<< endl;
}

using namespace std;
int main()
{
	printtitle();

	string str = "Betterscan » ";
	
	string os = getos();
	string bit = getsystembit();
	string hostnamestr = hostname();
	string ipstr = ip();

	cout << endl
		<< "[+] Operating System: " << os << endl
		<< "[+] System Bit Architecture: " << bit << endl
		<< "[+] Hostname: " << hostnamestr << endl
		<< "[+] IP: " << ipstr << endl
		<< endl;

	string command;
	while (1)
	{
		cout << str;
		getline(cin, command);

		vector<string> tokens = splitInput(command);

		if (!tokens.empty())
		{
			string commandname = tokens[0];

			if (commandname == "help")
			{
				cout
					<< endl
					<< "  Help" << endl
					<< " ______" << endl
					<< "help » Shows all commands." << endl
					<< "set [name] [value] » Set an environment variable." << endl
					<< "values » Shows all environment variables." << endl
					<< "value [name] » Shows a value of an environment variable." << endl
					<< "run » Runs the scan." << endl
					<< "lookup [type:ip|domain] ... » Lookup for something." << endl
					<< endl;
			}
			else if (commandname == "clear")
			{
				if (os == "Windows")
				{
					system("cls");
				}
				else
				{
					system("clear");
				}

				printtitle();
			}
			else if (commandname == "set")
			{
				if (tokens.size() >= 3)
				{
					setEnvironmentVariable(("BS_" + tokens[1]).c_str(), tokens[2].c_str());
					cout
						<< tokens[1]
						<< "=>"
						<< tokens[2] << endl
						<< endl;
				}
				else
				{
					cout << endl
						<< "[?] Usage: set [name] [value]" << endl
						<< endl;
				}
			}
			else if (commandname == "value")
			{
				if (tokens.size() >= 2)
				{
					cout
						<< tokens[1]
						<< "=>"
						<< getEnvironmentVariable(("BS_" + tokens[1]).c_str()) << endl
						<< endl;
				}
				else
				{
					cout << endl
						<< "[?] Usage: value [name]" << endl
						<< endl;
				}
			}
			else if (commandname == "values")
			{
				cout << endl;
				vector<string> envvars = getAllEnvironmentVariables();
				for (const string& envvar : envvars)
				{
					vector<string> strings = splitInput(envvar, '=');
					const char* first = strings[0].c_str();
					if (first[0] == 'B' && first[1] == 'S' && first[2] == '_')
					{
						cout << strings[0].substr(3) << "=>" << strings[1] << endl;
					}
				}
				cout << endl;
			}
			else if (commandname == "exit")
			{
				return 0;
			}
			else if (commandname == "lookup")
			{
				if (tokens.size() >= 3)
				{
					const string type = tokens[1];
					if (type == "domain")
					{
						lookupDomain(tokens[2]);
					}
					else if (type == "ip")
					{
						string ip = tokens[2];
						string hostname = hostnamebyip(ip);

						cout << endl
							<< "[+] IP: " << ip << endl
							<< "[+] Hostname: " << hostname << endl
							<< endl;
					}
					else
					{
						cout << endl
							<< "[?] Type parameter can be only \"ip\" or \"domain\"." << endl
							<< endl;
					}
				}
				else
				{
					cout << endl
						<< "[?] Usage: lookup [type:ip|domain] [arg]" << endl
						<< endl;
				}
			}
			else if (commandname == "run")
			{
				if (containsEnvKey("BS_HOST"))
				{
					string host = getEnvironmentVariable("BS_HOST");
					const char* hoststr = host.c_str();

					cout << endl
						<< "==========[ Nmap Scan ]==========" << endl
						<< endl;

					char string0[sizeof(hoststr) + 50];
					snprintf(string0, sizeof(string0), "nmap %s", hoststr);
					system(string0);

					// cout << endl
					//	<< "==========[ TCP Connect Scan ]==========" << endl
					//	<< endl;
					
					// char string1[sizeof(hoststr)+ 50];
					// snprintf(string1, sizeof(string1), "nmap -sT %s", hoststr);
					// system(string1);

					cout << endl
						<< "==========[ TCP Stealth Scan ]==========" << endl
						<< endl;

					char string2[sizeof(hoststr)+ 50];
					snprintf(string2, sizeof(string2), "nmap -sS %s", hoststr);
					system(string2);

					cout << endl
						<< "==========[ NULL Scan ]==========" << endl
						<< endl;

					char string3[sizeof(hoststr)+50];
					snprintf(string3, sizeof(string3), "nmap -sN %s", hoststr);
					system(string3);

					// cout << endl
					//	<< "==========[ UDP Scan ]==========" << endl
					//	<< endl;

					// char string4[sizeof(hoststr)+50];
					// snprintf(string4, sizeof(string4), "nmap -sU %s", hoststr);
					// system(string4);

					cout << endl
						<< "==========[ FIN Scan ]==========" << endl
						<< endl;

					char string5[sizeof(hoststr)+50];
					snprintf(string5, sizeof(string5), "nmap -sF %s", hoststr);
					system(string5);

					cout << endl
						<< "==========[ ACK Scan ]==========" << endl
						<< endl;

					char string6[sizeof(hoststr) +50];
					snprintf(string6, sizeof(string6), "nmap -sA %s", hoststr);
					system(string6);

					cout << endl
						<< "==========[ XMAS Scan ]==========" << endl
						<< endl;

					char string7[sizeof(hoststr) + 50];
					snprintf(string7, sizeof(string7), "nmap -sX %s", hoststr);
					system(string7);

					cout << endl
						<< "==========[ Show Version Scan ]==========" << endl
						<< endl;

					char string8[sizeof(hoststr) + 50];
					snprintf(string8, sizeof(string8), "nmap -sV %s", hoststr);
					system(string8);

					cout << endl
						<< "==========[ Service Scan ]==========" << endl
						<< endl;

					char string9[sizeof(hoststr) + 50];
					snprintf(string9, sizeof(string9), "nmap -O %s", hoststr);
					system(string9);

					cout << endl
						<< "==========[ Advanced Scan ]==========" << endl
						<< endl;

					char string10[sizeof(hoststr) + 50];
					snprintf(string10, sizeof(string10), "nmap -A %s", hoststr);
					system(string10);

					cout << endl
						<< "==========[ Hostname Scan ]==========" << endl
						<< endl;

					char string11[sizeof(hoststr) + 50];
					snprintf(string11, sizeof(string11), "nmap -sn %s", hoststr);
					system(string11);
				}
				else
				{
					cout << endl
						<< "Parameter HOST is invalid!" << endl
						<< "You must initialize it using:" << endl
						<< "  set HOST [host]" << endl
						<< endl;
				}
			}
		}
	}

	return 0;
}