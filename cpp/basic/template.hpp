///////////////////////////////函数模板//////////////////////////////////
template <typename T> 
T minimum(const T& lhs, const T& rhs)
{ return lhs < rhs ? lhs : rhs; }


////////////////////////////////变长////////////////////////////////////
template <typename... Args>
class MArgs{};

///////////////////////////////常数////////////////////////////////////
template<typename T, size_t L>
T loopIt(T x)
{
	T a[L];
	for (int ii = 0; ii < L; ii++)
	{
		a[ii] = x++;
	}
}
//////////////////////////////默认类型///////////////////////////////////
template <typename T = float, int count = 3>
T multIt(T x)
{
	for (int ii = 0; ii < count; ii++)
	{
		x = x * x;
	}
	return x;
}
///////////////////////////特化///////////////////////////////////
template <typename T>
T square(const T& t)
{
	return t*t;
}

template<>
string square<string>(const string& t)
{
	return t + t;
}

///////////////////////////类模板//////////////////////////////////////
template <class T>
class Matrix2x2
{
public:
	Matrix2x2(T m11, T m12, T m21, T m22);    //constructor
	Matrix2x2(T m[2][2]);
	Matrix2x2();

	int Add(Matrix2x2 x);
	int Multiply(Matrix2x2 x);
	void Print();
	T m[2][2];
};

template <class T>
Matrix2x2<T>::Matrix2x2(T _m11, T _m12, T _m21, T _m22)
{
	m[0][0] = _m11;
	m[0][1] = _m12;
	m[1][0] = _m21;
	m[1][1] = _m22;
}

template <class T>
Matrix2x2<T>::Matrix2x2(T _m)
{
	m[0][0] = _m[0][0];
	m[0][1] = _m[0][1];
	m[1][0] = _m[1][0];
	m[1][1] = _m[1][1];
}

template <class T>
Matrix2x2<T>::Matrix2x2()
{
	m[0][0] = 0;
	m[0][1] = 0;
	m[1][0] = 0;
	m[1][1] = 0;
}

template <class T>
Matrix2x2<T>::Add(Matrix2x2 _x)
{
	Matrix2x2<T> sum;
	sum.m[0][0] = m[0][0] + _x.m[0][0];
	sum.m[0][1] = m[0][1] + _x.m[0][1];
	sum.m[1][0] = m[1][0] + _x.m[1][0];
	sum.m[1][1] = m[1][1] + _x.m[1][1];
	return sum;
}

template <class T>
Matrix2x2<T>::Multiply(Matrix2x2 _x)
{
	Matrix2x2<T> sum;
	sum.m[0][0] = m[0][0] * _x.m[0][0] + m[0][1] * _x.m[1][0];
	sum.m[0][1] = m[0][0] * _x.m[0][1] + m[0][1] * _x.m[1][1];
	sum.m[1][0] = m[1][0] * _x.m[0][0] + m[1][1] * _x.m[1][0];
	sum.m[1][1] = m[1][0] * _x.m[0][1] + m[1][1] * _x.m[1][1];
	return sum;
}

template <class T>
Matrix2x2<T>::Print()
{
	cout << "|" << m[0][0] << "  " << m[0][1] << "|" << endl;
	cout << "|" << m[1][0] << "  " << m[1][1] << "|" << endl;
}
//////////////////////////////////静态成员变量//////////////////////////////////////////
template <class T>
class XYZ
{
public:
	void putPri();
	static T ipub;
private:
	static T ipri;
};

template <class T>
void XYZ<T>::putPri()
{
	cout << ipri++ << endl;
}

// Static variable initialization:
template <class T> T XYZ<T>::ipub = 1;
template <class T> T XYZ<T>::ipri = 1.2;

void test2()
{
	XYZ<int> aaa;
	XYZ<float> bbb;

	aaa.putPri();
	cout << aaa.ipub << endl;
	bbb.putPri();
}
/////////////////////////////////模板参数/////////////////////////////////////////////
template <template <typename T> typename U>
class Xyz
{
	....
};

//////////////////////////继承-模板类继承非模板类//////////////////////////////////////

enum eColor { none = 0, red, white, blue, yellow, green, black };

class Color
{
public:
	Color(eColor color);
	void setColor(eColor color);
	eColor getColor() { return mColor; };
	std::string getStrColor();

protected:
	eColor mColor;
};

Color::Color(eColor _color)
{
	mColor = _color;
}

void Color::setColor(eColor _color)
{
	mColor = _color;
}

std::string Color::getStrColor()
{
	switch (mColor)
	{
	case red:
		return "red";
	case white:
		return "white";
	case blue:
		return "blue";
	case yellow:
		return "yellow";
	case green:
		return "green";
	case black:
		return "black";
	case none:
	default:
		return "none";
	}
}


template <typename T>
class Circle : public Color
{
public:
	Circle(T centerX, T centerY, T radius, eColor color);
	Circle(T centerX, T centerY, T radius);
	Circle(T radius);
	Circle();

	T area();
	T circumference();
	T getX();
	T getY();
	T getRadius();

protected:
	T x;
	T y;
	T radius;
};

template <typename T>
Circle<T>::Circle(T _x, T _y, T _radius, eColor _color)
	: Color(_color)
{
	x = _x;
	y = _y;
	radius = _radius;
}

template <typename T>
Circle<T>::Circle(T _x, T _y, T _radius)
	: Color(none)
{
	x = _x;
	y = _y;
	radius = _radius;
}

template <typename T>
Circle<T>::Circle(T _radius)
	: Color(none)
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
	radius = _radius;
}

template <typename T>
Circle<T>::Circle()
	: Color(none)
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
	radius = static_cast<T>(1);
}

template <typename T>
T Circle<T>::area()
{
	return M_PI * radius * radius;
}

template <typename T>
T Circle<T>::circumference()
{
	return static_cast<T>(2) * M_PI * radius;
}


void test3()
{
	Circle<float> circleA(0.0, 0.0, 10.0, white);
	cout << "Area: " << circleA.area() << endl;
	cout << "Color: " << circleA.getStrColor() << endl;
}
////////////////////////////////继承-非模板类继承模板类////////////////////////////////
class Sphere : public Circle<float>
{
public:
	Sphere(float centerZ, float centerX, float centerY, float radius, eColor color);
	Sphere(float radius);
	Sphere();

	float surfaceArea();
	float volume();
	float getZ();

private:
	float z;
};

Sphere::Sphere(float _x, float _y, float _z, float _radius, eColor _color)
	: Circle<float>::Circle(_x, _y, _radius, _color)
{
	this->z = _z;
}

Sphere::Sphere(float _radius): Circle::Circle(_radius)
{
	// Defaults from Circle(_radius) constructor can also initialize x, y, z
	this->x = static_cast<float>(0);
	this->y = static_cast<float>(0);
	this->z = static_cast<float>(0);
	this->radius = _radius;
}

Sphere::Sphere()
{
	// Defaults from Circle() default constructor can also initialize values
	this->x = static_cast<float>(0);
	this->y = static_cast<float>(0);
	this->z = static_cast<float>(0);
	this->radius = static_cast<float>(1);
}

float Sphere::surfaceArea()
{
	return static_cast<float>(4) * M_PI * this->radius * this->radius;
}

float Sphere::volume()
{
	float three = 3;
	float four = 4;
	return four * M_PI * this->radius * this->radius * this->radius / three;
}

void test4()
{
	Sphere sphereA(0.0, 0.0, 0.0, 10.0, blue);
	cout << "Volume: " << sphereA.volume() << endl;
	cout << "Color: " << sphereA.getStrColor() << endl;
}


/////////////////////////////继承-模板类继承模板类///////////////////////////////////
template <typename T>
class TSphere : public Circle<T>
{
public:
	TSphere(T centerZ, T centerX, T centerY, T radius, eColor color);
	TSphere(T radius);
	TSphere();

	T surfaceArea();
	T volume();
	T getZ();

private:
	T z;
};

template <typename T>
TSphere<T>::TSphere(T _x, T _y, T _z, T _radius, eColor _color)
	: Circle<T>::Circle(_x, _y, _radius, _color)
{
	this->z = _z;
}

template <typename T>
TSphere<T>::TSphere(T _radius)
	: Circle<T>::Circle(_radius)
{
	// Defaults from Circle(_radius) constructor can also initialize x, y, z
	this->x = static_cast<T>(0);
	this->y = static_cast<T>(0);
	this->z = static_cast<T>(0);
	this->radius = _radius;
}

template <typename T>
TSphere<T>::TSphere()
{
	// Defaults from Circle() default constructor can also initialize values
	this->x = static_cast<T>(0);
	this->y = static_cast<T>(0);
	this->z = static_cast<T>(0);
	this->radius = static_cast<T>(1);
}

template <typename T>
T TSphere<T>::surfaceArea()
{
	return static_cast<T>(4) * M_PI * this->radius * this->radius;
}

template <typename T>
T TSphere<T>::volume()
{
	T three = 3;
	T four = 4;
	return four * M_PI * this->radius * this->radius * this->radius / three;
}



void test5()
{
	TSphere<float> sphereA(0.0, 0.0, 0.0, 10.0, blue);
	cout << "Volume: " << sphereA.volume() << endl;
	cout << "Color: " << sphereA.getStrColor() << endl;
}
///////////////////////////////////////////////////////////////////////////////////
