#include "SkyboxRenderer.hpp"

#include <stdio.h>

#include "util/MeshUtil.hpp"

constexpr float xUnit = 1.f / 4.f;
constexpr float yUnit = 1.f / 3.f;

SkyboxRenderer::SkyboxRenderer()
{
	MeshData data;

	//Front face
	MeshUtil::pushFace(data, 
		glm::vec3(-1, 1, -1) * skyboxSize,
		glm::vec3(2, 0, 0) * skyboxSize,
		glm::vec3(0, -2, 0) * skyboxSize,
		glm::vec2(1 * xUnit, 1 * yUnit),
		glm::vec2(xUnit, yUnit),
		1.f);

	//Right face 
	MeshUtil::pushFace(data, 
		glm::vec3(1, 1, -1) * skyboxSize,
		glm::vec3(0, 0, 2) * skyboxSize,
		glm::vec3(0, -2, 0) * skyboxSize,
		glm::vec2(2 * xUnit, 1 * yUnit),
		glm::vec2(xUnit, yUnit),
		1.f);
	//Back face 
	MeshUtil::pushFace(data, 
		glm::vec3(1, 1, 1) * skyboxSize,
		glm::vec3(-2, 0, 0) * skyboxSize,
		glm::vec3(0, -2, 0) * skyboxSize,
		glm::vec2(3 * xUnit, 1 * yUnit),
		glm::vec2(xUnit, yUnit),
		1.f);
	//Left face 
	MeshUtil::pushFace(data, 
		glm::vec3(-1, 1, 1) * skyboxSize,
		glm::vec3(0, 0, -2) * skyboxSize,
		glm::vec3(0, -2, 0) * skyboxSize,
		glm::vec2(0, 1 * yUnit),
		glm::vec2(xUnit, yUnit),
		1.f);
	//Top face 
	MeshUtil::pushFace(data, 
		glm::vec3(-1, 1, 1) * skyboxSize,
		glm::vec3(2, 0, 0) * skyboxSize,
		glm::vec3(0, 0, -2) * skyboxSize,
		glm::vec2(1 * xUnit, 0),
		glm::vec2(xUnit, yUnit),
		1.f);
	//Bottom face 
	MeshUtil::pushFace(data, 
		glm::vec3(-1, -1, -1) * skyboxSize,
		glm::vec3(2, 0, 0) * skyboxSize,
		glm::vec3(0, 0, 2) * skyboxSize,
		glm::vec2(1 * xUnit, 2 * yUnit),
		glm::vec2(xUnit, yUnit),
		1.f);

	m_texture = TextureManager::get().getTexture("skybox.png");

	m_skybox.create(data);
}

void SkyboxRenderer::render(glm::mat4& transform)
{
	m_texture->bind();


	m_skybox.bind();

	glDrawElements(GL_TRIANGLES, m_skybox.getIndicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	m_texture->unBind();
}
