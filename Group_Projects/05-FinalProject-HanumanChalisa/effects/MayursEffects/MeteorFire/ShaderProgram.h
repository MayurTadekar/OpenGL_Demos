/***************************************************************************
 * S.G.M.P
 * @file: ShaderProgram.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Thursday 2025-06-19 2:39:49 AM
 ***************************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include "../Common/Shader.h"
#include "../Common/Program.h"
#include "../Common/macros.h"
#include "IObject.h"

class IShaderProgram
{
public:
	virtual void Draw(IObject *object, vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix) = 0;
};
