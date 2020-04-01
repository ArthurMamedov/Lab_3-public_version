#ifndef __Ellipse
#define __Ellipse
#include"Shape.hpp"
class cEllipse: public Shape {
protected:
	int UpLeftX, UpLeftY, DefaultUpLeftX, DefaultUpLeftY;
	int Width, DefaultWidth;
	int Height, DefaultHeight;
	void Draw() override;
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
public:
	void SetDefaults() override;
	cEllipse(Graphics& graph, int x, int y, int width, int height, Color color, bool trace,
		int defaultX, int defaultY, int defaultWidth, int defaultHeight, Color defaultColor, bool defaultTrace, bool enable);
	cEllipse(Graphics& graph, int x, int y, int width, int height, Color color, bool trace = false);
	Point GetCenter() override;
	virtual void Write(ofstream& file) override;
	void Reset() override;
};
#endif