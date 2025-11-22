/**
 * @file geometry.hpp
 * @author Lukiancenko Liza
 * @brief Geometry
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

/// \cond
#include <cstring>
#include <cstddef>
/// \endcond
#include "list.hpp"

/**
 * @brief Base interface for geometric shapes.
 */
class Shape {
public:
    /**
     * @brief Move shape by offset.
     * @param x X-axis shift.
     * @param y Y-axis shift.
     */
    virtual void move(float x, float y) = 0;
};

class Point : public Shape {
public:
    float get_x() { return m_x; }
    float get_y() { return m_y; }
    void set_x(float v) { m_x = v; }
    void set_y(float v) { m_y = v; }
    void set_point(float x, float y) { m_x = x; m_y = y; }

    /**
     * @brief Move point.
     */
    void move(float x, float y) {
        m_x += x;
        m_y += y;
    }

private:
    float m_x;
    float m_y;
};

/**
 * @brief Line segment described by two points.
 */
class Line : public Shape {
public:
    const Point& get_p1() { return p1; }
    const Point& get_p2() { return p2; }
    void set_p1(const Point& v) { p1 = v; }
    void set_p2(const Point& v) { p2 = v; }

    /**
     * @brief Move line by shifting both endpoints.
     */
    void move(float x, float y) {
        p1.move(x, y);
        p2.move(x, y);
    }

private:
    Point p1, p2;
};

/**
 * @brief Triangle defined by 3 points.
 */
class Triangle : public Shape {
public:
    const Point& get_p1() { return p1; }
    const Point& get_p2() { return p2; }
    const Point& get_p3() { return p3; }

    void set_p1(const Point& v) { p1 = v; }
    void set_p2(const Point& v) { p2 = v; }
    void set_p3(const Point& v) { p3 = v; }

    /**
     * @brief Move all triangle vertices.
     */
    void move(float x, float y) {
        p1.move(x, y);
        p2.move(x, y);
        p3.move(x, y);
    }

private:
    Point p1, p2, p3;
};

/**
 * @brief Circle defined by center and radius.
 */
class Circle : public Shape {
public:
    const Point& get_center() { return center; }
    void set_center(Point v) { center = v; }

    float get_radius() { return radius; }
    void set_radius(float v) { radius = v; }

    /**
     * @brief Move the center of the circle.
     */
    void move(float x, float y) {
        center.move(x, y);
    }

private:
    Point center;
    float radius{};
};

/**
 * @brief Rectangle defined by 4 points.
 */
class Rectangle : public Shape {
public:
    const Point& get_p1() { return p1; }
    const Point& get_p2() { return p2; }
    const Point& get_p3() { return p3; }
    const Point& get_p4() { return p4; }

    void set_p1(const Point& v) { p1 = v; }
    void set_p2(const Point& v) { p2 = v; }
    void set_p3(const Point& v) { p3 = v; }
    void set_p4(const Point& v) { p4 = v; }

    /**
     * @brief Move all rectangle vertices.
     */
    void move(float x, float y) {
        p1.move(x, y);
        p2.move(x, y);
        p3.move(x, y);
        p4.move(x, y);
    }

private:
    Point p1, p2, p3, p4;
};

/**
 * @brief Square (same as Rectangle).
 */
class Square : public Rectangle {};

/**
 * @brief Polygon with dynamic number of vertices.
 */
class Polygon : public Shape {
public:
    /**
     * @brief Construct polygon.
     * @param v List of vertices.
     */
    Polygon(List<Point>& v)
        : vertices(v) {}

    const List<Point>& get_vertices() { return vertices; }

    void set_vertices(const List<Point>& v) { vertices = v; }

    /**
     * @brief Move all vertices of the polygon.
     */
    void move(float x, float y) {
        for (size_t i = 0; i < vertices.length(); i++) {
            vertices.get_mut(i).move(x, y);
        }
    }

private:
    List<Point>& vertices;
};