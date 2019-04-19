#include "MiniginPCH.h"
#include "TextureManager.h"
#include <SDL.h>
#include <memory>
#include "Texture2D.h"
int dae::TextureMananager::AddTexture(Texture2D * tex)
{
	if (m_AmountOfTextures++ == 0)
		m_Textures = std::vector<Texture2D *>(); 

	m_Textures.push_back(tex);
	return (int)m_Textures.size();
	//return 0; 
}
