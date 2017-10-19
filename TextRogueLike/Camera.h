#pragma once
#include "Level.h"

#define ACTUAL_CAMERA_WIDTH 16
#define ACTUAL_CAMERA_HEIGHT 16

#define APPARENT_CAMERA_WIDTH ACTUAL_CAMERA_WIDTH * 2
#define APPARENT_CAMERA_HEIGHT ACTUAL_CAMERA_HEIGHT * 1

enum class EFFECTS
{
	NONE, NOISE
};

class Camera
{
public:
	Camera();
	~Camera();
	
	void init(Player *p);

	//this will return a vector of tiles that the player can see, as they move 
	//it will (hopefully) move along the level with them!
	std::vector< std::vector<Tile *> > getCameraView(Level *l, EFFECTS e = EFFECTS::NONE);

	int getViewWidth();
	int getViewHeight();

private:
	Player *_player;
	int _actualViewWidth, _actualViewHeight;
	int _apparentViewWidth, _apparentViewHeight;
};

