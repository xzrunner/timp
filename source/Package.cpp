#include "Package.h"

#include <bimp/ImportStream.h>

#include <assert.h>

namespace timp
{

Package::Package(const std::string& filepath)
	: m_lod_count(1)
{
	LoadIndex(filepath);
}

Package::~Package()
{
}

void Package::SetTexPath(int tex, int lod, const std::string& path)
{
	int idx = tex * m_lod_count + lod;
	assert(idx < m_tex_paths.size());
	m_tex_paths[idx] = path;
}

const std::string& Package::GetTexPath(int tex, int lod) const
{
	int idx = tex * m_lod_count + lod;
	assert(idx < m_tex_paths.size());
	return m_tex_paths[idx];
}

void Package::LoadIndex(const std::string& filepath)
{
	m_textures.clear();
	TextureDescLoader loader(filepath, m_textures, m_lod_count);
	loader.Load();

	m_tex_paths.resize(m_textures.size() * m_lod_count);
}

/************************************************************************/
/* class Package::TextureDescLoader                                     */
/************************************************************************/

Package::TextureDescLoader::TextureDescLoader(const std::string& filepath, 
											  std::vector<TextureDesc>& textures,
											  int& lod_count)
	: bimp::FileLoader(filepath)
	, m_images(textures)
	, m_lod_count(lod_count)
{
}

void Package::TextureDescLoader::OnLoad(bimp::ImportStream& is)
{
	int tex_count = is.UInt16();
	int lod_count = is.UInt16();
	m_lod_count = lod_count;

	m_images.reserve(tex_count);
	for (int i = 0; i < tex_count; ++i)
	{
		TextureDesc img;
		img.w = is.UInt16();
		img.h = is.UInt16();
		img.type = is.UInt16();
		m_images.push_back(img);
	}
}

}