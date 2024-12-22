#pragma once

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\auto_gcroot.h>

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Text;
using namespace System::IO;

typedef int (*OPENSSL_init_crypto_t)(uint64_t opts, const OPENSSL_INIT_SETTINGS* settings);
typedef const EVP_CIPHER* (*EVP_aes_128_cbc_t)();
typedef EVP_CIPHER_CTX* (*EVP_CIPHER_CTX_new_t)();
typedef void (*EVP_CIPHER_CTX_free_t)(EVP_CIPHER_CTX*);
typedef int (*EVP_EncryptInit_ex_t)(EVP_CIPHER_CTX*, const EVP_CIPHER*, ENGINE*, const unsigned char*, const unsigned char*);
typedef int (*EVP_EncryptUpdate_t)(EVP_CIPHER_CTX*, unsigned char*, int*, const unsigned char*, int);
typedef int (*EVP_EncryptFinal_ex_t)(EVP_CIPHER_CTX*, unsigned char*, int*);

typedef int (*EVP_DecryptInit_ex_t)(EVP_CIPHER_CTX*, const EVP_CIPHER*, ENGINE*, const unsigned char*, const unsigned char*);
typedef int (*EVP_DecryptUpdate_t)(EVP_CIPHER_CTX*, unsigned char*, int*, const unsigned char*, int);
typedef int (*EVP_DecryptFinal_ex_t)(EVP_CIPHER_CTX*, unsigned char*, int*);

ref class Cipher
{
private:

	System::String^ password;
	HINSTANCE hLibCrypto;
	HINSTANCE hLibSSL;
	bool libsLoaded;


public:
	Cipher();
	~Cipher();
	bool encode(System::String^ pass, System::String^ fileToSave);
	void decode(System::String^ pass);
	void loadLibraries();
	bool areLibrariesLoaded();
};

