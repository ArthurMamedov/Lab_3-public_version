#include "Dot.hpp"

bool cDot::IsMovePossible(int dx, int dy, bool mode) {
	if (!mode)
		return X + dx + 5 < 767 and Y + dy + 5 < 431 and X + dx - 5 > 0 and Y + dy - 5 > 0;
	else
		return dx - 5 > 0 and dx + 5 < 767 and dy - 5 > 0 and dy + 5 < 431;
}

void cDot::_move(int dx, int dy, bool mode) {
	if (ShowTrace and Trace.empty())
		Trace.push_back(Center);
	Hide();
	if (!mode) {
		X += dx;
		Y += dy;
	}
	else {
		X = dx;
		Y = dy;
	}
	if (ShowTrace)
		Trace.push_back(Center);
	Draw();
	if (ShowTrace)
		DrawTrace();
}

bool cDot::IsScalePossible(double coefficient) {
	return true;
}

void cDot::_scale(double coefficient) {
	return;
}

void cDot::Draw() {
	Graph->FillEllipse(&SolidBrush(color), X-5, Y-5, 10, 10);
}

void cDot::SetDefaults() {
	DefaultX = X;
	DefaultY = Y;
}

cDot::cDot(Graphics& graphics, int x, int y, Color color, bool trace, int defaultX, int defaultY, Color defaultColor, bool defaultTrace, bool enable):
	Shape(graphics, color, trace, defaultColor, defaultTrace, enable) {
	DefaultX = defaultX; X = x;
	DefaultY = defaultY; Y = y;
}

cDot::cDot(Graphics& graphics, int x, int y, Color color, bool trace) : Shape(graphics, color, trace) {
	DefaultX = X = x;
	DefaultY = Y = y;
}

void cDot::Scale(double coefficient) {
	return;
}

void cDot::Write(ofstream& file) {
	file << dot << ' ' << X << ' ' << Y << ' ' 
		<< DefaultX << ' ' << DefaultY;
	Shape::Write(file);
}

Point cDot::GetCenter() {
	return Point(X, Y);
}

void cDot::Reset() {
	enabled = true;
	Hide();
	X = DefaultX;
	Y = DefaultY;
	color = DefaultColor;
	SwitchTrace(false);
	Draw();
	SwitchTrace(DefaultShowTrace);
}
