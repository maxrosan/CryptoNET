#include "DatabaseRAMHandler.h"
#include <msclr/marshal_cppstd.h>
#include <windows.h>

DatabaseRAMHandler::DatabaseRAMHandler(int type, Cipher^ cipher) {
    databaseLoaded = false;
    loadSQLite();
    this->type = type;
    this->cipher = cipher;

    if (type == DB_RAM) {
        createDBRAM();
        createTable();
    }
}

void DatabaseRAMHandler::saveFile(System::String^ path, System::String^ pass)
{
    System::String^ tempFile = saveToDiskTemp(path);
    cipher->encodeLargeFiles(tempFile, pass, path);
    cipher->eraseFile(tempFile);
}

void DatabaseRAMHandler::loadFile(System::String^ path, System::String^ pass)
{
    System::String^ tempFile = path + "-temp";
    cipher->decodeLargeFiles(path, pass, tempFile);
    loadFromDiskToRAM(tempFile);
    cipher->eraseFile(tempFile);
}


void DatabaseRAMHandler::loadFromDiskToRAM(String^ dbPath)
{
    sqlite3* diskDb = nullptr;

    // Abrir o banco de dados do disco
    std::string dbPathStd = marshal_as<std::string>(dbPath);
    if (sqlite3_open(dbPathStd.c_str(), &diskDb) != SQLITE_OK) {
        throw gcnew System::Exception("Erro ao abrir o banco de dados no disco.");
    }

    // Fazer backup do banco de dados do disco para a memória
    sqlite3_backup* pBackup = (sqlite3_backup *) sqlite3_backup_init(db, "main", diskDb, "main");
    if (pBackup)
    {
        if (sqlite3_backup_step(pBackup, -1) != SQLITE_DONE) {
            sqlite3_backup_finish(pBackup);
            sqlite3_close(db);
            sqlite3_close(diskDb);
            throw gcnew System::Exception("Erro ao realizar o backup do banco de dados.");
        }
        sqlite3_backup_finish(pBackup);
    }
    else
    {
        sqlite3_close(db);
        sqlite3_close(diskDb);
        throw gcnew System::Exception("Erro ao iniciar o backup do banco de dados.");
    }

    // Fechar o banco de dados do disco após o backup
    sqlite3_close(diskDb);
}

void DatabaseRAMHandler::createTable() {
    executeSQL("CREATE TABLE IF NOT EXISTS credentials (id INTEGER PRIMARY KEY AUTOINCREMENT, url TEXT, login TEXT, password TEXT);");
}

int DatabaseRAMHandler::getType()
{
    return type;
}

void DatabaseRAMHandler::executeSQL(System::String^ sql) {

    if (!db) {
        throw gcnew System::Exception("Failed to execute open db");
    }

    std::string sqlStd = marshal_as<std::string>(sql);
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sqlStd.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        System::String^ err = gcnew System::String(errMsg);
        sqlite3_free(errMsg);
        throw gcnew System::Exception(err);
    }
}

System::String^ DatabaseRAMHandler::saveToDiskTemp(System::String^ filePath)
{
    if (!db) {
        throw gcnew System::Exception("Banco de dados não inicializado.");
    }

    sqlite3* diskDb = nullptr;
    std::string dbPathStd = marshal_as<std::string>(filePath) + "-temp";
    int rc = sqlite3_open(dbPathStd.c_str(), &diskDb);

    if (rc != SQLITE_OK) {
        throw gcnew System::Exception("Erro ao abrir banco de dados no disco.");
    }

    sqlite3_backup* pBackup = (sqlite3_backup*)sqlite3_backup_init(diskDb, "main", db, "main");
    if (pBackup)
    {
        sqlite3_backup_step(pBackup, -1);
        sqlite3_backup_finish(pBackup);
    }
    else
    {
        sqlite3_close(diskDb);
        throw gcnew System::Exception("Erro ao fazer backup do banco de dados.");
    }

    sqlite3_close(diskDb);

    return (gcnew System::String(dbPathStd.c_str()));
}

void DatabaseRAMHandler::saveFinalFile(System::String^ filePath)
{
    throw gcnew System::NotImplementedException();
}

DatabaseRAMHandler::~DatabaseRAMHandler() {
    FreeLibrary(hSQLiteDll);
}

void DatabaseRAMHandler::createDBRAM() {
    sqlite3* pDb = nullptr;
    int rc = sqlite3_open(":memory:", &pDb);
    db = pDb;
    if (rc) {
        // Erro ao abrir o banco de dados
        throw gcnew System::Exception("Failed to initialize database in RAM");
    }
}

void DatabaseRAMHandler::loadFileToMemory(System::String^ filePath)
{
    array<System::Byte>^ fileData = nullptr;

    System::IO::FileStream^ fileStream = gcnew System::IO::FileStream(filePath, System::IO::FileMode::Open, System::IO::FileAccess::Read);
    fileData = gcnew array<System::Byte>(fileStream->Length);
    fileStream->Read(fileData, 0, fileData->Length);
    fileStream->Close();

    databaseLoaded = true;
}

void DatabaseRAMHandler::addItem(System::String^ url, System::String^ login, System::String^ password) {

    System::String^ sql = System::String::Format("INSERT INTO credentials (url, login, password) VALUES ('{0}', '{1}', '{2}')",
        url, login, password);
    executeSQL(sql);
}

Credential^ DatabaseRAMHandler::getCredential(System::String^ id) {

    if (!db) {
        throw gcnew System::Exception("Failed to execute open db");
    }

    Credential^ credential = nullptr;
    sqlite3_stmt* stmt;
    std::string sql = marshal_as<std::string>("SELECT id, url, login, password FROM credentials WHERE id = '" + id + "'");
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            String^ result = gcnew String(reinterpret_cast<const char*>(text));

            int id = sqlite3_column_int(stmt, 0);
            System::String^ url = gcnew System::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            System::String^ login = gcnew System::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            System::String^ password = gcnew System::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            credential = gcnew Credential(id, url, login, password);

            sqlite3_finalize(stmt);
        }
    }
    return credential; // Erro ao preparar a consulta
}

System::Collections::Generic::List<Credential^>^ DatabaseRAMHandler::getCredentials()
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

void DatabaseRAMHandler::commit() {
    executeSQL("COMMIT");
}

void DatabaseRAMHandler::loadSQLite() {
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
    sqlite3_column_int = (sqlite3_column_int_ptr)GetProcAddress(hSQLiteDll, "sqlite3_column_int");
    sqlite3_backup_init = (sqlite3_backup_init_ptr)GetProcAddress(hSQLiteDll, "sqlite3_backup_init");
    sqlite3_backup_step = (sqlite3_backup_step_ptr)GetProcAddress(hSQLiteDll, "sqlite3_backup_step");
    sqlite3_backup_finish = (sqlite3_backup_finish_ptr)GetProcAddress(hSQLiteDll, "sqlite3_backup_finish");


    if (!sqlite3_open || !sqlite3_exec || !sqlite3_prepare_v2 || !sqlite3_step || !sqlite3_finalize || !sqlite3_close
        || !sqlite3_column_text || !sqlite3_column_int) {
        throw gcnew System::Exception("Failed to get function pointers from SQLite3.dll");
    }
}

