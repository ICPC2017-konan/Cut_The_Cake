#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

struct Square {
	int width, depth;
	bool operator<(const Square& rhs) const {
		return width * depth < rhs.width * rhs.depth;
	}
};

int main() {
	int n, w, d;
	Square s;
	while (std::cin >> n >> w >> d && (n || w || d)) {
		std::vector<Square> squares; //配列のインデックスが識別番号に相当
		squares.push_back(s);
		squares.back().width = w; squares.back().depth = d;

		for (int i = 0; i < n; i++) {
			int no, pos;
			std::cin >> no >> pos;
			no--;
			auto square = squares[no];
			pos %= (squares[no].width * 2 + squares[no].depth * 2);

			//切断
			int direction = 0; //0横方向 1縦
			int cutPos = 0; //上からの高さまたは左からの幅
			if (pos <= squares[no].width) {
				direction = 1;
				cutPos = pos;
			}
			else if (pos <= squares[no].width + squares[no].depth) {
				direction = 0;
				cutPos = pos - squares[no].width;
			}
			else if (pos <= squares[no].width * 2 + squares[no].depth) {
				direction = 1;
				cutPos = squares[no].width - (pos - (squares[no].depth + squares[no].width));
			}
			else {
				direction = 0;
				cutPos = squares[no].depth - (pos - (squares[no].width * 2 + squares[no].depth));
			}

			squares.erase(squares.begin() + no);

			Square newSquare[2] = { square, square };
			switch (direction)
			{
			case 0: //横方向
				newSquare[0].depth = cutPos;
				newSquare[1].depth = square.depth - cutPos;
				break;
			case 1: //縦
				newSquare[0].width = cutPos;
				newSquare[1].width = square.width - cutPos;
				break;
			default:
				break;
			}

			//小さい方から追加
			if (newSquare[0].depth * newSquare[0].width < newSquare[1].depth * newSquare[1].width) {
				squares.push_back(newSquare[0]);
				squares.push_back(newSquare[1]);
			}
			else {
				squares.push_back(newSquare[1]);
				squares.push_back(newSquare[0]);
			}
		}

		//小さい方から出力
		std::sort(squares.begin(), squares.end());

		for (int i = 0; i < squares.size(); i++) {
			std::cout << squares[i].width * squares[i].depth;
			if (i == squares.size() - 1) {
				std::cout << std::endl;
			}
			else {
				std::cout << " ";
			}
		}
	}
	return 0;
}