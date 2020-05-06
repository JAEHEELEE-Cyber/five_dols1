
/*
main ���� ����

�Ʊ� AI, ���� AI ����
�Ʊ��� ���� �ΰ�

������ ���� ���� ����ġ�� ����Ͽ� �����Ӱ� �δ� ���

*��ġ����*

�� ������ �ΰ� �ִ� ������ ������� ����
Ž�� ���� �غ���

*/

#include <Windows.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#define endl '\n'
using namespace std;
int map[19][19];//�ٵ� ��
int w_board[19][19];//����ġ ��
int dir[8][2] = { { 1,0 },{ 0,1 },{ 1,1 },{ 1,-1 },{ -1,0 },{ 0,-1 },{ -1,-1 },{ -1,1 } };

int n = 19;
int w[2][6] = { { 0,2,25,421,1200000,10000000 },{ 0,1,22,105,17000,10000000 } };//�� 3���ٴ� ��2  //�� 4���ٴ� ��3// ����� �� 4�� �� ŭ
int w2[2][6][3][2];
void init() {
	// my or your / num / enemy / space
	//num=1 �϶� ����� 0�ΰ͸� 1 �������� 0
	w2[0][1][0][0] = w2[1][1][0][0] = 1;
	w2[0][1][0][1] = 1;
	//num=2 �϶�
	w2[0][2][0][0] = 29, w2[1][2][0][0] = 23;
	w2[0][2][0][1] = 29;

	//num=3
	w2[0][3][0][1] = 301;
	w2[0][3][0][0] = 20000, w2[1][3][0][0] = 91, w2[1][3][0][1] = 36, w2[1][3][1][0] = 1, w2[1][3][1][1] = 1;
	w2[0][3][1][0] = 301, w2[0][3][1][1] = 301;

	//num=4
	w2[0][4][0][0] = 21000; w2[0][4][1][0] = 20010; w2[0][4][2][0] = 20010;
	w2[1][4][0][0] = 4001; w2[1][4][1][0] = 4001; w2[1][4][2][0] = 4001;
}

typedef struct xy {
	int x, y;
}xy;
typedef struct info {
	int num = 0, enemy = 0, emptyspace = 0;
}info;

void search() {

}

xy add_weight(int color[2]) {//���� �� ��ó�� ����ġ �ο�
	memset(w_board, 0, sizeof(w_board));
	//�����ϰ� ���� �װ��� ����ġ�� 0���� ����� ������ ���� ����ġ �ο��� ���� �ʴ´�.
	//���� �װ��� ���� ���� ��� �ش� �ڸ� ��ó��
	//2,��2 ����2 �̷��� ����� Ȯ���ؾ���
	//1,2,3,4,��1,��2,��3,��4
	for (int type = 0; type < 2; type++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int sum = 0;
				info Count[5];//����, ����, ����, ��� �� ����
				if (map[i][j])continue;
				for (int d = 0; d < 4; d++) {
					int nx, ny;
					int cnt = 1;
					int zerocnt = 0;//�� ��ĭ 0~ 2 �������� �����ϵ��� ���鲨
					int zerocnt1 = 0;
					int remember = 0;
					int zerocnt2 = 0;
					int num = 0;
					int enemy_cnt = 0;
					int before;

					//cout << "������ " << endl;
					while (true) {
						nx = i + (cnt * dir[d][0]), ny = j + (cnt * dir[d][1]);
						before = map[nx - dir[d][0]][ny - dir[d][1]];
						//cout << "nx " << ny << " ny " << ny << " num " << num << " zerocnt " << zerocnt1 << " remember " << remember << " enemy " << enemy_cnt << endl;
						if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
							if (remember || zerocnt1 == 0) {
								enemy_cnt++;
							}
							if (before != 0)remember = zerocnt1;

							break;
						}
						if (map[nx][ny] == color[(type + 1) % 2]) {
							if (remember || zerocnt1 == 0) {
								enemy_cnt++;
							}
							if(before != 0)remember = zerocnt1;

							break;
						}
						
						if (map[nx][ny] == color[type]) {
							remember = zerocnt1;
							num++;
						}
						if (map[nx][ny] == 0)zerocnt1++;
						if (zerocnt1 >= 2)break;
						cnt++;
					}
					//cout <<"d: "<<d<< "remember " << remember <<" length "<<length<< endl;
					zerocnt1 = remember;
					cnt = 1;
					remember = 0;
					//�ݴ������
					//cout << "�ݴ���� " << endl;
					while (true) {
						nx = i + (cnt * dir[d + 4][0]), ny = j + (cnt * dir[d + 4][1]);
						//cout << "nx " << ny << " ny " << ny << " num " << num << " zerocnt " << zerocnt1 << " remember " << remember << " enemy " << enemy_cnt << endl;
						if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
							if (remember || zerocnt2 == 0) {
								enemy_cnt++;
							}
							if (before != 0)remember = zerocnt2;
							break;
						}
						if (map[nx][ny] == color[(type + 1) % 2]) {
							if (remember || zerocnt2 == 0) {
								enemy_cnt++;
							}
							if (before != 0)remember = zerocnt2;
							break;
						}
						
						if (map[nx][ny] == color[type]) {
							remember = zerocnt2;
							num++;
						}
						if (map[nx][ny] == 0)zerocnt2++;
						if (zerocnt2 >= 2)break;
						cnt++;
					}
					zerocnt2 = remember;
					zerocnt = zerocnt1 + zerocnt2;
					Count[d] = { num,enemy_cnt,zerocnt };
				}


				//

				//cout << "x " << i << " y " << j << " ����� ���ǵ� ������ �����ִ� ��� �� ���� " << endl;
				//for (int d = 0; d < 4; d++) {
				//	cout << d << ": " << Count[d].num << " " << Count[d].enemy<<" "<<Count[d].emptyspace << endl;
				//}
				//cout << endl;

				//���� ���� ��밡 ���� ���� ����ġ ���� ���� �帮��
				for (int d = 0; d < 4; d++) {
					int num = Count[d].num, enemy = Count[d].enemy, emptyspace = Count[d].emptyspace;
					int temp_w = w2[(type + 1) % 2][num][enemy][emptyspace];
					//�� ������ �ϳ��� ����, num+emptyspace>=5,enemy 2�� ����ġ �ο����� �ʴ´�. 
					if (emptyspace >= 2 || num + emptyspace >= 5)continue;
					if (num != 4 && enemy >= 2)continue;
					sum += temp_w;

				}
				w_board[i][j] += sum;
				if (map[i][j])w_board[i][j] = 0;
			}
		}
	}

	xy ret;
	int high = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (high < w_board[i][j]) {
				ret = { i,j };
				high = w_board[i][j];
			}
			else if (high == w_board[i][j]) {
				for (int d = 0; d < 8; d++) {
					int nx = i + dir[d][0], ny = j + dir[d][1];
					if (nx < 0 || ny < 0 || nx >= n || ny >= n)continue;
					if (map[nx][ny]) {
						ret = { i,j };
					}
					nx = i + dir[d][0], ny = j + dir[d][1];
					if (nx < 0 || ny < 0 || nx >= n || ny >= n)continue;
					if (map[nx][ny]) {
						ret = { i,j };
					}
				}
			}
		}
	}

	//����ġ����

	cout << "weight board" << endl;
	cout << " x/y ";
	for (int j = 0; j < n; j++) {
		cout.width(5);
		cout << j;
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout.width(5);
		cout << i;
		for (int j = 0; j < n; j++) {
			cout.width(5);
			cout << w_board[i][j];
		}
		cout << endl;
	}
	cout << endl;

	return ret;
}

void AI(int user_color, int ai_color) {
	int color[2] = { user_color,ai_color };
	xy pos = add_weight(color);
	//AI �˰��� ����
	map[pos.x][pos.y] = ai_color;
}

void Print() {
	cout << "x|y";
	for (int j = 0; j < n; j++) {
		cout.width(3);
		cout << j;
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout.width(3);
		cout << i;
		for (int j = 0; j < n; j++) {
			cout.width(3);
			if (map[i][j])
				cout << map[i][j];
			else cout << "";
		}
		cout << endl;
	}
}

void input(int type) {
	int x, y;
	while (true) {
		cout << "Waht is your next position (x,y)?: ";
		cin >> x >> y;
		if (x >= 0 && y >= 0 && x < n&&y < n&&map[x][y] == 0) {
			map[x][y] = type;
			break;
		}
		else {
			cout << "try other position" << endl;
		}

	}

	cout << endl;
}

void game_type(int type) {
	if (type == 1) {
		cout << "your color is black(1). please input 1! " << endl << endl;
		int turn = 0;
		while (true) {
			cout << "Your turn" << endl;
			Print();
			input(type);

			//AI turn
			cout << "AI turn" << endl;
			Print();
			Sleep(1000);

			AI(1, 2);
			turn++;
		}
	}

	else if (type == 2) {
		cout << "your color is white(2). please input 2! " << endl << endl;
		int turn = 0;
		while (true) {
			//AI turn
			cout << "AI turn" << endl;
			Print();
			Sleep(1000);
			if (turn == 0) {
				map[9][9] = 1;
			}
			else AI(2, 1);

			cout << "Your turn" << endl;
			Print();
			input(type);

			turn++;

		}
	}

}


int main() {
	init();
	cout << "well come, Five dols!" << endl;
	cout << "1: play black, 2: play white" << endl;
	int start;
	cin >> start;
	game_type(start);

}

