#pragma once
#include <memory>
#include "GameObject.h"
#include "Piramid.h"
namespace qbert
{
	class QbertState
	{
	public:
		QbertState(std::weak_ptr<dae::GameObject> pQbertObject, std::weak_ptr<Piramid> pPiramid) : m_pQbertObject{ std::move(pQbertObject) }, m_pPiramid{ std::move(pPiramid) } {};
		virtual ~QbertState() = default;

		//Rule of 5
		QbertState(const QbertState& other) = delete;
		QbertState(QbertState&& other) = delete;
		QbertState& operator=(const QbertState& other) = delete;
		QbertState& operator=(QbertState&& other) = delete;

		virtual void OnEnter() = 0;
		virtual std::unique_ptr<QbertState> Update() = 0;
		virtual std::unique_ptr<QbertState> FixedUpdate() = 0;

		std::weak_ptr<qbert::Piramid> GetPiramid() { return m_pPiramid; }



		enum class QbertStateType
		{
			Static,
			Moving,
			Falling,
			Teleporter
		};

		virtual QbertStateType GetType() = 0;

	protected:
		std::weak_ptr<dae::GameObject> m_pQbertObject;
		std::weak_ptr<qbert::Piramid> m_pPiramid;
	};
}