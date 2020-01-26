//
// Created by reut on 1/19/20.
//

#ifndef EX4_POINT_H
#define EX4_POINT_H

class Point {
private:
    int m_x;
    int m_y;
public:
    Point(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    virtual ~Point();
};

#endif //EX4_POINT_H
