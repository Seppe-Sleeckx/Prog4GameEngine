#pragma once
class InputAction
{
public:
	InputAction() = default;
	virtual ~InputAction();
private:
	void operator() ();

};

