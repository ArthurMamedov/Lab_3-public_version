#ifndef __Dot
#define __Dot
#include "Shape.hpp"
class cDot : public Shape {
protected:
	int X, Y, DefaultX, DefaultY;
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
	void Draw() override;
public:
	void SetDefaults() override;
	cDot(Graphics& graphics, int x, int y, Color color, bool trace, int defaultX, int defaultY, Color defaultColor, bool defaultTrace, bool enable);
	cDot(Graphics& graphics, int x, int y, Color color, bool trace);
	void Scale(double coefficient) override;
	void Write(ofstream& file) override;
	Point GetCenter() override;
	void Reset() override;
};
#endif