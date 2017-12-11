#ifndef _TIMP_TEXTURE_LOADER_H_
#define _TIMP_TEXTURE_LOADER_H_

#include <bimp/FileLoader.h>

namespace bimp { class ImportStream; }

namespace timp
{

class TextureLoader : public bimp::FileLoader
{
public:
	TextureLoader(const CU_STR& filepath);
	TextureLoader(const char* data, size_t size);
	TextureLoader(fs_file* file, uint32_t offset);

	int GetFormat() const { return m_format; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	const void* GetData() const { return m_data; }

protected:
	virtual void OnLoad(bimp::ImportStream& is) override;

private:
	int m_format;

	int m_width, m_height;

	const void* m_data;

}; // TextureLoader

}

#endif // _TIMP_TEXTURE_LOADER_H_