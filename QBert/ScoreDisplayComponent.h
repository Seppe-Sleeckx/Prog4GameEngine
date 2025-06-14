#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "Observer.h"

namespace dae
{
	class ScoreDisplayComponent : public Component, public IObserver
	{
	public:
		//Constructor
		ScoreDisplayComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object);

		//Destructor
		virtual ~ScoreDisplayComponent() override = default;

		//Rule of 5
		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void Notify(const GameObject& game_object, const Event& event) override;

	private:
		std::unique_ptr<TextComponent> m_textComponent;
	};
}


