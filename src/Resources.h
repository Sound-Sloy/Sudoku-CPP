#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <imgui.h>
#include "Utils.h"


namespace Resources {
	
	struct ResourcePack {
		std::unordered_map<std::string, Texture2D> Textures;
		std::unordered_map<std::string, Sound> Audio;
		std::unordered_map<std::string, std::string> YAMLs;
		std::unordered_map<std::string, std::string> Fonts;
	};


	class Resources {
	private:
		ResourcePack m_Resources;
		bool m_RecentlyLoaded = false;
	public:
		void Reset();
		void Load(std::string texturepack);
		ResourcePack Get();
		///?? Should I do it this way??
		bool ShouldReload();
		void Set_bRecentlyLoaded_to_False();
	};

}


