#include "includes.h"

Cursor::Cursor()
{
	cursorBmp = load_bitmap("Assets/Cursor/cursor.bmp", NULL);
}
Cursor::~Cursor()
{
	destroy_bitmap(cursorBmp);
}

void Cursor::drawCursor(BITMAP* bmp)
{
	draw_sprite(bmp, cursorBmp, mouse_x-15, mouse_y-15);
}