#include "Shape.hpp"

void Shape::HideTrace() {
	auto tmp = color;
	color = BG;
	DrawTrace();
	color = tmp;
}

///Draws the trace
void Shape::DrawTrace() {
	if (!Trace.empty())
		Graph->DrawLines(&Pen(color), &Trace[0], Trace.size());
}

///Hides the shape
void Shape::Hide() {
	auto tmp = color;
	color = BG;
	Draw();
	color = tmp;
}

Shape::Shape(Graphics& graphics, Color color, bool trace, Color defaultColor, bool defaultTrace, bool enable) {
	Graph = &graphics;
	enabled = enable;
	this->color = color;
	ShowTrace = trace;
	DefaultColor = defaultColor;
	DefaultShowTrace = defaultTrace;
}

///Constructor
Shape::Shape(Gdiplus::Graphics& graphics, Color color, bool trace) {
	Graph = &graphics;
	DefaultColor = this->color = color;
	DefaultShowTrace = ShowTrace = trace;
}

///Draws the shape
void Shape::Enable() {
	enabled = true;
	Draw();
	if (ShowTrace) {
		DrawTrace();
	}
}

///Draws or hides trace if shape is enabled
void Shape::SwitchTrace(bool switcher) {
	if (enabled) {
		ShowTrace = switcher;
		HideTrace();
		if (!switcher)
			Trace.erase(Trace.begin(), Trace.end());
		Draw();
	}
}

///Hides the shape and makes is unavailable
void Shape::Disable() {
	Hide();
	if (ShowTrace) {
		HideTrace();
	}
	enabled = false;
}

///Changed color to new one
void Shape::ChangeColor(Color newColor) {
	if (enabled) <%
		color = newColor;
		Draw();
		if (ShowTrace)
			DrawTrace();
	%>
}

///Moves the shape if enabled
void Shape::Move(int dx, int dy, bool mode) {
	if (!enabled) return;
	bool IsPossible = IsMovePossible(dx, dy, mode);
	if (IsPossible)
		_move(dx, dy, mode);
	else Draw();
}

///'Deformation' i guess
void Shape::Scale(double coefficient) {
	if (!enabled or coefficient < 0.01) return;
	if (IsScalePossible(coefficient))
		_scale(coefficient);
}

///Writing to a file
void Shape::Write(ofstream& file) {
	file << ' ' << (int)color.GetA()
		 << ' ' << (int)color.GetR()
		 << ' ' << (int)color.GetG()
		 << ' ' << (int)color.GetB()
		 << ' ' << ShowTrace
		 << ' ' << (int)DefaultColor.GetA() 
		 << ' ' << (int)DefaultColor.GetR()
		 << ' ' << (int)DefaultColor.GetG()
		 << ' ' << (int)DefaultColor.GetB()
		 << ' ' << DefaultShowTrace 
		 << ' ' << enabled << '\n';
}
