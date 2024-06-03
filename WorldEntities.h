#ifndef WORLDENTITIES
#define WORLDENTITIES
#include <allegro5/allegro.h>
#include "Engine.h"

Engine game;

enum Direction { DOWN, LEFT, RIGHT, UP };
enum ObjectType { PORTAL, POTION};

bool collision(float px, float py, float pw, float ph, float ox, float oy, float ow, float oh)
{
	bool x_overlaps = (px < ox + ow) && (px + pw > ox);
	bool y_overlaps = (py < oy + oh) && (py + ph > oy);
	bool coll = x_overlaps && y_overlaps;
	return coll;
}

//Klasa gracza
class Player
{
private:
	float px;
	float py;
	int dir = DOWN;
	int b_sourceX = 0;
	bool moving = false;
	ALLEGRO_BITMAP* player;
	int temp_item_counter = 0;
public:
	Player(float _px, float _py, ALLEGRO_BITMAP* _player)	{ px = _px * block_size + offset; py = _py * block_size; player = _player; }
	float getX()											{ return px; }
	float getY()											{ return py; }
	int getDIR()											{ return dir; }
	int getTEMP()											{ return temp_item_counter; }
	void setX(float x)										{ px = x; }
	void setY(float y)										{ py = y; }
	void setDIR(int d)										{ dir = d; }
	void setMoving(bool m)									{ moving = m; }
	void addTEMP()											{ temp_item_counter++; }

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

		if (py <= 0)								{ py += game.getMSpeed(); dir = UP; }
		else if (py > game.getDispH() - block_size)	{ py -= game.getMSpeed(); dir = DOWN; }
		else if (px <= 0)							{ px += game.getMSpeed(); dir = LEFT; }
		else if (px > game.getDispW() - block_size)	{ px -= game.getMSpeed(); dir = RIGHT; }

		//animacje gracza
		if (moving)
		{
			game.setTimeSinceLastFrameSwap(game.getTimeSinceLastFrameSwap()+game.getDeltaTime()); //+= game.getDeltaTime();
			if (game.getTimeSinceLastFrameSwap() > game.getAnimUpdateTime())
			{
				b_sourceX += al_get_bitmap_width(player) / 4;
				game.setTimeSinceLastFrameSwap(0.0);// = 0.0;
			}
			if (b_sourceX >= al_get_bitmap_width(player))
			{
				b_sourceX = 0;
			}
		}
		else
		{
			b_sourceX = 16;
			game.setTimeSinceLastFrameSwap(0.0);// = 0.0;
		}
	}

	void draw_player()
	{
		al_draw_bitmap_region(player, b_sourceX, dir * al_get_bitmap_height(player) / 4, block_size, block_size, px, py, 0);
		//al_draw_rectangle(px+2, py+12, px + 14, py + 16, al_map_rgb(255, 255, 255), 0);
	}
	void change_pos(int _x, int _y, int _d)
	{
		px = _x * block_size + offset;
		py = _y * block_size;
		dir = _d;
	}
};

class Enemy
{
	float posx;
	float posy;
	ALLEGRO_BITMAP* sprite;

	int dir;
	int b_sourceX = 0;
	bool moving = true;
	bool on_map = true;
	int movement_type;

	float path1 = 300;
	float path2 = 350;
	float path3 = 290;
	float path4 = 550;

	float s_x;
	float s_y;

	//musze to tak zrobic, bo inaczej animacja przeciwnika jest aktywna podczas poruszania sie gracza;
	float EnemyTimeSinceLastFrameSwap = 0.0;
	float EnemyAnimSpeed = game.getAnimSpeed() / 2;
	float EnemyAnimUpdateTime = 1.0 / EnemyAnimSpeed;
public:
	Enemy(float _posx, float _posy, int _m, int _dir, ALLEGRO_BITMAP* _sprite) { posx = _posx; posy = _posy; movement_type = _m; dir = _dir; sprite = _sprite; s_x = posx; s_y = posy; }
	float getPOSX() { return posx; }
	float getPOSY() { return posy; }
	void setPOSX(float x) { posx = x; }
	void setPOSY(float y) { posy = y; }
	void setONMAP(bool b) { on_map = b; }

	void update_enemy()
	{
		if(on_map)
		{
			if (movement_type == 0)
			{
				moving = false;
			}
			else if (movement_type == 1)
			{
				if (dir == DOWN)
				{
					posy++;
					if (posy == s_y + (block_size * 6))
					{
						dir = UP;
					}
				}
				else if (dir == UP)
				{
					posy--;
					if (posy == s_y)
					{
						dir = DOWN;
					}
				}
			}
			else if (movement_type == 2)
			{
				if (dir == DOWN)
				{
					posy++;
					if (posy == s_y + (block_size * 7))
					{
						dir = RIGHT;
					}
				}
				else if (dir == RIGHT)
				{
					posx++;
					if (posx == s_x + (block_size * 8))
					{
						dir = UP;
					}
				}
				else if (dir == UP)
				{
					posy--;
					if (posy == s_y)
					{
						dir = LEFT;
					}
				}
				else if (dir == LEFT)
				{
					posx--;
					if (posx == s_x)
					{
						dir = DOWN;
					}
				}
			}
			else if (movement_type == 3)
			{
				if (dir == RIGHT)
				{
					posx++;
					if (posx == s_x + (block_size * 8))
					{
						dir = DOWN;
					}
				}
				else if (dir == DOWN)
				{
					posy++;
					if (posy == s_y + (block_size * 7))
					{
						dir = LEFT;
					}
				}
				else if (dir == LEFT)
				{
					posx--;
					if (posx == s_x)
					{
						dir = UP;
					}
				}
				else if (dir == UP)
				{
					posy--;
					if (posy == s_y)
					{
						dir = RIGHT;
					}
				}
			}

			if (moving)
			{
				EnemyTimeSinceLastFrameSwap += game.getDeltaTime();
				if (EnemyTimeSinceLastFrameSwap > EnemyAnimUpdateTime)
				{
					b_sourceX += al_get_bitmap_width(sprite) / 4;
					EnemyTimeSinceLastFrameSwap = 0.0;
				}
				if (b_sourceX >= al_get_bitmap_width(sprite))
				{
					b_sourceX = 0;
				}
			}
			else
			{
				b_sourceX = 16;
				EnemyTimeSinceLastFrameSwap = 0.0;
			}
		}
	}
	void draw_enemy()
	{
		al_draw_bitmap_region(sprite, b_sourceX, dir * al_get_bitmap_height(sprite) / 4, block_size, block_size, posx, posy, 0);
		//al_draw_rectangle(posx + 2, posy + 12, posx + 14, posy + 16, al_map_rgb(255, 255, 255), 0);
	}
	bool isEnemyColliding(Player& p)
	{
		if(on_map)
		{
			if (collision(p.getX() + 2, p.getY() + 12, block_size - 4, block_size - 12, posx + 2, posy + 12, block_size - 4, block_size - 12))
			{
				return true;
			}
		}
	}
	bool isThere()
	{
		return on_map;
		
	}
};
class Object
{
	int tileX;
	int tileY;
	ALLEGRO_BITMAP* texture;
	bool on_map = true;
	int type;
public:
	Object(int _x, int _y, ALLEGRO_BITMAP* _t, int _type) { tileX = _x; tileY = _y; texture = _t; type = _type; }
	void setONMAP(bool b) { on_map = b; }
	bool isThere() { return on_map; }

	void drawObject()
	{
		al_draw_bitmap(texture, tileX * block_size + offset, tileY * block_size, 0);
	}
	int isObjectColliding(Player& p)
	{
		if(on_map)
		{
			if(type == PORTAL)
			{
				if (collision(p.getX() + 2, p.getY() + 12, block_size - 4, block_size - 12, tileX * block_size + offset, tileY * block_size, block_size, block_size))
				{
					return 1;
				}
			}
			else if (type == POTION)
			{
				if (collision(p.getX() + 2, p.getY() + 12, block_size - 4, block_size - 12, tileX * block_size + offset, tileY * block_size, block_size, block_size))
				{
					return 2;
				}
			}
		}
	}
	void changePos(int _x, int _y)
	{
		tileX = _x;
		tileY = _y;
	}
};
#endif