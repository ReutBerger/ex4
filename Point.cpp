//
// Created by reut on 1/19/20.
//

#include "Point.h"

Point::Point(int x, int y) {
    this->m_x = x;
    this->m_y = y;
}

int Point::getX() const {
    return this->m_x;
}

int Point::getY() const {
    return this->m_y;
}

void Point::setX(int x) {
    this->m_x = x;
}

void Point::setY(int y) {
    this->m_y = y;
}

Point::~Point() {

}