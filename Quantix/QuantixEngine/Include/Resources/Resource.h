#pragma once

#include <atomic>
#include <string>

#include "Core/DLLHeader.h"

namespace Quantix::Resources
{
	enum class EResourceStatus
	{
		DEFAULT = 0,
		LOADED,
		READY,
		FAILED
	};

	class QUANTIX_API Resource
	{
	protected:
		#pragma region Attributes

		std::atomic<EResourceStatus>	_status;

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Resource object
		 * 
		 */
		Resource() = default;

		/**
		 * @brief Construct a new Resource object
		 * 
		 * @param asset asset to copy
		 */
		Resource(const Resource& asset) = default;

		/**
		 * @brief Construct a new Resource object
		 * 
		 * @param asset asset to move
		 */
		Resource(Resource&& asset) = default;

		/**
		 * @brief Destroy the Resource object
		 * 
		 */
		virtual ~Resource() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Load ressource
		 * 
		 * @param file path to the ressource
		 */
		virtual void Load(const QXstring& file) noexcept = 0;

		/**
		 * @brief Init ressource
		 * 
		 */
		virtual void Init() noexcept = 0;

		/**
		 * @brief Is ressource ready
		 * 
		 * @return true ressource ready
		 * @return false ressource not ready
		 */
		inline bool	IsReady() noexcept { return _status.load() == EResourceStatus::READY; }

		/**
		 * @brief Is ressource loaded
		 * 
		 * @return true ressource loaded
		 * @return false ressource not loaded
		 */
		inline bool	IsLoaded() noexcept { return _status.load() == EResourceStatus::LOADED; }

		/**
		 * @brief Is ressource failed
		 * 
		 * @return true ressource failed
		 * @return false ressource not failed
		 */
		inline bool	IsFailed() noexcept { return _status.load() == EResourceStatus::FAILED; }

		#pragma endregion
	};
}