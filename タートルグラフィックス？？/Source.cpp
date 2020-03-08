#include "TurtleGraphics.h"
#include <string>

bool RollCake(TurtleGraphics& TG, std::size_t W,std::size_t H) {
	TG.Clear();
	TG.ReSize(W, H);
	TG.SetColor(0xff, 0, 0);

	TG.SetPosition(W/2, H/2);
	std::size_t C = 1;

	for (std::size_t i = 1; i < 16*8; i++) {
		TG.Draw(i);
		TG.Turn(17);
	}

	return true;
}

bool Draw5(TurtleGraphics& TG, std::size_t L, char S) {
	TG.Draw(L);
	TG.Draw(L);
	TG.Turn(90 * S);
	TG.Draw(L);
	TG.Turn(90 * S);
	TG.Draw(L);
	TG.Draw(L);
	TG.Turn(-90 * S);
	TG.Draw(L);
	TG.Turn(-90 * S);
	TG.Draw(L);
	TG.Draw(L);
	return true;
}

bool Peano(TurtleGraphics& TG, std::size_t W, std::size_t H) {
	std::size_t L = 32;

	TG.Clear();
	TG.ReSize(W, H);
	TG.SetColor(0xff, 0, 0);

	TG.SetAngle(180);
	TG.SetPosition(L,H-L);

	char S = -1;
	
	for (std::size_t k = 0; k < 3; k++) {
		for (std::size_t j = 0; j < 3; j++) {
			for (std::size_t i = 0; i < 3; i++) {
				Draw5(TG, L, S);

				if (i != 2) { TG.Draw(L); }
				S *= -1;
			}
			if (j != 2) {
				TG.Turn(90 * -S);
				TG.Draw(L);
				TG.Turn(90 * -S);
			}
			else {
				if (k == 2) { TG.Turn(-90 * S); }
					TG.Draw(L);
				
			}
		}
	}
	return true;
}
bool Peano_1(TurtleGraphics& TG,std::size_t L, std::size_t D,char S) {
	Draw5(TG, L, S);
	TG.Draw(L);
	Draw5(TG, L, -S);
	TG.Draw(L);
	Draw5(TG, L, S);

	return true;
}
bool Peano_2(TurtleGraphics& TG,std::size_t L, std::size_t D,char S) {
	Peano_1(TG, L, D, S);
	TG.Draw(L);
	Peano_1(TG, L, D, -S);
	TG.Draw(L);
	Peano_1(TG, L, D, S);
	return true;
}
bool Peano_3(TurtleGraphics& TG,std::size_t L, std::size_t D,char S) {
	Peano_2(TG, L, D, S);
	TG.Turn(90 * S);
	TG.Draw(L);	
	TG.Turn(90 * S);
	Peano_2(TG, L, D, -S);
	return true;
}
bool Peano_4(TurtleGraphics& TG,std::size_t L, std::size_t D,char S) {
	Peano_3(TG, L, D, S);
	TG.Turn(90 * -S);
	TG.Draw(L);	
	TG.Turn(90 * -S);
	//Peano_3(TG, L, D, -S);
	return true;
}
bool Peano2(TurtleGraphics& TG, std::size_t W, std::size_t H) {
	std::size_t L = 32;

	TG.Clear();
	TG.ReSize(W, H);
	TG.SetColor(0xff, 0, 0);

	TG.SetAngle(180);
	TG.SetPosition(L,H-L);

	char S = -1;
	Peano_4(TG, L, 3, S);
	return true;
}

bool Peano__1(TurtleGraphics& TG,std::size_t L, std::size_t D,char S) {
	Draw5(TG, L, S);
	TG.Draw(L);
	Draw5(TG, L, -S);
	TG.Draw(L);
	Draw5(TG, L, S);
	
	return true;
}
bool Peano__2(TurtleGraphics& TG, std::size_t L, std::size_t D, char S) {
	Peano__1(TG, L, D,S);
	TG.Turn(90*S);
	TG.Draw(L);
	TG.Turn(90 * S);
	Peano__1(TG, L, D,-S);
	TG.Turn(90*-S);
	TG.Draw(L);
	TG.Turn(90 * -S);
	Peano__1(TG, L, D,S);


	return true;
}
bool Peano__3(TurtleGraphics& TG, std::size_t L, std::size_t D, char S) {
	Peano__2(TG, L, D,S);
	TG.Draw(L);
	Peano__2(TG, L, D,-S);
	TG.Draw(L);
	Peano__2(TG, L, D,S);
	return true;
}
bool Peano__4(TurtleGraphics& TG, std::size_t L, std::size_t D, char S) {
	Peano__3(TG, L, D,S);
	TG.Turn(90 * S);
	TG.Draw(L);
	TG.Turn(90 * S);
	Peano__3(TG, L, D,-S);	
	TG.Turn(90 * -S);
	TG.Draw(L);
	TG.Turn(90 * -S);
	Peano__3(TG, L, D,S);
	return true;
}
bool Peano3(TurtleGraphics& TG, std::size_t W, std::size_t H) {
	std::size_t L = 4;

	TG.Clear();
	TG.ReSize(W, H);
	TG.SetColor(0xff, 0, 0);

	TG.SetAngle(180);
	TG.SetPosition(W/2,H/2);

	char S = -1;
	std::size_t C = 0;
	std::size_t X = 1;
	while (C<2) {
		for (std::size_t i = 0; i < X+(C>2?1:0); i++) {
			Peano__4(TG, L, 0, S);
			if (i != (X+(C>2?1:0)) - 1) { TG.Draw(L); }
			S *= -1;
		}
		TG.Turn(-90);
		//TG.Draw(L);	
		//TG.Turn(-90);
		S *= -1;
		X+=1;
		C++;
	}
	return true;
}

bool calcTriOrigin(TurtleGraphics& TG,double L,double C,double Angle) {

	TG.SetOrigin(TG.Width() / 2, TG.Height() / 2);
	TG.SetPosition(0, 0);

	double X = 0;
	double Y = 0;

	TG.SetAngle(Angle);
	TG.Move(L-(L - C));

	TG.MoveOrigin(TG.GetX(), TG.GetY());


	return true;
}
/** /
bool calcTriOrigin(TurtleGraphics& TG,double L,double C,double Angle) {

	TG.SetOrigin(TG.Width() / 2, TG.Height() / 2);
	TG.SetPosition(0, 0);

	double X = 0;
	double Y = 0;

	TG.SetAngle(Angle);
	TG.Move(C);

	TG.Turn(150);
	X += TG.GetX();
	Y += TG.GetY();
	TG.Turn(120);
	TG.Move(L);
	X += TG.GetX();
	Y += TG.GetY();
	TG.Turn(120);
	TG.Move(L);
	X += TG.GetX();
	Y += TG.GetY();

	TG.SetOrigin(TG.Width()+(X / 3),(Y / 3));
	TG.SetAngle(Angle);

	return true;
}
/**/
bool DrawTri(TurtleGraphics& TG, double L, double C) {
TG.SetPosition(0, 0);
	
		TG.Turn(90);
		TG.Turn(60);

		TG.Draw(L);
		TG.Turn(120);
		TG.Draw(L);
		TG.Turn(120);
		TG.Draw(L);

		return true;
}

bool RollTri(TurtleGraphics& TG) {

	std::string Name = "RollTri";

	double W = 256/2;
	double H = 256/2;

	TG.Clear();
	TG.SetColor(255, 0, 0);
	TG.ReSize(W, H);
	TG.SetOrigin(W/2, H/2);

	double L = 100;
	//double C = ((std::sqrt(L*L-(L/2*L/2))/3)*2);
	double C = 50.0;
	std::size_t D = 60;
	double Delta = (360 / D);
	double rad = 3.1415926535 / 180.0;
	for (std::size_t i = 0; i <D ; i++) {
		calcTriOrigin(TG, L, C, i * Delta);
		
		TG.SetPosition(0, 0);	
		TG.SetAngle(i * Delta);
		TG.Move(C);

		DrawTri(TG, L, C);

		WriteBitmap24( Name + std::to_string(i) + ".bmp",TG.GetSurface());
		TG.Clear();
		TG.ReSize(W, H);
	}
	return true;
}

int main() {
	TurtleGraphics TG(1,1);
	//RollCake(TG,1024,1024);
	//Peano3(TG, 1024, 1024);
	RollTri(TG);
	WriteBitmap24("tri.bmp",TG.GetSurface() );
	
	return 0;
}
/** /
int main() {
	TurtleGraphics TG(101, 101);

	TG.SetColor(0xff, 0, 0);

	//TG.Line(0, 0, 128, 128);

	TG.SetPosition(0, 100);
	TG.SetAngle(90);
	TG.Draw(100);
	TG.Turn(120);
	TG.Draw(100);	
	TG.Turn(120);
	TG.Draw(100);

	WriteBitmap24("TG.bmp", TG.GetSurface());

	return 0;
}
/**/