#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>
#include <rttrEnabled.h>

#include "Type.h"
#include "Resource.h"
#include "Physic/Transform3D.h"

#define FRAME 30.f
#define BLENDINGTIME 2.f

namespace Quantix::Resources
{
	struct Bone
	{
		Math::QXvec3					localPos;
		Math::QXquaternion				localRotation;
		Math::QXvec3					localScale;
	};

	struct AnimationInfo
	{
		QXstring												name;
		QXsizei													maxFrame;
		QXfloat													timeCap;
		QXfloat													currentTime = 0.f;
		QXint													animIndex = 0;

		void	Init(const QXstring tName, QXsizei tMaxFrame, QXfloat tTimeCap)
		{
			name = tName;
			maxFrame = tMaxFrame;
			timeCap = tTimeCap;
		}
		
		void	Update(float& frameTime)
		{
			currentTime += frameTime;
			if (currentTime >= timeCap)
			{
				// Reset currentTime (not reset to 0 to improve accuracy)
				currentTime -= timeCap;

				// Set current frame index to next frame
				animIndex = animIndex < maxFrame - 1 ? animIndex + 1 : 0;
			}
		}
	};

	class Animation : public Resource
	{
	public:
		Animation() = default;
		Animation(const Animation& anim) = default;
		Animation(Animation&& anim) = default;
		~Animation() = default;

		void Load(const QXstring& pathFile) override;
		void SetTRS(const aiAnimation* paiAnim, const aiMesh* paiMesh);
		void Init() override;
		void SetSkeletonOfMesh(QXuint indexBone, Quantix::Physic::Transform3D& objectTransform);
		void Update(Quantix::Physic::Transform3D& objectTransform);

	private:
		std::vector<Math::QXmat4>								_localTRS;
		std::vector<std::vector<Bone>>							_dataAnim;
		std::vector<Math::QXmat4>								_BlendedTRS;
		AnimationInfo											_info;
		//QXfloat													_changeAnim = 0.f;
		Math::QXvec4											_weight;
		QXuint													_nbBones;
	};
}

#endif // !_ANIMATION_H_