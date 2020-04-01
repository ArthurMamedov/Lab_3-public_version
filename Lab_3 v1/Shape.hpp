#ifndef __Shape
#define __Shape
#include<string>
#include<Windows.h>
#include<gdiplus.h>
#include<iostream>
#include<fstream>
#include"vector.hpp"

using namespace Gdiplus;
using namespace std;
using namespace KoSTL;

enum shapes {
	square = 1,
	circle = 2,
	triangle = 3,
	rectangle = 4,
	dot = 5,
	line = 6,
	ellipse = 7,
	star = 8,
	agregate = 9
};

class Shape abstract {
protected:
	const Color BG = Color(255, 12, 12, 12);
	Graphics* Graph;
	Color color, DefaultColor;
	bool ShowTrace, DefaultShowTrace;
	KoSTL::vector<Point> Trace;
	bool enabled = false;
	virtual void HideTrace();
	virtual void DrawTrace();
	virtual void Hide();
	virtual void Draw() abstract;
	virtual bool IsMovePossible(int dx, int dy, bool mode) abstract;
	virtual void _move(int dx, int dy, bool mode) abstract;
	virtual bool IsScalePossible(double coefficient) abstract;
	virtual void _scale(double coefficient) abstract;
	Shape(Graphics& graphics, Color color, bool trace, Color defaultColor, bool defaultTrace, bool enable);
	virtual void SetDefaults() abstract;
	friend class Displayer;
	friend class cAgregate;
public:
	Shape() = default;
	Shape(Graphics& graphics, Color color, bool trace);
	virtual void Enable();
	virtual void Disable();
	virtual Point GetCenter() abstract;
	virtual void SwitchTrace(bool switcher);
	virtual void ChangeColor(Color newColor);
	virtual void Move(int dx, int dy, bool mode = false);
	virtual void Scale(double coefficient);
	virtual void Reset() abstract;
	virtual void Write(ofstream& file);
	__declspec(property(get = GetCenter)) Point Center;
};
#endif