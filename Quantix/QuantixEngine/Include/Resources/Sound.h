#ifndef __SOUND_H__
#define __SOUND_H__

#include <fmod.hpp>

#include "rttrEnabled.h"
#include "Type.h"
#include "Core\DLLHeader.h"

namespace Quantix::Resources
{
	enum class QUANTIX_API ESoundMode
	{
		QX_2D = FMOD_2D,
		QX_3D = FMOD_3D,
	};

	class QUANTIX_API Sound
	{
		private:

			#pragma region Attributes
			
			FMOD::Sound*	_clip	{ nullptr };
			FMOD::Channel* _channel	{ nullptr };

			QXstring		_path;

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
			 * @param path path of the sound
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
			 * @brief Get Sound's clip
			 *
			 * @return const FMOD::Sound* clip value
			 */
			FMOD::Sound*	GetClip();

			/**
			 * @brief Get Sound's name
			 *
			 * @return QXstring name value
			 */
			QXstring		GetName();

			/**
			 * @brief Get Sound's type
			 *
			 * @return QXstring type value
			 */
			QXstring		GetType();

			//const unsigned int& GetSize();

			/**
			 * @brief Get Sound's time length
			 *
			 * @return QXuint time length value
			 */
			const QXuint	GetTimeLength();

			/**
			 * @brief Get Sound's volume
			 *
			 * @return QXfloat volume value
			 */
			const QXfloat	GetVolume();

			inline FMOD::Channel*	GetChannel() { return _channel; }

			inline QXstring			GetPath() { return _path; }

			/**
			 * @brief Set Sound's volume
			 *
			 * @param QXfloat volume value
			 */
			void			SetVolume(QXfloat newVolume);

			#pragma endregion

			/**
			 * @brief Play Sound's clip
			 *
			 * @return QXbool played successfully value
			 */
			const QXbool	Play();

			/**
			 * @brief Play Sound's clip
			 *
			 * @param channel to manage the clip
			 * @return QXbool played successfully value
			 */
			const QXbool	Play(FMOD::ChannelGroup* channel);

			/**
			 * @brief Pause Sound's clip
			 *
			 * @param channel to manage the clip
			 * @return QXbool pause successfully value
			 */
			const QXbool	Pause(FMOD::ChannelGroup* channel);

			/**
			 * @brief Check if the sound is in 3D
			 *
			 * @return QXbool is in 3D value
			 */
			const QXbool	Is3D();

			/**
			 * @brief Change the mode of the sound
			 *
			 * @param mode the sound will have
			 * @return QXbool changed successfully value
			 */
			const QXbool	ChangeMode(FMOD_MODE mode);

			#pragma endregion
			CLASS_REGISTRATION();
	};
}

#endif //__Sound_H__