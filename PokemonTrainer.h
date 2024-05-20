#pragma once


#include<allegro5/allegro.h>
#include<utility>
#include<string>

#include"Pokemon.h"


class PokemonTrainer {
	ALLEGRO_BITMAP* worldImg;
	ALLEGRO_BITMAP* battleImg;


public:
	float worldX;
	float worldY;
	float battleX;
	float battleY;
	float hitPoints;
	std::string name;
	std::vector<Pokemon> pokemons;


	~PokemonTrainer() noexcept {
		al_destroy_bitmap(battleImg); //nic nie robi, gdy argument to nullptr
		al_destroy_bitmap(worldImg);
	}


	PokemonTrainer(std::string const& _name,  float _worldX,  float _worldY,
		float _hitPoints,  char const* _worldImgPath, char const* _battleImgPath)
	: worldImg(al_load_bitmap(_worldImgPath))
	, battleImg(al_load_bitmap(_battleImgPath))
	, worldX{_worldX}
	, worldY{_worldY}
	, battleX{}
	, battleY{}
	, hitPoints{_hitPoints}
	, name{_name}
	{}


	//przenoszenie wy³¹cza kopiowanie


	PokemonTrainer(PokemonTrainer&& other) noexcept
	: worldImg{std::exchange(other.worldImg, nullptr)}
	, battleImg{std::exchange(other.battleImg, nullptr)}
	, worldX{other.worldX}
	, worldY{other.worldY}
	, battleX{other.battleX}
	, battleY{other.battleY}
	, hitPoints{other.hitPoints}
	, name{std::move(other.name)}
	, pokemons{std::move(other.pokemons)}
	{}


	PokemonTrainer& operator=(PokemonTrainer&& other) noexcept {
		std::swap(worldImg, other.worldImg);
		std::swap(battleImg, other.battleImg);
		std::swap(worldX, other.worldX);
		std::swap(worldY, other.worldY);
		std::swap(battleX, other.battleX);
		std::swap(battleY, other.battleY);
		std::swap(hitPoints, other.hitPoints);
		std::swap(name, other.name);
		std::swap(pokemons, other.pokemons);
		return *this;
	}


	void wordlImgDraw() const {
		al_draw_bitmap(worldImg, worldX, worldY, 0);
	}


	void battleImgDraw() const {
		al_draw_bitmap(battleImg, battleX, battleY, 0);
	}
};