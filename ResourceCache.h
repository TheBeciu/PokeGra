#pragma once


#include<allegro5/allegro.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_ttf.h>

#include<unordered_map>
#include<string>
#include<utility>
#include<stdexcept>


class ResourceCache {
private:
	std::unordered_map<std::string, ALLEGRO_BITMAP*> bitmaps;
	std::unordered_map<std::string, ALLEGRO_SAMPLE*> soundSamples;
	std::unordered_map<std::string, ALLEGRO_SAMPLE_INSTANCE*> soundSampleInstances;
	std::unordered_map<std::string, ALLEGRO_FONT*> fonts;


public:
	~ResourceCache() noexcept {
		for (auto& entry : bitmaps)
			al_destroy_bitmap(entry.second);

		for (auto& entry : soundSampleInstances) {
			al_stop_sample_instance(entry.second);
			al_detach_sample_instance(entry.second);
			al_destroy_sample_instance(entry.second);
		}

		for (auto& entry : soundSamples)
			al_destroy_sample(entry.second);

		for (auto& entry : fonts)
			al_destroy_font(entry.second);
	}


	ResourceCache() = default;


	//przenoszenie wy³¹cza kopiowanie


	ResourceCache(ResourceCache&& other) noexcept
	: bitmaps{std::move(other.bitmaps)}
	, soundSamples{std::move(other.soundSamples)}
	, soundSampleInstances{std::move(other.soundSampleInstances)}
	, fonts{std::move(other.fonts)}
	{}


	ResourceCache& operator=(ResourceCache&& other) noexcept {
		std::swap(bitmaps, other.bitmaps);
		std::swap(soundSamples, other.soundSamples);
		std::swap(soundSampleInstances, other.soundSampleInstances);
		std::swap(fonts, other.fonts);
		return *this;
	}


	ALLEGRO_BITMAP* bitmap(std::string const& filePath) {
		auto it = bitmaps.find(filePath);
		
		if (bitmaps.end() == it) {
			ALLEGRO_BITMAP* newBitmap = al_load_bitmap(filePath.c_str());

			if (nullptr == newBitmap)
				throw std::runtime_error{"ERROR: " + filePath + " not found"};

			bitmaps[filePath] = newBitmap;
			return newBitmap;
		}

		return it->second;
	}


	void removeBitmap(std::string const& filePath) {
		auto it = bitmaps.find(filePath);
		if (bitmaps.end() != it) {
			al_destroy_bitmap(it->second);
			bitmaps.erase(it);
		}
	}


	ALLEGRO_SAMPLE* soundSample(std::string const& filePath) {
		auto it = soundSamples.find(filePath);

		if (soundSamples.end() == it) {
			ALLEGRO_SAMPLE* newSample = al_load_sample(filePath.c_str());

			if (nullptr == newSample)
				throw std::runtime_error{ "ERROR: " + filePath + " not found" };

			soundSamples[filePath] = newSample;
			return newSample;
		}

		return it->second;
	}


	void removeSoundSample(std::string const& filePath) {
		auto sampleInstances = soundSampleInstances.find(filePath);
		if (soundSampleInstances.end() != sampleInstances) {
			al_stop_sample_instance(sampleInstances->second);
			al_detach_sample_instance(sampleInstances->second);
			al_destroy_sample_instance(sampleInstances->second);
			soundSampleInstances.erase(sampleInstances);
		}

		auto sample = soundSamples.find(filePath);
		if (soundSamples.end() != sample) {
			al_destroy_sample(sample->second);
			soundSamples.erase(sample);
		}
	}


	ALLEGRO_SAMPLE_INSTANCE* soundSampleInstance(std::string const& filePath) {
		auto it = soundSampleInstances.find(filePath);

		if (soundSampleInstances.end() == it) {
			ALLEGRO_SAMPLE_INSTANCE* newInstance = al_create_sample_instance(
				soundSample(filePath.c_str()));

			al_attach_sample_instance_to_mixer(newInstance, al_get_default_mixer());
			soundSampleInstances[filePath] = newInstance;
			return newInstance;
		}

		return it->second;
	}


	void removeSoundSampleInstance(std::string const& filePath) {
		auto sampleInstances = soundSampleInstances.find(filePath);
		if (soundSampleInstances.end() != sampleInstances) {
			al_stop_sample_instance(sampleInstances->second);
			al_detach_sample_instance(sampleInstances->second);
			al_destroy_sample_instance(sampleInstances->second);
			soundSampleInstances.erase(sampleInstances);
		}
	}


	ALLEGRO_FONT* font(std::string const& filePath) {
		auto it = fonts.find(filePath);

		if (fonts.end() == it) {
			ALLEGRO_FONT* newFont = al_load_ttf_font(filePath.c_str(), 15, 0);

			if (nullptr == newFont)
				throw std::runtime_error{"ERROR: " + filePath + " not found"};

			fonts[filePath] = newFont;
			return newFont;
		}

		return it->second;
	}


	void removeFont(std::string const& filePath) {
		auto it = fonts.find(filePath);
		if (fonts.end() != it) {
			al_destroy_font(it->second);
			fonts.erase(it);
		}
	}
};