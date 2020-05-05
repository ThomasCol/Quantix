#ifndef __SOUNDEMITTER_H__
#define __SOUNDEMITTER_H__

#include <fmod.hpp>

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "Resources/Sound.h"

namespace Quantix::Core::Components
{
	class QUANTIX_API SoundEmitter : public virtual Quantix::Core::DataStructure::Component
	{
		private:

			#pragma region Attributes

			Resources::Sound*		_sound;
			FMOD::ChannelGroup*		_channel;

			Resources::ESoundMode	_soundMode;

			QXfloat					_volume;

			QXbool					_loop;
			QXbool					_playOnAwake;

			#pragma endregion

		public:

			#pragma region Constructors & Destructor

			/**
			 * @brief Construct a new SoundEmitter object
			 *
			 */
			SoundEmitter();

			/**
			 * @brief Construct a new SoundEmitter object
			 *
			 * @param sound to emit
			 */
			SoundEmitter(Resources::Sound* sound) noexcept;

			/**
			 * @brief Construct a new SoundEmitter object by copy
			 *
			 * @param copy SoundEmitter
			 */
			SoundEmitter(const SoundEmitter& copy) noexcept;

			/**
			 * @brief Construct a new SoundEmitter object by move
			 *
			 * @param copy SoundEmitter
			 */
			SoundEmitter(SoundEmitter&& copy) noexcept;


			SoundEmitter(Core::DataStructure::GameComponent* object);

			/**
			 * @brief Destroy the SoundEmitter object
			 *
			 */
			~SoundEmitter();

			#pragma endregion

			#pragma region Methods

			SoundEmitter*	Copy() const override;

			virtual void	Init(Quantix::Core::DataStructure::GameComponent* object) override;

			/**
			 * @brief Play Sound of the emitter
			 *
			 * @return QXbool played successfully value
			 */
			const QXbool	PlaySound();

			/**
			 * @brief Set Mode of the Sound
			 *
			 * @return QXbool Setted successfully value
			 */
			void	SetSoundMode(Resources::ESoundMode mode);

			/**
			 * @brief Update position attributes of the emitter
			 *
			 */
			void			UpdateAttributes();

			#pragma region Accessors


			inline float				GetVolume() { _channel->getVolume(&_volume); return _volume; }

			inline Resources::ESoundMode GetSoundMode() { return _soundMode; }

			/**
			 * @brief Get Sound
			 *
			 * @return const Resources::Sound* sound value
			 */
			inline	const Resources::Sound*	GetSound() const					{ return _sound; }

			/**
			 * @brief Is Looping
			 *
			 * @return const QXbool is looping value
			 */
			inline	const QXbool			IsLooping() const					{ return _loop; }

			/**
			 * @brief Is Playing On Awake
			 *
			 * @return const QXbool is playing on awake value
			 */
			inline	const QXbool			IsPlayingOnAwake() const			{ return _playOnAwake; }


			/**
			 * @brief Set Sound
			 *
			 * @param Resources::Sound* sound new value
			 */
			inline	void					SetSound(Resources::Sound* sound)	{_sound = sound; }

			inline void						SetVolume(float volume) { _channel->setVolume(volume); _volume = volume;}

			/**
			 * @brief Set Loop
			 *
			 * @param QXbool is looping new value
			 */
			inline	void					SetLoop(QXbool loop)				{ _loop = loop; }

			/**
			 * @brief Set Play On Awake
			 *
			 * @param QXbool is playing on awake new value
			 */
			inline	void					SetPlayOnAwake(QXbool playOnAwake)	{ _playOnAwake = playOnAwake; }

			#pragma endregion

			#pragma endregion

			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component);
	};
}

#endif //__SOUNDEMITTER_H__