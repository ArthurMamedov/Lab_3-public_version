#include "Line.hpp"

void cLine::Draw() {
	Graph->FillEllipse(&SolidBrush(color), StartX - 5, StartY - 5, 10, 10);
	Graph->DrawLine(&Pen(color), StartX, StartY, EndX, EndY);
	Graph->FillEllipse(&SolidBrush(color), EndX - 5, EndY - 5, 10, 10);
}

bool cLine::IsMovePossible(int dx, int dy, bool mode) {
	if (!mode)
		return StartX + dx + 5 < 767 and StartY + dy + 5 < 431 and StartX + dx - 5 > 0 and StartY + dy - 5 > 0 and
		EndX + dx + 5 < 767 and EndY + dy + 5 < 431 and EndX + dx - 5 > 0 and EndY + dy - 5 > 0;
	else {
		Point d(StartX - EndX, StartY - EndY);
		return dx - 5 > 0 and dx + 5 < 767 and dy - 5 > 0 and dy + 5 < 431 and
			dx - d.X - 5 > 0 and dx - d.X + 5 < 767 and dy - d.Y - 5 > 0 and dy + 5 - d.Y < 431;
	}
}

void cLine::_move(int dx, int dy, bool mode) {
	if (ShowTrace and Trace.empty())
		Trace.push_back(Center);
	Hide();
	if (!mode) {
		StartX += dx; EndX += dx;
		StartY += dy; EndY += dy;
	}
	else {
		Point d(StartX - EndX, StartY - EndY);
		StartX = dx; EndX = dx - d.X;
		StartY = dy; EndY = dy - d.Y;
	}
	if (ShowTrace)
		Trace.push_back(Center);
	Draw();
	if (ShowTrace)
		DrawTrace();
}

bool cLine::IsScalePossible(double coefficient) {
	const Point current_center((StartX + EndX) / 2, (StartY + EndY) / 2);
	Point A(static_cast<int>(StartX * coefficient), static_cast<int>(StartY * coefficient));
	Point B(static_cast<int>(EndX * coefficient), static_cast<int>(EndY * coefficient));
	const Point AB_center((A.X + B.X) / 2, (A.Y + B.Y) / 2);
	const int offsetX = current_center.X - AB_center.X;
	const int offsetY = current_center.Y - AB_center.Y;
	A.X += offsetX; A.Y += offsetY; B.X += offsetX; B.Y += offsetY;
	return A.X - 5 > 0 and A.Y - 5 > 0 and A.X + 5 < 767 and A.Y + 5 < 431 and
		B.X - 5 > 0 and B.Y - 5 > 0 and B.X + 5 < 767 and B.Y + 5 < 431 and (coefficient >= 1 or pow(StartX - EndX, 2) + pow(StartY - EndY, 2) >= 121);
}

void cLine::_scale(double coefficient) {
	const Point current_center((StartX + EndX) / 2, (StartY + EndY) / 2);
	Point A(static_cast<int>(StartX * coefficient), static_cast<int>(StartY * coefficient));
	Point B(static_cast<int>(EndX * coefficient), static_cast<int>(EndY * coefficient));
	const Point AB_center((A.X + B.X) / 2, (A.Y + B.Y) / 2);
	const int offsetX = current_center.X - AB_center.X;
	const int offsetY = current_center.Y - AB_center.Y;
	A.X += offsetX; A.Y += offsetY; B.X += offsetX; B.Y += offsetY;
	Hide();
	StartX *= coefficient; StartY *= coefficient;
	EndX *= coefficient; EndY *= coefficient;
	_move(offsetX, offsetY, false);
}

void cLine::SetDefaults() {
	DefaultStartX = StartX;
	DefaultStartY = StartY;
	DefaultEndX = EndX;
	DefaultEndY = EndY;
}

cLine::cLine(Graphics& graph, int BegX, int BegY, int EndX, int EndY, Color color, bool trace,
	int defaultBegX, int defaultBegY, int defaultEndX, int defaultEndY, Color defaultColor, bool defaultTrace, bool enable) :
	Shape(graph, color, trace, defaultColor, defaultTrace, enable) {
	DefaultStartX = defaultBegX; StartX = BegX;
	DefaultStartY = defaultBegY; StartY = BegY;
	DefaultEndX = defaultEndX; this->EndX = EndX;
	DefaultEndY = defaultEndY; this->EndY = EndY;
}

cLine::cLine(Graphics& graph, int BegX, int BegY, int EndX, int EndY, Color color, bool trace) : Shape(graph, color, trace) {
	DefaultStartX = StartX = BegX;
	DefaultStartY = StartY = BegY;
	DefaultEndX = this->EndX = EndX;
	DefaultEndY = this->EndY = EndY;
}

Point cLine::GetCenter() {
	return Point((StartX + EndX) / 2, (StartY + EndY) / 2);
}

void cLine::Write(ofstream& file) {
	file << line << ' ' << StartX << ' ' << StartY << ' ' << EndX << ' ' << EndY 
		<< ' ' << DefaultStartX << ' ' << DefaultStartY << ' ' << DefaultEndX << ' ' << DefaultEndY;
	Shape::Write(file);
}

void cLine::Reset() {
	enabled = true;
	Hide();
	StartX = DefaultStartX;
	StartY = DefaultStartY;
	color = DefaultColor;
	EndX = DefaultEndX;
	EndY = DefaultEndY;
	SwitchTrace(false);
	Draw();
	SwitchTrace(DefaultShowTrace);
}