#ifndef __Line
#define __Line
#include "Shape.hpp"
class cLine : public Shape {
protected:
	void Draw() override;
	int StartX, StartY, DefaultStartX, DefaultStartY;
	int DefaultEndX, DefaultEndY, EndX, EndY;
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
public:
	void SetDefaults() override;
	cLine(Graphics& graph, int BegX, int BegY, int EndX, int EndY, Color color, bool trace,
		int defaultBegX, int defaultBefY, int defaultEndX, int defaultEndY, Color defaultColor, bool defaultTrace, bool enable);
	cLine(Graphics& graph, int BegX, int BegY, int EndX, int EndY, Color color, bool trace);
	Point GetCenter() override;
	void Write(ofstream& file) override;
	void Reset() override;
};
#endif