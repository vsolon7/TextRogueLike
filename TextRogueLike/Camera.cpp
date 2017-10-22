#include "Camera.h"
#include "Utility.h"

Camera::Camera()
{
}

void Camera::init(Player *p)
{
	//have one tile for noise, saves me from memory leaks and also don't have to delete tons
	_noiseTile = new Tile((char)TILE::NOISE, nullptr, NULL, NULL, TYPE::NOISE);

	_player = p;
}

std::vector< std::vector<Tile *> > Camera::getCameraView(Level *l, EFFECTS e)
{
	//the startX of the camera is 1/2 of the total camera width. this will have the player be as centered as possible
	int startX = _player->getCurrX() - ACTUAL_CAMERA_WIDTH / 2;
	//same with Y but with height
	int startY = _player->getCurrY() - ACTUAL_CAMERA_HEIGHT / 2;

	//the visibility of the camera. we will limit this using this variable just in case the
	//camera view width or height is larger than the level, that way we don't get vector subscript out of range
	_actualViewWidth = ACTUAL_CAMERA_WIDTH;
	_actualViewHeight = ACTUAL_CAMERA_HEIGHT;

	//just storing the level in a temp variable so we only have to call it once.
	std::vector<std::vector<Tile *> > tempLvl = l->getLevelData();

	//if the the player is too far to the left, this will cause startX to be less than 0
	//this limits that, vectors can't have negative indices. basically, the camera will be as close to the center
	//as it can be while staying within the level bounds.
	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;

	//if the visibility of the camera is bigger than the level, make sure the camera doesn't try to see out of the bounds of the level.
	if (tempLvl.size() <= ACTUAL_CAMERA_HEIGHT)
		_actualViewHeight = tempLvl.size();
	if (tempLvl[startY].size() <= ACTUAL_CAMERA_HEIGHT)
		_actualViewWidth = tempLvl.size();

	//and if the starting X and Y would cause the camera to go out of bounds, keep the camera as close to the right/bottom
	//as possible without going over the level bounds.
	if (startX >(signed int) tempLvl[startY].size() - _actualViewWidth)
		startX = tempLvl[startY].size() - _actualViewWidth;
	if (startY >(signed int) tempLvl.size() - _actualViewHeight)
		startY = tempLvl.size() - _actualViewHeight;

	//load the visible part of the level into the camera.
	std::vector< std::vector<Tile *> > camera(_actualViewHeight);

	int playerCurrX = _player->getCurrX();
	int playerCurrY = _player->getCurrY();

	for (unsigned int y = 0; y < camera.size(); y++)
	{
		for (int x = 0; x < _actualViewWidth; x++)
		{
			//if the noise effect is applied, obfuscate random tiles with noise!
			if (e == EFFECTS::NOISE && x != playerCurrX - startX && y != playerCurrY - startY)
			{
				int chance = (int)EFFECTS::NOISE;
				std::uniform_int_distribution<int> noiseRoll(0, 100);

				int roll = noiseRoll(Utility::randEngine);

				if (roll <= chance)
				{
					camera[y].push_back(_noiseTile);
				}
				else
					camera[y].push_back(tempLvl[startY + y][startX + x]);

			}
			else
				camera[y].push_back(tempLvl[startY + y][startX + x]);
		}
	}

	_apparentViewWidth = _actualViewWidth * 2;
	_apparentViewHeight = _actualViewHeight;

	return camera;
}

int Camera::getViewWidth()
{
	return _apparentViewWidth;
}

int Camera::getViewHeight()
{
	return _apparentViewHeight;
}

Camera::~Camera()
{
}
