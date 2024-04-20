#ifndef WORLDMAP
#define WORLDMAP

#include "Engine.h"
#include <allegro5/allegro.h>
#include <fstream>
#include "WorldEntities.h"

ALLEGRO_BITMAP* world_1;

void sprites_init()
{
	world_1 = al_load_bitmap("world_bitmap.png");
}

void sprites_deinit()
{
	al_destroy_bitmap(world_1);
}

bool collision(float px, float py, float pw, float ph, float ox, float oy, float ow, float oh)
{
	bool x_overlaps = (px < ox + ow) && (px + pw > ox);
	bool y_overlaps = (py < oy + oh) && (py + ph > oy);
	bool coll = x_overlaps && y_overlaps;
	return coll;
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
					al_draw_bitmap_region(world_1, 0, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 1:
					al_draw_bitmap_region(world_1, 16, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 2:
					al_draw_bitmap_region(world_1, 32, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 3:
					al_draw_bitmap_region(world_1, 48, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 4:
					al_draw_bitmap_region(world_1, 64, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 5:
					al_draw_bitmap_region(world_1, 80, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 6:
					al_draw_bitmap_region(world_1, 96, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 7:
					al_draw_bitmap_region(world_1, 112, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 8:
					al_draw_bitmap_region(world_1, 128, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 9:
					al_draw_bitmap_region(world_1, 144, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 10:
					al_draw_bitmap_region(world_1, 0, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 11:
					al_draw_bitmap_region(world_1, 16, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 12:
					al_draw_bitmap_region(world_1, 32, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 13:
					al_draw_bitmap_region(world_1, 48, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 14:
					al_draw_bitmap_region(world_1, 64, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 15:
					al_draw_bitmap_region(world_1, 80, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 16:
					al_draw_bitmap_region(world_1, 96, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 17:
					al_draw_bitmap_region(world_1, 112, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 18:
					al_draw_bitmap_region(world_1, 128, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 19:
					al_draw_bitmap_region(world_1, 144, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				}
			}
		}
	}
	bool isColliding(Player& p)
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			
			for (int j = 0; j < mapSizeY; j++)
			{
				if (map[i][j] > 10)
				{
					if (collision(p.getX()+2, p.getY()+12, block_size - 4, block_size - 12, (i * block_size + offset), (j * block_size), block_size, block_size))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};

#endif