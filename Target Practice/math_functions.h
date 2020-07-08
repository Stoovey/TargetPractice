float deg_to_rad(float angle_D);
float rad_to_deg(float angle_R);

float rad_to_fix(float angle_R);
float fix_to_rad(fixed angle_F);

float deg_to_fix(float angle_D);
float fix_to_deg(float angle_F);

float calc_vert_flight_displacement(float shotAngle, float shotPower, float gravity);
float calc_vert_flight_time(float shotAngle, float shotPower, float gravity);
float calc_horz_flight_displacement(float shotAngle, float shotPower, float flightTime);