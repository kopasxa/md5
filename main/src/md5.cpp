#include <string>
#include <Windows.h>
#include <Wincrypt.h>

char* md( std::string data, DWORD* result ) {
    DWORD dwStatus = 0;
    DWORD cbHash = 16;
    int i = 0;
    HCRYPTPROV cryptProv;
    HCRYPTHASH cryptHash;
    BYTE hash[16];
    std::string hex = "0123456789abcdef";
    char* strHash;
    strHash = (char*)malloc( 500 );
    memset( strHash, '\0', 500 );
    if (!CryptAcquireContext( &cryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT )) {
        dwStatus = GetLastError();
        printf( "CryptAcquireContext failed: %d\n", dwStatus );
        *result = dwStatus;
        return NULL;
    }
    if (!CryptCreateHash( cryptProv, CALG_MD5, 0, 0, &cryptHash )) {
        dwStatus = GetLastError();
        printf( "CryptCreateHash failed: %d\n", dwStatus );
        CryptReleaseContext( cryptProv, 0 );
        *result = dwStatus;
        return NULL;
    }
    if (!CryptHashData( cryptHash, (BYTE*)data.c_str(), data.length(), 0 )) {
        dwStatus = GetLastError();
        printf( "CryptHashData failed: %d\n", dwStatus );
        CryptReleaseContext( cryptProv, 0 );
        CryptDestroyHash( cryptHash );
        *result = dwStatus;
        return NULL;
    }
    if (!CryptGetHashParam( cryptHash, HP_HASHVAL, hash, &cbHash, 0 )) {
        dwStatus = GetLastError();
        printf( "CryptGetHashParam failed: %d\n", dwStatus );
        CryptReleaseContext( cryptProv, 0 );
        CryptDestroyHash( cryptHash );
        *result = dwStatus;
        return NULL;
    }
    for (i = 0; i < cbHash; i++) {
        strHash[i * 2] = hex[hash[i] >> 4];
        strHash[(i * 2) + 1] = hex[hash[i] & 0xF];
    }
    CryptReleaseContext( cryptProv, 0 );
    CryptDestroyHash( cryptHash );
    return strHash;
}
