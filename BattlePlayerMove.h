#pragma once


#include"BattleState.h"
#include"BattlePlayerAttack.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>

#include<string>
#include<vector>


class BattlePlayerMove : public BattleState {
	ALLEGRO_BITMAP* bottomBorder;
	ALLEGRO_BITMAP* topBorder;

	ALLEGRO_SAMPLE* battle;
	ALLEGRO_SAMPLE_INSTANCE* battleInstance;

	char const* mainOptions[4];
	int selectedOption;
	int currentOption;


public:
	~BattlePlayerMove() noexcept override {
		al_destroy_bitmap(topBorder);
		al_destroy_bitmap(bottomBorder);
	}


	BattlePlayerMove(ALLEGRO_SAMPLE* _battle,  ALLEGRO_SAMPLE_INSTANCE* _battleInstance)
	: bottomBorder{al_load_bitmap("battle/bottomBorder.png")}
	, topBorder{al_load_bitmap("battle/topBorder.png")}
	, battle{_battle}
	, battleInstance{_battleInstance}
	, mainOptions{"FIGHT", "POKEMON", "BAG", "RUN"}
	, selectedOption{-1}
	, currentOption{0}
	{}


	BattleState* handleInput(Engine& engine,  PokemonTrainer& player,
			PokemonTrainer& enemy) override {

		if (selectedOption==-1) {
			if (engine.checkKeyDownOnce(ALLEGRO_KEY_LEFT))
				currentOption = (4+currentOption-1) % 4;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_RIGHT))
				currentOption = (currentOption+1) % 4;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP))
				currentOption = (4 + currentOption - 2) % 4;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN))
				currentOption = (currentOption + 2) % 4;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
				if (currentOption == 3) {
					al_stop_sample_instance(battleInstance);
					al_detach_sample_instance(battleInstance);
					al_destroy_sample_instance(battleInstance);
					al_destroy_sample(battle);
					enemy.hitPoints = 0.0f;
					return BattleState::battleEnd();
				}
				selectedOption = currentOption;
				currentOption = 0;
			}
		} else if (selectedOption == 0) {
			std::size_t const SIZE = player.pokemons.front().attacks.size()+1;	//attacks + cancel

			if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP) && 0<currentOption)
				--currentOption;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN) && currentOption<SIZE-1)
				++currentOption;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER) && currentOption==0) {
				selectedOption = -1;
				currentOption = 0;
			} else if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER))
				return new BattlePlayerAttack(player.pokemons.front().attacks[currentOption-1],
					battle, battleInstance);
		} else if (selectedOption == 1) {
			std::size_t const SIZE = player.pokemons.size()+1;	//pokemons + cancel

			if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP) && 0<currentOption)
				--currentOption;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN) && currentOption<SIZE-1)
				++currentOption;
			else  if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
				selectedOption = -1;
				currentOption = 0;
			}
		} else if (selectedOption == 2) {
			std::size_t const SIZE = 1;	//cancel

			if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP) && 0<currentOption)
				--currentOption;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN) && currentOption<SIZE-1)
				++currentOption;
			else  if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
				selectedOption = -1;
				currentOption = 0;
			}
		}

		return nullptr;
	}


	BattleState* update(Engine& engine, PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW()/2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		if (selectedOption == -1)
			drawMainOptions(engine);
		else if (selectedOption == 0) {
			std::vector<std::string> options{"Cancel"};
			for (PokemonAttack const& attack : player.pokemons.front().attacks)
				options.emplace_back(attack.name);
			drawOptions(engine, options);
		} else if (selectedOption == 1) {
			std::vector<std::string> options{"Cancel"};
			for (Pokemon const& pokemon : player.pokemons)
				options.emplace_back(
					pokemon.name + " (HP: " + std::to_string(pokemon.hitPoints) + ")");
			drawOptions(engine, options);
		} else if (selectedOption == 2) {
			std::vector<std::string> options{"Cancel"};
			drawOptions(engine, options);
		}

		x = player.pokemons.front().battleX;
		y = player.pokemons.front().battleY;
		al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), 50.0f+x, y-60.0f, 0,
			"%s", player.pokemons.front().name.c_str());
		al_draw_filled_rectangle(50.0f+x, y-45.0f,
			50.0f+x+player.pokemons.front().hitPoints,  y-40.0f,  al_map_rgb(0, 255, 0));
		al_draw_bitmap(topBorder, x, y-60.0f, 0);
		player.pokemons.front().battleImgDraw();

		x = enemy.pokemons.front().battleX;
		y = enemy.pokemons.front().battleY;
		al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), 50.0f+x, y-60.0f, 0,
			"%s", enemy.pokemons.front().name.c_str());
		al_draw_filled_rectangle(50.0f+x, y-45.0f, 50.0f+x+enemy.pokemons.front().hitPoints, y-40.0f,
			al_map_rgb(0, 255, 0));
		al_draw_bitmap(topBorder, x, y-60.0f, 0);
		enemy.pokemons.front().battleImgDraw();

		return nullptr;
	}


private:
	void drawMainOptions(Engine& engine) {
		int optionId = 0;
		for (float y=60.0f; y<130.0f; y+=60.0f)
		for (float x=60.0f; x<130.0f; x+=60.0f) {
			al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), x, engine.getDispH()-170+y, 0,
				"%s%s", (currentOption==optionId) ? ">" : " ", mainOptions[optionId++]);
		}
	}


	void drawOptions(Engine& engine,  std::vector<std::string> const& options) {
		int optionId = currentOption;
		for (float y=60.0f;  y<130.0f && optionId<options.size();  y+=60.0f) {
			al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), 60.0f, engine.getDispH()-170+y, 0,
				"%s%s", (currentOption==optionId) ? ">" : " ", options[optionId++].c_str());
		}
	}
};