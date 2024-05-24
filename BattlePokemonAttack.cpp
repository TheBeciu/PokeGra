#pragma once


#include"BattlePokemonAttack.h"
#include"BattleUseItem.h"
#include"BattlePlayerMove.h"
#include"BattlePokemonDead.h"

#include<cmath>
#include<algorithm>


BattlePokemonAttack::BattlePokemonAttack(Engine& _engine,  ResourceCache& _cache,
	bool _enemyAttack)
: engine{_engine}
, cache{_cache}

, bottomBorder{cache.bitmap("battle/bottomBorder.png")}

, font{cache.font("battle/pokemon.ttf")}

, elapsedSeconds{0}

, enemyAttack{_enemyAttack}
, healing{false}
{}


BattleState* BattlePokemonAttack::update(PokemonTrainer& _player,  PokemonTrainer& _enemy) {
	float x = engine.getDispW() / 2.0f - 420.0f;
	float y = engine.getDispH() - 170.0f;
	al_draw_bitmap(bottomBorder, x, y, 0);

	//enemy jest traktowany jako atakuj¹cy
	PokemonTrainer& enemy = (enemyAttack) ? _enemy : _player;
	PokemonTrainer& player = (enemyAttack) ? _player : _enemy;
	Pokemon& enemyPokemon = enemy.pokemons.front();
	Pokemon& playerPokemon = player.pokemons.front();

	if (elapsedSeconds == 0.0f) {
		if (&enemy==&_enemy && enemyPokemon.hitPoints <= 40.0f && enemy.items.size()) {
			BattlePlayerMove* nextState = new BattlePlayerMove(engine, cache);
			return new BattleUseItem(engine, cache, enemy, nextState);
		}

		attackId = (enemyAttack) ? (std::rand() % enemyPokemon.attacks.size()) : 0;
		PokemonAttack const& attack = enemyPokemon.attacks[attackId];
		attack.battleSamplePlay();

		float const ENEMY_POKEMON_ATTACK = fmodf(
			(float)std::rand(), enemyPokemon.attack ? enemyPokemon.attack : 1);
		float const PLAYER_POKEMON_DEFENCE = fmodf(
			(float)std::rand(), playerPokemon.defence ? enemyPokemon.defence : 1);

		float const STRENGTH = ENEMY_POKEMON_ATTACK / std::max(1.0f, PLAYER_POKEMON_DEFENCE);

		float damage = fabsf(attack.hitPoints ? attack.hitPoints : 1);
		damage = (attack.hitPoints < 0 ? -1 : 1) * STRENGTH * fmodf((float)std::rand(), damage);
		healing = 0.0f < attack.hitPoints;
		if (healing) {
			enemyPokemon.hitPoints = std::max(
				0.0f,
				std::min(enemyPokemon.hitPoints + damage,  enemyPokemon.maxHitPoints));
		} else {
			playerPokemon.hitPoints = std::max(
				0.0f, 
				std::min(playerPokemon.hitPoints + damage,  playerPokemon.maxHitPoints));
		}

		damage = fabsf(attack.attack ? attack.attack : 1);
		damage = -1.0f * STRENGTH * fmodf((float)std::rand(), damage);
		playerPokemon.attack = std::max(
			playerPokemon.maxAttack * 0.5f,
			std::min(playerPokemon.attack + damage, playerPokemon.maxAttack));

		damage = fabsf(attack.defence ? attack.defence : 1);
		damage = -1.0f * STRENGTH * fmodf((float)std::rand(), damage);
		playerPokemon.defence = std::max(
			playerPokemon.maxDefence * 0.5f,
			std::min(playerPokemon.defence + damage, playerPokemon.maxDefence));
	}

	Pokemon& targetPokemon = healing ? enemyPokemon : playerPokemon;
	Pokemon& otherPokemon = healing ? playerPokemon : enemyPokemon;

	otherPokemon.battleNameDraw(cache);
	otherPokemon.battleStatsDraw(cache);
	otherPokemon.battleImgDraw();

	bool targetVisible = true;
	if (elapsedSeconds < 0.1f)
		targetVisible = false;
	else if (elapsedSeconds < 0.2f)
		targetVisible = true;
	else if (elapsedSeconds < 0.3f)
		targetVisible = false;
	else if (elapsedSeconds < 0.4f)
		targetVisible = true;

	if (targetVisible) {
		targetPokemon.battleNameDraw(cache);
		targetPokemon.battleStatsDraw(cache);
		targetPokemon.battleImgDraw();
	}

	if (elapsedSeconds < 1.5f) {
		enemyPokemon.attacks[attackId].battleX = targetPokemon.battleX;
		enemyPokemon.attacks[attackId].battleY = targetPokemon.battleY;
		enemyPokemon.attacks[attackId].battleImgDraw();
	}

	x = 40.0f;
	y = engine.getDispH() - 100.0f;
	al_draw_textf(font, al_map_rgb(0, 0, 0), x, y, 0, "%s have used %s!",
		enemyPokemon.name.c_str(), enemyPokemon.attacks[attackId].name.c_str());

	if (3.0f <= elapsedSeconds) {
		if (playerPokemon.hitPoints <= 0.0f)
			return new BattlePokemonDead(engine, cache, !enemyAttack);
		else if (enemyAttack)
			return new BattlePlayerMove(engine, cache);
		else
			return new BattlePokemonAttack(engine, cache, true);
	}

	elapsedSeconds += engine.getDeltaTime();

	return nullptr;
}