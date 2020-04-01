#ifndef __Rectangle
#define __Rectangle
#include"Shape.hpp"
class cRectangle : public Shape {
protected:
	int UpLeftX, UpLeftY, DefaultUpLeftX, DefaultUpLeftY;
	int Width, DefaultWidth;
	int Height, DefaultHeight;
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
	void Draw() override;
public:
	void SetDefaults() override;
	cRectangle(Graphics& graph, int x, int y, int width, int height, Color color, bool trace,
		int defaultX, int defaultY, int defaultWidth, int defaultHeight, Color defaultColor, bool defaultTrace, bool enable);
	cRectangle(Graphics& graph, int x, int y, int width, int height, Color color, bool trace = false);
	Point GetCenter() override;
	virtual void Write(ofstream& writer) override;
	void Reset() override;
};
#endif