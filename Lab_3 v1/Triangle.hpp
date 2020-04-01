#ifndef __Trig
#define __Trig
#include "Shape.hpp"
class cTriangle : public Shape {
protected:
	Point Points[3], DefaultPoints[3];
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
	void Draw() override;
public:
	void SetDefaults() override;
	cTriangle(Graphics& graph, int x, int y, int x2, int y2, int x3, int y3, Color color, bool trace, 
		int defaultX, int defaultY, int defaultX2, int defaultY2, int defaultX3, int defaultY3, Color defaultColor, bool defaultTrace, bool enable);
	cTriangle(Graphics& graph, int x, int y, int x2, int y2,int x3, int y3, Color color, bool trace = false);
	void Write(ofstream& file) override;
	void Reset() override;
	Point GetCenter() override;
};
#endif