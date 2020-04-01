#ifndef __Circle
#define __Circle
#include "Ellipse.hpp"
class cCircle : public cEllipse {
public:
	cCircle(Graphics& graphics, int x, int y, int side, Color color, bool trace,
		int defaultX, int defaultY, int defaultSide, Color defaultColor, bool defaultTrace, bool enable);
	cCircle(Graphics& graph, int x, int y, int side, Color color, bool trace);
	void Write(ofstream& file) override;
};
#endif