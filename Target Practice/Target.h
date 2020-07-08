class Target
{
private:
	int posX, posY;
	long int randNum;
	unsigned int time;
	BITMAP *targetBmp, *smashBmp, *activeBmp;
	bool beenHit, positionSet;
public:
	int getPosX();
	void setPosX(int newX);
	int getPosY();
	void setPosY(int newY);

	void move();
	void move(int x, int y);

	void checkHit();
	bool hasBeenHit();

	void drawTarget(BITMAP* bmp);

	void Target::setPosition();
	bool isPositionSet();

	void fallOff();

	void ctorTarget();
	void dtorTarget();

};