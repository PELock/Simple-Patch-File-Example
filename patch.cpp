////////////////////////////////////////////////////////////////////////////////
//
// Simple Patch File Example in C++ for Windows
//
// Language : C/C++
// Author   : Bartosz Wójcik
// Website  : http://www.pelock.com
//
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

int main()
{
	// patch bytes (those will be written to the selected file)
	BYTE cPatch[] = { 0xAA, 0xBB, 0xCC };

	// patch raw file offset
	const DWORD dwPatchRawOffset = 0x1234;

	// number of written patch bytes (param for WriteFile function)
	DWORD dwWritten = 0;

	// file handle
	HANDLE hFile = INVALID_HANDLE_VALUE;

	// open input file in write mode (use GENERIC_WRITE flag)
	hFile = CreateFile("file.exe", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// verify file handle
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Couldn't open the input file!", "Error", MB_ICONERROR);
		return 1;
	}

	// set proper patch offset (raw offset) where the patch bytes will be written
	SetFilePointer(hFile, dwPatchRawOffset, 0, FILE_BEGIN);

	// write patch bytes from cPatch array at the appropriate file offset
	WriteFile(hFile, cPatch, sizeof(cPatch), &dwWritten, NULL);

	// close the file handle
	CloseHandle(hFile);

	MessageBox(NULL, "File sucessfully patched", "Information", MB_ICONINFORMATION);

	return 0;
}
