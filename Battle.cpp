#include"Battle.h"

#include<utility>


void Battle::handleDefaultMenuEvents() {
	if (engine.checkKeyDownOnce(ALLEGRO_KEY_RIGHT))
		selection += 1;
	else if (engine.checkKeyDownOnce(ALLEGRO_KEY_LEFT))
		selection -= 1;
	else if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP))
		selection -= 2;
	else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN))
		selection += 2;
	/*
	chcemy resztê z dzielenia wiêksz¹ od zera, wiêc musimy uwglêdniæ, ¿e operator %
	zwraca liczby ujemne (np. -1 % 4 równa siê -1 zamiast 3)
	*/
	selection = (selection < 0)  ?  4 + selection  :  selection % 4;

	if (selection==0 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		menu = Menu::FIGHT;
		//selection = 0;
	} else if (selection==1 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		menu = Menu::BAG;
		selection = 0;
	} else if (selection==2 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		menu = Menu::POKEMON;
		selection = 0;
	} else if (selection==3 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		started = false;
		selection = 0;
	}
}


void Battle::drawDefaultMenu() {
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);

	float const W = (float)engine.getDispW();	//dostêpna szerokoœæ ekranu
	float const H = (float)engine.getDispH();	//dostêpna wysokoœæ ekranu
	float const O_W = 0.10f*W;					//10% ogólnej szerokoœci jako szerokoœæ opcji
	float const O_H = 0.05f*H;					//5% ogólnej wysokosæi jako szerokoœæ opcji
	float const M = 0.01f*W;					//1% ogólnej szerokoœci jako margines

	float tW = al_get_text_width(engine.font, "FIGHT");
	float tH = al_get_font_line_height(engine.font);
	float rectX = M;
	float rectY = H - 3.0f*O_H;
	float textX = rectX + 0.5f*O_W - 0.5f*tW;
	float textY = rectY + 0.5f*O_H - 0.5f*tH;
	ALLEGRO_COLOR color = (menu == Menu::DEFAULT && selection == 0) ? red : white;
	al_draw_textf(engine.font, color, textX, textY, 0, "FIGHT");
	al_draw_rectangle(rectX, rectY, rectX + O_W, rectY + O_H, color, 0);

	tW = al_get_text_width(engine.font, "BAG");
	rectX = 2.0f*M + O_W;
	rectY = H - 3.0f*O_H;
	textX = rectX + 0.5f*O_W - 0.5f*tW;
	textY = rectY + 0.5f*O_H - 0.5f*tH;
	color = (menu == Menu::DEFAULT && selection == 1) ? red : white;
	al_draw_textf(engine.font, color, textX, textY, 0, "BAG");
	al_draw_rectangle(rectX, rectY, rectX + O_W, rectY + O_H, color, 0);

	tW = al_get_text_width(engine.font, "POKEMON");
	rectX = M;
	rectY = H - 2.0f*O_H + M;
	textX = rectX + 0.5f*O_W - 0.5f*tW;
	textY = rectY + 0.5f*O_H - 0.5f*tH;
	color = (menu == Menu::DEFAULT && selection == 2) ? red : white;
	al_draw_textf(engine.font, color, textX, textY, 0, "POKEMON");
	al_draw_rectangle(rectX, rectY, rectX + O_W, rectY + O_H, color, 0);

	tW = al_get_text_width(engine.font, "RUN");
	rectX = 2.0f*M + O_W;
	rectY = H - 2.0f*O_H + M;
	textX = rectX + 0.5f*O_W - 0.5f*tW;
	textY = rectY + 0.5f*O_H - 0.5f*tH;
	color = (menu == Menu::DEFAULT && selection == 3) ? red : white;
	al_draw_textf(engine.font, color, textX, textY, 0, "RUN");
	al_draw_rectangle(rectX, rectY, rectX + O_W, rectY + O_H, color, 0);
}


void Battle::handleBagMenuEvents() {
	//wszystkie przedmioty + back
	int const POTIONS_COUNT = (playerPotions) ? ((int)playerPotions->size() + 1) : 1;

	if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP))
		selection -= 1;
	else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN))
		selection += 1;
	selection = (selection<0) ? POTIONS_COUNT+selection : selection%POTIONS_COUNT;

	if (selection==0 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		menu = Menu::DEFAULT;
		//selection = 0;
	} else if (1<= selection && selection<=POTIONS_COUNT
			&& engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		//przenosimy na koniec i usuwamy (selection-1, bo w tej tablicy nie ma back na pocz¹tku)
		std::swap(playerPotions->at(selection-1), playerPotions->back());
		playerPotions->pop_back();
		
		menu = Menu::DEFAULT;
		selection = 0;
	}
}


void Battle::drawBagMenu() {
	//mo¿na dodaæ do klasy, aby unikn¹æ alokowania pamiêci na opcje
	std::vector<std::string> options{ "BACK" };

	int const POTIONS_COUNT = (playerPotions) ? ((int)playerPotions->size()) : 0;
	for (int i=0; i<POTIONS_COUNT; ++i) {
		Potion const& potion = playerPotions->at(i);
		options.push_back(potion.name + " <" + std::to_string(potion.power) + ">");
	}

	draw2Options(selection, options);
}


void Battle::handlePokemonMenuEvents() {
	//wszystkie pokemony + back
	int const POKEMONS_COUNT = (playerPokemons) ? ((int)playerPokemons->size()+1) : 1;

	if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP))
		selection -= 1;
	else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN))
		selection += 1;
	selection = (selection<0) ? POKEMONS_COUNT+selection : selection%POKEMONS_COUNT;

	if (selection==0 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		menu = Menu::DEFAULT;
		//selection = 0;
	} else if (1<=selection && selection<=POKEMONS_COUNT
			&& engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		/*
		wybieramy pokemona, wiêc przesuwamy go na przód (selection-1, bo w tej tablicy
		nie ma back na pocz¹tku)
		*/
		std::swap(playerPokemons->at(selection-1), playerPokemons->front());
		menu = Menu::DEFAULT;
		selection = 0;
	}
}


void Battle::drawPokemonMenu() {
	//mo¿na dodaæ do klasy, aby unikn¹æ alokowania pamiêci na opcje
	std::vector<std::string> options{ "BACK" };

	int const POKEMONS_COUNT = (playerPokemons) ? ((int)playerPokemons->size()) : 0;
	for (int i=0; i<POKEMONS_COUNT; ++i) {
		Pokemon const& pokemon = playerPokemons->at(i);
		options.push_back(pokemon.name + " <" + std::to_string(pokemon.life) + ">");
	}

	draw2Options(selection, options);
}


void Battle::handleFightMenuEvents() {
	//wszystkie pokemony
	int const POKEMONS_COUNT = (playerPokemons)
		? ((int)playerPokemons->size()) : 0;
	//wszystkie ataki + back
	int const ATTACKS_COUNT = (POKEMONS_COUNT)
		? (int)playerPokemons->front().attacks.size()+1 : 1;

	if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP))
		selection -= 1;
	else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN))
		selection += 1;
	selection = (selection<0) ? ATTACKS_COUNT+selection : selection%ATTACKS_COUNT;

	if (selection==0 && engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		menu = Menu::DEFAULT;
		//selection = 0;
	} else if (1<=selection && selection<=ATTACKS_COUNT
			&& engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
		/*
		wybieramy atak, wiêc przesuwamy go na przód (selection-1, bo w tej tablicy
		nie ma back na pocz¹tku)
		*/
		std::swap(playerPokemons->front().attacks.at(selection-1),
			playerPokemons->front().attacks.front());
		menu = Menu::DEFAULT;
		selection = 0;
	}
}


void Battle::drawFightMenu() {
	//mo¿na dodaæ jako cz³onek klasy, aby unikn¹æ alokowania pamiêci na opcje
	std::vector<std::string> options{ "BACK" };

	if (playerPokemons && playerPokemons->size()) {
		for (PokemonAttack const& attack : playerPokemons->front().attacks)
			options.push_back(attack.name + " <" + std::to_string(attack.power) + ">");
	}

	draw2Options(selection, options);
}


void Battle::draw2Options(int firstSelection, std::vector<std::string> const& options) {
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);

	float const W = (float)engine.getDispW();	//dostêpna szerokoœæ ekranu
	float const H = (float)engine.getDispH();	//dostêpna wysokoœæ ekranu
	float const O_W = 0.30f*W;					//30% ogólnej szerokoœci jako szerokoœæ opcji
	float const O_H = 0.05f*H;					//5% ogólnej wysokosæi jako szerokoœæ opcji
	float const M = 0.01f*W;					//1% ogólnej szerokoœci jako margines

	float tW = al_get_text_width(engine.font, options[firstSelection].c_str());
	float tH = al_get_font_line_height(engine.font);
	float rectX = O_W;
	float rectY = H - 3.0f*O_H;
	float textX = rectX + 0.5f*O_W - 0.5f*tW;
	float textY = rectY + 0.5f*O_H - 0.5f*tH;
	al_draw_textf(engine.font, red, textX, textY, 0, options[firstSelection].c_str());
	al_draw_rectangle(rectX, rectY, rectX + O_W, rectY + O_H, red, 0);

	int const NEXT_SELECTION = (firstSelection + 1) % options.size();
	if (firstSelection != NEXT_SELECTION) {
		tW = al_get_text_width(engine.font, options[NEXT_SELECTION].c_str());
		rectX = O_W;
		rectY = H - 2.0f*O_H + M;
		textX = rectX + 0.5f*O_W - 0.5f*tW;
		textY = rectY + 0.5f*O_H - 0.5f*tH;
		al_draw_textf(engine.font, white, textX, textY, 0, options[NEXT_SELECTION].c_str());
		al_draw_rectangle(rectX, rectY, rectX + O_W, rectY + O_H, white, 0);
	}
}


void Battle::drawPlayerPokemon() {
	ALLEGRO_BITMAP* playerPokemon = (playerPokemons && playerPokemons->size())
		? playerPokemons->front().bitmap : nullptr;
	if (playerPokemon) {
		float const W = (float)engine.getDispW();	//dostêpna szerokoœæ ekranu
		float const H = (float)engine.getDispH();	//dostêpna wysokoœæ ekranu
		al_draw_bitmap(playerPokemon, 0.10f*W, 0.25f*H, 0);
	}
}


Battle::Battle(Engine& _engine)
: playerPokemons{}
, playerPotions{}
, engine{ _engine }
, menu{ Menu::DEFAULT }
, selection{ 0 }
, started{ false }
{}


bool Battle::isStarted() const {
	return started;
}


void Battle::start(std::vector<Pokemon>* _playerPokemons,  std::vector<Potion>* _playerPotions) {
	started = true;
	playerPokemons = _playerPokemons;
	playerPotions = _playerPotions;
}


void Battle::handleKeyboardEvents() {
	switch (menu) {
	case Menu::DEFAULT:
		handleDefaultMenuEvents();
		break;
	case Menu::BAG:
		handleBagMenuEvents();
		break;
	case Menu::POKEMON:
		handlePokemonMenuEvents();
		break;
	case Menu::FIGHT:
		handleFightMenuEvents();
		break;
	default:
		break;
	}
}


void Battle::draw() {
	switch (menu) {
	case Menu::BAG:
		drawBagMenu();
		break;
	case Menu::POKEMON:
		drawPokemonMenu();
		break;
	case Menu::FIGHT:
		drawFightMenu();
		break;
	default:
		break;
	}

	drawPlayerPokemon();
	drawDefaultMenu();
}