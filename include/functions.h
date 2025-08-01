void text_window(HWND hwnd) {
	x = 50;
	y = 100;
	w = 500;
	h = 100;
	hText = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			x, y, w, h, hwnd, (HMENU)plain_text, 0, 0);

	x = 195;
	y = 225;
	w = 65;
	h = 30;
	hEncrypt = CreateWindowA("button", "Encrypt", WS_VISIBLE | WS_CHILD,
		x, y, w, h, hwnd, (HMENU)encrypt, 0, 0);

	x = 295;
	y = 225;
	w = 65;
	h = 30;
	hDecrypt = CreateWindowA("button", "Decrypt", WS_VISIBLE | WS_CHILD,
		x, y, w, h, hwnd, (HMENU)decrypt, 0, 0);

	x = 250;
	y = 25;
	w = 50;
	h = 30;
	hClear = CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD,
		x, y, w, h, hwnd, (HMENU)clear, 0, 0);
	
	x = 600;
	y = 35;
	w = 150;
	h = 50;
	hKey = CreateWindowA("edit", "21", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		x, y, w, h, hwnd, (HMENU)key, 0, 0);

}

void encrypted_text_window(HWND hwnd) {
	x = 50;
	y = 300;
	w = 500;
	h = 100;
	hEncryptedText = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_READONLY | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		x, y, w, h, hwnd, (HMENU)encrypted_text, 0, 0);

	x = 250;
	y = 425;
	w = 50;
	h = 30;
	hCopy = CreateWindowA("button", "Copy", WS_VISIBLE | WS_CHILD,
		x, y, w, h, hwnd, (HMENU)copy, 0, 0);

}

void decrypted_text_window(HWND hwnd) {
	x = 50;
	y = 500;
	w = 500;
	h = 100;
	hDecryptedText = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE|ES_READONLY | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		x, y, w, h, hwnd, (HMENU)decrypted_text, 0, 0);


}

int* convert_text_to_asci(char* text_buffer,int text_length,int key_integer) {
	int* result = (int*)malloc(sizeof(int) * text_length);
	for (int i = 0; i < text_length; i++) {
		result[i] = (unsigned char)text_buffer[i];
	}
	return result;
}

int encrypt_algorithm_n1(int asci, int key_integer) {
	return (asci + key_integer) % BASE; // Simple algorithm: add key to ASCII value and wrap around at BASE	
}
int decrypt_algorithm_n1(int asci, int key_integer) {


	if (asci < key_integer) {
		asci += BASE; // Ensure we don't get negative values
	}
	return (asci - key_integer) % BASE; //bcos decryption turns value to minus key_integer
	
}


int* cipher_text_to_int_with_key(int* asci_array_of_text_buffer, int text_length, int key_integer) {
	int* result = (int*)malloc(text_length * sizeof(int) +1);
	for (int i = 0; i < text_length; i++) {
		result[i] = encrypt_algorithm_n1(asci_array_of_text_buffer[i], key_integer);
	}

	return result;
}

 unsigned char* encrypt_from_asci_to_char_with_key(int* asci_array_of_ciphered_text_with_key,int text_length) {
	 unsigned char* result = (unsigned char*)malloc(text_length + 1);
	for (int i = 0; i < text_length; i++) {
		result[i] = (unsigned char)(asci_array_of_ciphered_text_with_key[i]);
	}
	result[text_length] = '\0'; // Null-terminate the string
	return result;
}

 unsigned char* decrypt_from_asci_to_char_with_key(int* encrypted_text_buffer_to_int, int text_length, int key_integer) {
	 unsigned char* result = (unsigned char*)malloc(text_length + 1);
	 for (int i = 0; i < text_length; i++) {
		 result[i] = (unsigned char)decrypt_algorithm_n1(encrypted_text_buffer_to_int[i],key_integer);
	 }
	 result[text_length] = '\0'; // Null-terminate the string
	 return result;
 }
void loadBitmaps() {
	background_bm=(HBITMAP)LoadImageA(0, "assets/background.bmp", IMAGE_BITMAP, 900, 900, LR_LOADFROMFILE);

}