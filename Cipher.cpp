#include "Cipher.h"

Cipher::Cipher() {
	this->libsLoaded = false;
}

Cipher::~Cipher() {

}

void Cipher::loadLibraries() {
	this->hLibCrypto = LoadLibrary(L"./libcrypto-3-x64.dll");
	this->hLibSSL = LoadLibrary(L"./libssl-3-x64.dll");

    if (!this->hLibCrypto || !this->hLibSSL) {
        std::cout << "Falha ao carregar uma ou ambas as DLLs do OpenSSL." << std::endl;
        if (hLibCrypto) FreeLibrary(hLibCrypto);
        if (hLibSSL) FreeLibrary(hLibSSL);
        this->libsLoaded = false;
    } else {
        this->libsLoaded = true;
    }
}

bool Cipher::areLibrariesLoaded() {
    return this->libsLoaded;
}

// Função para adicionar padding PKCS#7
std::vector<unsigned char> addPadding(const std::vector<unsigned char>& data, int blockSize = AES_BLOCK_SIZE) {
    std::vector<unsigned char> paddedData = data;
    int paddingSize = blockSize - (data.size() % blockSize);
    for (int i = 0; i < paddingSize; ++i) {
        paddedData.push_back(paddingSize);
    }
    return paddedData;
}

#define BUFFER_LARGE_FILE 102400 // 4096
#define SALT_LENGTH 8
#define NEW(type, array, size) type* array = new type[size]
#define FREE(array) delete[] array;
#define LOAD_FUNC(type, name) type name = (type) GetProcAddress(hLibCrypto, #name); \
    do { if (!name) { FreeLibrary(hLibCrypto); throw gcnew Exception("Failed to load " #name); } } while(0)

void Cipher::decodeLargeFiles(System::String^ fileToOpen, System::String^ key, System::String^ fileToSave) {

    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());

    NEW(unsigned char, iv_array, EVP_MAX_IV_LENGTH);
    NEW(unsigned char, salt_array, SALT_LENGTH);
    NEW(unsigned char, final_key, EVP_MAX_KEY_LENGTH);
    NEW(unsigned char, inbuffer, BUFFER_LARGE_FILE);
    NEW(unsigned char, outbuffer, BUFFER_LARGE_FILE);

    int bytes_read, out_len;

    EVP_CIPHER_CTX* ctx;

    LOAD_FUNC(OPENSSL_init_crypto_t, OPENSSL_init_crypto);
    LOAD_FUNC(EVP_CIPHER_CTX_new_t, EVP_CIPHER_CTX_new);
    LOAD_FUNC(EVP_CIPHER_CTX_free_t, EVP_CIPHER_CTX_free);
    LOAD_FUNC(EVP_aes_256_cbc_t, EVP_aes_256_cbc);
    LOAD_FUNC(EVP_DecryptInit_ex_t, EVP_DecryptInit_ex);
    LOAD_FUNC(EVP_DecryptUpdate_t, EVP_DecryptUpdate);
    LOAD_FUNC(EVP_DecryptFinal_ex_t, EVP_DecryptFinal_ex);
    LOAD_FUNC(PKCS5_PBKDF2_HMAC_ptr, PKCS5_PBKDF2_HMAC);
    LOAD_FUNC(RAND_bytes_ptr, RAND_bytes);
    LOAD_FUNC(EVP_sha256_ptr, EVP_sha256);

    pin_ptr<const wchar_t> fileToOpen_WCH = PtrToStringChars(fileToOpen);
    pin_ptr<const wchar_t> fileToSave_WCH = PtrToStringChars(fileToSave);

    FILE *inFile, *outFile;

    if (!areLibrariesLoaded()) {
        throw gcnew Exception("Libraries aren't loaded!");
    }

    if (_wfopen_s(&inFile, fileToOpen_WCH, L"rb") != 0) {
        throw gcnew Exception("Failed to open " + fileToOpen);
    }

    if (_wfopen_s(&outFile, fileToSave_WCH, L"wb") != 0) {
        throw gcnew Exception("Failed to open " + fileToSave);
    }

    if (fread(salt_array, 1, SALT_LENGTH, inFile) < SALT_LENGTH) {
        throw gcnew Exception("Failed to read salt");
    }

    if (fread(iv_array, 1, EVP_MAX_IV_LENGTH, inFile) < EVP_MAX_IV_LENGTH) {
        throw gcnew Exception("Failed to read IV array");
    }

    if (!PKCS5_PBKDF2_HMAC(reinterpret_cast<const char*>(key_arr), -1, salt_array, sizeof(salt_array), 10000, EVP_sha256(), sizeof(final_key), final_key)) {
        throw gcnew Exception("Falha ao derivar a chave\n");
        FreeLibrary(hLibCrypto);
        return;
    }

    ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        throw gcnew Exception("Falha em criar contexto de cifra.");
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)final_key, (const unsigned char*)iv_array)) {
        EVP_CIPHER_CTX_free(ctx);
        throw gcnew Exception("Falha ao inicializar a descriptografia.");
    }

    while ((bytes_read = fread(inbuffer, 1, BUFFER_LARGE_FILE, inFile)) > 0) {
        if (1 != EVP_DecryptUpdate(ctx, outbuffer, &out_len, inbuffer, bytes_read)) {
            EVP_CIPHER_CTX_free(ctx);
            throw gcnew Exception("Falha ao atualizar a cifra.");
        }
        fwrite(outbuffer, 1, out_len, outFile);
    }

    if (1 != EVP_DecryptFinal_ex(ctx, outbuffer, &out_len)) {
        throw gcnew System::Exception("Failed to finish the process");
    }

    fwrite(outbuffer, 1, out_len, outFile);

    EVP_CIPHER_CTX_free(ctx);

    //

    fclose(inFile);
    fclose(outFile);

    FREE(iv_array);
    FREE(salt_array);
    FREE(final_key);
    FREE(inbuffer);
    FREE(outbuffer);

}

void Cipher::eraseFile(System::String^ fileToErase) {
    pin_ptr<const wchar_t> fileToOpen_WCH = PtrToStringChars(fileToErase);
    FILE *inFile;
    unsigned char inbuffer[BUFFER_LARGE_FILE];
    int bytes_read, bytes_total = 0;
    char* fileName;

    if (_wfopen_s(&inFile, fileToOpen_WCH, L"rb") != 0) {
        throw gcnew Exception("Failed to open " + fileToErase);
    }

    while ((bytes_read = fread(inbuffer, 1, BUFFER_LARGE_FILE, inFile)) > 0) {
        bytes_total += bytes_read;
    }

    fclose(inFile);

    if (_wfopen_s(&inFile, fileToOpen_WCH, L"wb") != 0) {
        throw gcnew Exception("Failed to open " + fileToErase);
    }

    memset(inbuffer, 0x0, BUFFER_LARGE_FILE);

    for (int i = 0; i < bytes_total; i += BUFFER_LARGE_FILE) {
        fwrite(inbuffer, 1, BUFFER_LARGE_FILE, inFile);
    }

    fclose(inFile);

    fileName = static_cast<char*>(Marshal::StringToHGlobalAnsi(fileToErase).ToPointer());
    unlink(fileName);
}

std::vector<unsigned char> Cipher::sha256(System::String^ password) {

    unsigned char src[32];
    unsigned char dst[32];
    std::vector<unsigned char> result;

    if (password->Length > 32) {
        throw gcnew Exception("String must contain less than 32 bytes");
    }

    unsigned char* password_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(password).ToPointer());
    memset(src, 0x0, sizeof src);
    memcpy(src, password_arr, password->Length);

    LOAD_FUNC(SHA256_t, SHA256);

    SHA256(src, sizeof src, dst);

    for (int i = 0; i < (sizeof dst); i++) {
        result.push_back(dst[i]);
    }

    return result;
}



void Cipher::encodeLargeFiles(System::String^ fileToOpen, System::String^ key, System::String^ fileToSave) {

    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());

    NEW(unsigned char, iv_array, EVP_MAX_IV_LENGTH);
    NEW(unsigned char, salt_array, SALT_LENGTH);
    NEW(unsigned char, final_key, EVP_MAX_KEY_LENGTH);
    NEW(unsigned char, inbuffer, BUFFER_LARGE_FILE);
    NEW(unsigned char, outbuffer, BUFFER_LARGE_FILE);

    pin_ptr<const wchar_t> fileToOpen_WCH = PtrToStringChars(fileToOpen);
    pin_ptr<const wchar_t> fileToSave_WCH = PtrToStringChars(fileToSave);

    FILE* inFile, *outFile;

    if (!areLibrariesLoaded()) {
        throw gcnew Exception("Libraries aren't loaded!");
    }

    if (_wfopen_s(&inFile, fileToOpen_WCH, L"rb") != 0) {
        throw gcnew Exception("Failed to open " + fileToOpen);
    }

    if (_wfopen_s(&outFile, fileToSave_WCH, L"wb") != 0) {
        throw gcnew Exception("Failed to open " + fileToSave);
    }

    LOAD_FUNC(OPENSSL_init_crypto_t, OPENSSL_init_crypto);
    LOAD_FUNC(EVP_CIPHER_CTX_new_t, EVP_CIPHER_CTX_new);
    LOAD_FUNC(EVP_CIPHER_CTX_free_t, EVP_CIPHER_CTX_free);
    LOAD_FUNC(EVP_aes_256_cbc_t, EVP_aes_256_cbc);
    LOAD_FUNC(EVP_EncryptInit_ex_t, EVP_EncryptInit_ex);
    LOAD_FUNC(EVP_EncryptUpdate_t, EVP_EncryptUpdate);
    LOAD_FUNC(EVP_EncryptFinal_ex_t, EVP_EncryptFinal_ex);
    LOAD_FUNC(PKCS5_PBKDF2_HMAC_ptr, PKCS5_PBKDF2_HMAC);
    LOAD_FUNC(RAND_bytes_ptr, RAND_bytes);
    LOAD_FUNC(EVP_sha256_ptr, EVP_sha256);

    if (!RAND_bytes(salt_array, sizeof(salt_array))) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao gerar salt aleatório\n");
    }

    if (!RAND_bytes(iv_array, sizeof(iv_array))) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao gerar IV aleatório\n");
    }

    if (!PKCS5_PBKDF2_HMAC(reinterpret_cast<const char*>(key_arr), -1, salt_array, sizeof(salt_array), 10000, EVP_sha256(), sizeof(final_key), final_key)) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao derivar a chave\n");
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        throw gcnew Exception("Falha em criar contexto de cifra.");
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)final_key, (const unsigned char*)iv_array)) {
        EVP_CIPHER_CTX_free(ctx);
        throw gcnew Exception("Falha ao inicializar a cifra.");
    }

    int bytes_read, out_len;

    fwrite(salt_array, 1, SALT_LENGTH, outFile);
    fwrite(iv_array, 1, EVP_MAX_IV_LENGTH, outFile);

    while ((bytes_read = fread(inbuffer, 1, BUFFER_LARGE_FILE, inFile)) > 0) {
        if (1 != EVP_EncryptUpdate(ctx, outbuffer, &out_len, inbuffer, bytes_read)) {
            EVP_CIPHER_CTX_free(ctx);
            throw gcnew Exception("Falha ao atualizar a cifra.");
        }
        fwrite(outbuffer, 1, out_len, outFile);
    }

    if (1 != EVP_EncryptFinal_ex(ctx, outbuffer, &out_len)) {
        throw gcnew System::Exception("Failed to finish the process");
    }
    fwrite(outbuffer, 1, out_len, outFile);

    EVP_CIPHER_CTX_free(ctx);


    //

    fclose(inFile);
    fclose(outFile);

    FREE(iv_array);
    FREE(salt_array);
    FREE(final_key);
    FREE(inbuffer);
    FREE(outbuffer);

}

array<Byte>^ Cipher::encodeText(System::String^ plaintext, System::String^ key, int maxLength) {

    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());

    NEW(unsigned char, iv_array, EVP_MAX_IV_LENGTH);
    NEW(unsigned char, salt_array, SALT_LENGTH);
    NEW(unsigned char, final_key, EVP_MAX_KEY_LENGTH);
    NEW(unsigned char, outbuffer, maxLength * 2);
    int out_len;

    if (!areLibrariesLoaded()) {
        throw gcnew Exception("Libraries aren't loaded!");
    }


    if ((plaintext->Length + 4) > maxLength) {
        throw gcnew Exception("String larger than maximum length allowed");
    }

    std::vector<unsigned char> plaintext_vec(maxLength);
    std::vector<unsigned char> output;

    for (int i = 0; i < 4; i++) {
        plaintext_vec[i] = (plaintext->Length >> i) & 0xFF;
    }

    for (int i = 0; i < plaintext->Length; i++) {
        plaintext_vec[(i + 4)] = static_cast<unsigned char>(plaintext[i]);
    }

    LOAD_FUNC(RAND_bytes_ptr, RAND_bytes);
    if (!RAND_bytes(salt_array, sizeof(salt_array))) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao gerar salt aleatório\n");
    }

    for (int i = (4 + plaintext->Length); i < maxLength; i++) {
        plaintext_vec[i] = salt_array[i % SALT_LENGTH];
    }

    LOAD_FUNC(OPENSSL_init_crypto_t, OPENSSL_init_crypto);
    LOAD_FUNC(EVP_CIPHER_CTX_new_t, EVP_CIPHER_CTX_new);
    LOAD_FUNC(EVP_CIPHER_CTX_free_t, EVP_CIPHER_CTX_free);
    LOAD_FUNC(EVP_aes_256_cbc_t, EVP_aes_256_cbc);
    LOAD_FUNC(EVP_EncryptInit_ex_t, EVP_EncryptInit_ex);
    LOAD_FUNC(EVP_EncryptUpdate_t, EVP_EncryptUpdate);
    LOAD_FUNC(EVP_EncryptFinal_ex_t, EVP_EncryptFinal_ex);
    LOAD_FUNC(PKCS5_PBKDF2_HMAC_ptr, PKCS5_PBKDF2_HMAC);
    LOAD_FUNC(EVP_sha256_ptr, EVP_sha256);

    if (!RAND_bytes(salt_array, sizeof(salt_array))) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao gerar salt aleatório\n");
    }

    if (!RAND_bytes(iv_array, sizeof(iv_array))) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao gerar IV aleatório\n");
    }

    if (!PKCS5_PBKDF2_HMAC(reinterpret_cast<const char*>(key_arr), -1, salt_array, sizeof(salt_array), 10000, EVP_sha256(), sizeof(final_key), final_key)) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao derivar a chave\n");
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        throw gcnew Exception("Falha em criar contexto de cifra.");
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)final_key, (const unsigned char*)iv_array)) {
        EVP_CIPHER_CTX_free(ctx);
        throw gcnew Exception("Falha ao inicializar a cifra.");
    }

    for (int i = 0; i < EVP_MAX_IV_LENGTH; i++) {
        output.push_back(iv_array[i]);
    }

    for (int i = 0; i < SALT_LENGTH; i++) {
        output.push_back(salt_array[i]);
    }

    if (1 != EVP_EncryptUpdate(ctx, outbuffer, &out_len, plaintext_vec.data(), plaintext_vec.size())) {
        EVP_CIPHER_CTX_free(ctx);
        throw gcnew Exception("Falha ao atualizar a cifra.");
    }

    for (int i = 0; i < out_len; i++) {
        output.push_back(outbuffer[i]);
    }

    if (1 != EVP_EncryptFinal_ex(ctx, outbuffer, &out_len)) {
        throw gcnew System::Exception("Failed to finish the process");
    }

    for (int i = 0; i < out_len; i++) {
        output.push_back(outbuffer[i]);
    }


    EVP_CIPHER_CTX_free(ctx);

    FREE(iv_array);
    FREE(salt_array);
    FREE(final_key);
    FREE(outbuffer);

    array<Byte>^ managedArray = gcnew array<Byte>(output.size());
    for (size_t i = 0; i < output.size(); ++i)
    {
        managedArray[i] = output[i];
    }
    
    return managedArray;
}

void Cipher::encode(System::String^ plaintext, System::String^ key, System::String^ fileToSave) {
    unsigned char iv_array[EVP_MAX_IV_LENGTH];
    unsigned char salt_array[8];
    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());
    unsigned char final_key[EVP_MAX_KEY_LENGTH];

    if (!areLibrariesLoaded()) {
        throw gcnew Exception("Libraries aren't loaded!");
    }

    std::vector<unsigned char> plaintext_vec(plaintext->Length);
    for (int i = 0; i < plaintext->Length; ++i) {
        plaintext_vec[i] = static_cast<unsigned char>(plaintext[i]);
    }

    plaintext_vec = addPadding(plaintext_vec);

    PKCS5_PBKDF2_HMAC_ptr PKCS5_PBKDF2_HMAC = (PKCS5_PBKDF2_HMAC_ptr)GetProcAddress(hLibCrypto, "PKCS5_PBKDF2_HMAC");
    if (!PKCS5_PBKDF2_HMAC) {
        throw std::runtime_error("Falha ao obter PKCS5_PBKDF2_HMAC\n");
        FreeLibrary(hLibCrypto);
        return;
    }

    // Carregar RAND_bytes
    RAND_bytes_ptr RAND_bytes = (RAND_bytes_ptr)GetProcAddress(hLibCrypto, "RAND_bytes");
    if (!RAND_bytes) {
        throw std::runtime_error("Falha ao obter RAND_bytes\n");
        FreeLibrary(hLibCrypto);
        return;
    }

    RAND_bytes(iv_array, EVP_MAX_IV_LENGTH);
    RAND_bytes(salt_array, 8);

    OPENSSL_init_crypto_t OPENSSL_init_crypto = (OPENSSL_init_crypto_t)GetProcAddress(hLibCrypto, "OPENSSL_init_crypto");
    EVP_aes_256_cbc_t EVP_aes_256_cbc = (EVP_aes_256_cbc_t)GetProcAddress(hLibCrypto, "EVP_aes_256_cbc");
    EVP_CIPHER_CTX_new_t EVP_CIPHER_CTX_new = (EVP_CIPHER_CTX_new_t)GetProcAddress(hLibCrypto, "EVP_CIPHER_CTX_new");
    EVP_CIPHER_CTX_free_t EVP_CIPHER_CTX_free = (EVP_CIPHER_CTX_free_t)GetProcAddress(hLibCrypto, "EVP_CIPHER_CTX_free");
    EVP_EncryptInit_ex_t EVP_EncryptInit_ex = (EVP_EncryptInit_ex_t)GetProcAddress(hLibCrypto, "EVP_EncryptInit_ex");
    EVP_EncryptUpdate_t EVP_EncryptUpdate = (EVP_EncryptUpdate_t)GetProcAddress(hLibCrypto, "EVP_EncryptUpdate");
    EVP_EncryptFinal_ex_t EVP_EncryptFinal_ex = (EVP_EncryptFinal_ex_t)GetProcAddress(hLibCrypto, "EVP_EncryptFinal_ex");

    EVP_CIPHER_CTX_set_padding_t EVP_CIPHER_CTX_set_padding = (EVP_CIPHER_CTX_set_padding_t)GetProcAddress(hLibCrypto, "EVP_CIPHER_CTX_set_padding");

    EVP_sha256_ptr EVP_sha256 = (EVP_sha256_ptr)GetProcAddress(hLibCrypto, "EVP_sha256");
    if (!EVP_sha256) {
        FreeLibrary(hLibCrypto);
        throw std::runtime_error("Falha ao obter EVP_sha256\n");
    }

    if (!RAND_bytes(salt_array, sizeof(salt_array))) {
        FreeLibrary(hLibCrypto);
        throw std::runtime_error("Falha ao gerar salt aleatório\n");
    }

    if (!RAND_bytes(iv_array, sizeof(iv_array))) {
        FreeLibrary(hLibCrypto);
        throw std::runtime_error("Falha ao gerar IV aleatório\n");
    }

    if (!PKCS5_PBKDF2_HMAC(reinterpret_cast<const char*>(key_arr), -1, salt_array, sizeof(salt_array), 10000, EVP_sha256(), sizeof(final_key), final_key)) {
        throw std::runtime_error("Falha ao derivar a chave\n");
        FreeLibrary(hLibCrypto);
        return;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Falha em criar contexto de cifra.");
    }

    if (!EVP_CIPHER_CTX_set_padding || !EVP_EncryptInit_ex || !EVP_EncryptUpdate) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Falha ao obter endereços das funções OpenSSL.");
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)final_key, (const unsigned char*)iv_array)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Falha ao inicializar a cifra.");
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0); // Desativar padding automático

    std::vector<unsigned char> ciphertext(plaintext_vec.size());
    int len = 0, ciphertext_len = 0;

    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext_vec.data(), plaintext_vec.size())) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Falha ao atualizar a cifra.");
    }
    ciphertext_len = len;

    try {
        FileStream^ fs = gcnew FileStream(fileToSave, FileMode::Create);

        array<Byte>^ bytes = BitConverter::GetBytes(ciphertext_len);

        fs->Write(bytes, 0, sizeof(int));

        for (int i = 0; i < EVP_MAX_IV_LENGTH; i++) {
            fs->WriteByte(iv_array[i]);
        }

        for (int i = 0; i < 8; i++) {
            fs->WriteByte(salt_array[i]);
        }

        for (int i = 0; i < ciphertext_len; i++) {
            fs->WriteByte(ciphertext[i]);
        }
        fs->Close();
    }
    catch (Exception^ e) {
        EVP_CIPHER_CTX_free(ctx);
        throw gcnew Exception(e->Message);
    }

    EVP_CIPHER_CTX_free(ctx);
}

System::String^ Cipher::decode(System::String^ fileToLoad, System::String^ key) {
    System::String^ result;
    unsigned char iv_array[EVP_MAX_IV_LENGTH];
    unsigned char salt_array[8];
    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());
    unsigned char final_key[EVP_MAX_KEY_LENGTH];

    if (!areLibrariesLoaded()) {
        throw gcnew Exception("Libraries aren't loaded!");
    }

    OPENSSL_init_crypto_t OPENSSL_init_crypto = (OPENSSL_init_crypto_t)GetProcAddress(hLibCrypto, "OPENSSL_init_crypto");
    EVP_CIPHER_CTX_new_t EVP_CIPHER_CTX_new = (EVP_CIPHER_CTX_new_t)GetProcAddress(hLibCrypto, "EVP_CIPHER_CTX_new");
    EVP_CIPHER_CTX_free_t EVP_CIPHER_CTX_free = (EVP_CIPHER_CTX_free_t)GetProcAddress(hLibCrypto, "EVP_CIPHER_CTX_free");
    EVP_aes_256_cbc_t EVP_aes_256_cbc = (EVP_aes_256_cbc_t)GetProcAddress(hLibCrypto, "EVP_aes_256_cbc");
    EVP_DecryptInit_ex_t EVP_DecryptInit_ex = (EVP_DecryptInit_ex_t)GetProcAddress(hLibCrypto, "EVP_DecryptInit_ex");
    EVP_DecryptUpdate_t EVP_DecryptUpdate = (EVP_DecryptUpdate_t)GetProcAddress(hLibCrypto, "EVP_DecryptUpdate");
    EVP_DecryptFinal_ex_t EVP_DecryptFinal_ex = (EVP_DecryptFinal_ex_t)GetProcAddress(hLibCrypto, "EVP_DecryptFinal_ex");
    EVP_CIPHER_CTX_set_padding_t EVP_CIPHER_CTX_set_padding = (EVP_CIPHER_CTX_set_padding_t)GetProcAddress(hLibCrypto, "EVP_CIPHER_CTX_set_padding");

    // Carregar PKCS5_PBKDF2_HMAC
    PKCS5_PBKDF2_HMAC_ptr PKCS5_PBKDF2_HMAC = (PKCS5_PBKDF2_HMAC_ptr)GetProcAddress(hLibCrypto, "PKCS5_PBKDF2_HMAC");
    if (!PKCS5_PBKDF2_HMAC) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao obter PKCS5_PBKDF2_HMAC\n");
    }

    // Carregar RAND_bytes
    RAND_bytes_ptr RAND_bytes = (RAND_bytes_ptr)GetProcAddress(hLibCrypto, "RAND_bytes");
    if (!RAND_bytes) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao obter RAND_bytes\n");
    }

    EVP_sha256_ptr EVP_sha256 = (EVP_sha256_ptr)GetProcAddress(hLibCrypto, "EVP_sha256");
    if (!EVP_sha256) {
        FreeLibrary(hLibCrypto);
        throw gcnew Exception("Falha ao obter EVP_sha256\n");
    }

    if (!EVP_CIPHER_CTX_new || !EVP_CIPHER_CTX_free || !EVP_DecryptInit_ex || !EVP_DecryptUpdate || !EVP_CIPHER_CTX_set_padding) {
        throw gcnew Exception("Failed to load decrypt functions.");
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw gcnew Exception("Failed to create crypt context!");
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0);

    try {
        FileStream^ fs = gcnew FileStream(fileToLoad, FileMode::Open);
        array<Byte>^ lengthBytes = gcnew array<Byte>(sizeof(int));

        fs->Read(lengthBytes, 0, sizeof(int));

        int ciphertext_len = BitConverter::ToInt32(lengthBytes, 0);

        for (int i = 0; i < EVP_MAX_IV_LENGTH; i++) {
            iv_array[i] = fs->ReadByte();
        }

        for (int i = 0; i < 8; i++) {
            salt_array[i] = fs->ReadByte();
        }

        if (!PKCS5_PBKDF2_HMAC(reinterpret_cast<const char*>(key_arr), -1, salt_array, sizeof(salt_array), 10000, EVP_sha256(), sizeof(final_key), final_key)) {
            FreeLibrary(hLibCrypto);
            throw gcnew Exception("Falha ao derivar a chave\n");
        }

        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)final_key, (const unsigned char*)iv_array)) {
            EVP_CIPHER_CTX_free(ctx);
            throw gcnew Exception("Falha ao inicializar a descriptografia.");
        }

        std::vector<unsigned char> ciphertext(ciphertext_len);
        for (int i = 0; i < ciphertext_len; i++) {
            ciphertext[i] = fs->ReadByte();
        }
        fs->Close();


        std::vector<unsigned char> decryptedtext(ciphertext_len);
        int decrypted_len = 0, len = 0;

        if (1 != EVP_DecryptUpdate(ctx, decryptedtext.data(), &len, ciphertext.data(), ciphertext_len)) {
            EVP_CIPHER_CTX_free(ctx);
            throw gcnew Exception("Falha ao atualizar a descriptografia.");
        }
        decrypted_len = len;

        if (decrypted_len > 0) {
            int padSize = static_cast<int>(decryptedtext[decrypted_len - 1]);
            if (padSize > 0 && padSize <= AES_BLOCK_SIZE && decrypted_len >= padSize) {
                for (int i = 1; i < padSize; ++i) {
                    if (decryptedtext[decrypted_len - i - 1] != padSize) {
                        padSize = 0; break;
                    }
                }
                decrypted_len -= padSize;
            }
        }

        std::string cppString((char*)decryptedtext.data(), decrypted_len);
        result = marshal_as<System::String^>(cppString);
    }
    catch (Exception^ e) {
        EVP_CIPHER_CTX_free(ctx);
        throw e;
    }

    EVP_CIPHER_CTX_free(ctx);
    return result;
}