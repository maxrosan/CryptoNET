#pragma once

#include <msclr/marshal_cppstd.h>

#include "DatabaseHandler.h"
#include "sqlite3.h"
#include "Cipher.h"

enum { DB_RAM };

ref class DatabaseRAMHandler
{
private:
    sqlite3* db;
    HINSTANCE hSQLiteDll;
    sqlite3_open_ptr sqlite3_open;
    sqlite3_exec_ptr sqlite3_exec;
    sqlite3_prepare_v2_ptr sqlite3_prepare_v2;
    sqlite3_step_ptr sqlite3_step;
    sqlite3_finalize_ptr sqlite3_finalize;
    sqlite3_close_ptr sqlite3_close;
    sqlite3_errmsg_ptr sqlite3_errmsg;
    sqlite3_free_ptr sqlite3_free;
    sqlite3_column_text_ptr sqlite3_column_text;
    sqlite3_column_int_ptr sqlite3_column_int;
    System::String^ fileName;

    bool databaseLoaded;
    array<System::Byte>^ fileData;
    int type;
    void loadFileToMemory(System::String^ filePath);
    void loadSQLite();
    void createDBRAM();
    void executeSQL(System::String^ sql);
    Cipher^ cipher;
public:

    DatabaseRAMHandler(int, Cipher ^cipher);
    void createTable();
    int getType();
    void addItem(System::String^ url, System::String^ login, System::String^ password);

    System::Collections::Generic::List<Credential^>^ getCredentials();
    void commit();
    ~DatabaseRAMHandler();
};

