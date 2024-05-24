#pragma once


#include<allegro5/allegro.h>

#include<string>
#include<vector>

#include"PokemonAttack.h"
#include"ResourceCache.h"


struct Pokemon {
	std::string name;

	ALLEGRO_BITMAP* battleImg;
	float battleX, battleY;
	float maxHitPoints, hitPoints;
	float maxAttack, attack;
	float maxDefence, defence;

	std::vector<PokemonAttack> attacks;


	void battleNameDraw(ResourceCache& cache) const {
		al_draw_textf(cache.font("battle/pokemon.ttf"),  al_map_rgb(0, 0, 0),
			30.0f + battleX,  battleY - 85.0f, 0,  "%s",  name.c_str());
	}


	void battleStatsDraw(ResourceCache& cache) const {
		al_draw_bitmap(cache.bitmap("battle/topBorder.png"),  battleX,  battleY - 60.0f,  0);

		al_draw_filled_rectangle(27.0f + battleX,  battleY - 58.0f,
			33.0f + battleX + 100.0f * 1.45f,  battleY - 27.0f,
			al_map_rgb(0, 0, 0));

		al_draw_filled_rectangle(30.0f + battleX,  battleY - 55.0f,
			30.0f + battleX + hitPoints * 1.45f,  battleY - 50.0f,
			al_map_rgb(0, 255, 0));
		al_draw_filled_rectangle(30.0f + battleX,  battleY - 45.0f,
			30.0f + battleX + attack * 1.45f,  battleY - 40.0f,
			al_map_rgb(255, 0, 0));
		al_draw_filled_rectangle(30.0f + battleX,  battleY - 35.0f,
			30.0f + battleX + defence * 1.45f,  battleY - 30.0f,
			al_map_rgb(0, 0, 255));
	}


	void battleImgDraw() const {
		al_draw_bitmap(battleImg, battleX, battleY, 0);
	}
};