#pragma once

class HitSquare{

protected: double _x = 0;
protected: double _y = 0;
protected: double _width = 0;
protected: double _height = 0;
protected: double _angle = 0;

		   // �L�����N�^�[���̈ړ����镨�̏ꍇ��z�肵��
		   // �Q�Ɠn���ň������󂯎��
public: HitSquare(double& x, double& y, double width, double height, double& angle);
public: double getX();
public: double getY();
public: double getWidth();
public: double getHeight();
public: double getAngle();
};