#include "Core/Components/Camera.h"
#include "Core/DataStructure/GameComponent.h"
#include "MathDefines.h"

#define SENSIBILITY 0.0025

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Core::Components::Camera>("Camera")
	.constructor<>()
	.constructor<const Math::QXvec3&, const Math::QXvec3&, const Math::QXvec3&>()
	.constructor<Quantix::Core::DataStructure::GameComponent*>()
	.constructor<const Quantix::Core::Components::Camera&>()
	.constructor<Quantix::Core::Components::Camera&&>()
	.method("Init", &Quantix::Core::Components::Camera::Init)
	.method("UpdateLookAt", &Quantix::Core::Components::Camera::UpdateLookAt)
	.method("ChangeView", &Quantix::Core::Components::Camera::ChangeView)
	.method("Rotate", &Quantix::Core::Components::Camera::Rotate)
	.method("GetLookAt", &Quantix::Core::Components::Camera::GetLookAt)
	.method("SetPos", &Quantix::Core::Components::Camera::SetPos)
	.method("GetPos", &Quantix::Core::Components::Camera::GetPos)
	.method("GetDir", &Quantix::Core::Components::Camera::GetDir)
	.method("GetUp", &Quantix::Core::Components::Camera::GetUp);
}

namespace Quantix::Core::Components
{
	Camera::Camera():
		_pos(Math::QXvec3(0,0,0)), _dir(Math::QXvec3(0, 0, 1)), _up(Math::QXvec3(0, 1, 0)), _angle(Math::QXvec3(0, 0, 0))
	{
	}

	Camera::Camera(const Math::QXvec3& pos, const Math::QXvec3& dir, const Math::QXvec3& up) :
		_pos(pos),
		_dir(dir),
		_up(up),
		_angle(Math::QXvec3(0, 0, 0)),
		_lookAt { Math::QXmat4::CreateLookAtMatrix(_pos, _pos + _dir, _up) }
	{
	}

	Camera::Camera(Core::DataStructure::GameComponent* object) :
		Quantix::Core::DataStructure::Component(object)
	{
	}

	Camera::Camera(const Camera& camera)
	{
		_pos = camera._pos;
		_dir = camera._dir;
		_up = camera._up;
		_angle = camera._angle;
	}

	Camera::Camera(Camera&& camera):
		Component(camera),
		_up{ std::move(camera._up) },
		_pos{ std::move(camera._pos) },
		_dir{ std::move(camera._dir) },
		_angle{ std::move(camera._angle) },
		_lookAt{ std::move(camera._lookAt) }
	{}

	void			Camera::Init(Math::QXvec3 pos, Math::QXvec3 dir, Math::QXvec3 up)
	{
		_pos = pos;
		_dir = dir;
		_up = up;
		_angle = Math::QXvec3(0, 0, 0);
	}

	void	Camera::UpdateLookAt(Math::QXvec3 pos)
	{
		_pos = pos;
		_lookAt = Math::QXmat4::CreateLookAtMatrix(_pos, _pos + _dir, _up);
	}

	void			Camera::ChangeView(int posX, int posY, int width, int height, double frameTime)
	{
		int x = posX - (int)(width * 0.5f);
		int y = posY - (int)(height * 0.5f);

		Math::QXvec3	rotDir{ (float)-y, (float)-x, 0.f };

		Rotate(rotDir * (float)frameTime * SENSIBILITY);
	}

	void			Camera::Rotate(Math::QXvec3 rotate)
	{
		_angle += rotate;

		if (_angle.x > (float)Q_PI / 3.f)
			_angle.x = (float)Q_PI / 3.f;
		if (_angle.x < (float)(-Q_PI) / 3.f)
			_angle.x = (float)(-Q_PI) / 3.f;

		_dir.z = cos(_angle.x) * cos(_angle.y);
		_dir.y = sin(_angle.x);
		_dir.x = cos(_angle.x) * sin(_angle.y);
	}
}