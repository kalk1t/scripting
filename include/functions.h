void text_window(HWND hwnd) {
	x = 50;
	y = 100;
	w = 300;
	h = 100;
	hText = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD,
			x, y, w, h, hwnd, (HMENU)text, 0, 0);




}

void loadBitmaps() {
	background_bm=(HBITMAP)LoadImageA(0, "assets/background.bmp", IMAGE_BITMAP, 900, 900, LR_LOADFROMFILE);

}