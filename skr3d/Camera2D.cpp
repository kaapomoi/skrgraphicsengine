#include "Camera2D.h"
namespace skrengine
{
	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(800),
		_screenHeight(800)
	{
		
	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(_cameraMatrix, scale);

			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
	{
		//Invert Y direction
		screenCoords.y = _screenHeight - screenCoords.y;
		//0 is center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		// scale coords
		screenCoords /= _scale;
		// Translate with the camera pos
		screenCoords += _position;
		return screenCoords; 
	}
}