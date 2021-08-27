#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

#define TOTAL_BYTES_READ    1024
#define OFFSET_BYTES 1024



class Registry {
private:
	HKEY hKeyParent;
	PWCHAR subkey;
	PWCHAR valueName;
	DWORD data;
	
	
public:
	bool createRegistryKey(HKEY UKEY, PWCHAR CHARACTER);
	bool WriteDwordInRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, DWORD word );
	bool readDwordValueRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, DWORD* word);
	bool writeStringInRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, PWCHAR word1);
	bool readUserInfoFromRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, PWCHAR* word);
	bool deleteregistryKey(HKEY UKEY, PWCHAR CHARACTER);



};