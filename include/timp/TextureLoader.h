#ifndef _TIMP_TEXTURE_LOADER_H_
#define _TIMP_TEXTURE_LOADER_H_

#include <bimp/FileLoader.h>

namespace bimp { class ImportStream; }

namespace timp
{

class TextureLoader : public bimp::FileLoader
{
public:
	TextureLoader(const std::string& filepath);

	int GetFormat() const { return m_format; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	const void* GetData() const { return m_data; }

protected:
	virtual void OnLoad(bimp::ImportStream& is);

private:
	int m_format;

	int m_width, m_height;

	const void* m_data;

}; // TextureLoader

}

#endif // _TIMP_TEXTURE_LOADER_H_