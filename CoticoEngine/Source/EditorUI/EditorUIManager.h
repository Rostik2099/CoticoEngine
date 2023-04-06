#pragma once
#include<ImGUI/imgui.h>
#include<ImGUI/imgui_impl_glfw.h>
#include<ImGUI/imgui_impl_opengl3.h>
#include<vector>

#include"EditorUI/ImGUILayer.h"

class EditorUIManager
{
public:
	void Render();

	static EditorUIManager* GetUIManager()
	{
		static EditorUIManager manager;
		return &manager;
	};

	void SetCustomColors();

	template<typename T>
	T* CreateNewLayer() 
	{
		T* newLayer = new T;
		layers.push_back(newLayer);
		return newLayer;
	};

private:
	EditorUIManager() 
	{
		SetCustomColors();
	};

	std::vector<ImGUILayer*> layers;
};
