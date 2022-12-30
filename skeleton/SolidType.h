#pragma once
#include "ColorHSV.h"
class SolidType {
public:
	Vector3 size;
	hsv colorHsv;
	Vector4 col;
	bool fade;
	bool render;
protected:
	void transformColor() {
		rgb rgbTransf = hsv2rgb(colorHsv);
		col = { rgbTransf.r,rgbTransf.g,rgbTransf.b,1.0 };
	}
};
class PWSCharacter : public SolidType {
public:
	PWSCharacter() {
		size = { 3,3,3 };
		colorHsv = { 150.0, 0.8, 0.9 };
		transformColor();
		fade = false;
		render = true;
	}
};
class Manguera1Features :public SolidType {
public:
	Manguera1Features()
	{
		size = { 0.3,0.3,0.3 };
		colorHsv = { 185.0,0.93,0.20 };
		transformColor();
		fade = true;
		render = true;
	}
};
class Manguera2Features :public SolidType {
public:
	Manguera2Features()
	{
		size = { 0.1,0.1,0.1 };
		colorHsv = { 206.0,0.50,0.30 };
		transformColor();
		fade = true;
		render = true;
	}
};
class Manguera3Features :public SolidType {
public:
	Manguera3Features()
	{
		size = { 0.5,0.5,0.5 };
		colorHsv = { 166.0,0.93,0.45 };
		transformColor();
		fade = true;
		render = true;
	}
};