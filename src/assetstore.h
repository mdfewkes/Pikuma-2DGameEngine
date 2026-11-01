#pragma once

#include <SDL2/SDL_image.h>

#include <string>
#include <map>

class AssetStore {
public:
	AssetStore();
	~AssetStore();

	void ClearAssets();
	void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
	SDL_Texture* GetTexture(const std::string& assetId);

private:
	std::map<std::string, SDL_Texture*> textures;
	// std::map<std::string, TTF_Font*> fonts;
	// std::map<std::string, SDL_Audio*> sounds;

};