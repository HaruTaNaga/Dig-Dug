#pragma once
#include "Texture2D.h"
#include <vector>
#include <memory>
#include <SDL.h>

class Texture2D; 
namespace dae {
	class TextureMananager {
	public: 
		TextureMananager() {};
		~TextureMananager() { for (auto i : m_Textures) delete i; };
		Texture2D * GetTexture(int id) { return m_Textures[id]; }
		int AddTexture(Texture2D * texture); 
		std::vector<Texture2D *> m_Textures; 
		int m_AmountOfTextures = 0; 

	};
}