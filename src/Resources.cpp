#include "Resources.h"


void Resources::Resources::Reset() {
	for (auto& [key, val] : this->m_Resources.Textures) {
		UnloadTexture(val);
	}
	this->m_Resources.Textures.clear();

	for (auto& [key, val] : this->m_Resources.Audio) {
		UnloadSound(val);
	}
	this->m_Resources.Audio.clear();

	this->m_Resources.Fonts.clear();
	this->m_Resources.YAMLs.clear();
}

void Resources::Resources::Load(std::string resPack) {
	this->Reset();

	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("./Resources/" + resPack)) {
		if (!dirEntry.is_regular_file()) {
			continue;
		}
		std::string FileExtension = StrToLower(dirEntry.path().extension().generic_string());
		std::string FileName = StrToLower(dirEntry.path().filename().generic_string());
		if (FileExtension == ".png") {
			this->m_Resources.Textures[FileName] = LoadTexture(dirEntry.path().generic_string().c_str());
		}
		if (FileExtension == ".ogg") {
			this->m_Resources.Audio[FileName] = LoadSound(dirEntry.path().generic_string().c_str());
		}
		if (FileExtension == ".ttf") {
			this->m_Resources.Fonts[FileName] = dirEntry.path().generic_string();
		}
		if (FileExtension == ".yml") {
			this->m_Resources.YAMLs[FileName] = dirEntry.path().generic_string();
		}
	}

	this->m_RecentlyLoaded = true;
}

Resources::ResourcePack Resources::Resources::Get() {
	return this->m_Resources;
}

bool Resources::Resources::ShouldReload() {
	return this->m_RecentlyLoaded;
}

void Resources::Resources::Set_bRecentlyLoaded_to_False() {
	this->m_RecentlyLoaded = false;
}
