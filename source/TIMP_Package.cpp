#include "TIMP_Package.h"

#include <bimp/BIMP_ImportStream.h>

#include <assert.h>

namespace timp
{

Package::Package(const std::string& filepath)
	: m_lod_count(1)
{
	LoadIndex(filepath);
}

Package::Package(fs_file* file, uint32_t offset)
	: m_lod_count(1)
{
	LoadIndex(file, offset);
}

Package::~Package()
{
}

void Package::SetTexPath(int tex, int lod, const bimp::FilePath& path)
{
	int idx = tex * m_lod_count + lod;
	assert(static_cast<size_t>(idx) < m_tex_paths.size());
	m_tex_paths[idx] = path;
}

const bimp::FilePath& Package::GetTexPath(int tex, int lod) const
{
	int idx = tex * m_lod_count + lod;
	assert(static_cast<size_t>(idx) < m_tex_paths.size());
	return m_tex_paths[idx];
}

const Package::TextureDesc& Package::GetTexDesc(int tex) const
{
	assert(tex >= 0 && static_cast<size_t>(tex) < m_textures.size());
	return m_textures[tex];
}

void Package::LoadIndex(const std::string& filepath)
{
	m_textures.clear();
	TextureDescLoader loader(filepath.c_str(), m_textures, m_lod_count);
	loader.Load();

	m_tex_paths.resize(m_textures.size() * m_lod_count);
}

void Package::LoadIndex(fs_file* file, uint32_t offset)
{
	m_textures.clear();
	TextureDescLoader loader(file, offset, m_textures, m_lod_count);
	loader.Load();

	m_tex_paths.resize(m_textures.size() * m_lod_count);
}

/************************************************************************/
/* class Package::TextureDescLoader                                     */
/************************************************************************/

Package::TextureDescLoader::TextureDescLoader(const bimp::ResString& filepath,
											  mm::AllocVector<TextureDesc>& textures,
											  int& lod_count)
	: bimp::FileLoader(filepath)
	, m_images(textures)
	, m_lod_count(lod_count)
{
}

Package::TextureDescLoader::TextureDescLoader(fs_file* file, uint32_t offset, 
											  mm::AllocVector<TextureDesc>& textures, 
											  int& lod_count)
	: bimp::FileLoader(file, offset)
	, m_images(textures)
	, m_lod_count(lod_count)
{
}

void Package::TextureDescLoader::OnLoad(bimp::ImportStream& is)
{
	int tex_count = is.UInt16();
	int lod_count = is.UInt16();
	m_lod_count = lod_count;
	// no lod
	m_lod_count = 1;

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