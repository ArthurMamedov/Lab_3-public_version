#ifndef __Agregate
#define __Agregate
#include "Shape.hpp"
class cAgregate : public Shape {
protected:
	KoSTL::vector<Shape*> _shapes;
	void Draw() override;
	bool IsMovePossible(int dx, int dy, bool mode) override;
	void _move(int dx, int dy, bool mode) override;
	bool IsScalePossible(double coefficient) override;
	void _scale(double coefficient) override;
public:
	void SetDefaults() override;
	cAgregate(Graphics& graphics, KoSTL::vector<Shape*>& shapes, Color color, bool trace);
	cAgregate(Graphics& graphics, KoSTL::vector<Shape*>& shapes, Color color, bool trace, Color defaultColor, bool defaultTrace, bool enabled);
	void ChangeColor(Color newColor) override;
	void Reset() override;
	void Write(ofstream& file) override;
	void Enable() override;
	void Disable() override;
	Point GetCenter() override;
	~cAgregate();
};
#endif