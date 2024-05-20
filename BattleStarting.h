#pragma once


#include"BattleState.h"
#include"BattleFaceToFace.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleStarting : public BattleState {
	ALLEGRO_BITMAP* largePokeball1;
	ALLEGRO_BITMAP* largePokeball2;
	ALLEGRO_BITMAP* largePokeball;

	ALLEGRO_SAMPLE* battleStart;
	ALLEGRO_SAMPLE_INSTANCE* battleStartInstance;
	ALLEGRO_SAMPLE* battle;
	ALLEGRO_SAMPLE_INSTANCE* battleInstance;
	
	float elapsedSeconds;


public:
	~BattleStarting() noexcept override {
		al_stop_sample_instance(battleStartInstance);
		al_detach_sample_instance(battleStartInstance);
		al_destroy_sample_instance(battleStartInstance);
		al_destroy_sample(battleStart);

		al_destroy_bitmap(largePokeball2);
		al_destroy_bitmap(largePokeball1);
	}

	
	BattleStarting()
	: largePokeball1{al_load_bitmap("battle/largePokeball1.png")}
	, largePokeball2{al_load_bitmap("battle/largePokeball2.png")}
	, largePokeball{largePokeball1}

	, battleStart{al_load_sample("battle/battleStart.mp3")}
	, battleStartInstance{al_create_sample_instance(battleStart)}
	//poni¿szy dŸwiêk u¿ywamy w nastêpnym stanie, ale ³adujemy tutaj, aby by³ gotowy do odtworzenia
	, battle{al_load_sample("battle/battle.mp3")}
	, battleInstance{al_create_sample_instance(battle)}

	, elapsedSeconds{0.0f}
	{
		al_attach_sample_instance_to_mixer(battleStartInstance, al_get_default_mixer());
		al_play_sample_instance(battleStartInstance);
	}


	//nie potrzebujemy, wiêc u¿ywamy implementacjê z klasy bazowej
	//BattleState* handleInput(Engine& engine, PokemonTrainer& player,
	//		PokemonTrainer& enemy) override {
	//	return nullptr;
	//}


	BattleState* update(Engine& engine,  PokemonTrainer& player,  PokemonTrainer& enemy) override {
		elapsedSeconds += engine.getDeltaTime();

		float const x = engine.getDispW()/2.0f - 230.0f;
		float const y = engine.getDispH()/2.0f - 230.0f;

		if (0.1f <= elapsedSeconds) {
			elapsedSeconds = 0.0f;
			largePokeball = (largePokeball==largePokeball1) ? largePokeball2 : largePokeball1;
		}
		
		al_draw_bitmap(largePokeball, x, y, 0);

		//mo¿na usun¹æ alokacjê pamiêci, je¿eli wydajnoœæ jest niesatysfakcjonuj¹ca
		if (!al_get_sample_instance_playing(battleStartInstance)) {
			return new BattleFaceToFace{engine,  battle, battleInstance};
		}

		return nullptr;
	}
};