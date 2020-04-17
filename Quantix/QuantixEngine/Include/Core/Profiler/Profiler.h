#pragma once

#include <GLFW/glfw3.h>

#include "Core/Debugger/Logger.h"
#include "Core/Platform/AppInfo.h"

#define BEGIN_PROFILING "\t\t**********************************************\n\
\t\t************ BEGIN PROFILING ***************\n\
\t\t**********************************************\n\n"

#define END_PROFILING "\t\t**********************************************\n\
\t\t************* END PROFILING ****************\n\
\t\t**********************************************\n\n"

namespace Quantix::Core::Profiling
{
	/**
	 * @brief Struct Info of one method you profil
	 * 
	 */
	struct Info
	{
		#pragma region Attributes
		QXstring	msg;
		QXdouble	beginTime;
		QXdouble	timer;
		QXint		id;
		QXbool		activate;
		#pragma endregion Attributes
	};

	/**
	 * @brief class Profiler
	 * 
	 */
	class QUANTIX_API Profiler
	{
	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new Profiler object
		 * 
		 */
		Profiler();

		/**
		 * @brief Construct a new Profiler object by copy but deleted
		 * 
		 * @param p 
		 */
		Profiler(const Profiler& p) = delete;

		/**
		 * @brief Construct a new Profiler object by move but deleted
		 * 
		 * @param p 
		 */
		Profiler(Profiler&& p) = delete;

		/**
		 * @brief Destroy the Profiler object
		 * 
		 */
		~Profiler();
		#pragma endregion Constructors/Destructor

		
		#pragma region Methods
		/**
		 * @brief Begin a specific profiling
		 * 
		 * @param type String name of the type of profiling
		 */
		void				StartProfiling(const QXstring& type);


		/**
		 * @brief Stop a specific profiling
		 * 
		 * @param type String name of the type of profiling
		 */
		void				StopProfiling(const QXstring& type);

		#pragma region Accessors
		/**
		 * @brief Set the Profiling to format the message
		 * 
		 */
		void				SetProfiling();

		/**
		 * @brief Set the Message object
		 * 
		 * @param type String of the type of profiling
		 * @param msg String message
		 */
		void				SetMessage(const QXstring& type, const QXstring& msg);


		void				SetActivate(bool activate) { _activate = activate; std::cout << _activate << std::endl; };
		
		/**
		 * @brief Get the Activate object
		 * 
		 * @return true 
		 * @return false 
		 */
		bool				GetActivate() const { return _activate; };
		#pragma endregion Accessors

		#pragma region Static
		/**
		 * @brief Get the Instance object
		 * 
		 * @return Profiler* 
		 */
		static Profiler*	GetInstance();
		#pragma endregion Static
		#pragma endregion Methods

	private:
		#pragma region Attributes
		static Profiler*											_instance;
		std::string													_profiling;
		std::map<QXstring, Info>									_infoProfiling;
		QXbool														_activateFirst;
		QXbool														_activate;
		#pragma endregion Attributes
	};
}

#define START_PROFILING(name) Quantix::Core::Profiling::Profiler::GetInstance()->StartProfiling(name)
#define STOP_PROFILING(name) Quantix::Core::Profiling::Profiler::GetInstance()->StopProfiling(name)
#define ACTIVATE_PROFILING(state) Quantix::Core::Profiling::Profiler::GetInstance()->SetActivate(state)
#define GETSTATE_PROFILING() Quantix::Core::Profiling::Profiler::GetInstance()->GetActivate()
#define GETSTATE_PROFILING() Quantix::Core::Profiling::Profiler::GetInstance()->GetActivate()
