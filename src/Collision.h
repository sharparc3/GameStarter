#pragma once
#include <utility>

namespace Shape
{
	typedef struct Point
	{
		float x;
		float y;
	} Point;

	typedef struct Rect
	{
		float x;
		float y;
		float w;
		float h;
	} Rect;

	typedef struct Circle
	{
		Point center;
		float radius;
	} Circle;
    

    // Point vs. Point
    bool isColliding(const Point& p1, const Point& p2) 
    {
        return (p1.x == p2.x) && (p1.y == p2.y);
    }

    // Point vs. Rect
    bool isColliding(const Point& p, const Rect& r) 
    {
        return (p.x >= r.x) && (p.x <= r.x + r.w) &&
            (p.y >= r.y) && (p.y <= r.y + r.h);
    }

    bool isColliding(const Rect& r, const Point& p)
    {
        return isColliding(p, r);
    }

    // Point vs. Circle
    bool isColliding(const Point& p, const Circle& c) 
    {
        float dx = p.x - c.center.x;
        float dy = p.y - c.center.y;
        return (dx * dx + dy * dy) <= (c.radius * c.radius);
    }

    bool isColliding(const Circle& c, const Point& p)
    {
        return isColliding(p, c);
    }

    // Rect vs. Rect
    bool isColliding(const Rect& r1, const Rect& r2) 
    {
        return (r1.x < r2.x + r2.w) && (r1.x + r1.w > r2.x) &&
            (r1.y < r2.y + r2.h) && (r1.y + r1.h > r2.y);
    }

    // Circle vs. Circle
    bool isColliding(const Circle& c1, const Circle& c2) 
    {
        float dx = c1.center.x - c2.center.x;
        float dy = c1.center.y - c2.center.y;
        float distance = dx * dx + dy * dy;
        float radiusSum = c1.radius + c2.radius;
        return distance <= (radiusSum * radiusSum);
    }

    // Rect vs. Circle
    bool isColliding(const Rect& r, const Circle& c) 
    {
        float closestX = std::max(r.x, std::min(c.center.x, r.x + r.w));
        float closestY = std::max(r.y, std::min(c.center.y, r.y + r.h));
        float dx = c.center.x - closestX;
        float dy = c.center.y - closestY;
        return (dx * dx + dy * dy) <= (c.radius * c.radius);
    }

    bool isColliding(const Circle& c, const Rect& r)
    {
        return isColliding(r, c);
    }
}

