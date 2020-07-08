#include "includes.h"

void Target::ctorTarget()
{

	targetBmp = load_bitmap("Assets/Target/target.bmp", NULL);
	smashBmp =  load_bitmap("Assets/Target/targetSmash.bmp", NULL);
	activeBmp = targetBmp;

	time = std::time(0);
	std::srand(time);
	randNum = long int(pow(long double(std::rand()),2));
	posY = randNum % 738;
	posX = randNum % 994;
	
	beenHit = false;
	positionSet=false;
}

void Target::dtorTarget()
{
	destroy_bitmap(targetBmp);
}

int Target::getPosX()
{
	return posX;
}
int Target::getPosY()
{
	return posY;
}
void Target::setPosX(int newX)
{
	posX = newX;
}
void Target::setPosY(int newY)
{
	posY = newY;
}

void Target::move(int x, int y)
{
	posX += x;
	posY -= y;
}

void Target::checkHit()
{
	if(
		((posX <= mouse_x)&&
		(mouse_x<=posX+targetBmp->w))&&
		((posY <= mouse_y)&&
		(mouse_y<=posY+targetBmp->h))
		)
	{
		if (mouse_b&1)
		{
			beenHit=true;
		}
	}
}

bool Target::hasBeenHit()
{
	return beenHit;
}

void Target::setPosition()
{
	time = std::time(0);
	std::srand(time);
	randNum = long int(pow(long double(std::rand()),2));
	posY = randNum % 738;
	posX = randNum % 994;
	positionSet = true;
}

bool Target::isPositionSet()
{
	return positionSet;
}

void Target::fallOff()
{
	activeBmp = smashBmp;
	if (posY<770)
	{
		posY+=10;
	}
}
void Target::drawTarget(BITMAP* bmp)
{
	draw_sprite(bmp, activeBmp, posX, posY);
}