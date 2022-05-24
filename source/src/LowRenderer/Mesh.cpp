#include "../include/LowRenderer/Mesh.h"

void LowRenderer::Mesh::updateModelMatrix()
{
	this->modelMat = lm::Mat4<float>::createTransformMatrix(this->rotation, this->postion, this->scale);
}

lm::mat4 LowRenderer::Mesh::calculateMVP(lm::Mat4<float> view)
{
	this->projectionMat = lm::mat4::perspectiveProjection(90, 800 / 600, 0.1f, 100.f);
	this->viewMat = view;
	this->mvp = projectionMat * viewMat * modelMat;

	return this->mvp;
}

LowRenderer::Mesh::Mesh(Resources::Model* model, lm::Vec3<float> position, lm::Vec3<float> rotation, lm::Vec3<float> scale, Resources::Texture* texture)
{
	this->postion = position;
	this->rotation = rotation;
	this->scale = scale;
	this->texture = texture;
	this->model = model;
	updateModelMatrix();
}

void LowRenderer::Mesh::updateUniform(Resources::Shader* shader, Camera& cam)
{
	shader->setMat4f(this->calculateMVP(cam.createViewMatrix()), "MVP");
	shader->setVec3f(cam.getPosition(), "viewPos");
	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	lm::mat4 tmp2 = this->modelMat;
	shader->setMat4f(tmp2, "model");
	lm::mat3 tmp = this->modelMat;
	(tmp.inverse()).transpose();
	shader->setMat3f(tmp, "normalMatrix");

	shader->setFloat("material.shininess", 32.0f);
}