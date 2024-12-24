#include "Cipher.h"

Cipher::Cipher() {
	this->libsLoaded = false;
}

Cipher::~Cipher() {

}

void Cipher::loadLibraries() {
	this->hLibCrypto = LoadLibrary(L"D:/Codigos/SSL/openssl-3.4.0/dist/bin/libcrypto-3-x64.dll");
	this->hLibSSL = LoadLibrary(L"D:/Codigos/SSL/openssl-3.4.0/dist/bin/libssl-3-x64.dll");

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

void Cipher::encode(System::String^ plaintext, System::String^ key, System::String^ fileToSave) {
    unsigned char iv_array[EVP_MAX_IV_LENGTH];
    unsigned char salt_array[8];
    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());
    unsigned char final_key[EVP_MAX_KEY_LENGTH];

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
        throw std::runtime_error(msclr::interop::marshal_as<std::string>(e->Message).c_str());
    }

    EVP_CIPHER_CTX_free(ctx);
}

System::String^ Cipher::decode(System::String^ fileToLoad, System::String^ key) {
    System::String^ result;
    unsigned char iv_array[EVP_MAX_IV_LENGTH];
    unsigned char salt_array[8];
    unsigned char* key_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());
    unsigned char final_key[EVP_MAX_KEY_LENGTH];

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
        throw std::runtime_error("Falha ao obter PKCS5_PBKDF2_HMAC\n");
    }

    // Carregar RAND_bytes
    RAND_bytes_ptr RAND_bytes = (RAND_bytes_ptr)GetProcAddress(hLibCrypto, "RAND_bytes");
    if (!RAND_bytes) {
        FreeLibrary(hLibCrypto);
        throw std::runtime_error("Falha ao obter RAND_bytes\n");
    }

    EVP_sha256_ptr EVP_sha256 = (EVP_sha256_ptr)GetProcAddress(hLibCrypto, "EVP_sha256");
    if (!EVP_sha256) {
        FreeLibrary(hLibCrypto);
        throw std::runtime_error("Falha ao obter EVP_sha256\n");
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
            throw std::runtime_error("Falha ao derivar a chave\n");
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