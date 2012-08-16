#ifndef RECTSHAPE_HH
#define RECTSHAPE_HH

#include "shape.h"
#include "vec2d.h"

class RectShape : public Shape
{
public:
  RectShape(Vec2D const& center, float const width, float const height);
  virtual bool collidesWith(CircleShape const* circle) const;
  virtual bool collidesWith(LineShape const* line) const;
  virtual bool collidesWith(RectShape const* rect) const;

  Vec2D center;
  float width;
  float height;
};
#endif
