
#include "VirtualDisk.h"

#include <msclr\marshal_cppstd.h>
#include <msclr\auto_gcroot.h>
using namespace msclr::interop;
using namespace System::Runtime::InteropServices;


VirtualDisk::VirtualDisk(System::String^ letter, System::String^ filePath, int sizeInMB, bool createDisk) {
	this->letter = letter;
	this->filePath = filePath;
	this->createDisk = createDisk;
    this->sizeInMB = sizeInMB;
}

void VirtualDisk::_run(System::String^ diskpartScript) {

    System::String^ tempScript = "exec.txt";

    System::IO::FileStream^ fs = gcnew System::IO::FileStream(tempScript, System::IO::FileMode::Create, System::IO::FileAccess::Write);
    for (int i = 0; i < diskpartScript->Length; i++) {
        fs->WriteByte(diskpartScript[i]);
    }
    fs->Close();

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    System::Diagnostics::Process^ process = gcnew System::Diagnostics::Process;

    process->StartInfo->FileName = "diskpart.exe";
    process->StartInfo->Arguments = "/s " + tempScript;
    process->StartInfo->UseShellExecute = true;

    process->StartInfo->CreateNoWindow = false;

    process->Start();

    process->WaitForExit();

    char* scriptFileNameChar = static_cast<char*>(Marshal::StringToHGlobalAnsi(tempScript).ToPointer());

    unlink(scriptFileNameChar);

}

void VirtualDisk::mount() {
   
    System::String^ diskpartScript =
        "select vdisk file=\"" + this->filePath + "\"\r\n"
        "attach vdisk\r\n";

    this->_run(diskpartScript);

}

void VirtualDisk::umount() {

    System::String^ diskpartScript =
        "select vdisk file=\"" + this->filePath + "\"\r\n"
        "detach vdisk\r\n";

    this->_run(diskpartScript);

}

void VirtualDisk::run() {

    System::String^ diskpartScript = "create vdisk file=\"" + this->filePath + "\" maximum=" + this->sizeInMB + " type=expandable\r\n"
        "select vdisk file=\"" + this->filePath + "\"\r\n"
        "attach vdisk\r\n"
        "create partition primary\r\n"
        "format fs=ntfs label=\"VHD\" quick\r\n"
        "assign letter=" + this->letter + "\r\n"
        "detach vdisk\r\n";


    this->_run(diskpartScript);


}