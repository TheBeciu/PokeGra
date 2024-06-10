#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"
#include"BattlePokemonAttack.h"
#include"BattlePlayerPokemon.h"
#include"BattleUseItem.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>

#include<string>
#include<vector>
#include<utility>


class BattlePlayerMove : public BattleState {
	Engine& engine;
	ResourceCache& cache;

	ALLEGRO_BITMAP* bottomBorder;

	ALLEGRO_FONT* font;

	char const* mainOptions[4];
	int selectedOption;
	int currentOption;


public:
	BattlePlayerMove(Engine& _engine,  ResourceCache& _cache)
	: engine{_engine}
	, cache{_cache}

	, bottomBorder{cache.bitmap("battle/bottomBorder.png")}

	, font{cache.font("battle/pokemon.ttf")}

	, mainOptions{"FIGHT", "POKEMON", "BAG", "RUN"}
	, selectedOption{-1}
	, currentOption{0}
	{}


	BattleState* handleInput(PokemonTrainer& player,  PokemonTrainer& enemy) override {
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
					cache.removeSoundSample("battle/battle.mp3");
					enemy.hitPoints = 0.0f;
					return BattleState::battleEscape();
				}
				selectedOption = currentOption;
				currentOption = 0;
			}
		} else if (selectedOption == 0) {
			std::size_t const SIZE = player.pokemons.front().attacks.size()+1;	//attacks + cancel
			if (engine.checkKeyDownOnce(ALLEGRO_KEY_LEFT))
				currentOption = (SIZE + currentOption - 1) % SIZE;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_RIGHT))
				currentOption = (currentOption + 1) % SIZE;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_UP))
				currentOption = (SIZE + currentOption - 2) % SIZE;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_DOWN))
				currentOption = (currentOption + 2) % SIZE;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
				if (-1 < currentOption  &&  currentOption < SIZE - 1) {
					std::swap(player.pokemons.front().attacks.front(),
						player.pokemons.front().attacks[currentOption]);
					return new BattlePokemonAttack(engine, cache, false);
				}
				selectedOption = -1;
				currentOption = 0;
			}
		} else if (selectedOption == 1) {
			std::size_t const SIZE = player.pokemons.size()+1;	//pokemons + cancel
			if (engine.checkKeyDownOnce(ALLEGRO_KEY_LEFT) && 0<currentOption)
				--currentOption;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_RIGHT) && currentOption<SIZE-1)
				++currentOption;
			else  if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
				if (0 < currentOption  &&  currentOption < SIZE-1) {
					std::swap(player.pokemons.front(), player.pokemons[currentOption]);
					return new BattlePlayerPokemon(engine, cache,
						new BattlePokemonAttack(engine, cache, true));
				}
				selectedOption = -1;
				currentOption = 0;
			}
		} else if (selectedOption == 2) {
			std::size_t const SIZE = player.items.size() + 1;	//items + cancel
			if (engine.checkKeyDownOnce(ALLEGRO_KEY_LEFT) && 0<currentOption)
				--currentOption;
			else if (engine.checkKeyDownOnce(ALLEGRO_KEY_RIGHT) && currentOption<SIZE-1)
				++currentOption;
			else  if (engine.checkKeyDownOnce(ALLEGRO_KEY_ENTER)) {
				if (currentOption == SIZE-1) {
					selectedOption = -1;
					currentOption = 0;
				} else {
					//std::swap(player.items.front(), player.items[currentOption]);
					BattlePokemonAttack* nextState = new BattlePokemonAttack(engine, cache, true);
					return new BattleUseItem(engine, cache, player, nextState);
				}
			}
		}
		else if (selectedOption == 3) {
			engine.changeState(engine.state, 4);
			return BattleState::battleEscape();
		}

		return nullptr;
	}


	BattleState* update(PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW()/2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		if (selectedOption == -1)
			drawMainOptions();
		else if (selectedOption == 0)
			drawAttacksOptions(player);
		else if (selectedOption == 1)
			drawPokemonsOptions(player);
		else if (selectedOption == 2)
			drawBagOptions(player);

		player.pokemons.front().battleNameDraw(cache);
		player.pokemons.front().battleStatsDraw(cache);
		player.pokemons.front().battleImgDraw();

		enemy.pokemons.front().battleNameDraw(cache);
		enemy.pokemons.front().battleStatsDraw(cache);
		enemy.pokemons.front().battleImgDraw();

		return nullptr;
	}


private:
	void drawMainOptions() {
		int optionId = 0;
		for (float y=60.0f; y<130.0f; y+=50.0f)
		for (float x=60.0f; x<190.0f; x+=120.0f) {
			al_draw_textf(font, al_map_rgb(0, 0, 0), x, engine.getDispH()-180+y, 0,
				"%s%s", (currentOption==optionId) ? ">" : " ", mainOptions[optionId++]);
		}
	}


	void drawBagOptions(PokemonTrainer& player) {
		std::vector<Item> const& options = player.items;
		int optionId = 0;
		float x = 60.0f;
		for (;  x<310.0f && optionId<options.size();  x+=120.0f) {
			al_draw_textf(font, al_map_rgb(0, 0, 0), x, engine.getDispH()-100, 0,
				"%s%s", (currentOption==optionId) ? ">" : " ", options[optionId++].name.c_str());
		}
		al_draw_textf(font, al_map_rgb(0, 0, 0), x, engine.getDispH() - 100, 0,
			"%sCancel", (currentOption == optionId) ? ">" : " ");
	}


	void drawPokemonsOptions(PokemonTrainer& player) {
		std::vector<Pokemon>& options = player.pokemons;
		int optionId = 0;
		float x = 60.0f;
		for (; x < 550.0f && optionId < options.size(); x += 250.0f) {
			al_draw_textf(font, al_map_rgb(0, 0, 0), x, engine.getDispH() - 100, 0,
				"%s%s (%d)", (currentOption == optionId) ? ">" : " ",
				options[optionId].name.c_str(),
				(int)options[optionId].hitPoints);
			++optionId;
		}
		al_draw_textf(font, al_map_rgb(0, 0, 0), x, engine.getDispH() - 100, 0,
			"%sCancel", (currentOption == optionId) ? ">" : " ");
	}


	void drawAttacksOptions(PokemonTrainer& player) {
		std::vector<PokemonAttack>& options = player.pokemons.front().attacks;
		int optionId = 0;
		for (float y = 60.0f; y < 130.0f; y += 50.0f)
		for (float x = 60.0f; x < 250.0f; x += 180.0f) {
			al_draw_textf(font, al_map_rgb(0, 0, 0), x, engine.getDispH() - 180 + y, 0,
				"%s%s", (currentOption == optionId) ? ">" : " ", options[optionId++].name.c_str());
		}
		al_draw_textf(font, al_map_rgb(0, 0, 0), 450.0f, engine.getDispH() - 70, 0,
			"%sCancel", (currentOption == optionId) ? ">" : " ");
	}
};