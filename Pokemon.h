#pragma once


#include<allegro5/allegro.h>

#include<string>
#include<vector>

#include"PokemonAttack.h"


struct Pokemon {
	std::string name;

	/*
	Tylko odniesienie, które musi byæ dostêpne, gdy u¿ywamy obiektu tej klasy.
	Ta klasa nie zwalnia pamiêci zajmowanej przez obrazek.
	*/
	ALLEGRO_BITMAP* bitmap;

	float life;		//poziom wytrzyma³oœci pokemona
	std::vector<PokemonAttack> attacks;
};