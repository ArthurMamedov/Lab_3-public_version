#include "Circle.hpp"

cCircle::cCircle(Graphics& graphics, int x, int y, int side, Color color, bool trace, int defaultX, int defaultY, int defaultSide, Color defaultColor, bool defaultTrace, bool enable) :
	cEllipse(graphics, x, y, side, side, color, trace, defaultX, defaultY, defaultSide, defaultSide, defaultColor, defaultTrace, enable) {}
cCircle::cCircle(Graphics& graph, int x, int y, int side, Color color, bool trace) :
	cEllipse(graph, x, y, side, side, color, trace) {}

void cCircle::Write(ofstream& file) {
	file << circle << ' ' << UpLeftX << ' ' << UpLeftY << ' ' << Width  << ' '
		<< DefaultUpLeftX << ' ' << DefaultUpLeftY << ' ' << DefaultWidth;
	Shape::Write(file);
}
