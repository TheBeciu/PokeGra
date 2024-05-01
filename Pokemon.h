#pragma once


#include<allegro5/allegro.h>

#include<string>
#include<vector>

#include"PokemonAttack.h"


struct Pokemon {
	std::string name;

	/*
	Tylko odniesienie, kt�re musi by� dost�pne, gdy u�ywamy obiektu tej klasy.
	Ta klasa nie zwalnia pami�ci zajmowanej przez obrazek.
	*/
	ALLEGRO_BITMAP* bitmap;

	float life;		//poziom wytrzyma�o�ci pokemona
	std::vector<PokemonAttack> attacks;
};