#ifndef __Star
#define __Star
#include"Shape.hpp"
class cStar : public Shape {
protected:
	KoSTL::vector<Point> Points, DefaultPoints;
	virtual void Draw() override;
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
public:
	void SetDefaults() override;
	cStar(Graphics& graphics, Point p1, Point p2, Point p3, Point p4, Point p5, Color color, bool trace,
		Point dp1, Point dp2, Point dp3, Point dp4, Point dp5, Color defaultColor, bool defaultTrace, bool enable);
	cStar(Graphics& graphics, int x, int y, Color color, bool trace);
	Point GetCenter() override;
	void Write(ofstream& file) override;
	virtual void Reset() override;
};
#endif