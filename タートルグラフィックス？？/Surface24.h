#pragma once
#include <algorithm>
#include <vector>
#include <cstdint>
#include <tuple>

#include <fstream>
#include <string>

class Surface24 {
public:
	typedef std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> Color;
	typedef std::vector<Color> Colors;
	
public:
	Surface24(){}
	Surface24(std::size_t Width, std::size_t Height) {
		Data.resize(Width * Height);

		W = Width;
		H = Height;
	}

	const Color& Index(std::size_t X, std::size_t Y) const{
		return Data[Y * W + X];
	}

	Color& Index(std::size_t X, std::size_t Y){

		if (X >= W) { std::out_of_range("out of range in Surface24::Index()"); }
		if (Y >= H) { std::out_of_range("out of range in Surface24::Index()"); }

		return Data[Y * W + X];
	}
	bool SetColor(std::size_t X,std::size_t Y,Color C) {
		Data[Y * W + X] = C;
		return true;
	}
	bool ReSize(std::size_t Width, std::size_t Height) {
		Surface24 R(Width, Height);

		std::size_t He = std::min(H, Height);
		std::size_t Wi = std::min(W, Width);

		for (std::size_t Y = 0; Y < He; Y++) {
			for (std::size_t X = 0; X < Wi; X++) {
				R.Index(X, Y) = Index(X, Y);
			}
		}

		(*this) = R;

		return true;
	}
	bool Clear() {

		Data.clear();
		Data.push_back({});
		W = 1;
		H = 1;

		return true;

	}
	std::size_t Size() const{
		return Data.size();
	}

	std::size_t Width() const{
		return W;
	}
	std::size_t Height() const{
		return H;
	}

protected:

	Colors Data{1};
	std::size_t W = 1;
	std::size_t H = 1;
};

Surface24::Color MakeColor24(std::uint8_t R, std::uint8_t G, std::uint8_t B) {
	return std::make_tuple(R, G, B);
}

bool WriteBitmap24(const std::string& Name,const Surface24& In) {
	std::ofstream ofs(Name, std::ios::binary);

	std::uint16_t i16 = 0;
	std::uint32_t i32 = 0;

	//BITMAP FILE HEADER
	i16 = 'B' + ('M' << 8);
	ofs.write((char*)&i16, 2);

	//i32 = 14 + 40 + ((In.Width()*3) + ((In.Width() % 4 > 0) ? 4 - In.Width() % 4 : 0))* In.Height();
	i32 = 14 + 40 + ((In.Width()*3) * In.Height());
	ofs.write((char*)&i32, 4);

	i16 = 0;
	ofs.write((char*)&i16, 2);
	ofs.write((char*)&i16, 2);

	i32 = 14 + 40;
	ofs.write((char*)&i32, 4);

	//BITMAP INFO HEADER
	i32 = 40;
	ofs.write((char*)&i32, 4);
	i32 = In.Width();
	ofs.write((char*)&i32, 4);
	i32 = In.Height();
	ofs.write((char*)&i32, 4);

	i16 = 1;
	ofs.write((char*)&i16, 2);
	i16 = 24;
	ofs.write((char*)&i16, 2);
	
	i32 = 0;//no conpress
	ofs.write((char*)&i32, 4);
	
	//i32 =((In.Width()*3) + ((In.Width() % 4 > 0) ? 4 - In.Width() % 4 : 0))* In.Height();
	i32 =(In.Width()*3)* In.Height();
	//i32 = 3780;
	ofs.write((char*)&i32, 4);
	
	i32 =0;
	ofs.write((char*)&i32, 4);
	i32 =0;
	ofs.write((char*)&i32, 4);

	i32 =0;
	ofs.write((char*)&i32, 4);
	i32 =0;
	ofs.write((char*)&i32, 4);

	for (std::intmax_t Y = In.Height()-1; Y >= 0; Y--) {
		for (std::size_t X = 0; X < In.Width(); X++) {
			const Surface24::Color& C = In.Index(X, Y);

			std::uint8_t i8 = 0;

			i8 = std::get<2>(C);
			ofs.write((char*)&i8, 1);
			i8 = std::get<1>(C);
			ofs.write((char*)&i8, 1);
			i8 = std::get<0>(C);
			ofs.write((char*)&i8, 1);
		}
		/**/
		if ((In.Width()*3) % 4) {
			for (std::size_t i = (In.Width()*3) % 4; i < 4; i++) {
				std::uint8_t i8 = 0xff;
				ofs.write((char*)&i8, 1);
			}
		}
		/**/
	}

	return true;
}