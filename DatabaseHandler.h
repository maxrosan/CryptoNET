#pragma once

#include <msclr\auto_gcroot.h>
#include <vcclr.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include "sqlite3.h"
#include <msclr\marshal_cppstd.h>


using namespace msclr::interop;

typedef int (*sqlite3_open_ptr)(const char*, sqlite3**);
typedef int (*sqlite3_exec_ptr)(sqlite3*, const char*, int(*callback)(void*, int, char**, char**), void*, char**);
typedef int (*sqlite3_prepare_v2_ptr)(sqlite3*, const char*, int, sqlite3_stmt**, const char**);
typedef int (*sqlite3_step_ptr)(sqlite3_stmt*);
typedef int (*sqlite3_finalize_ptr)(sqlite3_stmt*);
typedef void (*sqlite3_close_ptr)(sqlite3*);
typedef const void* (*sqlite3_errmsg_ptr) (sqlite3*);
typedef void (*sqlite3_free_ptr)(void*);
typedef unsigned char const* (*sqlite3_column_text_ptr) (struct sqlite3_stmt*, int);
typedef int (*sqlite3_column_int_ptr)(struct sqlite3_stmt*, int);

public ref class Credential
{
private:
    int id;
    System::String^ url;
    System::String^ login;
    System::String^ password;

public:
    // Constructor
    Credential(int id, System::String^ url, System::String^ login, System::String^ password)
        : id(id), url(url), login(login), password(password) {
    }

    // Properties for read/write access to private members
    property int Id {
        int get() { return id; }
        void set(int value) { id = value; }
    }

    property System::String^ Url {
        System::String^ get() { return url; }
        void set(System::String^ value) { url = value; }
    }

    property System::String^ Login {
        System::String^ get() { return login; }
        void set(System::String^ value) { login = value; }
    }

    property System::String^ Password {
        System::String^ get() { return password; }
        void set(System::String^ value) { password = value; }
    }

    // ToString method for easy debugging or display
    virtual System::String^ ToString() override {
        return System::String::Format("Credentials: ID={0}, URL={1}, Login={2}", id, url, login);
    }
};

ref class DatabaseHandler
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

public:
	DatabaseHandler(System::String ^file);
    ~DatabaseHandler();
    void loadSQLite();
    void createTable();
    void commit();
    System::String^ getFileName();
	void addItem(System::String^ url, System::String^ login, System::String^ password);
	void removeItem(int id);
	void updateItem(int id, System::String^ url, System::String^ login, System::String^ password);
    System::Collections::Generic::List<Credential^>^ getCredentials();
};

