#pragma once

class gObject {
public:
	virtual void Create() {}
	virtual void Step() {}
	virtual void Draw() {}
};

class Controller : public gObject {
public:
	Controller() {}
	~Controller() {}

	virtual void Create() override {}
	virtual void Step() override {}
	virtual void Draw() override {}
};