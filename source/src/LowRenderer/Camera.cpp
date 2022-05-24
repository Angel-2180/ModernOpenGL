#include "../include/LowRenderer/Camera.h"

LowRenderer::Camera::Camera(lm::vec3 position, lm::vec3 direction, lm::vec3 WorldUp)
{
	this->viewMatrix = lm::Mat4<float>::identity;

	this->speed = 3.f;
	this->sensitivity = 15.f;

	this->worldUp = WorldUp;
	this->position = position;
	this->right = lm::vec3(0.f);
	this->up = WorldUp;

	this->pitch = 0.f;
	this->yawn = -90.f;
	this->roll = 0.f;

	this->updateCamVec();
}
void LowRenderer::Camera::updateCamVec()
{
	this->front.X() = static_cast<float>(cos(degreesToRadians(this->yawn)) * cos(degreesToRadians(this->pitch)));
	this->front.Y() = static_cast<float>(sin(degreesToRadians(this->pitch)));
	this->front.Z() = static_cast<float>(sin(degreesToRadians(this->yawn)) * cos(degreesToRadians(this->pitch)));

	this->front = this->front.normalized();
	this->right = (this->front.crossProduct(this->worldUp)).normalized();
	this->up = (this->right.crossProduct(this->front)).normalized();
}

const lm::mat4 LowRenderer::Camera::createViewMatrix()
{
	lm::mat4 tmp;
	this->updateCamVec();
	this->viewMatrix = tmp.lookAt(this->position, this->position + this->front, this->up);

	return this->viewMatrix;
}

const lm::mat4 LowRenderer::Camera::getViewMatrix() const
{
	return this->viewMatrix;
}

const lm::vec3 LowRenderer::Camera::getPosition() const
{
	return this->position;
}
const lm::vec3 LowRenderer::Camera::getFront() const
{
	return this->front;
}

void LowRenderer::Camera::updateInput(const float& delta, const double& offsetX,
	const double& offsetY)
{
	this->updateMouseInput(delta, offsetX, offsetY);
}

void LowRenderer::Camera::updateMouseInput(const float& delta, const double& offsetX,
	const double& offsetY)
{
	//update pitch yawn roll
	this->pitch += static_cast<float>(-offsetY) * this->sensitivity * delta;
	this->yawn += static_cast<float>(offsetX) * this->sensitivity * delta;

	if (this->pitch > 80.f)
	{
		this->pitch = 80.f;
	}
	else if (this->pitch < -80.f)
	{
		this->pitch = -80.f;
	}

	if (this->yawn > 360 || this->yawn < -360.f)
	{
		this->yawn = 0.f;
	}
}

void LowRenderer::Camera::move(const float& delta, const int direction)
{
	switch (direction)
	{
	case FORWARD:
		this->position += this->front * delta * this->speed;
		break;
	case BACKWARD:
		this->position -= this->front * delta * this->speed;
		break;
	case LEFT:
		this->position -= this->right * delta * this->speed;
		break;
	case RIGHT:
		this->position += this->right * delta * this->speed;
		break;
	default:
		break;
	}
}