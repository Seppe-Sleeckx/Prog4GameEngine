#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

Texture2DRenderer::Texture2DRenderer(std::shared_ptr<GameObject> gameObject) :Component(gameObject), 
	m_srcRect{ SDL_Rect{} }
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
	if(m_srcRect.w <= 0|| m_srcRect.h <= 0)
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	else
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_srcRect);
}

void Texture2DRenderer::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void Texture2DRenderer::SetSrcRect(const SDL_Rect& src_rect)
{
	m_srcRect = src_rect;
}