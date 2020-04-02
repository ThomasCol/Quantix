#pragma once
#include <vector>
#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "Core/Type.h"


namespace fs = std::filesystem;

namespace Quantix::Core::Debugger
{
	/**
	 * @brief enum class TypeLog
	 * 
	 */
	enum class TypeLog
	{
		INFOS,
		WARNING,
		ERROR,
		PROFILING,
		DEFAULT
	};

	/**
	 * @brief struct Data for each Log
	 * 
	 */
	struct Data
	{
		#pragma region Attributes
		QXstring		_message;
		TypeLog			_type;
		#pragma endregion Attributes
	};

	/**
	 * @brief class Logger
	 * 
	 */
	class Logger
	{
	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new Logger object
		 * 
		 */
		Logger();

		/**
		 * @brief Construct a new Logger object by copy but deleted
		 * 
		 * @param log 
		 */
		Logger(const Logger& log) = delete;

		/**
		 * @brief Construct a new Logger object by move but deleted
		 * 
		 * @param log 
		 */
		Logger(Logger&& log) = delete;

		/**
		 * @brief Destroy the Logger object
		 * 
		 */
		~Logger();
		#pragma region Constructors/Destructor

		#pragma region Methods

		/**
		 * @brief Print all Log
		 * 
		 */
		void			PrintLog();

		void			SendMessage(TypeLog type, QXstring message);

		/**
		 * @brief Close the Logger and create a log file with all log
		 * 
		 */
		void			CloseLogger();

		#pragma region Accessors
		/**
		 * @brief Set the Infos object
		 * 
		 * @param msg String
		 */
		void			SetInfos(const QXstring& msg);

		/**
		 * @brief Set the Warning object
		 * 
		 * @param msg String
		 */
		void			SetWarning(const QXstring& msg);

		/**
		 * @brief Set the Error object
		 * 
		 * @param msg String
		 */
		void			SetError(const QXstring& msg);

		/**
		 * @brief Set the Profiling object
		 * 
		 * @param msg String
		 */
		void			SetProfiling(const QXstring& msg);
		#pragma endregion Accessors

		#pragma region Static
		/**
		 * @brief Get the Instance object
		 * 
		 * @return Logger* 
		 */
		static Logger*	GetInstance();
		#pragma endregion Static
		#pragma endregion Methods
	private:
		#pragma region Attributes
		static Logger*				_instance;
		std::vector<Data>			_data;
		#pragma endregion Attributes
	};
}

#define LOG(severity, message) Quantix::Core::Debugger::Logger::GetInstance()->Quantix::Core::Debugger::Logger::SendMessage(Quantix::Core::Debugger::TypeLog::severity, message);