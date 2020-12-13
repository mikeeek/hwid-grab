#include <stdio.h>
#include <windows.h>

void copy(const char* text)
{
	int len = strlen(text) + 1;
	HGLOBAL hmem = GlobalAlloc(GMEM_MOVEABLE, len);
	char* buffer = (char*)GlobalLock(hmem);
	strcpy_s(buffer, len, text);
	GlobalUnlock(hmem);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hmem);
	CloseClipboard();
}


void CheckValidHardwareID()
{
	DWORD MY_HWID[5] = { -1372710529,514760327, 1488013534, 895532923, -91202064 };
	DWORD dwSerial;
	GetVolumeInformation("C:\\", NULL, 0, &dwSerial, NULL, NULL, NULL, 0);

	for (int i = 0; i < 5; i++)
	{ 
			if (dwSerial == MY_HWID[i])
			{
				MessageBox(0, "HWID Ok!", "Loaded", MB_OK | MB_ICONINFORMATION);
				printf("Your HWID is: %d", dwSerial);
				ExitProcess(1);
			}	
	}

			printf("Your HWID is: %d\n", dwSerial);

			char buf[100];
			sprintf_s(buf, 100, "%d", dwSerial);
			copy(buf);

			MessageBox(0, "Wrong HWID. HWID copied to clipboard!", "Error", MB_OK | MB_ICONERROR);
			ExitProcess(1);
}

int main()
{
	printf("Grabbing your HWID based on your HDD/SSD ID's and copying it for you");

	CheckValidHardwareID();

}