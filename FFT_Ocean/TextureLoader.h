/***************************************************************************
 * S.G.M.P
 * @file: TextureLoader.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Thursday 2025-06-19 11:40:41 AM
 ***************************************************************************/

#ifndef _TEXTURE_LOADER_H
#define _TEXTURE_LOADER_H

namespace TextureLoader
{
	int LoadGLTexture(GLuint *texture, TCHAR imageResource[]);
	bool LoadTextureFromFile(const char* filepath, GLuint* texture);
};

#endif /* _TEXTURE_LOADER_H */
