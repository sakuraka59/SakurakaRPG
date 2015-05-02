#pragma once

class RenderObject;
class HitCircle
{
protected: RenderObject* _render_obj;
protected: double _radius;

public: HitCircle(RenderObject* render_obj, double radius);
public: double getCneterX();
public: double getCneterY();
public: double getRadius();

};