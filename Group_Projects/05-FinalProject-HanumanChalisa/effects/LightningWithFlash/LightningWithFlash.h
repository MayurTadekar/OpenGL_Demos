#pragma once
#include "../../include/common.h"

void initializeLightningWithFlash();
void updateLightningWithFlash(float deltaTime);
void renderLightningWithFlash(float currentTime, float triggerTime);
void uninitializeLightningWithFlash();