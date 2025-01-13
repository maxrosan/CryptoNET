#include "DatabaseHandler.h"

void DatabaseHandler::loadSQLite() {
    hSQLiteDll = LoadLibrary(TEXT("sqlite3.dll"));
    if (!hSQLiteDll) {
        throw gcnew System::Exception("Failed to load SQLite3.dll");
    }

    sqlite3_open = (sqlite3_open_ptr)GetProcAddress(hSQLiteDll, "sqlite3_open");
    sqlite3_exec = (sqlite3_exec_ptr)GetProcAddress(hSQLiteDll, "sqlite3_exec");
    sqlite3_prepare_v2 = (sqlite3_prepare_v2_ptr)GetProcAddress(hSQLiteDll, "sqlite3_prepare_v2");
    sqlite3_step = (sqlite3_step_ptr)GetProcAddress(hSQLiteDll, "sqlite3_step");
    sqlite3_finalize = (sqlite3_finalize_ptr)GetProcAddress(hSQLiteDll, "sqlite3_finalize");
    sqlite3_close = (sqlite3_close_ptr)GetProcAddress(hSQLiteDll, "sqlite3_close");
    sqlite3_errmsg = (sqlite3_errmsg_ptr)GetProcAddress(hSQLiteDll, "sqlite3_errmsg");
    sqlite3_free = (sqlite3_free_ptr)GetProcAddress(hSQLiteDll, "sqlite3_free");
    sqlite3_column_text = (sqlite3_column_text_ptr)GetProcAddress(hSQLiteDll, "sqlite3_column_text");
    sqlite3_column_int = (sqlite3_column_int_ptr) GetProcAddress(hSQLiteDll, "sqlite3_column_int");
    sqlite3_backup_init = (sqlite3_backup_init_ptr)GetProcAddress(hSQLiteDll, "sqlite3_backup_init");
    sqlite3_backup_step = (sqlite3_backup_step_ptr)GetProcAddress(hSQLiteDll, "sqlite3_backup_step");
    sqlite3_backup_finish = (sqlite3_backup_finish_ptr)GetProcAddress(hSQLiteDll, "sqlite3_backup_finish");


    if (!sqlite3_open || !sqlite3_exec || !sqlite3_prepare_v2 || !sqlite3_step || !sqlite3_finalize || !sqlite3_close 
        || !sqlite3_column_text || !sqlite3_column_int) {
        throw gcnew System::Exception("Failed to get function pointers from SQLite3.dll");
    }
}

void DatabaseHandler::createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS credentials (id INTEGER PRIMARY KEY AUTOINCREMENT, url TEXT, login TEXT, password TEXT);";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        throw gcnew System::Exception("SQL error creating table");
    }
}

DatabaseHandler::DatabaseHandler(System::String^ file) {

    loadSQLite();

    std::string fileStdString = marshal_as<std::string>(file);
    sqlite3* pDb = nullptr;
    int rc = sqlite3_open(fileStdString.c_str(), &pDb);
    db = pDb;
    if (rc) {
        throw gcnew System::Exception("Can't open database");
    }

    fileName = file;

    createTable();
}

DatabaseHandler::~DatabaseHandler() {
    sqlite3_close(db);
    FreeLibrary(hSQLiteDll);
}

void DatabaseHandler::addItem(System::String^ url, System::String^ login, System::String^ password) {

    System::String^ sql = System::String::Format("INSERT INTO credentials (url, login, password) VALUES ('{0}', '{1}', '{2}')",
        url, login, password);
    pin_ptr<const wchar_t> wch = PtrToStringChars(sql);
    std::string sqlStdString = marshal_as<std::string>(sql);
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStdString.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        throw gcnew System::Exception("SQL error inserting data");
    }

}

void DatabaseHandler::removeItem(int id) {
    System::String^ sql = System::String::Format("DELETE FROM credentials WHERE id = {0}", id);
    pin_ptr<const wchar_t> wch = PtrToStringChars(sql);
    std::string sqlStdString = marshal_as<std::string>(sql);
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStdString.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        throw gcnew System::Exception("SQL error deleting data");
    }
}

void DatabaseHandler::updateItem(int id, System::String^ url, System::String^ login, System::String^ password) {
    System::String^ sql = System::String::Format("UPDATE credentials SET url = '{0}', login = '{1}', password = '{2}' WHERE id = {3}",
        url, login, password, id);
    pin_ptr<const wchar_t> wch = PtrToStringChars(sql);
    std::string sqlStdString = marshal_as<std::string>(sql);
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlStdString.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        throw gcnew System::Exception("SQL error updating data");
    }
}

System::Collections::Generic::List<Credential^>^ DatabaseHandler::getCredentials()
{
    System::Collections::Generic::List<Credential^>^ credentials = gcnew System::Collections::Generic::List<Credential^>();

    const char* sql = "SELECT id, url, login, password FROM credentials";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw gcnew System::Exception("Failed to prepare statement");
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        System::String^ url = gcnew System::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        System::String^ login = gcnew System::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        System::String^ password = gcnew System::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));

        credentials->Add(gcnew Credential(id, url, login, password));
    }

    if (rc != SQLITE_DONE) {
        throw gcnew System::Exception("Error executing statement");
    }

    sqlite3_finalize(stmt);

    return credentials;
}

void DatabaseHandler::commit() {
    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
}

System::String^ DatabaseHandler::getFileName()
{
    return fileName;
}
