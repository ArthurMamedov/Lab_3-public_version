//#include<functional>
#include<conio.h>
#include<Windows.h>
#include<thread>
#include<regex>
#include "Displayer.hpp"
const Color DefaultColor(255, 255, 255, 255);

#pragma region Factory
class Factory {
private:
	Displayer* disp;
	Graphics* graph;
public:
	Factory(Displayer* disp, Graphics* graph) {
		this->disp = disp;
		this->graph = graph;
	};
	Shape* MakeShape(int shape, Color color = DefaultColor, bool trace = false, KoSTL::vector<int> shapes_for_vector = {}) {
		switch (shape) {
		case square:
			return new cSquare(*graph, 373, 205, 20, color, trace);
		case triangle:
			return new cTriangle(*graph, 370, 225, 395, 225, 383, 205, color, trace);
		case circle:
			return new cCircle(*graph, 373, 205, 20, color, trace);
		case line:
			return new cLine(*graph, 373, 215, 393, 215, color, trace);
		case dot:
			return new cDot(*graph, 383, 215, color, trace);
		case rectangle:
			return new cRectangle(*graph, 373, 200, 20, 30, color, trace);
		case ellipse:
			return new cEllipse(*graph, 373, 200, 20, 30, color, trace);
		case star:
			return new cStar(*graph, 383, 205, color, trace);
		case agregate: {
			if (shapes_for_vector.empty()) throw exception("Empty parameters error");
			KoSTL::vector<Shape*> tmp;
			for (auto shape_number : shapes_for_vector) {
				tmp.push_back(disp->Shapes[shape_number]);
			}
			for (int c = shapes_for_vector.size() - 1; c >= 0; c--) {
				disp->Shapes.erase(shapes_for_vector[c]);
			} tmp.shrink_to_fit();
			return new cAgregate(*graph, tmp, color, trace);
		}
		default: throw exception("Wrong operation code");
		}
	}
	Shape* RestoreShape(int shape, KoSTL::vector<int> params) {
		switch (shape) {
		case square:
			return new cSquare(*graph, params[0], params[1], params[2],
				Color(params[6], params[7], params[8], params[9]),
				params[10], params[3], params[4], params[5],
				Color(params[11], params[12], params[13], params[14]),
				params[15], params[16]);
		case triangle:
			return new cTriangle(*graph, params[0], params[1], params[2], params[3], params[4], params[5],
				Color(params[12], params[13], params[14], params[15]),
				params[16], params[6], params[7], params[8], params[9], params[10], params[11],
				Color(params[17], params[18], params[19], params[20]),
				params[21], params[22]);
		case circle:
			return new cCircle(*graph, params[0], params[1], params[2],
				Color(params[6], params[7], params[8], params[9]),
				params[10], params[3], params[4], params[5],
				Color(params[11], params[12], params[13], params[14]),
				params[15], params[16]);
		case line:
			return new cLine(*graph, params[0], params[1], params[2], params[3],
				Color(params[8], params[9], params[10], params[11]),
				params[12], params[4], params[5], params[6], params[7],
				Color(params[13], params[14], params[15], params[16]),
				params[17], params[18]);
		case dot:
			return new cDot(*graph, params[0], params[1],
				Color(params[4], params[5], params[6], params[7]),
				params[8], params[2], params[3],
				Color(params[9], params[10], params[11], params[12]),
				params[13], params[14]);
		case rectangle:
			return new cRectangle(*graph, params[0], params[1], params[2], params[3],
				Color(params[8], params[9], params[10], params[11]),
				params[12], params[4], params[5], params[6], params[7],
				Color(params[13], params[14], params[15], params[16]),
				params[17], params[18]);
		case ellipse:
			return new cEllipse(*graph, params[0], params[1], params[2], params[3],
				Color(params[8], params[9], params[10], params[11]),
				params[12], params[4], params[5], params[6], params[7],
				Color(params[13], params[14], params[15], params[16]),
				params[17], params[18]);
		case star:
			return new cStar(*graph,
				Point(params[0], params[1]),
				Point(params[2], params[3]),
				Point(params[4], params[5]),
				Point(params[6], params[7]),
				Point(params[8], params[9]),
				Color(params[20], params[21], params[22], params[23]), params[24],
				Point(params[10], params[11]),
				Point(params[12], params[13]),
				Point(params[14], params[15]),
				Point(params[16], params[17]),
				Point(params[18], params[19]),
				Color(params[25], params[26], params[27], params[28]),
				params[29], params[30]);
		case agregate: {
			KoSTL::vector<Shape*> tmp;
			for (auto c = disp->Size - 1; c > disp->Size - params[0] - 1; c--)
				tmp.push_back(disp->Shapes[c]);
			const auto start_index = disp->Size - 1;
			for (auto c = start_index; c > start_index - params[0]; c--)
				disp->Shapes.erase(c);
			tmp.shrink_to_fit();
			return new cAgregate(*graph, tmp, Color(params[1], params[2], params[3], params[4]), params[5], Color(params[6], params[7], params[8], params[9]), params[10], params[11]);
		}
		default: throw exception("Wrong operation code");
		}
	}
};

void Displayer::drawer() {
	for (auto shape : Shapes)
		if (shape->ShowTrace and shape->enabled)
			shape->DrawTrace();
	for (auto shape : Shapes)
		if (shape->enabled)
			shape->Draw();
}
#pragma endregion

int Displayer::GetSize() const {
	return Shapes.size();
}

size_t Displayer::GetSensitivity() const {
	return sensitivity;
}

void Displayer::SetSensitivity(size_t sensitivity) {
	this->sensitivity = sensitivity;
}

Displayer::Displayer(Graphics* graphics) {
	this->graphics = graphics; 
	sensitivity = 0;
}

void Displayer::Add(int shape, Color color, bool trace, KoSTL::vector<int> coords) {
	Factory fact(this, graphics);
	Shapes.push_back(fact.MakeShape(shape, color, trace, coords));
	Shapes[Size - 1]->Enable();
	drawer();
}

void Displayer::Erase(int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size()) {
		Shapes[index]->Disable();
		delete Shapes[index];
		Shapes.erase(index);
	}
	else if (index == -1) {
		for (auto shape : Shapes) {
			shape->Disable();
			delete shape;
		}
		Shapes.clear();
	}
	else throw exception("Bad index");
	drawer();
}

void Displayer::FollowTrace(int index) {
	if (Shapes[index]->enabled and !Shapes[index]->Trace.empty()) {
		auto diffX = Shapes[index]->Trace.back().X;
		Shapes[index]->ShowTrace = false;
		for (auto c = 0; c < Shapes[index]->Trace.size(); c++) {
			Shapes[index]->Move(-Shapes[index]->Center.X + Shapes[index]->Trace[c].X, -Shapes[index]->Center.Y + Shapes[index]->Trace[c].Y, false);
			Shapes[index]->DrawTrace();
			drawer();
			this_thread::sleep_for(chrono::milliseconds(27));
		}
		Shapes[index]->ShowTrace = true;
	}
}

void Displayer::Init() {
	for (auto shape : Shapes) {
		shape->Draw();
		if (shape->ShowTrace)
			shape->DrawTrace();
	}
	//shape->Enable();
}

void Displayer::Move(int dx, int dy, bool mode, int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->Move(dx, dy, mode);
	else throw exception("Bad index");
	for (size_t c = 0; c < Shapes.size(); c++) {
		for (size_t p = 0; p < c; p++) {
			if (
				abs(Shapes[c]->Center.X - Shapes[p]->Center.X) < sensitivity and
				abs(Shapes[c]->Center.Y - Shapes[p]->Center.Y) < sensitivity and
				Shapes[c]->enabled and
				Shapes[p]->enabled
				)
			{
				Color averageColor(
					(Shapes[c]->color.GetA() + Shapes[p]->color.GetA()) / 2,
					(Shapes[c]->color.GetR() + Shapes[p]->color.GetR()) / 2,
					(Shapes[c]->color.GetG() + Shapes[p]->color.GetG()) / 2,
					(Shapes[c]->color.GetB() + Shapes[p]->color.GetB()) / 2
				);
				Shapes[c]->ChangeColor(averageColor);
				Shapes[p]->ChangeColor(averageColor);
				Shapes[c]->Scale(1.2);
				Shapes[p]->Scale(1.2);
			}
		}
	}
	drawer();
}

void Displayer::ChangeColor(Color newColor, int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->ChangeColor(newColor);
	else throw exception("Bad index");
	drawer();
}

void Displayer::Scale(double coefficient, int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->Scale(coefficient);
	else throw exception("Bad index");
	drawer();
}

void Displayer::Reset(int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->Reset();
	else throw exception("Bad index");
	drawer();
}

void Displayer::SwitchTrace(bool switcher, int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->SwitchTrace(switcher);
	else throw exception("Bad index");
	drawer();
}

void Displayer::Disable(int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->Disable();
	else throw exception("Bad index");
	drawer();
}

void Displayer::Enable(int index) {
	if (Shapes.empty()) return;
	if (index >= 0 and index < Shapes.size())
		Shapes[index]->Enable();
	else throw exception("Bad index");
	drawer();
}

void Displayer::DrawField(std::string file_path, bool redraw_shapes) {  // Draws the red rectangle - the field
	static std::string File_path = file_path == "" ? File_path : file_path;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	this_thread::sleep_for(chrono::milliseconds(50));
	graphics->DrawRectangle(&Pen(Color(255, 255, 0, 0)), 0, 0, 767, 431);
	if (!File_path.empty()) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "File path: " << File_path << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "No selected file" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	cout << "Selected shape index: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "None" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "Lab 3 v15 [BETA]";
	if (redraw_shapes) {
		drawer();
	}
}

void Displayer::Blink(int index) {  //This is needed to define the shape which is switched to
	if (index >= Size or index < 0)
		return;

	if (Shapes[index]->enabled)
		Shapes[index]->Disable();
	else
		Shapes[index]->Enable();
	this_thread::sleep_for(chrono::milliseconds(120));
	if (!Shapes[index]->enabled)
		Shapes[index]->Enable();
	else
		Shapes[index]->Disable();
}

Displayer::~Displayer() {
	for (auto shape : Shapes)
		delete shape;
}

void Displayer::Read(string& file_path) {
	ifstream file;
	try {
		file.open(file_path, fstream::in);
	}
	catch (...) {
		cout << static_cast<char>(7) << "Didn't manage to open file!";
		return;
	}
	static const std::regex regular("(\\d){1,}");  // I just was too lazy to make my own function that splits a string so I decided to use regular expressions.
	int shape;
	KoSTL::vector<int> shape_params;
	std::smatch matches;
	Factory fact(this, graphics);
	for (auto _shape : Shapes)  // Clearing old Shapes vector
		delete _shape;
	Shapes.clear();
	std::string raw;
	while (std::getline(file, raw)) {								// reading from a file by line
		while (std::regex_search(raw, matches, regular)) {			// spliting the line by ' '
			shape_params.push_back(atoi(matches.str().c_str()));	// and writing the sublines to shape_params
			raw = matches.suffix().str();
		};
		raw = "";
		shape = shape_params[0]; shape_params.erase(0);
		Shapes.push_back(fact.RestoreShape(shape, shape_params));  // Restoring shapes according to the data in file
		if (Shapes[Size - 1]->enabled)
			Shapes[Size - 1]->Enable();
		shape_params.clear();
	}
	for (auto _shape : Shapes)
		if (_shape->enabled)
			_shape->Draw();
	file.close();
}

void Displayer::Write(string& file_path) {
	ofstream file;
	try {
		file.open(file_path, fstream::out);
	}
	catch (...) {
		cout << static_cast<char>(7) << "Didn't manage to open the file";
		return;
	}
	for (auto shape : Shapes)
		shape->Write(file);
	file.close();
}