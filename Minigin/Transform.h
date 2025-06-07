#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		//Constructor
		Transform() = default;

		//Destructor
		~Transform() = default;

		//Rule of 5
		Transform(const Transform& other) = default;
		Transform(Transform&& other) = default;
		Transform& operator=(const Transform& other) = default;
		Transform& operator=(Transform&& other) = default;

		static Transform Origin();

		const Transform& Combine(const Transform& parentWorldTransform);

		//POSITION
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& position);

		//ROTATION
		const glm::vec3& GetRotation() const { return m_rotation; }
		void SetRotation(float x, float y, float z);
		void SetRotation(const glm::vec3& rotation);

		//SCALE
		const glm::vec3& GetScale() const { return m_scale; }
		void SetScale(float x, float y, float z);
		void SetScale(const glm::vec3& scale);

		//Operator overloading
		Transform operator-(const Transform& rhs);
	private:
		glm::vec3 m_position{};
		glm::vec3 m_rotation{};
		glm::vec3 m_scale{};
	};
}
