#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

Texture2DRenderer::Texture2DRenderer(std::shared_ptr<GameObject> gameObject) :Component(gameObject)
{
}

Texture2DRenderer::~Texture2DRenderer()
{
	m_texture.reset();
}

void Texture2DRenderer::Render() const
{
	if (!m_texture)
		return;

	const auto& pos = GetOwner()->GetWorldTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

}

void Texture2DRenderer::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
