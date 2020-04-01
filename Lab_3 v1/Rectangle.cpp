#include<iostream>
#include"Rectangle.hpp"
cRectangle::cRectangle(Graphics& graph, int x, int y, int width, int height, Color color, bool trace) :
	Shape(graph, color, trace) {
	DefaultUpLeftX = UpLeftX = x;
	DefaultUpLeftY = UpLeftY = y;
	DefaultWidth = Width = width;
	DefaultHeight = Height = height;
}

Point cRectangle::GetCenter() {
	return Point(UpLeftX + Width / 2, UpLeftY + Height / 2);
}

void cRectangle::Write(ofstream& file) {
	file << rectangle << ' ' << UpLeftX << ' ' << UpLeftY << ' ' << Width << ' ' << Height << ' ' 
		<< DefaultUpLeftX << ' ' << DefaultUpLeftY << ' ' << DefaultWidth << ' ' << DefaultHeight;
	Shape::Write(file);
}

bool cRectangle::IsMovePossible(int dx, int dy, bool mode) {
	if (!mode)
		return UpLeftX + dx + Width < 767 and UpLeftY + dy + Height < 431 and UpLeftX + dx > 0 and UpLeftY + dy > 0;
	else
		return dx > 0 and dx + Width < 767 and dy > 0 and dy + Height < 431;
}

void cRectangle::_move(int dx, int dy, bool mode) {
	if (ShowTrace and Trace.empty())
		Trace.push_back(Center);
	Hide();
	if (!mode) {
		UpLeftX += dx;
		UpLeftY += dy;
	}
	else {
		UpLeftX = dx;
		UpLeftY = dy;
	}
	if (ShowTrace)
		Trace.push_back(Center);
	Draw();
	if (ShowTrace)
		DrawTrace();
}

bool cRectangle::IsScalePossible(double coefficient) {
	bool IsPossible = true;
	const auto offsetX = UpLeftX + (Width / 2);
	const auto offsetY = UpLeftY + (Height / 2);
	const auto X = offsetX - (offsetX * coefficient);
	const auto Y = offsetY - (offsetY * coefficient);
	const auto UpRightX = UpLeftX + Width;
	const auto DownLeftY = UpLeftY + Height;
	if (coefficient > 1)
		IsPossible = UpRightX * coefficient + X < 767 and UpLeftX * coefficient + X > 0 and
		DownLeftY * coefficient + Y < 431 and UpLeftY * coefficient + Y > 0;
	else
		IsPossible = IsPossible and Width * coefficient > 7 and Height * coefficient > 7;
	return IsPossible;
}

void cRectangle::_scale(double coefficient) {
	Hide();
	int SaveWidth = Width, SaveHeight = Height;
	Width = static_cast<int>(Width * coefficient);
	Height = static_cast<int>(Height * coefficient);
	_move(UpLeftX + (SaveWidth - Width) / 2, UpLeftY + (SaveHeight - Height) / 2, true);
}

void cRectangle::Draw() {
	Graph->FillRectangle(&SolidBrush(color), UpLeftX, UpLeftY, Width, Height);
}

void cRectangle::SetDefaults() {
	DefaultUpLeftX = UpLeftX;
	DefaultUpLeftY = UpLeftY;
	DefaultWidth = Width;
	DefaultHeight = Height;
}

cRectangle::cRectangle(Graphics& graph, int x, int y, int width, int height, Color color, bool trace,
	int defaultX, int defaultY, int defaultWidth, int defaultHeight, Color defaultColor, bool defaultTrace, bool enable) :
	Shape(graph, color, trace, defaultColor, defaultTrace, enable) {
	UpLeftX = x; UpLeftY = y;
	DefaultUpLeftX = defaultX; DefaultUpLeftY = defaultY;
	Width = width; Height = height;
	DefaultWidth = defaultWidth; DefaultHeight = defaultHeight;
}

void cRectangle::Reset() {
	enabled = true;
	Hide();
	UpLeftX = DefaultUpLeftX;
	UpLeftY = DefaultUpLeftY;
	color = DefaultColor;
	Width = DefaultWidth;
	Height = DefaultHeight;
	SwitchTrace(false);
	Draw();
	SwitchTrace(DefaultShowTrace);
}