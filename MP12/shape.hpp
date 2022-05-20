#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include<iomanip>    
#include<iterator>

#define PI 3.14159265358979323846 

using namespace std;

// partners: pjj3, xrouth2

/*
Introduction Paragraph: In this MP we were introduced to C++ by implementing the
Shape class, and each of its derived classes, with three other functions.
These functions are to create a list of shapes read from a file, then another two functions
to iterate through these lists and find the max volume and the max area of the shapes.
In order for these functions to work we needed to make the derived classes: circle, rectangle,
sphere, and rectprism. These classes will be able to calculate the area and volume of the shape.
They will also be able to add or subtract two of these shapes together. This is useful because in
the shape class we need to access the get area and the get shape functions, in order to implement the
max area and max volume functions.

*/

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		  name_ = name;//take the private variable "name_" and set it to the input name
	}
	
  	string getName() {
		return name_; //returns the private variable set by the input
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;//private variable


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = (T) 0, T length = (T) 0):Shape("Rectangle") {
		  width_ = width;
		  length_ = length;//set the values of private variables
	}
	
  	double getArea() const {
		//calculating the area using the area formula for rectangles
		return (double) (width_ * length_);
	}
	
  	double getVolume() const {
		//zero is returned because a rectangle is a 2d object with no volume
		return (double) 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		Rectangle<T> rect;// creating a new rectangle using the rectangle class 
		rect.length_ = this->length_ + rec.length_; //adding the lengths of the two rectangles
		rect.width_ = this->width_ + rec.width_;//adding the width of the two rectangles
		return rect;
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		Rectangle<T> rect;//creating a new rectangle using the rectangle class
		rect.length_ = max((T) 0, (T) (this->length_ - rec.length_));//subtracting the lengths of the two rectangles, if the output is negative then the length is zero
		rect.width_ = max((T) 0, (T) (this->width_ - rec.width_));//subtracting the widths of the two rectangles, if the output is negative then the width is zero
		return rect;
	} 
	
	T getWidth() const { 
		return width_;//returns the width
	}
	
	T getLength() const { 
		return length_;//returns the length
	}
private:
	T width_;//private variables
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius = 1.0):Shape("Circle") {
		  radius_ = radius;//set the values of the private variables
	}
	
  	double getArea() const{
		  return (radius_ * radius_ * PI);//calculates the area of the circle using the area formula for circles
	}
	
 	double getVolume() const{
		 return (double) 0;//returns zero because circles are 2d and will not have a volume

	}
	
  	Circle operator + (const Circle& cir){
		Circle circ;//creating a new circle using the circle class
		circ.radius_ = this->radius_ + cir.radius_;//adding the radii of two circles
		return circ;
	}
	
	Circle operator - (const Circle& cir){
		Circle circ;//creating a new circle using the circle
		circ.radius_ = max((double) 0, this->radius_ - cir.radius_);//subtracting the radii of two circles, but if the radius is negative then 0 is returned
		return circ;
	} 

	double getRadius() const { 
		return radius_;//returns the radius
	}
	
private:
	double radius_;//private varibles

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius = 1):Shape("Sphere") {
		radius_ = radius;//setting values to the private variables
	}

  	double getVolume() const {
		return (4.0 / 3.0) * (double) pow(radius_, 3) * PI;//calculating the volume of spheres using the formula for the volume of a sphere
	}	
	
  	double getArea() const {
		return 4 * PI * radius_ * radius_;//calculating the area of a sphere using the formula for the area of a sphere
	}

	Sphere operator + (const Sphere& sph) {
		Sphere sphere;//creating a new sphere using the sphere class
		sphere.radius_ = this->radius_ + sph.radius_;//adding the radii of two spheres
		return sphere;
	}

	Sphere operator - (const Sphere& sph) {
		Sphere sphere;//creating a new sphere using the sphere class
		sphere.radius_ = max((double) 0, this->radius_ - sph.radius_);//subtracting the radii of two spheres, if the radius is negative then zero is returned
		return sphere;
	} 
	
	double getRadius() const {
		return radius_;//returns the radius
	}

private:
	double radius_;//private variable

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width = 1.0, double length = 1.0, double height = 1.0):Shape("RectPrism") {
		width_ = width;//set the values of the private variables
		length_ = length;
		height_ = height;
	}
	
  	double getVolume() const {
		return width_ * height_ * length_;//calculating the volume of the rectangular prism using the formula for the volume of a rectprism
	}
  	
	double getArea() const {
		return 2 * ((length_ * width_)+ (length_ * height_) + (width_ * height_));//calculating the area of rectangular prisms using the formula for area of rectangular prisms
	}
	
	RectPrism operator + (const RectPrism& rectp){
		RectPrism rp;//making a new rectangular prism using the rectangular prism class
		rp.length_ = this->length_ + rectp.length_;//adding the lengths of the two RP's
		rp.width_ = this->width_ + rectp.width_;//adding the width of the two RP's
		rp.height_ = this->height_ + rectp.height_;//adding the height of the two RP's
		return rp;
	}
	
	RectPrism operator - (const RectPrism& rectp){
		RectPrism rp;
		rp.length_ = max(0.0, this->length_ - rectp.length_);//subtracting the lengths of the two RP's, if the value is less than zero then zero is returned
		rp.width_ = max(0.0, this->width_ - rectp.width_);//subtracting the widths of the two RP's, if the value is less than zero then zero is returned
		rp.height_ = max(0.0, this->height_ - rectp.height_);//subtracting the height of the two RP's, if the value is less than zero then zero is returned
		return rp;

	}	
	
	double getWidth() const { 
		return width_;//returns the width
	}
	
	double getLength() const { 
		return length_;//returns the length
	}
	
	double getHeight() const { 
		return height_;//returns the height
	}
private:
  	double length_;//private variables
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	ifstream ifs(file_name, ifstream::in);
	int length;
	ifs >> length;//take in the number of objects
	list<Shape*> shapes;

	while(!ifs.eof()) {//iterate through the file
		Shape* spt; //make a new shape
		string shapet;
		ifs >> shapet;// take in the name of the shape on that line

		if (shapet == "Circle") {//checks if the name of the shape is a circle
			double radius;
			ifs >> radius;//takes in the radius of the circle
			spt = new Circle(radius);//makes a new circle using the given radius
		}
		else if (shapet == "Rectangle"){//checks if the name of the shape is rectangle
			double width, length;
			ifs >> width >> length;//takes in the width and the length of the rect
			// Type is double unless both inputs are ints. 
			if (fmod(width, 1.0) == 0 && (fmod(length, 1.0) == 0)) {
				spt = new Rectangle<int>((int) width, (int) length);
			}
			else {
				spt = new Rectangle<double>(width, length);//makes a new rect with the given width and length
			}
		}
		else if (shapet == "Sphere") {//checks if the name of the shape is a sphere
			double radius;
			ifs >> radius;//takes in the radius of the shape
			spt = new Sphere(radius);//makes a new sphere with the given radius
		}
		else if (shapet == "RectPrism") {//checks if the name of the shape is a rectprism
			double width, length, height;
			ifs >> width >> length >> height;//takes in the height, width, and length
			spt = new RectPrism(width, length, height);//makes a new rectprism using the width, length, and height
		}
		if (shapet != "") {
			shapes.push_back(spt);
		}
	}

	ifs.close();//close the file
	return shapes;
}


// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	list<Shape*>::iterator it = shapes.begin();//iterator to the first element of the list of shapes
	do {
		//if the area of the respective shape is greater than the current max then that area becomes the new max area
		if (max_area < (double) ((*it)->getArea())) {
			max_area = (double) ((*it)->getArea());
		}
	} while (*it++ != shapes.back()); //increment the iterator until the end of the list
	
	return max_area;//returns the max area
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	list<Shape*>::iterator it = shapes.begin();//iterator to the first element of the list of shapes
	//increment the iterator until the end of the list
	while (*it != shapes.back()) {
		//if the volume of the respective shape is greater than the current volume then the volume of that shape becomes the new max volume
		if (max_volume < (double) ((*it)->getVolume())) {
			max_volume = (double) ((*it)->getVolume());
		}
		it++;
	}

	return max_volume;//returns the max volume
}
#endif