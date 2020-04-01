#include<Windows.h>
#include<gdiplus.h>
#include<conio.h>
#include<iostream>
#include"Displayer.hpp"

#pragma region Auxiliary functions
enum colors {
	black = 0, gray = 8,
	blue = 1, light_blue = 9,
	green = 2, light_green = 10,
	aqua = 3, light_aqua = 11,
	red = 4, light_red = 12,
	purple = 5, light_purple = 13,
	yellow = 6, light_yellow = 14,
	white = 7, bright_white = 15
};

const HANDLE COLOR = GetStdHandle(STD_OUTPUT_HANDLE);

KoSTL::vector<const char*> list_of_shapes { 
	"Choose the shape\n",
	"Square" ,
	"Circle", 
	"Triangle" ,
	"Rectangle" ,
	"Dot" ,
	"Line" ,
	"Ellipse", 
	"Star",
	"Agregate",
	"Exit"
};

int menu(const vector<const char*> &words, int color = 10) {
	std::system("cls");
	int number = words.size();
	int selected = 1;
	char key{};
	COORD k; k.X = 0; k.Y = 0;
	auto hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	static const auto out = [&]() {
		SetConsoleTextAttribute(COLOR, color);
		std::cout << "     " << words[0] << endl;
		SetConsoleTextAttribute(COLOR, colors::white);
		for (int c = 1; c < number; c++) {
			if (c == selected) {
				SetConsoleTextAttribute(COLOR, color);
				std::cout << "> ";
				SetConsoleTextAttribute(COLOR, colors::white);
			}
			std::cout << words[c] << endl;
		}
	};
	out();
	while (key != 13) {
		key = _getch();
		if (key == 80 and selected < number - 1)
			selected++;
		else if (key == 72 and selected > 1)
			selected--;
		SetConsoleCursorPosition(hnd, k);
		std::system("cls");
		out();
	}
	std::system("cls");
	return selected;
}

template<class T>
void Print(T message, int color) {
	SetConsoleTextAttribute(COLOR, color);
	std::cout << message;
	SetConsoleTextAttribute(COLOR, white);
}


void PrintIndex(int& index, int& figure_number) {
	COORD crd; crd.X = 22; crd.Y = 25;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
	if (figure_number==0) {
		Print("None", light_red);
	}
	else {
		Print(index, light_green);
		std::cout << "    \b\b\b\b";
	}
}

void AddShape(int& shape_number, KoSTL::vector<int> cords, int &figure_number, Displayer& disp, int &index) {
	shape_number = menu(list_of_shapes, 10);
	if (shape_number >= list_of_shapes.size() - 1) {
		disp.DrawField("", true);
		
		PrintIndex(index, figure_number);
		disp.Blink(index);
		return;
	}
	if (shape_number == agregate) {
		cout << "Shapes number: ";
		Print(figure_number, light_green);
		cout << "\nEnter the indexes of already created shapes (to finish - enter any negativ number): ";
		while (true) {
			int tmp;
			std::cin >> tmp;
			if (tmp > -1) {
				cords.push_back(tmp);
				figure_number--;
			}
			else break;
		} system("cls");
		disp.Add(agregate, Color(255, 255, 255, 255), false, cords);
		cords.clear();
	}
	else
		disp.Add(shape_number);
	figure_number++;
	if (!disp.Size) index = 0;
	else index = disp.Size - 1;
	disp.DrawField();
	PrintIndex(index, figure_number);
	disp.Blink(index);
}

void DeleteShape(Displayer& disp, int& index, int& figure_number) {
	disp.Erase(index);
	index--;
	figure_number--;
	if (index < 0) index = 0;
	PrintIndex(index, figure_number);
	disp.Blink(index);
}

void ChangeColorShape(Displayer& disp, int& index, int& figure_number) {
	int r, g, b;
	std::system("cls");
	std::cout << "Enter R:\n>"; cin >> r;
	std::cout << "Enter G:\n>"; cin >> g;
	std::cout << "Enter B:\n>"; cin >> b;
	std::system("cls");
	disp.ChangeColor(Color(255, static_cast<BYTE>(r), static_cast<BYTE>(g), static_cast<BYTE>(b)), index);
	disp.DrawField();
	PrintIndex(index, figure_number);
}

void GoToNextShape(int& index, int& figure_number, Displayer& disp) {
	if (index == -1) return;
	index++;
	if (index > figure_number - 1)
		index = 0;
	PrintIndex(index, figure_number);
	disp.Blink(index);
}

void GoToPrevStep(int& index, int& figure_number, Displayer& disp) {
	if (index == -1) return;
	index--;
	if (index < 0)
		index = figure_number - 1;
	PrintIndex(index, figure_number);
	disp.Blink(index);
}

void ShowHelp() {
	std::system("cls");
	SetConsoleTextAttribute(COLOR, white);
	std::cout
		<< "O-------------------------------------------------------HELP-----------------------------------------------------------O\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   'w' - move shape up                                  ||     'a' - move shape left                                  |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   's' - move shape down                                ||     'd' - move shape right                                 |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   '+(=)' - add new shape (then a menu will appear      ||     '-' - delete the active shape                          |\n"
		<< "|where you can select the shape you need, when an        ||                                                            |\n"
		<< "|agregate selected - type indexes of shapes from which   ||     'O' - exit the program                                 |\n"
		<< "|to make an agregate                                     ||                                                            |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   'q' - increase in size (deformarion)                 ||     'e' - decrease in size (deformation)                   |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   'T' - turn off leaving trace                         ||     't' - leave the trace                                  |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   'h' - hide the shape                                 ||     'H' - show the shape after hiding                      |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   '>(.)' - go to next shape                            ||     '<(,)' - go to prev shape                              |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   'f' - move by trace (if there is)                    ||     'r' - reset shape to defaults                          |\n"
		<< "|                                                        ||                                                            |\n"
		<< "|   'c' - change color (then enter R, G and B            ||     'R' - write to file (file must be set as a console     |\n"
		<< "|from 0 to 255                                           ||argument), if file is not set - the alarm sound will play   |\n"
		<< "|                                                        ||                                                            |\n"
		<< "O-------------------------------------------------------HELP-----------------------------------------------------------O\n";
}
#pragma endregion

int main(int argc, char** argv) {
	std::system("cls");
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(hWnd);
	Graphics graphics(hdc);
	
	string file = "";
	if (argc > 1)
		file = argv[1];

	Displayer disp(&graphics);
	disp.Sensitivity = 15;

	if(argc >= 1)
		disp.Read(file);
	disp.DrawField(file);
	int index = -1, figure_number = disp.Size, shape_number = 0;
	while (true) {
		char switcher = _getch();
		switch (switcher) {
		case 'w':
			disp.Move(0, -10, false, index); break;
		case 'a':
			disp.Move(-10, 0, false, index); break;
		case 's':
			disp.Move(0, 10, false, index); break;
		case 'd':
			disp.Move(10, 0, false, index); break;
		case '+': case '=':
			AddShape(shape_number, {}, figure_number, disp, index);
			break;
		case'f':
			disp.FollowTrace(index);
			break;
		case '-':
			DeleteShape(disp, index, figure_number);
			break;
		case 'c':
			ChangeColorShape(disp, index, figure_number);
			break;
		case 'r':
			disp.Reset(index); break;
		case 't':
			disp.SwitchTrace(true, index); break;
		case 'e':
			disp.Scale(0.5, index); break;
		case 'q':
			disp.Scale(2, index); break;
		case 'T':
			disp.SwitchTrace(false, index); break;
		case 'O':
			if (!gdiplusToken)
				GdiplusShutdown(gdiplusToken);
			return 0;
		case 'h':
			disp.Disable(index);
			break;
		case 'R':
			if (argc > 1) disp.Write(file);
			else cout << (char)7;
			break;
		case'H':
			disp.Enable(index); break;
		case '>': case '.':
			GoToNextShape(index, figure_number, disp); break;
		case '<': case ',':
			GoToPrevStep(index, figure_number, disp); break;
		case char(0):
			if (_getch() == char(59)) {
				ShowHelp();
				system("pause");
				system("cls");
				disp.Init();
				disp.DrawField(file);
			}
			break;
		default: break;
		}
	}
	if (!gdiplusToken)
		GdiplusShutdown(gdiplusToken);
	return 0;
}