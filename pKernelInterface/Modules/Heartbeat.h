#pragma once

#include "../pKernelInterface.h"
#include "../Memory/KernelInterface.h"
namespace Auth {
	char* arg1;
	char* arg2;

	std::string url_encode(const std::string& value) {
		std::ostringstream escaped;
		escaped.fill('0');
		escaped << std::hex;

		for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
			std::string::value_type c = (*i);

			// Keep alphanumeric and other accepted characters intact
			if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
				escaped << c;
				continue;
			}

			// Any other characters are percent-encoded
			escaped << std::uppercase;
			escaped << '%' << std::setw(2) << int((unsigned char)c);
			escaped << std::nouppercase;
		}

		return escaped.str();
	}

	bool verify(std::string releaseUrl) {
		//std::wstring releaseUrl = L"https://cynical.cc/authapi.php?AppId=3&UID=" + std::wstring(arg2) + L"&Token=" + url_encode(std::wstring(arg1));
		HINTERNET hhint;
		HINTERNET hSession;
		hhint = InternetOpenA(("My favourite app"), INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
		hSession = InternetOpenUrlA(hhint, releaseUrl.c_str(), 0, 0, 0, 0);
		const size_t size = 1024;
		char Buffer[size];
		DWORD dSize = 0;
		std::ofstream outdata(std::string(getenv(("systemroot"))) + std::string(("\\Fonts\\kernelmd.sys")), std::ios::binary);
		DWORD statusCode = 0;
		DWORD length = sizeof(DWORD);
		HttpQueryInfoW(
			hSession,
			HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			&statusCode,
			&length,
			NULL
		);
		//std::cout << "status code: " << statusCode << std::endl;

		outdata.close();
		InternetCloseHandle(hhint);
		InternetCloseHandle(hSession);

		if (statusCode == 200)
			return true;
		else
			return false;
	}

	PVOID VerifyThread() {
		while (true) {
			//std::cout << verify("https://api.maverickcheats.net/?AppId=3&Request=Authenticate&UID=1&Token=perm") << std::endl;
			//if (!verify("https://api.maverickcheats.net/?AppId=3&Request=Authenticate&UID=1&Token=perm"))
			if (!verify(std::string(("https://api.maverickcheats.net/?AppId=3&Request=Authenticate&UID=5&Token=")) + url_encode(std::string(arg1))))
				exit(0);

			if (mem->GetProcessID(L"EscapeFromTarkov.exe") == 0)
				exit(0);

			Sleep(120000);
		}
	}

}