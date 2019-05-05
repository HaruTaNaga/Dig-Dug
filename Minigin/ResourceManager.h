#pragma once


namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final 
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
		Texture2D * LoadTexturePtr(const std::string & file); 
	};

}
