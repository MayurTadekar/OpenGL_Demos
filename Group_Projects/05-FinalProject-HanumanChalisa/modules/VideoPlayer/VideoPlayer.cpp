#include "VideoPlayer.h"
#include <stdio.h>

// ---------------------------------------------------------------------------
// Helper : build absolute path relative to the .exe location
// ---------------------------------------------------------------------------
static void BuildAbsolutePath(const wchar_t* relFileName, wchar_t* outPath, DWORD maxChars)
{
    GetModuleFileNameW(NULL, outPath, maxChars);

    wchar_t* lastSlash = wcsrchr(outPath, L'\\');
    if (lastSlash)
        *(lastSlash + 1) = L'\0';

    wcsncat_s(outPath, maxChars, relFileName, _TRUNCATE);
}

// ---------------------------------------------------------------------------
bool VideoPlayerInit(VideoPlayer& vp, const wchar_t* fileName)
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE)
    {
        fprintf(stderr, "VideoPlayer: CoInitializeEx failed 0x%08X\n", hr);
        return false;
    }

    hr = MFStartup(MF_VERSION);
    if (FAILED(hr))
    {
        fprintf(stderr, "VideoPlayer: MFStartup failed 0x%08X\n", hr);
        CoUninitialize();
        return false;
    }

    wchar_t absPath[MAX_PATH] = {};
    BuildAbsolutePath(fileName, absPath, MAX_PATH);
    fprintf(stderr, "VideoPlayer: opening %ls\n", absPath);

    IMFAttributes* pAttr = nullptr;
    MFCreateAttributes(&pAttr, 1);
    pAttr->SetUINT32(MF_SOURCE_READER_ENABLE_VIDEO_PROCESSING, TRUE);

    hr = MFCreateSourceReaderFromURL(absPath, pAttr, &vp.pReader);
    pAttr->Release();

    if (FAILED(hr))
    {
        fprintf(stderr, "VideoPlayer: MFCreateSourceReaderFromURL failed 0x%08X\n", hr);
        MFShutdown();
        CoUninitialize();
        return false;
    }

    IMFMediaType* pType = nullptr;
    MFCreateMediaType(&pType);
    pType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    pType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32);
    hr = vp.pReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, pType);
    pType->Release();

    if (FAILED(hr))
    {
        fprintf(stderr, "VideoPlayer: SetCurrentMediaType (RGB32) failed 0x%08X\n", hr);
        vp.pReader->Release(); vp.pReader = nullptr;
        MFShutdown();
        CoUninitialize();
        return false;
    }

    IMFMediaType* pCurrent = nullptr;
    vp.pReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM, &pCurrent);

    UINT32 w = 0, h = 0;
    MFGetAttributeSize(pCurrent, MF_MT_FRAME_SIZE, &w, &h);
    vp.width = (int)w;
    vp.height = (int)h;

    UINT32 num = 0, den = 1;
    MFGetAttributeRatio(pCurrent, MF_MT_FRAME_RATE, &num, &den);
    vp.videoFPS = (den > 0 && num > 0) ? (float)num / (float)den : 30.0f;
    vp.frameDuration = 1.0f / vp.videoFPS;
    pCurrent->Release();

    fprintf(stderr, "VideoPlayer: %dx%d @ %.2f fps\n", vp.width, vp.height, vp.videoFPS);

    glGenTextures(1, &vp.textureID);
    glBindTexture(GL_TEXTURE_2D, vp.textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,
                 vp.width, vp.height, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    vp.bEOF = false;
    vp.lastFrameTimestamp = -1LL;

    return true;
}

// ---------------------------------------------------------------------------
void VideoPlayerUpdateTexture(VideoPlayer& vp, float)
{
    if (!vp.pReader || vp.bEOF || vp.textureID == 0)
        return;

    for (int i = 0; i < vp.speedMultiplier; i++)
    {
        DWORD streamIndex = 0;
        DWORD flags = 0;
        LONGLONG timestamp = 0;
        IMFSample* pSample = nullptr;

        HRESULT hr = vp.pReader->ReadSample(
            (DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            0,
            &streamIndex,
            &flags,
            &timestamp,
            &pSample);

        if (FAILED(hr))
        {
            fprintf(stderr, "VideoPlayer: ReadSample failed 0x%08X\n", hr);
            if (pSample) pSample->Release();
            return;
        }

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            if (vp.bLooping)
            {
                PROPVARIANT var;
                PropVariantInit(&var);
                var.vt = VT_I8;
                var.hVal.QuadPart = 0;
                vp.pReader->SetCurrentPosition(GUID_NULL, var);
                PropVariantClear(&var);
                vp.lastFrameTimestamp = -1LL;
            }
            else
            {
                vp.bEOF = true;
            }
            if (pSample) pSample->Release();
            return;
        }

        bool bUpload = (i == vp.speedMultiplier - 1);

        if (pSample)
        {
            if (timestamp <= vp.lastFrameTimestamp)
            {
                pSample->Release();
                continue;
            }
            vp.lastFrameTimestamp = timestamp;

            if (bUpload)
            {
                IMFMediaBuffer* pBuf = nullptr;
                hr = pSample->ConvertToContiguousBuffer(&pBuf);
                if (SUCCEEDED(hr) && pBuf)
                {
                    BYTE* pData = nullptr;
                    DWORD maxLen = 0;
                    DWORD curLen = 0;
                    hr = pBuf->Lock(&pData, &maxLen, &curLen);
                    if (SUCCEEDED(hr) && pData)
                    {
                        glBindTexture(GL_TEXTURE_2D, vp.textureID);
                        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
                        glPixelStorei(GL_UNPACK_ROW_LENGTH, vp.width);

                        int stride = vp.width * 4;
                        for (int row = 0; row < vp.height; row++)
                        {
                            BYTE* srcRow = pData + (vp.height - 1 - row) * stride;
                            glTexSubImage2D(GL_TEXTURE_2D, 0,
                                            0, row,
                                            vp.width, 1,
                                            GL_BGRA, GL_UNSIGNED_BYTE, srcRow);
                        }

                        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
                        glBindTexture(GL_TEXTURE_2D, 0);

                        pBuf->Unlock();
                    }
                    pBuf->Release();
                }
            }

            pSample->Release(); // always release
        }
    }
}

// ---------------------------------------------------------------------------
void VideoPlayerUninit(VideoPlayer& vp)
{
    if (vp.textureID)
    {
        glDeleteTextures(1, &vp.textureID);
        vp.textureID = 0;
    }

    if (vp.pReader)
    {
        vp.pReader->Release();
        vp.pReader = nullptr;
    }

    MFShutdown();
    CoUninitialize();

    vp.width = 0;
    vp.height = 0;
    vp.bEOF = false;
    vp.lastFrameTimestamp = -1LL;

    fprintf(stderr, "VideoPlayer: uninitialized\n");
}
