#include "Core/Physic/Transform2D.h"
#include "Core/DataStructure/GameObject2D.h"

namespace Quantix::Core::Physic
{
#pragma region Constructors&Destructor

	Transform2D::Transform2D()  noexcept :
		_position{ 0.f, 0.f }, _rotationAngle{ 0.f }, _scale{ 1.f, 1.f }, _trs{}, _childs{}
	{}

	Transform2D::Transform2D(Quantix::Core::DataStructure::GameObject2D* object)  noexcept :
		_position{ 0.f, 0.f }, _rotationAngle{ 0.f }, _scale{ 1.f, 1.f }, _trs{ Math::QXmat4::CreateTRSMatrix({_position.x, _position.y, 0.f}, {0.f, 0.f, 0.f, _rotationAngle}, {_scale.x, _scale.y, 0.f}) }, _childs{}, _gameObject{ object }
	{
	}

	Transform2D::Transform2D(const Transform2D& t) noexcept :
		_position{ t._position }, _rotationAngle{ t._rotationAngle }, _scale{ t._scale }, _trs{ t._trs }
	{
		for (auto it = t._childs.begin(); it != t._childs.end(); ++it)
		{
			_childs.push_back(*it);
		}
	}

	Transform2D::Transform2D(Transform2D&& t) noexcept :
		_position{ std::move(t._position) }, _rotationAngle{ std::move(t._rotationAngle) }, _scale{ std::move(t._scale) },
		_trs{ std::move(t._trs) }, _childs{ std::move(t._childs) },
		_gameObject{ std::move(t._gameObject) }
	{}

	Transform2D::Transform2D(const Math::QXvec2& pos, const QXfloat& rotAngle, const Math::QXvec2& sca)  noexcept :
		_position{ pos }, _rotationAngle{ rotAngle }, _scale{ sca },
		_trs{ Math::QXmat4::CreateTRSMatrix({pos.x, pos.y, 0.f}, {0.f, 0.f, 0.f, rotAngle}, {sca.x, sca.y, 0.f}) }, _childs{}
	{}

	Transform2D::Transform2D(Math::QXvec2&& pos, float&& rotAngle, Math::QXvec2&& sca)  noexcept :
		_position{ std::move(pos) }, _rotationAngle{ std::move(rotAngle) }, _scale{ std::move(sca) },
		_trs{ Math::QXmat4::CreateTRSMatrix(
			{std::move(pos.x), std::move(pos.y), 0.f}, {0.f, 0.f, 0.f, std::move(rotAngle)}, {std::move(sca.x), std::move(sca.y), 0.f}) },
		_childs{}
	{}

	Transform2D::~Transform2D() noexcept
	{}

#pragma endregion

#pragma region Methods

#pragma region Getters&Setters

	const Math::QXvec2& Transform2D::GetPosition() noexcept
	{
		return _position;
	}

	const QXfloat& Transform2D::GetRotationAngle() noexcept
	{
		return _rotationAngle;
	}

	const Math::QXvec2& Transform2D::GetScale() noexcept
	{
		return _scale;
	}

	const Math::QXmat4& Transform2D::GetTRS() noexcept
	{
		return _trs;
	}

	void Transform2D::SetPosition(const Math::QXvec2& newPos) noexcept
	{
		_position = newPos;
		UpdateTRS();
	}

	void Transform2D::SetRotationAngle(const QXfloat& newRot) noexcept
	{
		_rotationAngle = newRot;
		UpdateTRS();
	}

	void Transform2D::SetScale(const Math::QXvec2& newSca) noexcept
	{
		_scale = newSca;
		UpdateTRS();
	}

	void Transform2D::SetParent(Transform2D* newParent) noexcept
	{
		Transform2D* tmp = _parent;
		_parent = newParent;

		if (tmp)
			tmp->RemoveChild(this);
	}


#pragma endregion

#pragma region Functions

	void	Transform2D::UpdateTRS() noexcept
	{
		Math::QXvec3 vec(0.f, 0.f, _rotationAngle);
		_trs = Math::QXmat4::CreateTRSMatrix({ _position.x, _position.y, 0.f }, Math::QXquaternion::EulerToQuaternion(vec), { _scale.x, _scale.y, 0.f });
	}

	void	Transform2D::Update(const Transform2D* parentTransform) noexcept
	{
		UpdateTRS();

		_trs *= parentTransform->_trs;
	}


	void	Transform2D::Translate(const Math::QXvec2& pos) noexcept
	{
		_position += pos;
		UpdateTRS();
	}

	void	Transform2D::Rotate(const QXfloat& rot) noexcept
	{
		_rotationAngle += rot;
		UpdateTRS();
	}

	void	Transform2D::Scale(const Math::QXvec2& sca) noexcept
	{
		_scale += sca;
		UpdateTRS();
	}

	void	Transform2D::AddChild(Transform2D* child) noexcept
	{
		_childs.push_back(child);
	}

	QXbool Transform2D::FindTransform(Transform2D* toFind) noexcept
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

	void	Transform2D::RemoveChild(Transform2D* toRemove) noexcept
	{
		_childs.remove(toRemove);
		toRemove->SetParent(nullptr);
	}

#pragma endregion

#pragma region Operators

	Transform2D& Transform2D::operator=(const Transform2D& t) noexcept
	{
		_position = t._position;
		_rotationAngle = t._rotationAngle;
		_scale = t._scale;
		_trs = t._trs;
		_childs = t._childs;

		return *this;
	}

	Transform2D& Transform2D::operator=(Transform2D&& t) noexcept
	{
		_position = std::move(t._position);
		_rotationAngle = std::move(t._rotationAngle);
		_scale = std::move(t._scale);
		_trs = std::move(t._trs);
		_childs = std::move(t._childs);

		return *this;
	}

#pragma endregion

#pragma endregion
}