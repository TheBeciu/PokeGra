#ifndef WORLDMAP
#define WORLDMAP

#include "Engine.h"
#include <allegro5/allegro.h>
#include <fstream>
#include "WorldEntities.h"

ALLEGRO_BITMAP* world_1;
ALLEGRO_BITMAP* world_2;

enum MAP { OVERWORLD, DESERT, CAVE, ENDHALL };

//const int block_size = 16;
//const int offset = 187;		//offset x

void sprites_init()
{
	world_1 = al_load_bitmap("world1_bitmap.png");
	world_2 = al_load_bitmap("world2_bitmap.png");
}

void sprites_deinit()
{
	al_destroy_bitmap(world_1);
	al_destroy_bitmap(world_2);
}

class TileMap
{
	//const int block_size = 16;
	int loadCounterX = 0;
	int loadCounterY = 0;
	int mapSizeX;
	int mapSizeY;
	int map[30][30];
	const char* mapfile;
	//const int offset = 187;
	int playerStartTileX = 3;
	int playerStartTileY = 3;
	int currentMap = -1;
	std::vector<ALLEGRO_BITMAP*> mapList;
public:
	//TileMap(const char* _m, int _x, int _y ) { mapfile = _m; playerStartTileX = _x; playerStartTileY = _y; }

	int getSpawnX() { return playerStartTileX; }
	int getSpawnY() { return playerStartTileY; }

	void LoadListOfMaps()
	{
		mapList.push_back(world_1);
		mapList.push_back(world_2);
	}

	void LoadTileMap(const char* _mapfile)
	{
		std::ifstream openfile(_mapfile);
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
		ALLEGRO_BITMAP* world_texture;
		switch (currentMap)
		{
		case OVERWORLD:
			world_texture = mapList[OVERWORLD];
			break;
		case DESERT:
			world_texture = mapList[DESERT];
			break;
		default:
			std::cout << "blad";
			return;
		}

		for (int i = 0; i < mapSizeX; i++)
		{
			for (int j = 0; j < mapSizeY; j++)
			{
				switch (map[i][j])
				{
				case 0:
					al_draw_bitmap_region(world_texture, 0, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 1:
					al_draw_bitmap_region(world_texture, 16, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 2:
					al_draw_bitmap_region(world_texture, 32, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 3:
					al_draw_bitmap_region(world_texture, 48, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 4:
					al_draw_bitmap_region(world_texture, 64, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 5:
					al_draw_bitmap_region(world_texture, 80, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 6:
					al_draw_bitmap_region(world_texture, 96, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 7:
					al_draw_bitmap_region(world_texture, 112, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 8:
					al_draw_bitmap_region(world_texture, 128, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 9:
					al_draw_bitmap_region(world_texture, 144, 0, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 10:
					al_draw_bitmap_region(world_texture, 0, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 11:
					al_draw_bitmap_region(world_texture, 16, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 12:
					al_draw_bitmap_region(world_texture, 32, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 13:
					al_draw_bitmap_region(world_texture, 48, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 14:
					al_draw_bitmap_region(world_texture, 64, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 15:
					al_draw_bitmap_region(world_texture, 80, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 16:
					al_draw_bitmap_region(world_texture, 96, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 17:
					al_draw_bitmap_region(world_texture, 112, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 18:
					al_draw_bitmap_region(world_texture, 128, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				case 19:
					al_draw_bitmap_region(world_texture, 144, 16, block_size, block_size, i * block_size + offset, j * block_size, 0);
					break;
				}
			}
		}
	}
	int isTileColliding(Player& p)
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			
			for (int j = 0; j < mapSizeY; j++)
			{
				if (map[i][j] > 10)
				{
					if (collision(p.getX()+2, p.getY()+12, block_size - 4, block_size - 12, (i * block_size + offset), (j * block_size), block_size, block_size))
					{
						return 1;
					}
				}
				else if (map[i][j] == 10)
				{
					if (collision(p.getX() + 2, p.getY() + 12, block_size - 4, block_size - 12, (i * block_size + offset), (j * block_size), block_size, block_size))
					{
						map[i][j] = 0;
						return 2;
					}
				}
			}
		}
		return 0;
	}
	void changeMap(int nState)
	{
		//pre-proccess
		switch (currentMap)
		{
		case OVERWORLD:
			std::cout << "\tleaving OVERWORLD\n";
			loadCounterX = 0;
			loadCounterY = 0;
			break;
		case DESERT:
			std::cout << "\tleaving DESERT\n";
			loadCounterX = 0;
			loadCounterY = 0;
			break;
		case CAVE:
			std::cout << "\tleaving ENDHALL\n";
			loadCounterX = 0;
			loadCounterY = 0;
			break;
		case ENDHALL:
			std::cout << "\tleaving ENDHALL\n";
			loadCounterX = 0;
			loadCounterY = 0;
			break;
		}

		currentMap = nState;

		//post-proccess
		switch (currentMap)
		{
		case OVERWORLD:
			std::cout << "\tentering OVERWORLD\n";
			LoadTileMap("test_tile_map_0.txt");
			break;
		case DESERT:
			std::cout << "\tentering DESERT\n";
			LoadTileMap("test_tile_map_1.txt");
			break;
		case CAVE:
			std::cout << "\tentering CAVE\n";
			break;
		case ENDHALL:
			std::cout << "entering ENDHALL\n";
			break;
		}

	}
	int current()
	{
		return currentMap;
	}
};

#endif