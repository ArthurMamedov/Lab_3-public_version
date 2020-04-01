#include "Agregate.hpp"

void cAgregate::Draw() {
	for (auto shape : _shapes) 
		shape->Draw();
}

bool cAgregate::IsMovePossible(int dx, int dy, bool mode) {
	bool sum = true;
	for (auto shape : _shapes)
		sum = sum and shape->IsMovePossible(dx, dy, mode);
	return sum;
}

void cAgregate::_move(int dx, int dy, bool mode) {
	if (ShowTrace and Trace.empty())
		cAgregate::Trace.push_back(GetCenter());

	for (auto shape : _shapes) {
		shape->_move(dx, dy, mode);
	}

	if (ShowTrace)
		cAgregate::Trace.push_back(GetCenter());
}

bool cAgregate::IsScalePossible(double coefficient) {
	bool sum = true;
	for (auto shape : _shapes)
		sum = sum and shape->IsScalePossible(coefficient);
	return sum;
}

void cAgregate::_scale(double coefficient) {
	for (auto shape : _shapes)
		shape->_scale(coefficient);
}

void cAgregate::SetDefaults() {
	return;
}

cAgregate::cAgregate(Graphics& graphics, vector<Shape*>& shapes, Color color, bool trace):
	Shape(graphics, color, trace) {
	const auto _ = _shapes = shapes;
	for (auto shape : _shapes) {
		shape->SetDefaults();
		shape->SwitchTrace(false);
		shape->enabled = true;
		shape->ChangeColor(color);
	}
}

cAgregate::cAgregate(Graphics& graphics, KoSTL::vector<Shape*>& shapes, Color color, bool trace, Color defaultColor, bool defaultTrace, bool enabled):
	Shape(graphics, color, trace, defaultColor, defaultTrace, enabled) {
	const auto _ = _shapes = shapes;
	for (auto shape : _shapes) {
		shape->SetDefaults();
		shape->SwitchTrace(false);
		shape->enabled = enabled;
		shape->ChangeColor(color);
	}
}

void cAgregate::ChangeColor(Color newColor) {
	if (enabled) {
		color = newColor;
		for (auto shape : _shapes)
			shape->ChangeColor(newColor);

	}
}

void cAgregate::Reset() {
	enabled = true;
	Hide();
	color = DefaultColor;
	ShowTrace = DefaultShowTrace;
	for (auto shape : _shapes)
		shape->Reset();
	SwitchTrace(false);
	Draw();
	SwitchTrace(DefaultShowTrace);
}

void cAgregate::Write(ofstream& file) {
	for (auto shape : _shapes)
		shape->Write(file);
	file << agregate << ' ' << _shapes.size(); 
	Shape::Write(file);
}

void cAgregate::Enable() {
	enabled = true;
	for (auto shape : _shapes)
		shape->Enable();
	if (ShowTrace)
		DrawTrace();
}

void cAgregate::Disable() {
	for (auto shape : _shapes)
		shape->Disable();
	if (ShowTrace)
		HideTrace();
	enabled = false;
}

Point cAgregate::GetCenter() {
	size_t count = 0;
	Point agregate_center(0, 0);
	for (auto shape : _shapes) {
		count++;
		agregate_center.X += shape->Center.X;
		agregate_center.Y += shape->Center.Y;
	}
	agregate_center.X /= count;
	agregate_center.Y /= count;
	return agregate_center;
}

cAgregate::~cAgregate() {
	for (auto shape : _shapes)
		delete shape;
}