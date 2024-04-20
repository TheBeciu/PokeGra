#ifndef WORLDENTITIES
#define WORLDENTITIES
#include <allegro5/allegro.h>
#include "Engine.h"

Engine game;

enum Direction { DOWN, LEFT, RIGHT, UP };

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
	Player(float _px, float _py)	{ px = _px; py = _py; }
	float getX()					{ return px; }
	float getY()					{ return py; }
	int getDIR()					{ return dir; }
	void setX(float x)				{ px = x; }
	void setY(float y)				{ py = y; }
	void setDIR(int d)				{ dir = d; }
	void setMoving(bool m)			{ moving = m; }

	//friend class Engine;

	void update_player()
	{
		moving = true;

		//poruszanie gracza
		if (game.key[ALLEGRO_KEY_UP])			{ py -= game.getMSpeed(); dir = UP; }
		else if (game.key[ALLEGRO_KEY_DOWN])	{ py += game.getMSpeed(); dir = DOWN; }
		else if (game.key[ALLEGRO_KEY_LEFT])	{ px -= game.getMSpeed(); dir = LEFT; }
		else if (game.key[ALLEGRO_KEY_RIGHT])	{ px += game.getMSpeed(); dir = RIGHT; }
		else { moving = false; }
		/*if (collision(px, py, 100, 100, 16, 16))
		{
			if (game.key[ALLEGRO_KEY_UP]) { y += game.getMSpeed(); dir = UP; }
			else if (game.key[ALLEGRO_KEY_DOWN]) { y -= game.getMSpeed(); dir = DOWN; }
			else if (game.key[ALLEGRO_KEY_LEFT]) { x += game.getMSpeed(); dir = LEFT; }
			else if (game.key[ALLEGRO_KEY_RIGHT]) { x -= game.getMSpeed(); dir = RIGHT; }
		}*/

		if (py <= 0)							{ py += game.getMSpeed(); dir = UP; }
		else if (py > game.getDispH() - 16)		{ py -= game.getMSpeed(); dir = DOWN; }
		else if (px <= 0)						{ px += game.getMSpeed(); dir = LEFT; }
		else if (px > game.getDispW() - 16)		{ px -= game.getMSpeed(); dir = RIGHT; }

		//animacje gracza
		if (moving)
		{
			game.setTimeSinceLastFrameSwap(game.getTimeSinceLastFrameSwap()+game.getDeltaTime()); //+= game.getDeltaTime();
			if (game.getTimeSinceLastFrameSwap() > game.getAnimUpdateTime())
			{
				p_sourceX += al_get_bitmap_width(player) / 4;
				game.setTimeSinceLastFrameSwap(0.0);// = 0.0;
			}
			if (p_sourceX >= al_get_bitmap_width(player))
			{
				p_sourceX = 0;
			}
		}
		else
		{
			p_sourceX = 16;
			game.setTimeSinceLastFrameSwap(0.0);// = 0.0;
		}
	}

	void draw_player()
	{
		al_draw_bitmap_region(player, p_sourceX, dir * al_get_bitmap_height(player) / 4, 16, 16, px, py, 0);
		al_draw_rectangle(px+2, py+12, px + 14, py + 16, al_map_rgb(255, 255, 255), 0);
	}
};

#endif