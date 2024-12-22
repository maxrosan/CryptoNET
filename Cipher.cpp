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

bool Cipher::encode(System::String^ pass, System::String^ fileToSave) {

    OPENSSL_init_crypto_t OPENSSL_init_crypto = (OPENSSL_init_crypto_t)GetProcAddress(this->hLibCrypto, "OPENSSL_init_crypto");
    EVP_aes_128_cbc_t EVP_aes_128_cbc = (EVP_aes_128_cbc_t)GetProcAddress(this->hLibCrypto, "EVP_aes_128_cbc");
    EVP_CIPHER_CTX_new_t EVP_CIPHER_CTX_new = (EVP_CIPHER_CTX_new_t)GetProcAddress(this->hLibCrypto, "EVP_CIPHER_CTX_new");
    EVP_CIPHER_CTX_free_t EVP_CIPHER_CTX_free = (EVP_CIPHER_CTX_free_t)GetProcAddress(this->hLibCrypto, "EVP_CIPHER_CTX_free");
    EVP_EncryptInit_ex_t EVP_EncryptInit_ex = (EVP_EncryptInit_ex_t)GetProcAddress(this->hLibCrypto, "EVP_EncryptInit_ex");
    EVP_EncryptUpdate_t EVP_EncryptUpdate = (EVP_EncryptUpdate_t)GetProcAddress(this->hLibCrypto, "EVP_EncryptUpdate");
    EVP_EncryptFinal_ex_t EVP_EncryptFinal_ex = (EVP_EncryptFinal_ex_t)GetProcAddress(this->hLibCrypto, "EVP_EncryptFinal_ex");

    if (!OPENSSL_init_crypto || !EVP_aes_128_cbc || !EVP_CIPHER_CTX_new || !EVP_CIPHER_CTX_free || !EVP_EncryptInit_ex || !EVP_EncryptUpdate || !EVP_EncryptFinal_ex) {
        std::cerr << "Falha ao obter endereço de uma das funções do OpenSSL." << std::endl;
        FreeLibrary(this->hLibCrypto);
        return false;
    }

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    //char* unmanagedString = static_cast<char*>(Marshal::StringToHGlobalAnsi(pass).ToPointer());
    
    System::String^ plaintext = "Texto a ser criptografado";
    System::String^ key = "0123456789abcdef"; // 16 bytes para AES-128, ajuste conforme necessário
    System::String^ iv = "0123456789abcdef"; // Vetor de inicialização, 16 bytes para AES-128

    char* key_arr = static_cast<char*>(Marshal::StringToHGlobalAnsi(key).ToPointer());
    char *iv_arr = static_cast<char*>(Marshal::StringToHGlobalAnsi(iv).ToPointer());
    unsigned char* plaintext_arr = static_cast<unsigned char*>(Marshal::StringToHGlobalAnsi(iv).ToPointer());

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Falha em criar contexto de cifra." << std::endl;
        FreeLibrary(this->hLibCrypto);
        return false;
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (const unsigned char*)key_arr, (const unsigned char*)iv_arr)) {
        std::cerr << "Falha ao inicializar a cifra." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        FreeLibrary(hLibCrypto);
        return false;
    }

    std::vector<unsigned char> ciphertext(plaintext->Length + AES_BLOCK_SIZE);
    int len = 0, ciphertext_len = 0;

    // Criptografar
    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext_arr, plaintext->Length)) {
        std::cerr << "Falha ao atualizar a cifra." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        FreeLibrary(hLibCrypto);
        return 1;
    }
    ciphertext_len = len;

    // Finalizar a criptografia
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len)) {
        std::cerr << "Falha ao finalizar a cifra." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        FreeLibrary(hLibCrypto);
        return 1;
    }
    ciphertext_len += len;

    try {

        FileStream^ fs = gcnew FileStream(fileToSave, FileMode::Create);

        for (int i = 0; i < ciphertext_len; i++) {
            unsigned char c = ciphertext[i];
            fs->WriteByte(c);
        }
        fs->Close();

    } catch (Exception^ e) {
        Console::WriteLine("Erro ao salvar o arquivo: {0}", e->Message);
        // Limpeza
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Limpeza
    EVP_CIPHER_CTX_free(ctx);


    return true;
}

void Cipher::decode(System::String^ pass) {

}

bool Cipher::areLibrariesLoaded() {
    return this->libsLoaded;
}