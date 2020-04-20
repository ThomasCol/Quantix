//Main for FMod tests

#include <stdio.h>

#include <fmod.hpp>
#include <fmod_errors.h>

void InitFMod()
{
    FMOD_RESULT result;
    FMOD::System* system = NULL;

    result = FMOD::System_Create(&system);      // Create the main system object.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return;
    }

    result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return;
    }

    FMOD::Sound* backgroundHandler{ nullptr };
    result = system->createSound("Media/Sounds/BackgroundTest.wav", FMOD_DEFAULT, nullptr, &backgroundHandler);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return;
    }

    result = system->playSound(backgroundHandler, nullptr, false, nullptr);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return;
    }
}

int main()
{
	InitFMod();

	return 0;
}