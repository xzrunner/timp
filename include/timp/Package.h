#ifndef _TIMP_PACKAGE_H_
#define _TIMP_PACKAGE_H_

#include <cu/uncopyable.h>
#include <cu/cu_stl.h>
#include <bimp/FileLoader.h>
#include <bimp/FilePath.h>

#include <vector>

#include <stdint.h>

namespace bimp { class ImportStream; }

namespace timp
{

class ImportStream;
class Texture;

class Package : private cu::Uncopyable
{
public:
	Package(const CU_STR& filepath);
	Package(fs_file* file, uint32_t offset);
	~Package();

	int GetTexCount() const { return m_textures.size(); }
	int GetLodCount() const { return m_lod_count; }

	void SetTexPath(int tex, int lod, const bimp::FilePath& path);
	const bimp::FilePath& GetTexPath(int tex, int lod) const;

public:
	struct TextureDesc
	{
		int w, h;
		int type;
	};

	const CU_VEC<TextureDesc>& GetAllTextures() const { return m_textures; }
	const TextureDesc& GetTexDesc(int tex) const;

private:
	void LoadIndex(const CU_STR& filepath);
	void LoadIndex(fs_file* file, uint32_t offset);

private:
	class TextureDescLoader : public bimp::FileLoader
	{
	public:
		TextureDescLoader(const std::string& filepath,
			CU_VEC<TextureDesc>& images, int& lod_count);
		TextureDescLoader(fs_file* file, uint32_t offset, 
			CU_VEC<TextureDesc>& images, int& lod_count);

	protected:
		virtual void OnLoad(bimp::ImportStream& is);

	private:
		CU_VEC<TextureDesc>& m_images;
		int& m_lod_count;

	}; // TextureDescLoader

private:
	CU_VEC<TextureDesc> m_textures;

	int m_lod_count;
	CU_VEC<bimp::FilePath> m_tex_paths;

}; // Package

using PackagePtr = std::unique_ptr<Package, mm::alloc_deleter<mm::Allocator<Package>>>;

}

#endif // _TIMP_PACKAGE_H_