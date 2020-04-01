#pragma once
#include <sstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <functional>

#include "AppInfo.h"
#include "Logger.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define BEGIN_PROFILING "**********************************************\n\
************** BEGIN PROFILING ***************\n\
**********************************************\n\n"

#define END_PROFILING "**********************************************\n\
*************** END PROFILING ****************\n\
**********************************************\n\n"

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
	class Profiler
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
		 * @brief Calculate a counter of FPS
		 * 
		 */
		void				FrameCounter();

		/**
		 * @brief Begin a specific profiling
		 * 
		 * @param type String name of the type of profiling
		 */
		void				StartProfiling(QXstring type);


		/**
		 * @brief Stop a specific profiling
		 * 
		 * @param type String name of the type of profiling
		 */
		void				StopProfiling(QXstring type);

		/**
		 * @brief Update the timer of all profiling already started
		 * 
		 * @param deltaTime float frameTime Value for add to all timer
		 */
		void				Update(QXfloat deltaTime);


		#pragma region Accessors
		/**
		 * @brief Get the FPS
		 * 
		 * @return int of the fps
		 */
		int					GetFrameCounter();

		/**
		 * @brief Set the App Info object
		 * 
		 * @param app AppInfo
		 */
		inline void			SetAppInfo(app App) { _info = &App; };

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
		void				SetMessage(QXstring type, QXstring msg);
		
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
		app*														_info;
		std::string													_profiling;
		std::map<QXstring, Info>									_infoProfiling;
		std::vector<QXstring>										_elementErase;
		QXint														_frameRate;
		QXbool														_activate;
		#pragma endregion Attributes
	};
}