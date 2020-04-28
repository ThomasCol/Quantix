#ifndef __SOUND_H__
#define __SOUND_H__

#include <fmod.hpp>
#include "Type.h"
#include "Core\DLLHeader.h"

namespace Quantix::Resources
{
	class QUANTIX_API Sound
	{
		private:

			#pragma region Attributes
			
			FMOD::Sound* _clip	{ nullptr };

			#pragma endregion

			#pragma region Methods

			/**
			 * @brief method that sort the type of the sound got by FMod
			 *
			 * @return QXstring type of sound value
			 */
			QXstring SortType(FMOD_SOUND_TYPE type);

			#pragma endregion

		public:

			#pragma region Constructors & Destructor

			/**
			 * @brief Construct a new Sound object
			 *
			 */
			Sound(const char* path);

			/**
			 * @brief Construct a new Sound object by copy
			 *
			 * @param copy Sound
			 */
			Sound(const Sound& copy) noexcept;

			/**
			 * @brief Construct a new Sound object by move
			 *
			 * @param copy Sound
			 */
			Sound(Sound&& copy) noexcept;

			/**
			 * @brief Destroy the Sound object
			 *
			 */
			~Sound();

			#pragma endregion

			#pragma region Methods

			#pragma region Accessors

			/**
			 * @brief Get Sound clip
			 *
			 * @return const FMOD::Sound* clip value
			 */
			FMOD::Sound*	GetClip();

			/**
			 * @brief Get Sound name
			 *
			 * @return QXstring name value
			 */
			QXstring		GetName();

			/**
			 * @brief Get Sound type
			 *
			 * @return QXstring type value
			 */
			QXstring		GetType();

			//const unsigned int& GetSize();

			/**
			 * @brief Get Sound time length
			 *
			 * @return QXuint time length value
			 */
			const QXuint	GetTimeLength();

			#pragma endregion

			/**
			 * @brief Play Sound's clip
			 *
			 * @return bool played value
			 */
			bool	Play();

			#pragma endregion
	};
}

#endif //__Sound_H__