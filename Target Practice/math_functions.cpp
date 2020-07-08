#include "includes.h"

float deg_to_rad(float angle_D)
{
	return (PI/180)*angle_D;
}
float rad_to_deg(float angle_R)
{
	return (180/PI)*angle_R;
}

float rad_to_fix(float angle_R)
{
	return (128/PI)*angle_R;
}
float fix_to_rad(fixed angle_F)
{
	return (PI/128)*angle_F;
}

float deg_to_fix(float angle_D)
{
	return ((128/180)*angle_D);
}
float fix_to_deg(float angle_F)
{
	return (180/128)*angle_F;
}

//Using constant acceleration formulae (SUVAT)
//Assumes angle is taken with the positive horizontal at 0 degrees

float calc_vert_flight_displacement(float shotAngle, float shotPower, float gravity)
{
	float sy,uy,a;
	a = -gravity;
	uy = shotPower * sin(deg_to_rad(shotAngle));
	sy = -pow(uy,2)/(2*a);
	return sy;
}
float calc_vert_flight_time(float shotAngle, float shotPower, float gravity)
{
	float uy,a,t;
	a = -gravity;
	uy = shotPower * sin(deg_to_rad(shotAngle));
	t = -2 * (uy/a);
	return t;
}
float calc_horz_flight_displacement(float shotAngle, float shotPower, float flightTime)
{
	float sx,ux,t;
	t = flightTime;
	ux = shotPower * cos(deg_to_rad(shotAngle));

	sx = ux*t;
	return sx;
}