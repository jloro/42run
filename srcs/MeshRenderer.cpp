#include "MeshRenderer.hpp"
#include "gtc/matrix_transform.hpp"
#include <iostream>
#include "stb_image.h"
#include <cstdlib>
#include <time.h>
#include "glm.hpp"
#include <gtc/random.hpp>
#include "Engine.hpp"


MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, bool render) : Renderer(shader), _model(model), _render(render)
{
    transform = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)};
	InitCollider(_model->GetMin(), _model->GetMax(), glm::vec3(1.0f));
    UpdateMatrix();
}
MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, const Transform &trans, bool render) : Renderer(shader, trans), _model(model), _render(render)
{
	InitCollider(_model->GetMin(), _model->GetMax(), glm::vec3(1.0f));
    UpdateMatrix();
}
void        MeshRenderer::Draw(void) const
{
	if (_render)
	{
		if (_shader == nullptr)
		{
			std::cout << "MeshRenderer : Cannot Draw with whitout shader" << std::endl;
			return;
		}
		_shader->use();
		_shader->setMat4("view", Camera::instance->GetMatView());
		_shader->setMat4("projection", Camera::instance->GetMatProj());
		_shader->setMat4("model", _modelMatrix);
		_model->Draw(_shader);
		_shaderCollider->use();
		_shaderCollider->setMat4("view", Camera::instance->GetMatView());
		_shaderCollider->setMat4("projection", Camera::instance->GetMatProj());
		_shaderCollider->setMat4("model", _modelMatrixCollider);
		DrawCollider();
	}
}

MeshRenderer::MeshRenderer(MeshRenderer const & src) : Renderer(src._shader, src.transform)
{
	_model = src._model;
}

MeshRenderer::~MeshRenderer(void) {}

MeshRenderer &	MeshRenderer::operator=(MeshRenderer const & rhs)
{
    this->_model = rhs._model;
    this->_shader = rhs._shader;
    this->transform = rhs.transform;
    UpdateMatrix();
    return *this;
}

void MeshRenderer::Destroy(void)
{
	Engine42::Engine::Destroy(std::shared_ptr<MeshRenderer>(this));
}

bool				MeshRenderer::IsRender() const { return _render; }
void				MeshRenderer::SetRender(bool render) { _render = render; }
