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
		Rysuje jeden raz options[firstSelection] i ewentualnie inn� opcj�, kt�ra po niej wyst�puje.
		Funkcja sprawdza po ostatniej opcji tak�e pierwsz�.
		*/

	void drawPlayerPokemon();
		//Rysuje pierwszego pokemona gracza z listy, je�eli istnieje


public:
	Battle(Battle&&) = delete;	//kopiowanie i przenoszenie wy��czone


	explicit Battle(Engine& _engine);


	bool isStarted() const;
		//Zwraca true po wywo�aniu metody start(...)


	void start(std::vector<Pokemon>* _playerPokemons,  std::vector<Potion>* _playerPotions);
		/*
		Rozpoczyna tryb walki. Mo�esz przekaza� nullptr albo puste tablice, aby zasygnalizowa�
		brak pokemon�w lub przedmiot�w
		*/


	void handleKeyboardEvents();

	void draw();
};