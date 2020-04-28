#ifndef __SOUNDCORE_H__
#define __SOUNDCORE_H__

#include "Core/DLLHeader.h"
#include <fmod.hpp>

namespace Quantix::Core
{
	class QUANTIX_API SoundCore
	{
		private:

			#pragma region Attributes

			static SoundCore*	_instance;
			FMOD::System*		_system;

			#pragma endregion

			#pragma region Constructor

			/**
			 * @brief Construct a new SoundCore object
			 *
			 */
			SoundCore();

			#pragma endregion

		public:

			#pragma region Constructors & Destructor
		
			SoundCore(const SoundCore& copy) = delete;
			SoundCore(SoundCore&& copy) = delete;

			/**
			 * @brief Destroy the SoundCore object
			 *
			 */
			~SoundCore();

			#pragma endregion

			#pragma region Methods

			inline static SoundCore*	GetInstance()	{ _instance == nullptr ? _instance = new SoundCore : _instance; return _instance; }
			inline FMOD::System*		GetSystem()		{ return _system; }
			void						Update();
			bool						Try(FMOD_RESULT result);

			#pragma endregion

	};
}
#endif //__SOUNDCORE_H__