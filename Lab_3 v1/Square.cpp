#include "Square.hpp"

cSquare::cSquare(Graphics& graph, int x, int y, int side, Color color, bool trace, 
	int defaultX, int defaultY, int defaultSide, Color defaultColor, bool defaultTrace, bool enable):
	cRectangle(graph, x, y, side, side, color, trace, defaultX, defaultY, defaultSide, defaultSide, defaultColor, defaultTrace, enable) {}

cSquare::cSquare(Graphics& graph, int x, int y, int side, Color color, bool trace) :
	cRectangle(graph, x, y, side, side, color, trace) {}

void cSquare::Write(ofstream& file) {
	file << square << ' ' << UpLeftX << ' ' << UpLeftY << ' ' << Width << ' ' 
		<< DefaultUpLeftX << ' ' << DefaultUpLeftY << ' ' << DefaultWidth;
	Shape::Write(file);
}
