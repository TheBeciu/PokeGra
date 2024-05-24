#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"
#include"BattleShowEnemies.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleStarting : public BattleState {
	Engine& engine;
	ResourceCache& cache;

	ALLEGRO_BITMAP* largePokeball1;
	ALLEGRO_BITMAP* largePokeball2;
	ALLEGRO_BITMAP* largePokeball;

	ALLEGRO_SAMPLE_INSTANCE* battleStartInstance;
	
	float elapsedSeconds;


public:
	BattleStarting(Engine& _engine,  ResourceCache& _cache)
	: engine{_engine}
	, cache{_cache}

	, largePokeball1{cache.bitmap("battle/largePokeball1.png")}
	, largePokeball2{cache.bitmap("battle/largePokeball2.png")}
	, largePokeball{ largePokeball1 }

	, battleStartInstance{cache.soundSampleInstance("battle/battleStart.mp3")}

	, elapsedSeconds{}	//0.0f
	{
		al_play_sample_instance(battleStartInstance);
	}


	//nie potrzebujemy, wiêc u¿ywamy implementacjê z klasy bazowej
	//BattleState* handleInput(Engine& engine, PokemonTrainer& player,
	//		PokemonTrainer& enemy) override {
	//	return nullptr;
	//}


	BattleState* update(PokemonTrainer& player, PokemonTrainer& enemy) override {
		elapsedSeconds += engine.getDeltaTime();

		float const x = engine.getDispW()/2.0f - 230.0f;
		float const y = engine.getDispH()/2.0f - 230.0f;

		if (0.1f <= elapsedSeconds) {
			elapsedSeconds = 0.0f;
			largePokeball = (largePokeball==largePokeball1) ? largePokeball2 : largePokeball1;
		}
		
		al_draw_bitmap(largePokeball, x, y, 0);

		//mo¿na usun¹æ alokacjê pamiêci, je¿eli wydajnoœæ jest niesatysfakcjonuj¹ca
		if (!al_get_sample_instance_playing(battleStartInstance))
			return new BattleShowEnemies{engine, cache};

		return nullptr;
	}
};