#include "object.h"

Object::Object(int x, int y, int h, int w){
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    //setXSpeed(0);
    //setYSpeed(0);
}

void Object::setX(int x){
    xLoc = x;
}

void Object::setY(int y){
    yLoc = y;
}

void Object::setHeight(int h){
    height = h;
}

void Object::setWidth(int w){
    width = w;
}

int Object::getX(){
    return xLoc;
}

int Object::getY(){
    return yLoc;
}

//int Object::getNewX(){
  //  return newXLoc;
//}

//int Object::getNewY(){
  //  return newYLoc;
//}

//void Object::setXSpeed(int x){
  //  xSpeed = x;
//}

//void Object::setYSpeed(int y){
  //  ySpeed = y;
//}

//void Object::update(){

//}

int Object::getHeight(){
    return height;
}

int Object::getWidth(){
    return width;
}