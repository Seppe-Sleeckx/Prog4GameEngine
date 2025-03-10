#pragma once
#include <numeric>

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform;
	int ID;
};

class GameObject3DAlt
{
public:
	~GameObject3DAlt()
	{
		delete ptransform;
	}

	Transform* ptransform = new Transform();
	int ID;
};

#define MAX_STEP_SIZE 1024
class TrashTheCache
{
public:
	void Setup();
	void Update();
	void RunIntegerTest(int sampleSize);
	void RunGameObjectTest(int sampleSize);
	void RunGameObjectAltTest(int sampleSize);

private:
	float* m_pIntegerResultsArr = new float[(int)log2(MAX_STEP_SIZE) + 1];
	float* m_pGameObjectResultsArr = new float[(int)log2(MAX_STEP_SIZE) + 1];
	float* m_pGameObjectAltResultArr = new float[(int)log2(MAX_STEP_SIZE) + 1];
};

