#include "Triangle.hpp"

bool cTriangle::IsMovePossible(int dx, int dy, bool mode) {
	if (!mode) {
		bool outcome = true;
		for (short c = 0; c < 3 and outcome; c++) {
			outcome = outcome && (Points[c].X + dx > 0) && (Points[c].X + dx < 767) && (Points[c].Y + dy > 0) && (Points[c].Y + dy < 431);
		} return outcome;
	}
	else {
		bool outcome = (dx > 0) && (dx < 767) && (dy > 0) && (dy < 431);
		int offsetX = -Points[0].X + dx, offsetY = -Points[0].Y + dy;
		for (short c = 1; c < 3 and outcome; c++) {
			outcome = outcome && (Points[c].X + offsetX < 767) && (Points[c].X + offsetX > 0) && (Points[c].Y + offsetY < 431) && (Points[c].X + offsetX > 0);
		} return outcome;
	}
}

void cTriangle::_move(int dx, int dy, bool mode) {
	if (ShowTrace and Trace.empty())
		Trace.push_back(Center);
	Hide();
	if (!mode) {
		for (short c = 0; c < 3; c++) {
			Points[c].X += dx;
			Points[c].Y += dy;
		}
	} 
	else {
		int offsetX = -Points[0].X + dx, offsetY = -Points[0].Y + dy;
		Points[0].X = dx;
		Points[0].Y = dy;
		for (short c = 1; c < 3; c++) {
			Points[c].X += offsetX; 
			Points[c].Y += offsetY;
		}
	}
	if (ShowTrace)
		Trace.push_back(Center);
	Draw();
	if (ShowTrace) DrawTrace();
}

bool cTriangle::IsScalePossible(double coefficient)
{
	bool outcome = true;
	const auto averageX = (Points[0].X + Points[1].X + Points[2].X) / 3;
	const auto averageY = (Points[0].Y + Points[1].Y + Points[2].Y) / 3;
	const auto offsetX = averageX - averageX * coefficient;
	const auto offsetY = averageY - averageY * coefficient;
	for (short c = 0; c < 3 and outcome; c++) {
		outcome = outcome && (Points[c].X * coefficient + offsetX > 0) && (Points[c].X * coefficient + offsetX < 767) &&
			(Points[c].Y * coefficient + offsetY > 0) && (Points[c].Y * coefficient + offsetY < 431);
	}
	if (coefficient < 1) {
		outcome = outcome && pow(Points[1].X - Points[0].X, 2) + pow(Points[1].Y - Points[0].Y, 2) > 100 &&
			pow(Points[2].X - Points[1].X, 2) + pow(Points[2].Y - Points[1].Y, 2) > 100 &&
			pow(Points[0].X - Points[2].X, 2) + pow(Points[0].Y - Points[2].Y, 2) > 100;
	} return outcome;
}

void cTriangle::_scale(double coefficient) {
	const auto averageX = (Points[0].X + Points[1].X + Points[2].X) / 3;
	const auto averageY = (Points[0].Y + Points[1].Y + Points[2].Y) / 3;
	const auto offsetX = averageX - averageX * coefficient;
	const auto offsetY = averageY - averageY * coefficient;
	Hide();
	for (short c = 0; c < 3; c++) {
		Points[c].X = static_cast<int>(Points[c].X * coefficient);
		Points[c].Y = static_cast<int>(Points[c].Y * coefficient);
	}
	Move(offsetX, offsetY, false);
}

void cTriangle::Draw() {
	Graph->FillPolygon(&SolidBrush(color), Points, 3);
}

void cTriangle::SetDefaults() {
	for (int c = 0; c < 3; c++) {
		DefaultPoints[c] = Points[c];
	}
}

cTriangle::cTriangle(Graphics& graph, int x, int y, int x2, int y2, int x3, int y3, Color color, bool trace,
	int defaultX, int defaultY, int defaultX2, int defaultY2, int defaultX3, int defaultY3, Color defaultColor, bool defaultTrace, bool enable) :
	Shape(graph, color, trace, defaultColor, defaultTrace, enable) {
	DefaultPoints[0] = Point(defaultX, defaultY); Points[0] = Point(x, y);
	DefaultPoints[1] = Point(defaultX2, defaultY2); Points[1] = Point(x2, y2);
	DefaultPoints[2] = Point(defaultX3, defaultY3); Points[2] = Point(x3, y3);
}

cTriangle::cTriangle(Graphics& graph, int x, int y, int x2, int y2, int x3, int y3, Color color, bool trace) :
	Shape(graph, color, trace) {
	DefaultPoints[0] = Points[0] = Point(x, y);
	DefaultPoints[1] = Points[1] = Point(x2, y2);
	DefaultPoints[2] = Points[2] = Point(x3, y3);
}

void cTriangle::Write(ofstream& file) {
	file << triangle;
	for (size_t c = 0; c < 3; c++)
		file << ' ' << Points[c].X << ' ' << Points[c].Y;
	for (size_t c = 0; c < 3; c++)
		file << ' ' << DefaultPoints[c].X << ' ' << DefaultPoints[c].Y;
	Shape::Write(file);
}

void cTriangle::Reset() {
	enabled = true;
	Hide();
	for (short c = 0; c < 3; c++)
		Points[c] = DefaultPoints[c];
	color = DefaultColor;
	ShowTrace = DefaultShowTrace;
	SwitchTrace(false);
	Draw();
	SwitchTrace(DefaultShowTrace);
}

Point cTriangle::GetCenter() {
	auto centerX = (Points[0].X + Points[1].X + Points[2].X) / 3;
	auto centerY = (Points[0].Y + Points[1].Y + Points[2].Y) / 3;
	return Point(centerX, centerY);
}
