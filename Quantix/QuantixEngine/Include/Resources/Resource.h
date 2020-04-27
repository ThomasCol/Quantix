#pragma once

#include <atomic>
#include <string>

namespace Quantix::Resources
{
	enum class EResourceStatus
	{
		DEFAULT = 0,
		LOADED,
		READY,
		FAILED
	};

	class Resource
	{
	protected:
		std::atomic<EResourceStatus>	_status;

	public:
		Resource() = default;
		Resource(const Resource& asset) = default;
		Resource(Resource&& asset) noexcept = default;
		virtual ~Resource() = default;

		virtual void Load(const QXstring& file) = 0;
		virtual void Init() = 0;

		inline bool	IsReady() { return _status.load() == EResourceStatus::READY; }
		inline bool	IsLoaded() { return _status.load() == EResourceStatus::LOADED; }
		inline bool	IsFailed() { return _status.load() == EResourceStatus::FAILED; }
	};
}