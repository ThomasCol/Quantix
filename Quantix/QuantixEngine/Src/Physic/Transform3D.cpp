#include "Physic/Transform3D.h"
#include "Core/DataStructure/GameObject3D.h"

namespace Quantix::Physic
{
	#pragma region Constructors&Destructor

	Transform3D::Transform3D() :
		_position {0.f, 0.f, 0.f},
		_rotation {1.0f, 0.f, 0.f, 0.f},
		_scale {1.f, 1.f, 1.f},
		_forward{0.f, 0.f, 1.f},
		_up{0.f, 1.f, 0.f},
		_trs {},
		_childs {}
	{}

	Transform3D::Transform3D(const Transform3D& t) noexcept:
		_position{ t._position },
		_rotation{ t._rotation },
		_scale{ t._scale },
		_forward{ t._forward },
		_up{ t._up },
		_trs{ t._trs }
	{
		for (auto it = t._childs.begin(); it != t._childs.end(); ++it)
		{
			_childs.push_back(*it);
		}
	}

	Transform3D::Transform3D(Transform3D&& t) noexcept:
		_position{ std::move(t._position) },
		_rotation{ std::move(t._rotation) },
		_scale{ std::move(t._scale) },
		_forward{ std::move(t._forward) },
		_up{ std::move(t._up) },
		_trs{ std::move(t._trs) },
		_childs{ std::move(t._childs) },
		_gameObject {std::move(t._gameObject)}
	{}

	Transform3D::Transform3D(const Math::QXvec3& pos, const Math::QXquaternion& rot, const Math::QXvec3& sca, Quantix::Core::DataStructure::GameObject3D* object) :
		_position{ pos }, _rotation{ rot }, _scale{ sca }, _trs{ Math::QXmat4::CreateTRSMatrix(pos, rot, sca)}, _childs{}, _gameObject{ object }
	{
		_forward = _rotation * Math::QXvec3::forward;
		_up = _rotation * Math::QXvec3::up;
	}

	Transform3D::Transform3D(Math::QXvec3&& pos, Math::QXquaternion&& rot, Math::QXvec3&& sca) :
		_position{ std::move(pos) }, _rotation{ std::move(rot) }, _scale{ std::move(sca) }, 
		_trs{ Math::QXmat4::CreateTRSMatrix(std::move(pos), std::move(rot), std::move(sca)) }, _childs{}
	{
		_forward = _rotation * Math::QXvec3::forward;
		_up = _rotation * Math::QXvec3::up;
	}

	Transform3D::~Transform3D()
	{}

	#pragma endregion

	#pragma region Methods

	#pragma region Getters&Setters

	const Math::QXvec3& Transform3D::GetPosition()
	{
		return _position;
	}

	const Math::QXvec3& Transform3D::GetGlobalPosition()
	{
		return _globalPosition;
	}

	Math::QXquaternion& Transform3D::GetRotation()
	{
		return _rotation;
	}

	Math::QXquaternion& Transform3D::GetGlobalRotation()
	{
		return _globalRotation;
	}

	const Math::QXvec3& Transform3D::GetScale()
	{
		return _scale;
	}

	const Math::QXvec3& Transform3D::GetGlobalScale()
	{
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

	void	Transform3D::SetPosition(const Math::QXvec3& newPos)
	{
		_position = newPos;
	}

	void Transform3D::SetGlobalPosition(const Math::QXvec3& newPos)
	{
		if (_parent)
			_globalPosition = _parent->GetGlobalPosition() + newPos;
		else
			_globalPosition = newPos;
	}

	void	Transform3D::SetRotation(const Math::QXquaternion& newRot)
	{
		_rotation = newRot;
	}

	void Transform3D::SetGlobalRotation(const Math::QXquaternion& newRot)
	{
		if (_parent)
			_globalRotation = _parent->GetGlobalRotation() * newRot;
		else
			_globalRotation = newRot;
	}

	void	Transform3D::SetScale(const Math::QXvec3& newSca)
	{
		_scale = newSca;
	}

	void Transform3D::SetGlobalScale(const Math::QXvec3& newSca)
	{
		if (_parent)
			_globalScale = _parent->GetGlobalScale() + newSca;
		else
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

	#pragma endregion

	#pragma region Functions

	void	Transform3D::UpdateTRS()
	{
		_trs = Math::QXmat4::CreateTRSMatrix(_position, _rotation, _scale);
	}

	void	Transform3D::Update(const Transform3D* parentTransform)
	{
		UpdateTRS();

		_forward = _rotation * Math::QXvec3::forward;
		_up = _rotation * Math::QXvec3::up;

		_trs *= parentTransform->_trs;
	}

	void	Transform3D::Translate(const Math::QXvec3& pos)
	{
		_position += pos;
	}

	void	Transform3D::Rotate(const Math::QXquaternion& rot)
	{
		_rotation = _rotation * rot;
	}

	void	Transform3D::Scale(const Math::QXvec3& sca)
	{
		_scale += sca;
	}

	void	Transform3D::AddChild(Transform3D* child)
	{
		_childs.push_back(child);
	}

	QXbool Transform3D::FindTransform(Transform3D* toFind)
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
