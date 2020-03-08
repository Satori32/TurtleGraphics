#pragma once
#include <cmath>
#include <algorithm>

#include "Surface24.h"

//ブレゼンハムはパクった。
//https://ja.wikipedia.org/wiki/ブレゼンハムのアルゴリズム

class TurtleGraphics {
public:

	typedef Surface24 Surface;
	typedef Surface24::Color Color;

    TurtleGraphics(std::size_t Width, std::size_t Height):S(Width,Height){}

    bool SetCanvas(std::size_t Width, std::size_t Height) {
        S.ReSize(Width, Height);
        return true;
    }

	bool Turn(double Angle) {
		A = std::abs(std::fmod(A+360.0+std::fmod(Angle,360.0),360.0));
		return true;
	}
    bool SetAngle(double Angle) {
		A = std::fmod(std::fmod(Angle,360.0)+360.0,360.0);
        return true;
    }

	bool Draw(double L) {
        double DX = std::sin(A*Rad) * L;
        double DY = std::cos(A*Rad) * L;

        if (OX + PX + DX >= Width()) { return false; }
        if (OY + PY + DY >= Height()) { return false; }
        Line(OX + PX, OY + PY, OX + PX + DX, OY + PY + DY);

        PX += DX;
        PY += DY;

        return true;
	}
    std::size_t Width() {
        return S.Width();
    }
    std::size_t Height() {
        return S.Height();
    }
    bool Move(double L) {
        PX += std::sin(A * Rad) * L;
        PY += std::cos(A * Rad) * L;

        return true;
    }
    double GetAngle() {
        return A;
    }

    bool SetPosition(double X, double Y) {
        PX = X - OX;
        PY = Y - OY;

        return true;
    }

    bool MovePosition(double X, double Y) {
        PX += X;
        PY += Y;
    }

    bool Clear() {
        S.Clear();
        S.ReSize(1,1);
        return true;
    }

    bool ReSize(std::size_t Width, std::size_t Height) {
        S.ReSize(Width, Height);
        return true;
    }

    bool SetOrigin(double X, double Y) {
        OX = X;
        OY = Y;

        return true;
    }
    bool MoveOrigin(double X, double Y) {
        OX += X;
        OY += Y;
        return true;
    }
    double GetX() {
        return OX + PX;
    }
    double GetY() {
        return OY + PY;
    }
    double GetOriginX() {
        return OX;
    }
    double GetOriginY() {
        return OY;
    }
    bool SetColor(std::uint8_t R, std::uint8_t G, std::uint8_t B) {
        C = MakeColor24(R, G, B);
        return true;
    }

    bool SetPixel(double X,double Y) {
        S.Index(OX + X, OY + Y) = C;
        return true;
    }

    const Surface& GetSurface() const {
        return S;
    }

    bool Line(double x0, double y0, double x1, double y1) {
        double dx = std::abs((double)(x1) - (double)(x0));
        double dy = std::abs((double)(y1) - (double)(y0));
        double sx = (x0 < x1) ? sx = 1 : sx = -1;
        double sy = (y0 < y1) ? sy = 1 : sy = -1;
        double err = dx - dy;

        std::size_t C = 0;

        while (true) {
            C++;
            SetPixel(x0, y0);

            double X = std::abs(x1 - x0);
            double Y = std::abs(y1 - y0);

            if (std::hypot(X, Y) <= 1) {
                break;
            }

            double e2 = 2 * err;

            if (e2 > -dy) {
                err = err - dy;
                x0 = x0 + sx;
            }
            if (e2 < dx) {
                err = err + dx;
                y0 = y0 + sy;
            }
        }
        return true;
    }
protected:
	double OX = 0;
	double OY = 0;

	double PX = 0;
	double PY = 0;
	double A = 0;
    double Rad = 3.1415926535/180.0;

	Surface24 S;
    Surface24::Color C;

};