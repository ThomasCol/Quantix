#include "Core/Components/Camera.h"
#include "MathDefines.h"

namespace Quantix::Core::Components
{
	Camera::Camera():
		_pos(Math::QXvec3(0,0,0)), _dir(Math::QXvec3(0, 0, 1)), _up(Math::QXvec3(0, 1, 0)), _angle(Math::QXvec3(0, 0, 0))
	{
	}

	Camera::Camera(Math::QXvec3 pos, Math::QXvec3 dir, Math::QXvec3 up) :
		_pos(pos),
		_dir(dir),
		_up(up),
		_angle(Math::QXvec3(0, 0, 0)),
		_lookAt { Math::QXmat4::CreateLookAtMatrix(_pos, _pos + _dir, _up) }
	{
	}

	Camera::Camera(const Camera& camera)
	{
		_pos = camera._pos;
		_dir = camera._dir;
		_up = camera._up;
		_angle = camera._angle;
	}

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

		Rotate(rotDir * (float)frameTime * 0.005f);//SENSIBILITY);
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