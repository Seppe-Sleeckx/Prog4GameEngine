#include "TrashTheCache.h"
#include <chrono>
#include <vector>
#include "imgui.h"

void TrashTheCache::Update()
{
	//Excercise 2
	// ******
	//Setup
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	bool windowActive = true;
	ImGui::Begin("Excercise 2", &windowActive, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	//Elements
	static int samplesAmount;
	if (ImGui::Button("-")) samplesAmount = (samplesAmount > 1) ? samplesAmount - 1 : 1;
	ImGui::SameLine();
	ImGui::Text("%d", samplesAmount);
	ImGui::SameLine();
	if (ImGui::Button("+")) samplesAmount++;

	if (ImGui::Button("Trash the cache"))
	{
		RunIntegerTest(samplesAmount);
	}
}

void TrashTheCache::RunIntegerTest(int sampleSize)
{
	const int bufferSize = (int)std::pow(2, 26);
	int* buffer = new int[bufferSize] {};

	//constexpr int sampleSize = 3;
	constexpr int maxStepSize = 1024;

	if (sampleSize <= 2)
		return;

	float* elapsedAverageTimes = new float[(int)std::log2(maxStepSize) + 1];

	for (int stepsize = 1; stepsize <= maxStepSize; stepsize *= 2)
	{
		//Run tests
		//*****
		float* elapsedTempTimes = new float[sampleSize];
		for (int sampleNumber = 0; sampleNumber < sampleSize; sampleNumber++)
		{
			auto begin = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += stepsize)
			{
				buffer[i] *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			//std::cout << "operation took: " << elapsedTime / 1000.f << "ms" << std::endl;
			elapsedTempTimes[sampleNumber] = (float)elapsedTime;
		}


		//Calculate average results
		//*****
		float minVal = std::numeric_limits<float>::max();
		float maxVal = std::numeric_limits<float>::lowest();;

		//Calculate highest and lowest values
		for (int elapsedTempTimesIdx = 0; elapsedTempTimesIdx < sampleSize; elapsedTempTimesIdx++)
		{
			if (elapsedTempTimes[elapsedTempTimesIdx] < minVal) minVal = elapsedTempTimes[elapsedTempTimesIdx];
			if (elapsedTempTimes[elapsedTempTimesIdx] > maxVal) maxVal = elapsedTempTimes[elapsedTempTimesIdx];
		}

		bool minExcluded = false;
		bool maxExcluded = false;
		float sum = 0.f;
		//compute sum of every number except minVal and maxVal
		for (int elapsedTempTimesIdx = 0; elapsedTempTimesIdx < sampleSize; elapsedTempTimesIdx++)
		{
			if (elapsedTempTimes[elapsedTempTimesIdx] == minVal && !minExcluded)
				minExcluded = true;
			else if (elapsedTempTimes[elapsedTempTimesIdx] == maxVal && !maxExcluded)
				maxExcluded = true;
			else
				sum += elapsedTempTimes[elapsedTempTimesIdx];
		}

		elapsedAverageTimes[(int)std::log2(stepsize)] = sum / (sampleSize - 2);
		//std::cout << "Average Time with stepsize " << stepsize << " is: " << elapsedAverageTimes[(int)std::log2(stepsize)] / 1000.f << " ms\n";
		delete[] elapsedTempTimes;
	}

	for (int i = 0; i < (int)std::log2(maxStepSize)+1; i++)
	{
		m_pIntegerResultsArr[i] = elapsedAverageTimes[i];
	}

	delete[] buffer;
	delete[] elapsedAverageTimes;
}

void TrashTheCache::RunGameObjectTest(int sampleSize)
{
	const int bufferSize = (int)std::pow(2, 26);
	GameObject3D* buffer = new GameObject3D[bufferSize]{};

	//constexpr int sampleSize = 30;
	constexpr int maxStepSize = 1024;

	if (sampleSize <= 2)
		return;

	float* elapsedAverageTimes = new float[(int)std::log2(maxStepSize) + 1];

	for (int stepsize = 1; stepsize <= maxStepSize; stepsize *= 2)
	{
		//Run tests
		//*****
		float* elapsedTempTimes = new float[sampleSize];
		for (int sampleNumber = 0; sampleNumber < sampleSize; sampleNumber++)
		{
			auto begin = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += stepsize)
			{
				buffer[i].ID *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			//std::cout << "operation took: " << elapsedTime / 1000.f << "ms" << std::endl;
			elapsedTempTimes[sampleNumber] = (float)elapsedTime;
		}


		//Calculate average results
		//*****
		float minVal = std::numeric_limits<float>::max();
		float maxVal = std::numeric_limits<float>::lowest();;

		//Calculate highest and lowest values
		for (int elapsedTempTimesIdx = 0; elapsedTempTimesIdx < sampleSize; elapsedTempTimesIdx++)
		{
			if (elapsedTempTimes[elapsedTempTimesIdx] < minVal) minVal = elapsedTempTimes[elapsedTempTimesIdx];
			if (elapsedTempTimes[elapsedTempTimesIdx] > maxVal) maxVal = elapsedTempTimes[elapsedTempTimesIdx];
		}

		bool minExcluded = false;
		bool maxExcluded = false;
		float sum = 0.f;
		//compute sum of every number except minVal and maxVal
		for (int elapsedTempTimesIdx = 0; elapsedTempTimesIdx < sampleSize; elapsedTempTimesIdx++)
		{
			if (elapsedTempTimes[elapsedTempTimesIdx] == minVal && !minExcluded)
				minExcluded = true;
			else if (elapsedTempTimes[elapsedTempTimesIdx] == maxVal && !maxExcluded)
				maxExcluded = true;
			else
				sum += elapsedTempTimes[elapsedTempTimesIdx];
		}

		elapsedAverageTimes[(int)std::log2(stepsize)] = sum / (sampleSize - 2);
		//std::cout << "Average Time with stepsize " << stepsize << " is: " << elapsedAverageTimes[(int)std::log2(stepsize)] / 1000.f << " ms\n";
		delete[] elapsedTempTimes;
	}

	for (int i = 0; i < (int)std::log2(sampleSize) + 1; i++)
	{
		m_pGameObjectResultsArr[i] = elapsedAverageTimes[i];
	}

	delete[] buffer;
	delete[] elapsedAverageTimes;
}

void TrashTheCache::RunGameObjectAltTest(int sampleSize)
{
	const int bufferSize = (int)std::pow(2, 26);
	GameObject3DAlt* buffer = new GameObject3DAlt[bufferSize]{};

	//constexpr int sampleSize = 30;
	constexpr int maxStepSize = 1024;

	if (sampleSize <= 2)
		return;

	float* elapsedAverageTimes = new float[(int)std::log2(maxStepSize) + 1];

	for (int stepsize = 1; stepsize <= maxStepSize; stepsize *= 2)
	{
		//Run tests
		//*****
		float* elapsedTempTimes = new float[sampleSize];
		for (int sampleNumber = 0; sampleNumber < sampleSize; sampleNumber++)
		{
			auto begin = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += stepsize)
			{
				buffer[i].ID *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			//std::cout << "operation took: " << elapsedTime / 1000.f << "ms" << std::endl;
			elapsedTempTimes[sampleNumber] = (float)elapsedTime;
		}


		//Calculate average results
		//*****
		float minVal = std::numeric_limits<float>::max();
		float maxVal = std::numeric_limits<float>::lowest();;

		//Calculate highest and lowest values
		for (int elapsedTempTimesIdx = 0; elapsedTempTimesIdx < sampleSize; elapsedTempTimesIdx++)
		{
			if (elapsedTempTimes[elapsedTempTimesIdx] < minVal) minVal = elapsedTempTimes[elapsedTempTimesIdx];
			if (elapsedTempTimes[elapsedTempTimesIdx] > maxVal) maxVal = elapsedTempTimes[elapsedTempTimesIdx];
		}

		bool minExcluded = false;
		bool maxExcluded = false;
		float sum = 0.f;
		//compute sum of every number except minVal and maxVal
		for (int elapsedTempTimesIdx = 0; elapsedTempTimesIdx < sampleSize; elapsedTempTimesIdx++)
		{
			if (elapsedTempTimes[elapsedTempTimesIdx] == minVal && !minExcluded)
				minExcluded = true;
			else if (elapsedTempTimes[elapsedTempTimesIdx] == maxVal && !maxExcluded)
				maxExcluded = true;
			else
				sum += elapsedTempTimes[elapsedTempTimesIdx];
		}

		elapsedAverageTimes[(int)std::log2(stepsize)] = sum / (sampleSize - 2);
		//std::cout << "Average Time with stepsize " << stepsize << " is: " << elapsedAverageTimes[(int)std::log2(stepsize)] / 1000.f << " ms\n";
		delete[] elapsedTempTimes;
	}

	for (int i = 0; i < (int)std::log2(sampleSize) + 1; i++)
	{
		m_pGameObjectAltResultArr[i] = elapsedAverageTimes[i];
	}

	delete[] buffer;
	delete[] elapsedAverageTimes;
}