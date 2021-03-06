#define ROBOT_COUNT 4
// #define ROBOT_SPACING 40

#define ARENA_WIDTH 1000//(32*32 + 33*ROBOT_SPACING)
#define ARENA_HEIGHT 1000//(32*32 + 33*ROBOT_SPACING)

#define LIGHT_1_X ARENA_WIDTH / 2
#define LIGHT_1_Y ARENA_HEIGHT / 2 + 200
#define LIGHT_2_X ARENA_WIDTH / 2 - 200
#define LIGHT_2_Y ARENA_HEIGHT / 2 - 100
#define LIGHT_3_X ARENA_WIDTH / 2 + 200
#define LIGHT_3_Y ARENA_HEIGHT / 2 - 100

#define SIMULATION_TIME 180 //in seconds


// function to check if randomly generated positions are in collision
bool collision(float x, float y, float pos_list[ROBOT_COUNT][4], int limit) {
	for (int i = 0; i < limit; i++) {
		float existing_x = pos_list[i][0];
		float existing_y = pos_list[i][1];
		float dist = sqrt(pow(x - existing_x, 2) + pow(y - existing_y, 2));
		if (dist <= radius * 2) {
			return true;
		}
	}
	return false;
}

void setup_positions(float robot_pos[ROBOT_COUNT][4])
{

//assign each robot a random position, centered around light source
	int x= ARENA_WIDTH / 2;
	int y= ARENA_HEIGHT / 2;


// triangular positions
	// robot_pos[0][0] = ARENA_WIDTH/2;
	// robot_pos[0][1] = ARENA_HEIGHT/2 + 100;
	// robot_pos[0][2] = 1.57;
	// robot_pos[0][3] = 0;
	robot_pos[1][0] = LIGHT_1_X;
	robot_pos[1][1] = LIGHT_1_Y;
	robot_pos[1][2] = 1.57;
	robot_pos[1][3] = 10;
	robot_pos[2][0] = LIGHT_2_X;
	robot_pos[2][1] = LIGHT_2_Y;
	robot_pos[2][2] = 1.57;
	robot_pos[2][3] = 10;
	robot_pos[3][0] = LIGHT_3_X;
	robot_pos[3][1] = LIGHT_3_Y;
	robot_pos[3][2] = 1.57;
	robot_pos[3][3] = 10;

	float x0;
	float y0;
	float t0;
	do
	{
		x0 = (float) rand() * (400-radius*2) / RAND_MAX + LIGHT_2_X + 2*radius;
		y0 = (float) rand() * (400-radius*2) / RAND_MAX + LIGHT_2_Y -100 + 2*radius;
		t0 = rand() * 2 * PI / RAND_MAX;
	} while (collision(x0, y0, robot_pos, 0));
	robot_pos[0][0] = x0;
	robot_pos[0][1] = y0;
	robot_pos[0][2] = t0;
	robot_pos[0][3] = 0;

}
