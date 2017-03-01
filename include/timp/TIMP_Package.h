#ifndef _TIMP_PACKAGE_H_
#define _TIMP_PACKAGE_H_

#include <CU_Uncopyable.h>
#include <bimp/FileLoader.h>

#include <vector>
#include <string>

#include <stdint.h>

namespace bimp { class ImportStream; }

namespace timp
{

class ImportStream;
class Texture;

class Package : private cu::Uncopyable
{
public:
	Package(const std::string& filepath);
	~Package();

	int GetTexCount() const { return m_textures.size(); }
	int GetLodCount() const { return m_lod_count; }

	void SetTexPath(int tex, int lod, const std::string& path);
	const std::string& GetTexPath(int tex, int lod) const;

public:
	struct TextureDesc
	{
		int w, h;
		int type;
	};

	const std::vector<TextureDesc>& GetAllTextures() const { return m_textures; }

private:
	void LoadIndex(const std::string& filepath);

private:
	class TextureDescLoader : public bimp::FileLoader
	{
	public:
		TextureDescLoader(const std::string& filepath, 
			std::vector<TextureDesc>& images, int& lod_count);

	protected:
		virtual void OnLoad(bimp::ImportStream& is);

	private:
		std::vector<TextureDesc>& m_images;
		int& m_lod_count;

	}; // TextureDescLoader

private:
	std::vector<TextureDesc> m_textures;

	int m_lod_count;
	std::vector<std::string> m_tex_paths;

}; // Package

}

#endif // _TIMP_PACKAGE_H_