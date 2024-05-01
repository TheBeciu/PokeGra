#pragma once


#include<vector>
#include<string>

#include"Engine.h"
#include"Pokemon.h"
#include"Potion.h"


class Battle {
	enum class Menu {
		DEFAULT,
		FIGHT,
		BAG,
		POKEMON,
		RUN
	};


	std::vector<Pokemon>* playerPokemons;
	std::vector<Potion>* playerPotions;
	Engine& engine;

	Menu menu;
	int selection;

	bool started;


	void handleDefaultMenuEvents();
	void drawDefaultMenu();


	void handleBagMenuEvents();
	void drawBagMenu();


	void handlePokemonMenuEvents();
	void drawPokemonMenu();


	void handleFightMenuEvents();
	void drawFightMenu();


	void draw2Options(int firstSelection,  std::vector<std::string> const& options);
		/*
		Rysuje jeden raz options[firstSelection] i ewentualnie inn¹ opcjê, która po niej wystêpuje.
		Funkcja sprawdza po ostatniej opcji tak¿e pierwsz¹.
		*/

	void drawPlayerPokemon();
		//Rysuje pierwszego pokemona gracza z listy, je¿eli istnieje


public:
	Battle(Battle&&) = delete;	//kopiowanie i przenoszenie wy³¹czone


	explicit Battle(Engine& _engine);


	bool isStarted() const;
		//Zwraca true po wywo³aniu metody start(...)


	void start(std::vector<Pokemon>* _playerPokemons,  std::vector<Potion>* _playerPotions);
		/*
		Rozpoczyna tryb walki. Mo¿esz przekazaæ nullptr albo puste tablice, aby zasygnalizowaæ
		brak pokemonów lub przedmiotów
		*/


	void handleKeyboardEvents();

	void draw();
};