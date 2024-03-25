#ifndef WORLDENTITIES
#define WORLDENTITIES
#include <allegro5/allegro.h>
//#include "Engine.h"

//class Engine g;

enum Direction { DOWN, LEFT, RIGHT, UP };

bool collision(float& px, float& py, float ex, float ey, float width, float hight)
{
	if (px + width <= ex || px >= ex + width || py + hight <= ey || py >= hight + ey)
	{
		return false;
	}
	return true;
}

unsigned char key[ALLEGRO_KEY_MAX];
//Klasa gracza
class Player
{
private:
	float px;
	float py;
	int dir = DOWN;
	int p_sourceX = 0;
	bool moving = false;
	ALLEGRO_BITMAP* player = al_load_bitmap("player_temp.png");
public:
	Player(float _px, float _py) { px = _px; py = _py; }
	float getX() { return px; }
	float getY() { return py; }
	int getDIR() { return dir; }
	void setX(float x) { px = x; }
	void setY(float y) { py = y; }

	friend class Engine;

	void update_player(float& x, float& y)
	{
		moving = true;

		//poruszanie gracza
		if (key[ALLEGRO_KEY_UP]) { y -= g.mSpeed; dir = UP; }
		else if (key[ALLEGRO_KEY_DOWN]) { y += g.mSpeed; dir = DOWN; }
		else if (key[ALLEGRO_KEY_LEFT]) { x -= g.mSpeed; dir = LEFT; }
		else if (key[ALLEGRO_KEY_RIGHT]) { x += g.mSpeed; dir = RIGHT; }
		else { moving = false; }

		if (collision(x, y, 100, 100, 16, 16))
		{
			if (key[ALLEGRO_KEY_UP]) { y += g.mSpeed; dir = UP; }
			else if (key[ALLEGRO_KEY_DOWN]) { y -= g.mSpeed; dir = DOWN; }
			else if (key[ALLEGRO_KEY_LEFT]) { x += g.mSpeed; dir = LEFT; }
			else if (key[ALLEGRO_KEY_RIGHT]) { x -= g.mSpeed; dir = RIGHT; }
		}

		if (y <= 0) { y += g.mSpeed; dir = UP; }
		else if (y > g.dispH - 16) { y -= g.mSpeed; dir = DOWN; }
		else if (x <= 0) { x += g.mSpeed; dir = LEFT; }
		else if (x > g.dispW - 16) { x -= g.mSpeed; dir = RIGHT; }

		//animacje gracza
		if (moving)
		{
			g.timeSinceLastFrameSwap += g.deltaTime;
			if (g.timeSinceLastFrameSwap > g.animUpdateTime)
			{
				p_sourceX += al_get_bitmap_width(player) / 4;
				g.timeSinceLastFrameSwap = 0.0;
			}
			if (p_sourceX >= al_get_bitmap_width(player))
			{
				p_sourceX = 0;
			}
		}
		else
		{
			p_sourceX = 16;
			g.timeSinceLastFrameSwap = 0.0;
		}
	}

	void draw_player(float x, float y)
	{
		al_draw_bitmap_region(player, p_sourceX, dir * al_get_bitmap_height(player) / 4, 16, 16, x, y, 0);
	}
};

#endif