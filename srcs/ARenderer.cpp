#include "ARenderer.hpp"

ARenderer::ARenderer() : AComponent(), _shader(nullptr) {}
ARenderer::ARenderer(std::shared_ptr<GameObject> obj) : AComponent(obj.get()), _shader(nullptr) {}
ARenderer::ARenderer(std::shared_ptr<Shader>  shader, std::shared_ptr<GameObject> obj) : AComponent(obj.get()), _shader(shader) { }
ARenderer::ARenderer(std::shared_ptr<Shader>  shader, GameObject *obj) : AComponent(obj), _shader(shader) {  }
ARenderer::~ARenderer() {}

std::shared_ptr<Shader> ARenderer::GetShader(void) const { return _shader;}
void                    ARenderer::SetShader(std::shared_ptr<Shader>  shader) {_shader = shader;}
void	ARenderer::InitCollider(glm::vec3 min, glm::vec3 max, glm::vec3 scale)
{
	scaleCollider = scale;
	this->min = min;
	this->max = max;
	std::vector<float>	vertices = {
		min.x, min.y, max.z,
		max.x, min.y, max.z,
		min.x, max.y, max.z,
		max.x, max.y, max.z,
		min.x, max.y, min.z,
		max.x, max.y, min.z,
		min.x, min.y, min.z,
		max.x, min.y, min.z
	};
	std::vector<unsigned int> faces {
		0, 1, 2,
			2, 1, 3,
			2, 3, 4,
			4, 3, 5,
			4, 5, 6,
			6, 5, 7,
			6, 7, 0,
			0, 7, 1,
			1, 7, 3,
			3, 7, 5,
			6, 0, 4,
			4, 0, 2
	};
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Collider.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	_shaderCollider.reset(new Shader(shadersPath, type));
	std::vector<Vertex> finalVertices;
	for (int i = 0; i < 8; i++)
	{
		Vertex v;
		v.position = glm::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
		finalVertices.push_back(v);
	}
	std::vector<Texture> p;
	_meshCollider.reset(new Mesh(finalVertices, faces, p));
	_meshCollider->SendToOpenGL();
}

void	ARenderer::DrawCollider() const
{
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_meshCollider->Draw(_shaderCollider);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
}
