#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

public ref class VirtualDisk
{
private:

	System::String^ letter;
	System::String^ filePath;
	bool createDisk;
	int sizeInMB;

	void _run(System::String^ code);

public:
	VirtualDisk(System::String^ letter, System::String^ filePath, int sizeInGB, bool createDisk);
	void run();
	void mount();
	void umount();
};

