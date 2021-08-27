#include "Windows_Registry.h"


//to create key in registry if not created
bool Registry::createRegistryKey(HKEY UKEY, PWCHAR CHARACTER)
{
	DWORD dwDisposition; //It verify new key is created or open existing key
	HKEY  hKey;
	DWORD Ret;
	HKEY hKeyParent = UKEY ;
	PWCHAR subkey = CHARACTER;
	Ret =
		RegCreateKeyEx(
			hKeyParent,
			subkey,
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&hKey,
			&dwDisposition);
	if (Ret != ERROR_SUCCESS)
	{
		printf("Error opening or creating key.\n");
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;

}


//to write dword to the created key
bool Registry::WriteDwordInRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, DWORD word)
{
	DWORD Ret;
	HKEY hKey;
	HKEY hKeyParent = UKEY;
	PWCHAR subkey = CHARACTER;
	PWCHAR valueName = value;
	DWORD data = word;
	
	//Open the key
	Ret = RegOpenKeyEx(
		hKeyParent,
		subkey,
		0,
		KEY_WRITE,
		&hKey
	);
	if (Ret == ERROR_SUCCESS)
	{
		//Set the value in key
		if (ERROR_SUCCESS !=
			RegSetValueEx(
				hKey,
				valueName,
				0,
				REG_DWORD,
				reinterpret_cast<BYTE*>(&data),
				sizeof(data)))
		{
			RegCloseKey(hKey);
			return FALSE;
		}
		//close the key
		RegCloseKey(hKey);
		return TRUE;
	}
	return FALSE;


}

//to read the dword for created key
bool Registry::readDwordValueRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, DWORD* word)
{
	HKEY hKey;
	DWORD Ret;
	HKEY hKeyParent = UKEY;
	PWCHAR subkey = CHARACTER;
	PWCHAR valueName = value;
	DWORD* readData =  word;
	//Check if the registry exists
	Ret = RegOpenKeyEx(
		hKeyParent,
		subkey,
		0,
		KEY_READ,
		&hKey
	);
	if (Ret == ERROR_SUCCESS)
	{
		DWORD data;
		DWORD len = sizeof(DWORD);//size of data
		Ret = RegQueryValueEx(
			hKey,
			valueName,
			NULL,
			NULL,
			(LPBYTE)(&data),
			&len
		);
		if (Ret == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			(*readData) = data;
			return TRUE;
		}
		RegCloseKey(hKey);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

//to write string in the created key
bool Registry::writeStringInRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, PWCHAR value1)
{
	DWORD Ret;
	HKEY hKey;
	HKEY hKeyParent = UKEY;
	PWCHAR subkey = CHARACTER;
	PWCHAR valueName = value;
	PWCHAR strData = value1;
	//Check if the registry exists
	Ret = RegOpenKeyEx(
		hKeyParent,
		subkey,
		0,
		KEY_WRITE,
		&hKey
	);
	if (Ret == ERROR_SUCCESS)
	{
		if (ERROR_SUCCESS !=
			RegSetValueEx(
				hKey,
				valueName,
				0,
				REG_SZ,
				(LPBYTE)(strData),
				((((DWORD)lstrlen(strData) + 1)) * 2)))
		{
			RegCloseKey(hKey);
			return FALSE;
		}
		RegCloseKey(hKey);
		return TRUE;
	}
	return FALSE;

}


//to read string
bool Registry::readUserInfoFromRegistry(HKEY UKEY, PWCHAR CHARACTER, PWCHAR value, PWCHAR* word)
{
	HKEY hKey;
	HKEY hKeyParent = UKEY;
	PWCHAR subkey = CHARACTER;
	PWCHAR valueName = value;
	PWCHAR* readData = word;
	DWORD len = TOTAL_BYTES_READ;
	DWORD readDataLen = len;
	PWCHAR readBuffer = (PWCHAR)malloc(sizeof(PWCHAR) * len);
	if (readBuffer == NULL)
		return FALSE;
	//Check if the registry exists
	DWORD Ret = RegOpenKeyEx(
		hKeyParent,
		subkey,
		0,
		KEY_READ,
		&hKey
	);
	if (Ret == ERROR_SUCCESS)
	{
		Ret = RegQueryValueEx(
			hKey,
			valueName,
			NULL,
			NULL,
			(BYTE*)readBuffer,
			&readDataLen
		);
		while (Ret == ERROR_MORE_DATA)
		{
			// Get a buffer that is big enough.
			len += OFFSET_BYTES;
			readBuffer = (PWCHAR)realloc(readBuffer, len);
			readDataLen = len;
			Ret = RegQueryValueEx(
				hKey,
				valueName,
				NULL,
				NULL,
				(BYTE*)readBuffer,
				&readDataLen
			);
		}
		if (Ret != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			return false;;
		}
		*readData = readBuffer;
		RegCloseKey(hKey);
		return true;
	}
	else
	{
		return false;
	}

}

//to delete key
bool Registry::deleteregistryKey(HKEY UKEY, PWCHAR CHARACTER)
{
	HKEY  hKey;
	DWORD Ret;
	HKEY hKeyParent = UKEY;
	PWCHAR subkey = CHARACTER;

	Ret = RegDeleteKey(hKeyParent, subkey);
	if (Ret != ERROR_SUCCESS)
	{
		printf("Error deleting key");
		return FALSE;
	}

	

}