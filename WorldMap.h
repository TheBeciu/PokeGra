#ifndef WORLDMAP
#define WORLDMAP

#include "Engine.h"
#include <allegro5/allegro.h>
#include <fstream>

ALLEGRO_BITMAP* world_1;

void sprites_init()
{
	world_1 = al_load_bitmap("world_bitmap.png");
}

void sprites_deinit()
{
	al_destroy_bitmap(world_1);
}

bool collision(float& px, float& py, float ex, float ey, float width, float hight)
{
	if (px + width <= ex || px >= ex + width || py + hight <= ey || py >= hight + ey)
	{
		return false;
	}
	return true;
}

class TileMap
{
	const int block_size = 16;
	int loadCounterX = 0;
	int loadCounterY = 0;
	int mapSizeX;
	int mapSizeY;
	int map[30][30];
	const char* mapfile;
	const int offset = 187;
public:
	TileMap(const char* _m) { mapfile = _m; }

	void LoadTileMap()
	{
		std::ifstream openfile(mapfile);
		if (openfile.is_open())
		{
			openfile >> mapSizeX >> mapSizeY;
			while (!openfile.eof())
			{
				openfile >> map[loadCounterX][loadCounterY];
				loadCounterX++;
				if (loadCounterX >= mapSizeX)
				{
					loadCounterX = 0;
					loadCounterY++;
				}
			}
		}
	}
	void DrawTileMap()
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			for (int j = 0; j < mapSizeY; j++)
			{
				switch (map[i][j])
				{
				case 0:
					al_draw_bitmap_region(world_1, 0, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 1:
					al_draw_bitmap_region(world_1, 16, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 2:
					al_draw_bitmap_region(world_1, 32, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 3:
					al_draw_bitmap_region(world_1, 48, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 4:
					al_draw_bitmap_region(world_1, 64, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 5:
					al_draw_bitmap_region(world_1, 80, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 6:
					al_draw_bitmap_region(world_1, 96, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 7:
					al_draw_bitmap_region(world_1, 112, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 8:
					al_draw_bitmap_region(world_1, 128, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 9:
					al_draw_bitmap_region(world_1, 144, 0, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				}
			}
		}
	}
};

class ObjectMap
{
	const int block_size = 16;
	int loadCounterX = 0;
	int loadCounterY = 0;
	int mapSizeX;
	int mapSizeY;
	int map[30][30];
	const char* mapfile;
	const int offset = 187;
public:
	ObjectMap(const char* _m) { mapfile = _m; }
	void LoadObjectMap()
	{
		std::ifstream openfile(mapfile);
		if (openfile.is_open())
		{
			openfile >> mapSizeX >> mapSizeY;
			while (!openfile.eof())
			{
				openfile >> map[loadCounterX][loadCounterY];
				loadCounterX++;
				if (loadCounterX >= mapSizeX)
				{
					loadCounterX = 0;
					loadCounterY++;
				}
			}
		}
	}
	void DrawObjectMap()
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			for (int j = 0; j < mapSizeY; j++)
			{
				switch (map[i][j])
				{
				case 0:
					//al_draw_filled_rectangle(i * block_size, j * block_size, i * block_size + block_size, j * block_size + block_size, al_map_rgb(0, 255, 0));
					break;
				case 1:
					al_draw_bitmap_region(world_1, 16, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 2:
					al_draw_bitmap_region(world_1, 32, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 3:
					al_draw_bitmap_region(world_1, 48, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 4:
					al_draw_bitmap_region(world_1, 64, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 5:
					al_draw_bitmap_region(world_1, 80, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 6:
					al_draw_bitmap_region(world_1, 96, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 7:
					al_draw_bitmap_region(world_1, 112, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 8:
					al_draw_bitmap_region(world_1, 128, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				case 9:
					al_draw_bitmap_region(world_1, 144, 16, 16, 16, i * block_size + offset, j * block_size, 0);
					break;
				}
			}
		}
	}
	/*bool ObjectCollision(int object, float &px, float &py)
	{
		switch (object)
		{
		case 0:
		case 1:
		case 2:
			if(collision(px,py,))
		}
	}*/
};

#endif