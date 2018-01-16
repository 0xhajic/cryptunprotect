// cryptunprotect.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#pragma comment(lib, "crypt32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR *szFileName = argv[1];
	TCHAR *szData;

	DATA_BLOB blobln;
	DATA_BLOB blobEntropy;
	DATA_BLOB blobOut;
	CRYPTPROTECT_PROMPTSTRUCT promptStruct;
	LPBYTE lpData;
	DWORD dwDataSize;
	HANDLE hFile, hFile1;
	DWORD dwReadByte, dwWriteByte;

	if(argc!=2)
	{
		printf("Usage cryptunprotect.exe <Encrypt File Name>");
		return FALSE;
	}

	hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwDataSize = GetFileSize(hFile, NULL);
	lpData = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, dwDataSize);
	ReadFile(hFile, lpData, dwDataSize, &dwReadByte, NULL);
	CloseHandle(hFile);

	blobln.cbData = dwDataSize;
	blobln.pbData = lpData;

	//blobEntropy.cbData = dwEntropySize;
	//blogEntropy.pbData = lpEntropy;

	promptStruct.cbSize = sizeof(CRYPTPROTECT_PROMPTSTRUCT);
	promptStruct.dwPromptFlags = CRYPTPROTECT_PROMPT_ON_PROTECT;
	promptStruct.hwndApp = NULL;
	promptStruct.szPrompt = L"HEHEHE";

	if(!CryptUnprotectData(&blobln, NULL, NULL, NULL, &promptStruct, 0, &blobOut)){
		printf("Failed to Decrypt Data.");
		return FALSE;
	}

	hFile1 = CreateFile(L"crypteunprotec.dec", GENERIC_WRITE, 0, 
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile1 == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	WriteFile(hFile1, blobOut.pbData, blobOut.cbData, &dwWriteByte, NULL);
	CloseHandle(hFile1);

	printf("Decrypted file generated as cryptunprotec.dec");

	return 0;
}

