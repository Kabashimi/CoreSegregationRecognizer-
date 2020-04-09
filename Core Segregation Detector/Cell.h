#pragma once

ref class Cell
{
public:
	Cell();
	~Cell();

	float x, y;
	float xSpan, ySpan;
	float value;
	bool active;
	bool automatonActive;
	double distanceToCenter;

	void setDistanceToCenter(double);
};

