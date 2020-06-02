#include "Physic/Transform3D.h"
#include "Core/DataStructure/GameObject3D.h"
#include "Core/Components/CharacterController.h"
#include "Core/Components/Camera.h"

namespace Quantix::Physic
{
	#pragma region Constructors&Destructor

	Transform3D::Transform3D() :
		_parent {nullptr},
		_position {0.f, 0.f, 0.f},
		_rotation {1.0f, 0.f, 0.f, 0.f},
		_scale {1.f, 1.f, 1.f},
		_forward{0.f, 0.f, 1.f},
		_up{0.f, 1.f, 0.f},
		_trs {},
		_childs {},
		_gameObject{ nullptr },
		_space {Space::LOCAL},
		_globalHasChanged{ QX_FALSE }
	{}

	Transform3D::Transform3D(const Transform3D& t) noexcept:
		_parent{ t._parent },
		_position{ t._position },
		_rotation{ t._rotation },
		_scale{ t._scale },
		_forward{ t._forward },
		_up{ t._up },
		_trs{ t._trs },
		_space{ t._space },
		_globalHasChanged { t._globalHasChanged }
	{
		for (auto it = t._childs.begin(); it != t._childs.end(); ++it)
		{
			(*it)->SetParent(this);
			_childs.push_back(*it);
		}
	}

	Transform3D::Transform3D(Transform3D&& t) noexcept:
		_parent{ std::move(t._parent) },
		_position{ std::move(t._position) },
		_rotation{ std::move(t._rotation) },
		_scale{ std::move(t._scale) },
		_forward{ std::move(t._forward) },
		_up{ std::move(t._up) },
		_trs{ std::move(t._trs) },
		_childs{ std::move(t._childs) },
		_gameObject {std::move(t._gameObject)},
		_space{ std::move(t._space) },
		_globalHasChanged{ std::move(t._globalHasChanged) }
	{}

	Transform3D::Transform3D(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& sca, Quantix::Core::DataStructure::GameObject3D* object) :
		_position{ pos }, _rotation{ rot }, _scale{ sca }, _trs{ Math::QXmat4::CreateTRSMatrix(pos, rot, sca)}, _childs{}, _gameObject{ object },
		_space{ Space::LOCAL }, _globalHasChanged{ QX_FALSE }
	{
		_forward = _rotation * Math::QXvec3::forward;
		_up = _rotation * Math::QXvec3::up;
	}

	Transform3D::Transform3D(Math::QXvec3&& pos, Math::QXquaternion&& rot, Math::QXvec3&& sca) :
		_position{ std::move(pos) }, _rotation{ std::move(rot) }, _scale{ std::move(sca) }, 
		_trs{ Math::QXmat4::CreateTRSMatrix(std::move(pos), std::move(rot), std::move(sca)) }, _childs{}, _space{ Space::LOCAL }, _globalHasChanged{ QX_FALSE }
	{
		_trsLocal = Math::QXmat4::CreateTRSMatrix(pos, rot, sca);
		_forward = _rotation * Math::QXvec3::forward;
		_up = _rotation * Math::QXvec3::up;
	}

	Transform3D::~Transform3D()
	{}

	#pragma endregion

	#pragma region Methods

	#pragma region Getters&Setters

	Transform3D* Transform3D::GetParent() const
	{
		return _parent;
	}

	const Math::QXvec3& Transform3D::GetPosition()
	{
		return _position;
	}

	const Math::QXvec3& Transform3D::GetGlobalPosition()
	{
		_globalPosition.x = _trs[3][0];
		_globalPosition.y = _trs[3][1];
		_globalPosition.z = _trs[3][2];
		return _globalPosition;
	}

	Math::QXquaternion& Transform3D::GetRotation()
	{
		return _rotation;
	}

	Math::QXquaternion& Transform3D::GetGlobalRotation()
	{
		Math::QXvec3 rot;

		rot.x = atan2f(_trs[1][2], _trs[2][2]);
		rot.y = atan2f(-_trs[0][2], sqrtf(_trs[1][2] * _trs[1][2] + _trs[2][2] * _trs[2][2]));
		rot.z = atan2f(_trs[0][1], _trs[0][0]);

		_globalRotation = Math::QXquaternion::EulerToQuaternion(rot);

		return _globalRotation;
	}

	const Math::QXvec3& Transform3D::GetScale()
	{
		return _scale;
	}

	const Math::QXvec3& Transform3D::GetGlobalScale()
	{
		_globalScale.x = _trs[0][0];
		_globalScale.y = _trs[1][1];
		_globalScale.z = _trs[2][2];

		return _globalScale;
	}

	const Math::QXvec3& Transform3D::GetForward()
	{
		return _forward;
	}

	const Math::QXvec3& Transform3D::GetUp()
	{
		return _up;
	}

	const Math::QXmat4& Transform3D::GetTRS()
	{
		return _trs;
	}

	void Transform3D::SetTRS(Math::QXmat4& trs)
	{
		_trs = trs;
	}

	void Transform3D::SetParent(Transform3D* newParent)
	{
		Transform3D* tmp = _parent;
		_parent = newParent;

		if (tmp)
			tmp->RemoveChild(this);
	}

	void	Transform3D::SetPosition(const Math::QXvec3& newPos)
	{
		_position = newPos;
	}

	void Transform3D::SetGlobalPosition(const Math::QXvec3& newPos)
	{
		_globalHasChanged = QX_TRUE;
		_globalPosition = newPos;
	}

	void	Transform3D::SetRotation(const Math::QXquaternion& newRot)
	{
		_rotation = newRot;
	}

	void Transform3D::SetGlobalRotation(const Math::QXquaternion& newRot)
	{
		_globalHasChanged = QX_TRUE;
		_globalRotation = newRot;
	}

	void	Transform3D::SetScale(const Math::QXvec3& newSca)
	{
		_scale = newSca;
	}

	void Transform3D::SetGlobalScale(const Math::QXvec3& newSca)
	{
		_globalHasChanged = QX_TRUE;
		_globalScale = newSca;
	}

	void	Transform3D::SetForward(const Math::QXvec3& newFor)
	{
		_forward = newFor;
	}

	void Transform3D::SetUp(const Math::QXvec3& newUp)
	{
		_up = newUp;
	}

	void Transform3D::SetSpace(Space space)
	{ 
		_space = space;
		if (_space == Space::WORLD)
 			UpdateGlobalTransform();
	}

	#pragma endregion

	#pragma region Functions

	void	Transform3D::UpdateTRS()
	{
		_trsLocal = Math::QXmat4::CreateTRSMatrix(_position, _rotation, _scale);
	}

	void	Transform3D::UpdateTRSLocal(const Transform3D* parentTransform)
	{
		_trs = Math::QXmat4::CreateTRSMatrix(_globalPosition, _globalRotation, _globalScale);
		_globalHasChanged = QX_FALSE;
		_trsLocal = parentTransform->_trs.Inverse() * _trs;
		_position.x = _trsLocal[0][3];
		_position.y = _trsLocal[1][3];
		_position.z = _trsLocal[2][3];

		Math::QXvec3 rot;

		rot.x = atan2f(_trsLocal[1][2], _trsLocal[2][2]);
		rot.y = atan2f(-_trsLocal[0][2], sqrtf(_trsLocal[1][2] * _trsLocal[1][2] + _trsLocal[2][2] * _trsLocal[2][2]));
		rot.z = atan2f(_trsLocal[0][1], _trsLocal[0][0]);

		_rotation = Math::QXquaternion::EulerToQuaternion(rot);

		_scale.x = _trsLocal[0][0];
		_scale.y = _trsLocal[1][1];
		_scale.z = _trsLocal[2][2];
	}

	void	Transform3D::UpdateGlobalTransform()
	{
		GetGlobalPosition();
		GetGlobalRotation();
		GetGlobalScale();
	}

	void	Transform3D::Update(Transform3D* parentTransform)
	{
		if (_globalHasChanged)
			UpdateTRSLocal(parentTransform);
		UpdateTRS();

		_parent = parentTransform;

		_forward = _rotation * Math::QXvec3::forward;
		_up = _rotation * Math::QXvec3::up;

		_trs = _trsLocal * parentTransform->_trs;
		UpdateGlobalTransform();
	}

	void	Transform3D::Translate(const Math::QXvec3& pos)
	{
		if (_space == Space::LOCAL)
			_position += pos;
		else if (_space == Space::WORLD)
		{
			_globalHasChanged = QX_TRUE;
			_globalPosition += pos;
		}
	}

	void	Transform3D::Rotate(const Math::QXquaternion& rot)
	{
		if (_space == Space::LOCAL)
			_rotation = _rotation * rot;
		else if (_space == Space::WORLD)
		{
			_globalHasChanged = QX_TRUE;
			_globalRotation = _globalRotation * rot;
		}
	}

	void	Transform3D::Scale(const Math::QXvec3& sca)
	{
		if (_space == Space::LOCAL)
			_scale += sca;
		else if (_space == Space::WORLD)
		{
			_globalHasChanged = QX_TRUE;
			_globalScale += sca;
		}
	}

	void	Transform3D::AddChild(Transform3D* child)
	{
		child->SetParent(this);
		_childs.push_back(child);
	}

	void	Transform3D::RemoveChild(Transform3D* toRemove)
	{
		_childs.remove(toRemove);
		toRemove->SetParent(nullptr);
	}

	void	Transform3D::Detach()
	{
		Transform3D* world	{ this };

		while (world->GetParent() != nullptr)
			world = world->GetParent();

		_parent->SetParent(world);
	}

	QXbool	Transform3D::FindTransform(Transform3D* toFind)
	{
		for (auto it = _childs.begin(); it != _childs.end(); ++it)
		{
			if ((*it)->_childs.size() > 0)
				if ((*it)->FindTransform(toFind))
					return QX_TRUE;

			if ((*it)->GetObject()->GetName() == toFind->GetObject()->GetName())
				return QX_TRUE;
		}
		return QX_FALSE;
	}

	#pragma endregion

	#pragma region Operators

	Transform3D& Transform3D::operator=(const Transform3D& t) noexcept
	{
		_position = t._position;
		_rotation = t._rotation;
		_scale = t._scale;
		_trs = t._trs;
		_childs = t._childs;

		return *this;
	}

	Transform3D& Transform3D::operator=(Transform3D&& t) noexcept
	{
		_position = std::move(t._position);
		_rotation = std::move(t._rotation);
		_scale = std::move(t._scale);
		_trs = std::move(t._trs);
		_childs = std::move(t._childs);

		return *this;
	}

	#pragma endregion
	
	#pragma endregion
}
