#ifndef __Square
#define __Square
#include"Rectangle.hpp"
class cSquare : public cRectangle {
protected:
public:
	cSquare(Graphics& graph, int x, int y, int side, Color color, bool trace,
		int defaultX, int defaultY, int defaultSide, Color defaultColor, bool defaultTrace, bool enable);
	cSquare(Graphics& graph, int x, int y, int side, Color color, bool trace);
	void Write(ofstream& file) override;
};
#endif