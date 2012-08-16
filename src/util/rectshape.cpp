#include "circleshape.h"
#include "lineshape.h"
#include "rectshape.h"
#include "util.h"

RectShape::RectShape(Vec2D const& center, float const width, float const height) :
  Shape(), center(center), width(width), height(height)
{
}
bool RectShape::collidesWith(CircleShape const* circle) const
{
  return circleRectIntersect(circle->center, circle->radius, center, width, height);
}

bool RectShape::collidesWith(LineShape const* line) const
{
  return lineRectIntersect(line->p1, line->p2, line->radius, center, width, height);
}

bool RectShape::collidesWith(RectShape const* rect) const
{
  return rectsIntersect(center, width, height, rect->center, rect->width, rect->height);
}
