#pragma once


#include<allegro5/allegro.h>

#include<string>
#include<vector>

#include"PokemonAttack.h"


class Pokemon {
	ALLEGRO_BITMAP* battleImg;


public:
	std::vector<PokemonAttack> attacks;
	std::string name;
	float battleX;
	float battleY;
	float hitPoints;


	~Pokemon() noexcept {
		al_destroy_bitmap(battleImg);
	}


	Pokemon(std::string const& _name, float _hitPoints, char const* _battleImgPath)
		: battleImg(al_load_bitmap(_battleImgPath))
		, battleX{}
		, battleY{}
		, hitPoints{ _hitPoints }
		, name{ _name }
	{}


	//przenoszenie wy³¹cza kopiowanie


	Pokemon(Pokemon&& other) noexcept
		: battleImg{ std::exchange(other.battleImg, nullptr) }
		, battleX{ other.battleX }
		, battleY{ other.battleY }
		, hitPoints{ other.hitPoints }
		, name{ std::move(other.name) }
	{}


	Pokemon& operator=(Pokemon&& other) noexcept {
		std::swap(battleImg, other.battleImg);
		std::swap(battleX, other.battleX);
		std::swap(battleY, other.battleY);
		std::swap(hitPoints, other.hitPoints);
		std::swap(name, other.name);
		return *this;
	}


	void battleImgDraw() const {
		al_draw_bitmap(battleImg, battleX, battleY, 0);
	}
};