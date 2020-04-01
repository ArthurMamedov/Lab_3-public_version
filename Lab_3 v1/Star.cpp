#include "Star.hpp"

void cStar::Draw() {
	Graph->FillPolygon(&SolidBrush(color), &Points[0], Points.size(), FillMode::FillModeWinding);
}

bool cStar::IsMovePossible(int dx, int dy, bool mode) {
	bool check = true;
	vector<Point> tmp;
	if (!mode) {
		for (size_t c = 0; c < Points.size(); c++)
			tmp.push_back(Point(Points[c].X + dx, Points[c].Y + dy));
		for (size_t c = 0; c < tmp.size() and check; c++)
			check = check && tmp[c].X < 767 && tmp[c].X > 0 && tmp[c].Y > 0 && tmp[c].Y < 431;
	}
	else {
		tmp.push_back(Point(dx, dy));
		tmp.push_back(Point(dx += -26, dy += -20));
		tmp.push_back(Point(dx += 32, dy));
		tmp.push_back(Point(dx += -26, dy += 20));
		tmp.push_back(Point(dx += 10, dy += -30));
		for (size_t c = 0; c < Points.size() and check; c++) {
			check = check && tmp[c].X < 767 && tmp[c].X > 0 && tmp[c].Y > 0 && tmp[c].Y < 431;
		}
	}
	return check;
}

void cStar::_move(int dx, int dy, bool mode) {
	if (ShowTrace and Trace.empty())
		Trace.push_back(Center);
	Hide();
	if (!mode) {
		for (size_t c = 0; c < Points.size(); c++) {
			Points[c].X += dx; 
			Points[c].Y += dy;
		}
	}
	else {
		vector<Point> tmp;
		tmp.push_back(Point(dx, dy));
		tmp.push_back(Point(dx += -26, dy += -20));
		tmp.push_back(Point(dx += 32, dy));
		tmp.push_back(Point(dx += -26, dy += 20));
		tmp.push_back(Point(dx += 10, dy += -30));
		for (size_t c = 0; c < tmp.size(); c++)
			Points[c] = tmp[c];
	}
	if (ShowTrace)
		Trace.push_back(Center);
	Draw();
	if (ShowTrace)
		DrawTrace();
}

bool cStar::IsScalePossible(double coefficient) {
	bool outcome = true;
	const auto averageX = (Points[0].X + 0.0 + Points[1].X + Points[2].X + Points[3].X + Points[4].X) / 5;
	const auto averageY = (Points[0].Y + 0.0 + Points[1].Y + Points[2].Y + Points[3].Y + Points[4].Y) / 5;
	const auto offsetX = static_cast<int>(averageX - averageX * coefficient);
	const auto offsetY = static_cast<int>(averageY - averageY * coefficient);
	for (uint8_t c = 0; c < 5 and outcome; c++) {
		outcome = outcome && (Points[c].X * coefficient + offsetX > 0) && (Points[c].X * coefficient + offsetX < 767) &&
			(Points[c].Y * coefficient + offsetY > 0) && (Points[c].Y * coefficient + offsetY < 431);
	} if (coefficient < 1) {
		outcome = outcome && pow(Points[1].X - Points[0].X, 2) + pow(Points[1].Y - Points[0].Y, 2) > 300 &&
			pow(Points[2].X - Points[1].X, 2) + pow(Points[2].Y - Points[1].Y, 2) > 300 &&
			pow(Points[3].X - Points[2].X, 2) + pow(Points[3].Y - Points[2].Y, 2) > 300 &&
			pow(Points[4].X - Points[3].X, 2) + pow(Points[4].Y - Points[3].Y, 2) > 300 &&
			pow(Points[0].X - Points[4].X, 2) + pow(Points[0].Y - Points[4].Y, 2) > 300;
	} return outcome;
}

void cStar::_scale(double coefficient) {
	const auto averageX = (Points[0].X + Points[1].X + Points[2].X + Points[3].X + Points[4].X) / 5;
	const auto averageY = (Points[0].Y + Points[1].Y + Points[2].Y + Points[3].Y + Points[4].Y) / 5;
	const auto offsetX = averageX - averageX * coefficient;
	const auto offsetY = averageY - averageY * coefficient;
	Hide();
	for (short c = 0; c < 5; c++) {
		Points[c].X = static_cast<int>(Points[c].X * coefficient);
		Points[c].Y = static_cast<int>(Points[c].Y * coefficient);
	}
	_move(offsetX, offsetY, false);
}

void cStar::SetDefaults() {
	DefaultPoints = Points;
}

cStar::cStar(Graphics& graphics, Point p1, Point p2, Point p3, Point p4, Point p5, Color color, bool trace,
	Point dp1, Point dp2, Point dp3, Point dp4, Point dp5, Color defaultColor, bool defaultTrace, bool enable) :
	Shape(graphics, color, trace, defaultColor, defaultTrace, enable) {
	Points.push_back(p1);
	Points.push_back(p2);
	Points.push_back(p3);
	Points.push_back(p4);
	Points.push_back(p5);

	DefaultPoints.push_back(dp1);
	DefaultPoints.push_back(dp2);
	DefaultPoints.push_back(dp3);
	DefaultPoints.push_back(dp4);
	DefaultPoints.push_back(dp5);
}

cStar::cStar(Graphics& graphics, int x, int y, Color color, bool trace) :
	Shape(graphics, color, trace) {
	Points.push_back(Point(x, y));
	Points.push_back(Point(x += -26, y += -20));
	Points.push_back(Point(x += 32, y));
	Points.push_back(Point(x += -26, y += 20));
	Points.push_back(Point(x += 10, y += -30));
	auto _ = DefaultPoints = Points;
}

Point cStar::GetCenter() {
	int X = 0, Y = 0;
	for (size_t c = 0; c < Points.size(); c++) {
		X += Points[c].X; 
		Y += Points[c].Y;
	}
	return Point(X / 5, Y / 5);
}

void cStar::Write(ofstream& file) {
	file << star;
	for (size_t c = 0; c < Points.size(); c++)
		file << ' ' << Points[c].X << ' ' << Points[c].Y;
	for (size_t c = 0; c < DefaultPoints.size(); c++)
		file << ' ' << DefaultPoints[c].X << ' ' << DefaultPoints[c].Y;
	Shape::Write(file);
}

void cStar::Reset() {
	enabled = true;
	Hide();
	color = DefaultColor;
	ShowTrace = DefaultShowTrace;
	auto _ = Points = DefaultPoints;
	SwitchTrace(false);
	Draw();
	SwitchTrace(DefaultShowTrace);
}
