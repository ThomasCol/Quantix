#include "Resources/Animation.h"

namespace Quantix::Resources
{
	void Animation::Load(const QXstring& pathFile)
	{
		Assimp::Importer Importer;
		const aiScene* pScene = Importer.ReadFile(pathFile.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		const aiMesh* paiMesh = pScene->mMeshes[0];
		const aiAnimation* paiAnim = pScene->mAnimations[0];

		_info.Init(paiAnim->mName.data, paiAnim->mChannels[0]->mNumPositionKeys, 1 / FRAME);
		_weight = Math::QXvec4{ 0.f, 0.f, 0.f, 0.f };
		SetTRS(paiAnim, paiMesh); 
	}

	void Animation::SetTRS(const aiAnimation* paiAnim, const aiMesh* paiMesh)
	{
		_nbBones = paiAnim->mNumChannels;
		for (QXuint i = 0; i < paiAnim->mNumChannels; i++)
		{
			for (QXuint j = 0; j < paiMesh->mBones[i]->mNumWeights; j++)
			{
				for (QXuint k = 0; k < 4; k++)
				{
					if (_weight[k] == 0.0f)
					{
						_weight[k] = paiMesh->mBones[i]->mWeights[j].mWeight;
						return;
					}
				}
			}
			std::vector<Bone> bone;
			for (QXuint j = 0; j < paiAnim->mChannels[i]->mNumPositionKeys; j++)
			{
				aiVector3D pos = paiAnim->mChannels[i]->mPositionKeys[i].mValue;
				aiQuaternion rot = paiAnim->mChannels[i]->mRotationKeys[i].mValue;
				aiVector3D sca = paiAnim->mChannels[i]->mScalingKeys[i].mValue;

				bone.push_back({Math::QXvec3(pos.x, pos.y, pos.z), Math::QXquaternion(rot.w, rot.x, rot.y, rot.z), Math::QXvec3(sca.x, sca.y, sca.z)});
			}
			_dataAnim.push_back(bone);
		}
	}

	void Animation::Init()
	{

	}

	void Animation::SetSkeletonOfMesh(QXuint indexBone, Quantix::Core::Physic::Transform3D* objectTransform)
	{
		_BlendedTRS[indexBone] = objectTransform->GetTRS() * Math::QXmat4::CreateTRSMatrix(_dataAnim[indexBone][_info.animIndex].localPos, _dataAnim[indexBone][_info.animIndex].localRotation, _dataAnim[indexBone][_info.animIndex].localScale);
	}

	void Animation::UpdateTimer(QXdouble frameTime)
	{
		_info.Update((QXfloat)frameTime);
	}

	void Animation::SendAnimationData(Quantix::Core::Physic::Transform3D* objectTransform)
	{

	}
	
	void Animation::Update(QXdouble frameTime, Quantix::Core::Physic::Transform3D* objectTransform)
	{
		for (QXuint i = 0; i < _nbBones; i++)
			SetSkeletonOfMesh(i, objectTransform);

		SendAnimationData(objectTransform);

		UpdateTimer(frameTime);
	}
}