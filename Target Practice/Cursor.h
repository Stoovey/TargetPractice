class Cursor
{
private:
	BITMAP* cursorBmp;
public:
	Cursor();
	~Cursor();
	void drawCursor(BITMAP* bmp);

};