#define main 1
#define generate 2
#define clear 3
#define copy 4
#define encrypt 5
#define decrypt 6

#define plain_text 11
#define encrypted_text 12
#define decrypted_text 13
#define key 14

#define MAX_TEXT_SIZE 4096
#define BASE 256
int x, y, w, h;

HWND hText,hEncryptedText,hDecryptedText,hEncrypt,hDecrypt,hClear,hCopy,hKey;

HBITMAP background_bm;