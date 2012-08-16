#ifndef SHAPE_HH
#define SHAPE_HH

class CircleShape;
class LineShape;
class RectShape;

class Shape
{
public:
  virtual bool collidesWith(CircleShape const* circle) const = 0;
  virtual bool collidesWith(LineShape const* line) const = 0;
  virtual bool collidesWith(RectShape const* rect) const = 0;
};
#endif
