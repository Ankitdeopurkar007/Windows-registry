#include <Windows.h>
#include <iostream>
#include "Windows_Registry.h"

#define TOTAL_BYTES_READ    1024
#define OFFSET_BYTES 1024

int main()
{
	BOOL status;
	DWORD readData;
	PWCHAR readMessage = nullptr;
	Registry a;

	char c;
	//int count = 0;
	int flag_dword = 0;
	int flag_string = 0;
	printf("Enter the operation you have to perform :->\n");
	printf("1. Create Key in Registry\n");
	printf("2. Delete Key in Registry\n");
	cin >> c;

	switch (c) {
	case '1':
		status = a.createRegistryKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\NM"); //create key
		status = a.createRegistryKey(HKEY_CURRENT_USER, L"SOFTWARE\\NM"); //create key
		printf("Key Succesfully Created\n");
		if (status != TRUE)
			return FALSE;
		break;


	case '2':
		status = a.deleteregistryKey(HKEY_CURRENT_USER, L"SOFTWARE\\NM");
		status = a.deleteregistryKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\NM");
		printf("Key Successfully Deleted");
		if (status != TRUE)
		{
			return FALSE;
		}
	default:
		printf("Invalid Choice");

	}
	printf("Which value would you like to add to the key:\n");
	printf("1.Integer \n");
	printf("2.String\n");

	cin >> c;
	switch (c) {
	case '1':
		status = a.WriteDwordInRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\NM", L"date", 23082021); //write dword
		status = a.WriteDwordInRegistry(HKEY_CURRENT_USER, L"SOFTWARE\\NM", L"date", 23082021); //write dword
		printf("Integer value successfully added\n");

		flag_dword = 1;


		if (status != TRUE)
			return FALSE;

		break;


	case '2':
		status = a.writeStringInRegistry(HKEY_CURRENT_USER, L"SOFTWARE\\NM", L"Message", L"Happy");
		status = a.writeStringInRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\NM", L"Message", L"Happy");//write string
		printf("String added successfully\n");

		flag_string = 1;
		if (status != TRUE)
			return FALSE;
		break;

	default:
		printf("Invalid Choice");

	}
	printf("The values stored in key are:\n");
	if (flag_dword == 1)
	{
		status = a.readDwordValueRegistry(HKEY_CURRENT_USER, L"SOFTWARE\\NM", L"date", &readData); //read dword
		if (status != TRUE)
			return FALSE;
		printf("%ld\n", readData);
	}
	else if (flag_string == 1)
	{
		status = a.readUserInfoFromRegistry(HKEY_CURRENT_USER, L"SOFTWARE\\NM", L"Message", &readMessage); //read string
		if (status != TRUE)
			return FALSE;
		if (readMessage != nullptr)
		{
			printf(" Message = %S\n", readMessage);
			free(readMessage);
			readMessage = nullptr;
		}
	}
	else {
		printf("No content available\n");
	}

	return 0;
}

	



	

	



	
	

		
		
	
	

	

	













	

	
	


