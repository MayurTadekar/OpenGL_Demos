/***************************************************************************
 * S.G.M.P
 * @file: IObject.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: Wednesday 2025-06-18 6:00:39 PM
 ***************************************************************************/

#pragma once

#include <GL/GL.h>
#include "./../../../include/vmath.h"

class IObject
{
public:
	virtual void Draw(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix) = 0;
};
