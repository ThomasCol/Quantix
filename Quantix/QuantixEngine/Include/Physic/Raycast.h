#ifndef __RAYCAST_H__
#define __RAYCAST_H__

#include "Core/DLLHeader.h"
#include "Core/MathHeader.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Type.h"

namespace Quantix::Physic
{
	struct QUANTIX_API Raycast
	{
		QXbool status{ QX_FALSE };

		Math::QXvec3 normalClosestBlock {0,0,0};
		Math::QXvec3 positionClosestBlock {0,0,0};
		QXfloat distanceClosestBlock {0};
		Core::DataStructure::GameObject3D* actorClosestBlock {nullptr};

		Raycast() = delete;

		/**
		 * @brief Construct a new Raycast object
		 * 
		 * @param origin Origin of the Raycast
		 * @param unitDir Direction of the raycast
		 * @param distMax Distance Max of the raycast
		 */
		Raycast(const Math::QXvec3& origin, const Math::QXvec3& unitDir, QXfloat distMax) noexcept;

		/**
		 * @brief Construct a new Raycast object
		 * 
		 * @param src Raycast to copy
		 */
		Raycast(const Raycast& src) = default;

		/**
		 * @brief Construct a new Raycast object
		 * 
		 * @param src Raycast to move
		 */
		Raycast(Raycast&& src) = default;
	};
}
#endif
