#pragma once


#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>

#include<string>


struct PokemonAttack {
	std::string name;

	float hitPoints;
	float attack;
	float defence;

	float battleX, battleY;
	ALLEGRO_BITMAP* battleImg;
	ALLEGRO_SAMPLE* battleSample;


	void battleImgDraw() const {
		al_draw_bitmap(battleImg, battleX, battleY, 0);
	}


	void battleSamplePlay() const {
		al_play_sample(battleSample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
	}
};