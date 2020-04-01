#ifndef __Displayer
#define __Displayer
#pragma region includes
#include"Ellipse.hpp"
#include"Circle.hpp"
#include"Square.hpp"
#include"Rectangle.hpp"
#include"Triangle.hpp"
#include"Dot.hpp"
#include"Star.hpp"
#include"Line.hpp"
#include"Agregate.hpp"
#pragma endregion
class Displayer {
private:
	Graphics* graphics;
	KoSTL::vector<Shape*> Shapes;
	void drawer();
	size_t sensitivity;
public:
	int GetSize() const;
	size_t GetSensitivity() const;
	void SetSensitivity(size_t sensitivity);
	__declspec(property(get = GetSize)) int Size;  // Thanks Microsoft for this sugar
	__declspec(property(get = GetSensitivity, put = SetSensitivity)) size_t Sensitivity;
	Displayer(Graphics* graphics);
	void Add(int shape, Color color = Color(255, 255, 255, 255), bool trace = false, KoSTL::vector<int> coordinates = {});
	void Erase(int);
	void FollowTrace(int index);
	void Init();
	void Move(int dx, int dy, bool mode, int index);
	void ChangeColor(Color newColor, int index);
	void Scale(double coefficient, int index);
	void Reset(int index);
	void SwitchTrace(bool switcher, int index);
	void Disable(int index);
	void Enable(int index);
	void DrawField(std::string file_path = "", bool redraw_shapes = false);
	void Blink(int index);
	void Read(string& file);
	void Write(string& file);
	~Displayer();
	friend class Factory;
};
#endif