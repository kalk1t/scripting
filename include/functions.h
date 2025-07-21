void text_window(HWND hwnd) {
	x = 50;
	y = 100;
	w = 500;
	h = 100;
	hText = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			x, y, w, h, hwnd, (HMENU)plain_text, 0, 0);

	x = 650;
	y = 140;
	w = 65;
	h = 30;
	hGenerate = CreateWindowA("button", "Generate", WS_VISIBLE | WS_CHILD,
		x, y, w, h, hwnd, (HMENU)generate, 0, 0);

	x = 250;
	y = 25;
	w = 50;
	h = 30;
	hClear = CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD,
		x, y, w, h, hwnd, (HMENU)clear, 0, 0);


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
	hCopy = CreateWindowA("button", "copy", WS_VISIBLE | WS_CHILD,
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


void loadBitmaps() {
	background_bm=(HBITMAP)LoadImageA(0, "assets/background.bmp", IMAGE_BITMAP, 900, 900, LR_LOADFROMFILE);

}