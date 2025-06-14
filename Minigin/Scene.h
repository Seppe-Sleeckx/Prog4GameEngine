#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;

		const std::string& GetName() { return m_name; };

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		explicit Scene(const std::string& name);

	private:
		std::string m_name;
		std::vector <std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;
	};

}
