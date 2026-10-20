
#include <Windows.h>
#include <wincodec.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include "macros.h"
#include "common.h"
#include <fstream>
#include <cstring>

namespace TextureLoader
{
	int LoadGLTexture(GLuint *texture, TCHAR imageResource[])
	{

		/* VARIABLE DECLARATION */
		HBITMAP hBitmap;
		BITMAP bmp;
		BOOL bResult = FALSE;

		/* CODE */
		hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResource, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

		if (hBitmap)
		{
			bResult = TRUE;

			GetObject(hBitmap, sizeof(bmp), &bmp);

			glGenTextures(1, texture);

			glBindTexture(GL_TEXTURE_2D, *texture);
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				// gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.bmWidth, bmp.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
				
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			DeleteObject(hBitmap);
			hBitmap = NULL;
		}
		return (bResult);
	}

	// Load texture from file (supports JPG, PNG, BMP via WIC)
	bool LoadTextureFromFile(const char* filepath, GLuint* texture)
	{
		if (!filepath || !texture)
		{
			LOG_ERROR("log.txt", "LoadTextureFromFile: Invalid parameters (filepath or texture is null)");
			return false;
		}

		CoInitialize(NULL);

		// Check if file exists
		std::ifstream file(filepath, std::ios::binary);
		if (!file.is_open())
		{
			char logMsg[256];
			sprintf_s(logMsg, sizeof(logMsg), "LoadTextureFromFile: File not found - %s", filepath);
			LOG_ERROR("log.txt", logMsg);
			return false;
		}
		file.close();

		// Convert char* to LPCWSTR for Windows APIs
		int len = MultiByteToWideChar(CP_UTF8, 0, filepath, -1, NULL, 0);
		wchar_t* wcFilepath = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, filepath, -1, wcFilepath, len);

		// Use Windows Imaging Component (WIC) to load image
		IWICImagingFactory* pFactory = NULL;
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrame = NULL;
		IWICFormatConverter* pConverter = NULL;
		IWICBitmap* pBitmap = NULL;

		HRESULT hr = S_OK;
		int imageWidth = 0;
		int imageHeight = 0;
		unsigned char* imageData = NULL;

		// Create WIC factory
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pFactory);
		
		if (SUCCEEDED(hr))
		{
			// Create decoder
			hr = pFactory->CreateDecoderFromFilename(
				wcFilepath,
				NULL,
				GENERIC_READ,
				WICDecodeMetadataCacheOnLoad,
				&pDecoder);
		}

		if (SUCCEEDED(hr))
		{
			// Get first frame
			hr = pDecoder->GetFrame(0, &pFrame);
		}

		if (SUCCEEDED(hr))
		{
			// Get image dimensions
			hr = pFrame->GetSize((UINT*)&imageWidth, (UINT*)&imageHeight);
		}

		if (SUCCEEDED(hr))
		{
			// Create format converter for RGB
			hr = pFactory->CreateFormatConverter(&pConverter);
		}

		if (SUCCEEDED(hr))
		{
			// Convert to 24-bit RGB
			hr = pConverter->Initialize(
				pFrame,
				GUID_WICPixelFormat24bppBGR,
				WICBitmapDitherTypeNone,
				NULL,
				0.0,
				WICBitmapPaletteTypeCustom);
		}

		if (SUCCEEDED(hr))
		{
			// Allocate image buffer
			imageData = new unsigned char[imageWidth * imageHeight * 3];

			// Copy pixels
			hr = pConverter->CopyPixels(
				NULL,
				imageWidth * 3,
				imageWidth * imageHeight * 3,
				imageData);
		}

		// Create OpenGL texture if loading was successful
		if (SUCCEEDED(hr) && imageData)
		{
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imageData);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			char logMsg[256];
			sprintf_s(logMsg, sizeof(logMsg), "LoadTextureFromFile: Successfully loaded %dx%d texture from %s", imageWidth, imageHeight, filepath);
			LOG_ENTRY("log.txt", logMsg);
		}
		else
		{
			char logMsg[512];
			sprintf_s(logMsg, sizeof(logMsg), "LoadTextureFromFile: Failed to load texture from %s (HRESULT: 0x%08X)", filepath, hr);
			LOG_ERROR("log.txt", logMsg);
		}

		// Cleanup
		if (imageData) delete[] imageData;
		if (pConverter) pConverter->Release();
		if (pBitmap) pBitmap->Release();
		if (pFrame) pFrame->Release();
		if (pDecoder) pDecoder->Release();
		if (pFactory) pFactory->Release();
		if (wcFilepath) delete[] wcFilepath;

		CoUninitialize();

		return SUCCEEDED(hr) && imageData != NULL;
	}

} // namespace TextureLoader
