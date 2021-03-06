#ifndef UTIL_HH
#define UTIL_HH

#include "vec2d.h"

bool circlesIntersect(Vec2D const& p1, float const r1, Vec2D const& p2, float const r2);
bool circleLineIntersect(Vec2D const& p, float const r, Vec2D const& l1, Vec2D const& l2, float const lr);
bool lineLineIntersect(Vec2D const& l11, Vec2D const& l12, float const l1r,
                       Vec2D const& l21, Vec2D const& l22, float const l2r);

bool rectsIntersect(Vec2D const& c1, float const w1, float const h1, Vec2D const& c2, float const w2, float const h2);
bool circleRectIntersect(Vec2D const& p, float const r, Vec2D const& c, float const w, float const h);
bool lineRectIntersect(Vec2D const& l1, Vec2D const& l2, float const lr, Vec2D const& c, float const w, float const h);

Vec2D circleLineIntersectionPoint(Vec2D const& p, float const r, Vec2D const& l1, Vec2D const& l2, float const lr);

float randInt(int const minValue, int const maxValue);
float randFloat(float const minValue, float const maxValue);
float lerp(float a, float b, float x);
#endif
