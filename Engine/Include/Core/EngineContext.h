#pragma once

#include "Managers/RandomManager.h"
#include "Managers/SaveManager.h"
#include "Managers/TimeManager.h"
#include "Managers/ClipboardManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/AudioManager.h"
#include "Managers/InputManager.h"

struct EngineContext
{
    RandomManager random;
    TimeManager time;
    SaveManager save;
    ClipboardManager clipboard;
    ResourceManager resources;
    AudioManager audio;
    InputManager input;
};