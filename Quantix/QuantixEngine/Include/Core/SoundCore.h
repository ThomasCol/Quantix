#ifndef __SOUNDCORE_H__
#define __SOUNDCORE_H__

#include <vector>
#include <fmod.hpp>

#include "Core/DLLHeader.h"
#include "Type.h"

namespace Quantix::Core
{
	class QUANTIX_API SoundCore
	{
		private:

			#pragma region Attributes

			static SoundCore*	_instance;
			FMOD::System*		_system;
			std::vector<QXbool>	_listeners;

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

			/**
			 * @brief Try the FMOD method and manage FMOD errors
			 *
			 * @param FMOD_RESULT result of the FMOD method
			 * @return QXbool method succeeding value
			 */
			QXbool						Try(FMOD_RESULT result);

			/**
			 * @brief Add a listener to the list
			 *
			 * @return QXuint listener ID
			 */
			QXuint						AddListener();

			/**
			 * @brief Supp the listener of the list
			 *
			 * @param const QXuint listener ID
			 */
			void						SuppListener(const QXuint ID);

			#pragma endregion

	};
}
#endif //__SOUNDCORE_H__