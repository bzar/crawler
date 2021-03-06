#include "circleshape.h"
#include "lineshape.h"
#include "rectshape.h"
#include "util.h"

CircleShape::CircleShape(Vec2D const& center, float const radius) :
  Shape(), center(center), radius(radius)
{
}
bool CircleShape::collidesWith(CircleShape const* circle) const
{
  return circlesIntersect(center, radius, circle->center, circle->radius);
}

bool CircleShape::collidesWith(LineShape const* line) const
{
  return circleLineIntersect(center, radius, line->p1, line->p2, line->radius);
}

bool CircleShape::collidesWith(RectShape const* rect) const
{
  return circleRectIntersect(center, radius, rect->center, rect->width, rect->height);
}
