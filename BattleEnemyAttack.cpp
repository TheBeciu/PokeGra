#pragma once


#include"BattleEnemyAttack.h"
#include"BattlePlayerMove.h"

#include<cmath>
#include<algorithm>


BattleEnemyAttack::~BattleEnemyAttack() noexcept {
	al_destroy_sample(scratch);
	al_destroy_bitmap(topBorder);
	al_destroy_bitmap(bottomBorder);
}


BattleEnemyAttack::BattleEnemyAttack(ALLEGRO_SAMPLE* _battle,
	ALLEGRO_SAMPLE_INSTANCE* _battleInstance)
: bottomBorder{al_load_bitmap("battle/bottomBorder.png")}
, topBorder{al_load_bitmap("battle/topBorder.png")}
, battle{_battle}
, battleInstance{_battleInstance}
, scratch{al_load_sample("battle/scratch.mp3")}
, elapsedSeconds{0}
{}


BattleState* BattleEnemyAttack::update(Engine& engine, PokemonTrainer& player, PokemonTrainer& enemy) {
	bool playerVisible = true;

	if (elapsedSeconds == 0.0f) {
		al_play_sample(scratch, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
		attackId = std::rand() % enemy.pokemons.front().attacks.size();
		damage = fmodf((float)std::rand(), enemy.pokemons.front().attacks[attackId].power);
		player.pokemons.front().hitPoints -= damage;
		player.pokemons.front().hitPoints = std::max(0.0f, player.pokemons.front().hitPoints);
	} else if (elapsedSeconds < 0.1f)
		playerVisible = false;
	else if (elapsedSeconds < 0.2f)
		playerVisible = true;
	else if (elapsedSeconds < 0.3f)
		playerVisible = false;
	else if (elapsedSeconds < 0.4f)
		playerVisible = true;
	else if (5.0f < elapsedSeconds) {
		if (player.pokemons.front().hitPoints <= 0.0f) {
			enemy.hitPoints = 0.0f;
			al_stop_sample_instance(battleInstance);
			al_detach_sample_instance(battleInstance);
			al_destroy_sample_instance(battleInstance);
			al_destroy_sample(battle);
			return BattleState::battleEnd();
		} else 
			return new BattlePlayerMove(battle, battleInstance);
	}
	elapsedSeconds += engine.getDeltaTime();
		
		
	float x = engine.getDispW()/2.0f - 420.0f;
	float y = engine.getDispH() - 170.0f;
	al_draw_bitmap(bottomBorder, x, y, 0);

	x = 40.0f;
	y = engine.getDispH() - 100.0f;
	al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), x, y, 0,
		"%s used %s (damage: %.0f)!", enemy.pokemons.front().name.c_str(),
		enemy.pokemons.front().attacks[attackId].name.c_str(), damage);

	if (playerVisible) {
		x = player.pokemons.front().battleX;
		y = player.pokemons.front().battleY;
		al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), 50.0f+x, y-60.0f, 0,
			"%s", player.pokemons.front().name.c_str());
		al_draw_filled_rectangle(50.0f+x, y-45.0f,
			50.0f+x+player.pokemons.front().hitPoints,  y-40.0f,  al_map_rgb(0, 255, 0));
		al_draw_bitmap(topBorder, x, y-60.0f, 0);
		player.pokemons.front().battleImgDraw();
	}

	x = enemy.pokemons.front().battleX;
	y = enemy.pokemons.front().battleY;
	al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), 50.0f+x, y-60.0f, 0,
		"%s", enemy.pokemons.front().name.c_str());
	al_draw_filled_rectangle(50.0f+x, y-45.0f, 50.0f+x+enemy.pokemons.front().hitPoints,
		y-40.0f,  al_map_rgb(0, 255, 0));
	al_draw_bitmap(topBorder, x, y-60.0f, 0);
	enemy.pokemons.front().battleImgDraw();

	return nullptr;
}