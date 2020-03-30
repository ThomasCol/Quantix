#include "Physic/Transform.h"

namespace Quantix::Physic
{
#pragma region 2D
	#pragma region Constructors&Destructor

	Transform2D::Transform2D() : 
		_position {0.f, 0.f}, _rotationAngle {0.f}, _scale {1.f, 1.f}, _trs {}, _childs {}
	{}

	Transform2D::Transform2D(const Transform2D& t) :
		_position{ t._position }, _rotationAngle{ t._rotationAngle }, _scale{ t._scale }, _trs{ t._trs }, _childs{ t._childs }
	{}

	Transform2D::Transform2D(Transform2D&& t) :
		_position{ std::move(t._position) }, _rotationAngle{ std::move(t._rotationAngle) }, _scale{ std::move(t._scale) }, 
		_trs{ std::move(t._trs) }, _childs{ std::move(t._childs) }
	{}

	Transform2D::Transform2D(const Math::QXvec2& pos, const QXfloat& rotAngle, const Math::QXvec2& sca) :
		_position{ pos }, _rotationAngle{ rotAngle }, _scale{ sca },
		_trs{ Math::QXmat4::CreateTRSMatrix({pos.x, pos.y, 0.f}, {0.f, 0.f, rotAngle}, {sca.x, sca.y, 0.f}) }, _childs{}
	{}

	Transform2D::Transform2D(Math::QXvec2&& pos, float&& rotAngle, Math::QXvec2&& sca) :
		_position{ std::move(pos) }, _rotationAngle{ std::move(rotAngle) }, _scale{ std::move(sca) },
		_trs{ Math::QXmat4::CreateTRSMatrix(
			{std::move(pos.x), std::move(pos.y), 0.f}, {0.f, 0.f, std::move(rotAngle)}, {std::move(sca.x), std::move(sca.y), 0.f}) }, 
		_childs{}
	{}

	Transform2D::~Transform2D()
	{}

	#pragma endregion
	
	#pragma region Methods

	#pragma region Getters&Setters

	const Math::QXvec2& Transform2D::GetPosition()
	{
		return _position;
	}

	const QXfloat& Transform2D::GetRotationAngle()
	{
		return _rotationAngle;
	}

	const Math::QXvec2& Transform2D::GetScale()
	{
		return _scale;
	}

	const Math::QXmat4& Transform2D::GetTRS()
	{
		return _trs;
	}

	void Transform2D::SetPosition(const Math::QXvec2& newPos)
	{
		_position = newPos;
		UpdateTRS();
	}

	void Transform2D::SetRotationAngle(const QXfloat& newRot)
	{
		_rotationAngle = newRot;
		UpdateTRS();
	}

	void Transform2D::SetScale(const Math::QXvec2& newSca)
	{
		_scale = newSca;
		UpdateTRS();
	}

	#pragma endregion

	void	Transform2D::UpdateTRS()
	{
		_trs = Math::QXmat4::CreateTRSMatrix({ _position.x, _position.y, 0.f }, { 0.f, 0.f, _rotationAngle }, { _scale.x, _scale.y, 0.f });
	}

	void	Transform2D::Update(const Math::QXmat4& trsParent) const
	{
		std::vector<Transform2D>::const_iterator it;

		for (it = _childs.cbegin(); it != _childs.cend(); ++it)
			it->Update(_trs);
	}


	void	Transform2D::Translate(const Math::QXvec2& pos)
	{
		_position += pos;
		UpdateTRS();
	}

	void	Transform2D::Rotate(const QXfloat& rot)
	{
		_rotationAngle += rot;
		UpdateTRS();
	}

	void	Transform2D::Scale(const Math::QXvec2& sca)
	{
		_scale += sca;
		UpdateTRS();
	}

	void	Transform2D::AddChild(const Transform2D& child)
	{
		_childs.push_back(child);
	}

	void	Transform2D::AddChild(Transform2D&& child)
	{
		_childs.push_back(std::move(child));
	}

	#pragma region Operators

	Transform2D& Transform2D::operator=(const Transform2D& t)
	{
		_position = t._position;
		_rotationAngle = t._rotationAngle;
		_scale = t._scale;
		_trs = t._trs;
		_childs = t._childs;

		return *this;
	}

	Transform2D& Transform2D::operator=(Transform2D&& t)
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
#pragma endregion

#pragma region 3D
	#pragma region Constructors&Destructor

	Transform3D::Transform3D() :
		_position {0.f, 0.f, 0.f}, _rotation {0.f, 0.f, 0.f}, _scale {1.f, 1.f, 1.f}, _trs {}, _childs {}
	{}

	Transform3D::Transform3D(const Transform3D& t) :
		_position{ t._position }, _rotation{ t._rotation }, _scale{ t._scale }, _trs{ t._trs }, _childs{ t._childs }
	{}

	Transform3D::Transform3D(Transform3D&& t) :
		_position{ std::move(t._position) }, _rotation{ std::move(t._rotation) }, _scale{ std::move(t._scale) }, 
		_trs{ std::move(t._trs) }, _childs{ std::move(t._childs) }
	{}

	Transform3D::Transform3D(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& sca) :
		_position{ pos }, _rotation{ rot }, _scale{ sca }, _trs{ Math::QXmat4::CreateTRSMatrix(pos, rot, sca)}, _childs{}
	{}

	Transform3D::Transform3D(Math::QXvec3&& pos, Math::QXvec3&& rot, Math::QXvec3&& sca) :
		_position{ std::move(pos) }, _rotation{ std::move(rot) }, _scale{ std::move(sca) }, 
		_trs{ Math::QXmat4::CreateTRSMatrix(std::move(pos), std::move(rot), std::move(sca)) }, _childs{}
	{}

	Transform3D::~Transform3D()
	{}

	#pragma endregion

	#pragma region Methods

	#pragma region Getters&Setters

	const Math::QXvec3& Transform3D::GetPosition()
	{
		return _position;
	}

	const Math::QXvec3& Transform3D::GetRotation()
	{
		return _rotation;
	}

	const Math::QXvec3& Transform3D::GetScale()
	{
		return _scale;
	}

	const Math::QXmat4& Transform3D::GetTRS()
	{
		return _trs;
	}

	void	Transform3D::SetPosition(const Math::QXvec3& newPos)
	{
		_position = newPos;
		UpdateTRS();
	}

	void	Transform3D::SetRotation(const Math::QXvec3& newRot)
	{
		_rotation = newRot;
		UpdateTRS();
	}

	void	Transform3D::SetScale(const Math::QXvec3& newSca)
	{
		_scale = newSca;
		UpdateTRS();
	}

	#pragma endregion

	void	Transform3D::UpdateTRS()
	{
		_trs = Math::QXmat4::CreateTRSMatrix(_position, _rotation, _scale);
	}

	void	Transform3D::Update(const Math::QXmat4& trsParent) const
	{
		std::vector<Transform3D>::const_iterator it;

		for (it = _childs.cbegin(); it != _childs.cend(); ++it)
			it->Update(_trs);
	}

	void	Transform3D::Translate(const Math::QXvec3& pos)
	{
		_position += pos;
		UpdateTRS();
	}

	void	Transform3D::Rotate(const Math::QXvec3& rot)
	{
		_rotation += rot;
		UpdateTRS();
	}

	void	Transform3D::Scale(const Math::QXvec3& sca)
	{
		_scale += sca;
		UpdateTRS();
	}

	void	Transform3D::AddChild(const Transform3D& child)
	{
		_childs.push_back(child);
	}

	void	Transform3D::AddChild(Transform3D&& child)
	{
		_childs.push_back(std::move(child));
	}

	#pragma region Operators

	Transform3D& Transform3D::operator=(const Transform3D& t)
	{
		_position = t._position;
		_rotation = t._rotation;
		_scale = t._scale;
		_trs = t._trs;
		_childs = t._childs;

		return *this;
	}

	Transform3D& Transform3D::operator=(Transform3D&& t)
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
#pragma endregion
}