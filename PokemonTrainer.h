#pragma once


#include<allegro5/allegro.h>
#include<string>

#include"Pokemon.h"
#include"Item.h"
#include"ResourceCache.h"


struct PokemonTrainer {
	std::string name;

	ALLEGRO_BITMAP* worldImg;
	float worldX;
	float worldY;

	ALLEGRO_BITMAP* battleImg;
	float battleX;
	float battleY;
	float hitPoints;
	
	std::vector<Pokemon> pokemons;

	std::vector<Item> items;


	void wordlImgDraw() const {
		al_draw_bitmap(worldImg, worldX, worldY, 0);
	}


	void battlePokeballsDraw(ResourceCache& cache) const {
		al_draw_bitmap(cache.bitmap("battle/topBorder.png"),  battleX,  battleY - 60.0f,  0);

		for (std::size_t pokeball = 0;  pokeball < pokemons.size();  ++pokeball)
			al_draw_bitmap(cache.bitmap("battle/smallPokeball.png"),
				25.0f * pokeball + battleX,  battleY - 60.0f,  0);
	}


	void battleImgDraw() const {
		al_draw_bitmap(battleImg, battleX, battleY, 0);
	}
};