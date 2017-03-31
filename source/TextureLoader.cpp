#include "TextureLoader.h"
#include "TextureFormat.h"

#include <bimp/BIMP_ImportStream.h>
#include <fault.h>

namespace timp
{

TextureLoader::TextureLoader(const std::string& filepath)
	: bimp::FileLoader(filepath)
	, m_format(0)
	, m_width(0)
	, m_height(0)
	, m_data(NULL)
{
}

TextureLoader::TextureLoader(const char* data, size_t size)
	: bimp::FileLoader(data, size)
	, m_format(0)
	, m_width(0)
	, m_height(0)
	, m_data(NULL)
{	
}

void TextureLoader::OnLoad(bimp::ImportStream& is)
{
	m_format = is.UInt8();
	// 暂时先对pvr这样处理， 之后会调整打包工具
	if(m_format==2) {
		is.UInt8();
		m_format = TEXTURE_PVR4;
	}else if(m_format == 4) {
		m_format = TEXTURE_ETC2;
	}
	
	switch (m_format)
	{
	case TEXTURE_RGBA4: case TEXTURE_RGBA8:
		m_width  = is.UInt16();
		m_height = is.UInt16();
		m_data   = is.Stream();
		break;
	case TEXTURE_PVR4:
		m_width  = is.UInt16();
		m_height = is.UInt16();
		m_data   = is.Stream();
		break;
	case TEXTURE_ETC1:
		break;
	case TEXTURE_ETC2:
		m_width  = is.UInt16();
		m_height = is.UInt16();
		m_data   = is.Stream();
		break;
	default:
		fault("unknown texture format\n");
	}
}

}