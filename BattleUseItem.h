#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"PokemonTrainer.h"
#include"BattleState.h"
#include"Item.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>

#include<algorithm>
#include<utility>


class BattleUseItem : public BattleState {
	Engine& engine;
	ResourceCache& cache;
	PokemonTrainer& trainer;

	BattleState* nextState;

	ALLEGRO_BITMAP* bottomBorder;
	ALLEGRO_BITMAP* wishBitmap;

	ALLEGRO_SAMPLE* wishSample;

	ALLEGRO_FONT* font;

	float elapsedSeconds;


public:
	BattleUseItem(Engine& _engine,  ResourceCache& _cache,  PokemonTrainer& _trainer,
			BattleState* _nextState)
	: engine{_engine}
	, cache{_cache}
	, trainer{_trainer}
		
	, nextState{_nextState}

	, bottomBorder{cache.bitmap("battle/bottomBorder.png")}
	, wishBitmap{cache.bitmap("battle/wish.png")}

	, wishSample{cache.soundSample("battle/wish.mp3")}

	, font{cache.font("battle/pokemon.ttf")}

	, elapsedSeconds{}
	{}


	BattleState* update(PokemonTrainer& player,  PokemonTrainer& enemy) override {
		float x = engine.getDispW() / 2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		player.pokemons.front().battleNameDraw(cache);
		player.pokemons.front().battleStatsDraw(cache);
		player.pokemons.front().battleImgDraw();

		enemy.pokemons.front().battleNameDraw(cache);
		enemy.pokemons.front().battleStatsDraw(cache);
		enemy.pokemons.front().battleImgDraw();

		if (elapsedSeconds == 0.0f) {
			al_play_sample(wishSample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);

			Pokemon& pokemon = trainer.pokemons.front();
			Item const& item = trainer.items.front();

			pokemon.hitPoints += item.hitPoints;
			pokemon.hitPoints = std::min(std::max(pokemon.hitPoints, 0.0f), pokemon.maxHitPoints);

			pokemon.attack += item.attack;
			pokemon.attack = std::min(std::max(pokemon.attack, 0.0f), pokemon.maxAttack);

			pokemon.defence += item.defence;
			pokemon.defence = std::min(std::max(pokemon.defence, 0.0f), pokemon.maxDefence);
		} else if (elapsedSeconds < 3.0f) {
			Pokemon& pokemon = trainer.pokemons.front();
			Item const& item = trainer.items.front();

			x = 40.0f;
			y = engine.getDispH() - 100.0f;
			al_draw_textf(font, al_map_rgb(0, 0, 0), x, y, 0,
				"%s have used %s!", trainer.name.c_str(), item.name.c_str());

			al_draw_bitmap(wishBitmap, pokemon.battleX, pokemon.battleY, 0);
		} else if (4.0f <= elapsedSeconds) {
			std::swap(trainer.items.front(), trainer.items.back());
			trainer.items.pop_back();
			return nextState;
		}

		elapsedSeconds += engine.getDeltaTime();

		return nullptr;
	}
};