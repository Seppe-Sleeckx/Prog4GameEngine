#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

Texture2DRenderer::Texture2DRenderer(std::shared_ptr<GameObject> gameObject) :Component(gameObject), 
	m_srcRect{ std::make_unique<SDL_Rect>()}
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

	//texures get rendered around their center (not top left)
	auto pos = GetOwner()->GetWorldTransform().GetPosition();
	if (m_srcRect->w <= 0 || m_srcRect->h <= 0)
	{
		auto xScale = GetOwner()->GetWorldTransform().GetScale().x;
		auto yScale = GetOwner()->GetWorldTransform().GetScale().y;
		pos.x -= (xScale * m_texture->GetSize().x)/ 2.f;
		pos.y -= (yScale * m_texture->GetSize().y)     / 2.f;
		pos.x *= GetOwner()->GetWorldTransform().GetScale().x;
		pos.y *= GetOwner()->GetWorldTransform().GetScale().y;
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
	else
	{
		auto xScale = GetOwner()->GetWorldTransform().GetScale().x;
		auto yScale = GetOwner()->GetWorldTransform().GetScale().y;
		pos.x -= (xScale * m_srcRect->w)/2.f;
		pos.y -= (yScale * m_srcRect->h)/2.f;
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, *m_srcRect, xScale, yScale);
	}
}

void Texture2DRenderer::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void Texture2DRenderer::SetSrcRect(const SDL_Rect& src_rect)
{
	*m_srcRect = src_rect;
}