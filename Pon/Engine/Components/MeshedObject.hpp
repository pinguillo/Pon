#pragma once
#include "BasicComponents.hpp"

class MeshedObject {
public:
	MeshedObject() {}
	~MeshedObject() {}

	void Create() {}

	void Draw()
	{/*
		if (model != nullptr) {
			model->setScale(transform.scale);
			model->setRotation(transform.rotation);
			model->setPosition(transform.position);
			model->UpdateTransform();
			model->Draw();
		}*/
	}

	void DrawShader(ui32 sh)
	{/*
		if (model != nullptr) {
			model->setScale(transform.scale);
			model->setRotation(transform.rotation);
			model->setPosition(transform.position);
			model->UpdateTransform();
			//model->DrawShader(sh);
		}*/
	}

	/*void LoadModel(Model* _model);
	void LoadModel(const std::string& filePath);
	void LoadShader(Shader* sh);
	void LoadShader(const char* VSpath, const char* FSpath);

	Model* getModel() { return model; }*/

	Transform transform;
private:
	//Model* model{};
};