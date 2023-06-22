#include "ofApp.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <stack>
#include <queue>

//--------------------------------------------------------------
void ofApp::setup() { // ���� ������ ���ִ� �Լ�
	ofSetFrameRate(30); // �ʴ� �������� �������ش�.
	ofBackground(255, 255, 255); // ����� ���� ������� �������ش�.

	game_flag = 0; // �÷��׵��� �ʱ�ȭ���ش�.
	key_flag = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() { // �̷ο� �÷��̾ �׷��ִ� �Լ�
	int area = 10; // ���� ũ�⸦ 10���� �������ش�.

	if (game_flag == 1) { // ������ ���۵Ǿ��ٸ� �׷��ش�.
		drawShadow(); // �̷ο� �׸��ڸ� ���� �׷��ش�.

		ofSetColor(0); // ���� ���� ���������� �������ش�.
		ofSetLineWidth(10); // ���� ���⸦ 10���� �������ش�.
		for (int i = 0; i < HEIGHT; i += 2) { // �̷θ� ������ �迭�� ���鼭 ���� �׾�� �ϴ� ���� ã���ش�.
			for (int j = 0; j < WIDTH; j += 2) {
				if (i != HEIGHT - 1) {
					if (maze[i][j] == -1 && maze[i + 1][j] == -1) { // ���� ��ġ�� ���̰� �ٷ� �����ʵ� ���̶��
						ofDrawLine(j * area + 5, i * area, j * area + 5, (i + 2) * area + 10); // ���� �׷��ش�.
					}
				}
				if (j != WIDTH - 1) {
					if (maze[i][j] == -1 && maze[i][j + 1] == -1) { //���� ��ġ�� ���̰� �ٷ� �ص� ���̶��
						ofDrawLine(j * area, i * area + 5, (j + 2) * area + 10, i * area + 5); // ���� �׷��ش�
					}
				}
			}
		}

		ofSetColor(0); // �÷��̾��� ��ġ�� ������ ��ġ�� ���������� �����Ѵ�.
		if (save_flag == 1) { // ���� ���� �� ��ġ�� �����ߴٸ�
			ofDrawCircle(sx * area + 5, sy * area + 5, 5); // ������ ��ġ�� �׷��ش�.
		}
		ofDrawCircle(px * area + 5, py * area + 5, 5); // �÷��̾ �׷��ش�.

		if (px == WIDTH - 2 && py == HEIGHT - 2) { // ���� ���������� �����ߴٸ� ������ �� ���̹Ƿ�
			gameClear(); // ������ ���� �� �ʿ��� �͵��� ���ش�.
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) { // Ű�� Ŭ���� �Ǿ��� �� �۵��ϴ� �Լ�
	if (key == 's') { // s�� ������
		if (game_flag == 0 && key_flag == 0) { // ���� ���� �ƴϸ鼭 �ٸ� �۾��� ���� ���� �ƴ϶��
			key_flag = 1; // �۾� ������ ǥ�ø� ���ش�.
			gameStart(); // ������ ������ �� �ʿ��� �͵��� ���ش�.
			key_flag = 0; // �۾��� �����ٰ� ǥ�ø� ���ش�.
		}
	}

	if (key == 'r') { // r�� ������
		if (key_flag == 0) { // �ٸ� �۾��� ���� ���� �ƴ϶��
			game_flag = 0; // ���� ���� �ƴ϶�� ǥ�ø� ���ش�.
			key_flag = 1; // �۾� ������ ǥ�ø� ���ش�.
			freeMemory(); // ���� �Ҵ��� �޸𸮸� �������ش�.
			gameStart(); // ������ ������ �� �ʿ��� �͵��� ���ش�.
			key_flag = 0; // �۾��� �����ٰ� ǥ�ø� ���ش�.
		}
	}

	if (key == 'q') { // q�� ������
		if (key_flag == 0) { // �ٸ� �۾��� ���� ���� �ƴ϶��
			game_flag = 0; // ���� ���� �ƴ϶�� ǥ�ø� ���ش�.
			key_flag = 1; // �۾� ������ ǥ�ø� ���ش�.
			printf("Good Bye!\n");
			freeMemory(); // ���� �Ҵ��� �޸𸮸� �������ش�.
			_Exit(0); // ���α׷��� �������ش�.
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) { // Ű�� Ŭ���ߴ� ������ �� �۵��ϴ� �Լ�
	if (key == OF_KEY_RIGHT) { // ������ ����Ű�� ������ �ð�
		if (game_flag == 1 && px + 2 < WIDTH) { // ���� ���̸鼭 �÷��̾ ���� ������ ���� ���� �ʰ�
			if (maze[py][px + 1] != -1) { // �÷��̾��� �����ʿ� ���� ���ٸ�
				px += 2; // �÷��̾ ���������� �̵����� �ش�.
				cnt++; // �÷��̾ �̵��� Ƚ���� 1�� �����ش�.
			}
		}
	}

	if (key == OF_KEY_LEFT) { // ���� ����Ű�� ������ �ð�
		if (game_flag == 1 && px - 2 >= 0) { // ���� ���̸鼭 �÷��̾ ���� ���� ���� ���� �ʰ�
			if (maze[py][px - 1] != -1) { // �÷��̾��� ���ʿ� ���� ���ٸ�
				px -= 2; // �÷��̾ �������� �̵����� �ش�.
				cnt++; // �÷��̾ �̵��� Ƚ���� 1�� �����ش�.
			}
		}
	}

	if (key == OF_KEY_DOWN) { // �Ʒ��� ����Ű�� ������ �ð�
		if (game_flag == 1 && py + 2 < HEIGHT) { // ���� ���̸鼭 �÷��̾ ���� �Ʒ��� ���� ���� �ʰ�
			if (maze[py + 1][px] != -1) { // �÷��̾��� �Ʒ��ʿ� ���� ���ٸ�
				py += 2; // �÷��̾ �Ʒ������� �̵����� �ش�.
				cnt++; // �÷��̾ �̵��� Ƚ���� 1�� �����ش�.
			}
		}
	}

	if (key == OF_KEY_UP) { // ���� ����Ű�� ������ �ð�
		if (game_flag == 1 && py - 2 >= 0) { // ���� ���̸鼭 �÷��̾ ���� ���� ���� ���� �ʰ�
			if (maze[py - 1][px] != -1) { // �÷��̾��� ���ʿ� ���� ���ٸ�
				py -= 2; // �÷��̾ �������� �̵����� �ش�.
				cnt++; // �÷��̾ �̵��� Ƚ���� 1�� �����ش�.
			}
		}
	}

	if (key == 't') { // t�� ������ �ð�
		if (game_flag == 1 && save_flag == 1) { // ���� ���̸鼭 ������ �÷��̾��� ��ġ�� �����߾��ٸ�
			px = sx; // ������ ��ġ�� �÷��̾ �̵����� �ش�.
			py = sy;
			cnt++; // �÷��̾ �̵��� Ƚ���� 1�� �����ش�.
			save_flag = 0; // �÷��̾��� ��ġ�� �������� �ʾҴٰ� ǥ�ø� ���ش�.
		}
	}

	if (key == ' ') { // �����̽��ٸ� ������ �ð�
		if (game_flag == 1) { //���� ���̶��
			sx = px; // �÷��̾��� ��ġ�� �������ش�.
			sy = py;
			cnt++; // �÷��̾ �̵��� Ƚ���� 1�� �����ش�.
			save_flag = 1; // �÷��̾��� ��ġ�� �����ߴٰ� ǥ�ø� ���ش�.
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}

void ofApp::input() { // �̷��� ũ��� ���̵��� �Է¹޾��ִ� �Լ�
	printf("Width? : "); // �̷��� ����, ������ �� ������ �޾��ش�.
	scanf("%d", &WIDTH);
	printf("Height? : ");
	scanf("%d", &HEIGHT);
	HEIGHT = 2 * HEIGHT + 1; // ���� ������ �̷��� ���� ũ�⸦ ������ش�.
	WIDTH = 2 * WIDTH + 1;

	printf("Mode?\n"); // �÷����� ��带 �޾��ش�.
	printf("1. Easy\n");
	printf("2. Normal\n");
	printf("3. Hard\n");
	printf("4. Extreme Hard\n");
	while (1) {
		scanf("%d", &mode);
		if (mode == 1 || mode == 2 || mode == 3 || mode == 4) { // �ùٸ� ��带 ������
			break; // �� ���� �÷����Ѵ�.
		}
		else { // �ùٸ��� ���� ��带 ������
			printf("Please enter correct value.\n"); // ���� �޽����� ��� �� �ٽ� ��带 �Է¹޴´�.
		}
	}
}

void ofApp::init() { // �̷θ� ������ �迭�� ���� �Ҵ����ְ� �������� �ʱ�ȭ���ִ� �Լ�
	px = 1; // �÷��̾��� ��ġ�� �ʱ�ȭ���ش�.
	py = 1;
	cnt = 0; // �÷��̾ ������ Ƚ���� �ʱ�ȭ���ش�.
	save_flag = 0; // �÷��̾��� ��ġ�� �������� �ʾҴٰ� ǥ�ø� ���ش�.

	maze = new int* [HEIGHT]; // �̷θ� ������ �迭�� ���� �Ҵ����ش�.
	for (int i = 0; i < HEIGHT; i++) {
		maze[i] = new int[WIDTH];
	}

	for (int i = 0; i < HEIGHT; i++) { // �̷θ� ������ �迭�� �ʱ�ȭ���ش�.
		for (int j = 0; j < WIDTH; j++) {
			maze[i][j] = -1;
		}
	}
}

void ofApp::randDir() { // �̷θ� ������ �� ����� dir�迭�� �������� �����ִ� �Լ�
	int a, b, cur;

	random_device rd; // �������� ���ڸ� �̱� ���� seed�� �������ش�.
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 3); // 0���� 3���� �������� ��÷���ش�.

	for (int i = 0; i < 4; i++) { // 0���� 3���� dir�迭�� ���鼭 �������� ���õ� index�� �ִ� ����� ������ index�� �ִ� ������ �ٲ��ش�.
		cur = dis(gen);

		a = dir[i][0];
		b = dir[i][1];

		dir[i][0] = dir[cur][0];
		dir[i][1] = dir[cur][1];

		dir[cur][0] = a;
		dir[cur][1] = b;
	}
}

void ofApp::makeMaze() { // �Է¹��� �̷��� ũ�⸦ �������� ������ �̷θ� �������ִ� �Լ�
	int row, col, nrow, ncol, push_flag;
	stack<pair<int, int>> s; // DFS�� �̷θ� �����ϱ� ���ؼ� stack�� �������ش�.

	s.push(make_pair(1, 1)); // ���� ��ġ�� stack�� �־��ְ� �湮�ߴٰ� ǥ�ø� ���ش�.
	maze[1][1] = 0;
	while (s.empty() == 0) { // stack�� �� ������ �ݺ����ش�.
		push_flag = 0; // stack�� push�ߴٴ� ���� ǥ�ø� ���ִ� �÷��״�.

		row = s.top().first; // stack�� �� ���� �ִ� ��ġ�� �������ش�. (pop�� ���� �ʴ´�.)
		col = s.top().second;

		randDir();
		for (int i = 0; i < 4; i++) { // �̵��� ������ ��, �Ʒ�, ����, ������ �� 4�� �����Ƿ� 4�� �ݺ��Ѵ�.
			nrow = row + 2 * dir[i][0]; // ���� ��ġ�� �̵��� ���⿡ ���� �̵��� ��ġ�� �������ش�.
			ncol = col + 2 * dir[i][1];

			if (nrow >= 1 && nrow <= HEIGHT - 2 && ncol >= 1 && ncol <= WIDTH - 2 && maze[nrow][ncol] == -1) { // �̵��� ��ġ�� ���� ����� �ʰ� ���� �湮���� �ʴ� ���̶��
				s.push(make_pair(nrow, ncol)); // �̵��� ��ġ�� stack�� �־��ش�.
				push_flag = 1; // stack�� push�ߴٰ� ǥ�ø� ���ش�.
				maze[nrow][ncol] = 0; // �̵��� ��ġ�� �湮�� ���̶�� ǥ�ø� ���ش�.
				maze[row + dir[i][0]][col + dir[i][1]] = 0; // �波�� �̵��ϱ� ���ؼ� ���̿� �ִ� ���� ����ؾ� �ϹǷ� ���� �湮�� ���̶�� ǥ�ø� ���ش�.
			}
		}

		if (push_flag == 0) { // for���� �� ���������� stack�� push�� ���� �ʾҴٸ� (���� ��ġ���� �� �� �ִ� ���� ���� �Ͱ� ����.)
			s.pop(); // ���� ��ġ�� stack���� pop���ش�.
		}
	}
}

void ofApp::mazeSolve() { // �������� ���� �̷θ� ����ϱ� ���� �ʿ��� �������� �ּҰ��� �����ִ� �Լ�
	int row, col, nrow, ncol, mrow, mcol;
	int num = 1; // �ݺ����� �ݺ��� Ƚ���� �������ִ� ����
	ans = 0; // �̷θ� ����ϱ� ���� �ʿ��� �������� �ּҰ��� �ʱ�ȭ���ش�.
	queue<pair<int, int>> q; // �׻� �ּ��� ������ �����ϴ� BFS�� ����� ���̹Ƿ� queue�� �����Ѵ�.

	q.push(make_pair(1, 1)); // ���� ��ġ�� queue�� �־��ְ� �湮�ߴٰ� ǥ�ø� ���ش�.
	maze[1][1] = num++;

	while (q.empty() == 0) { // queue�� �� ������ �ݺ����ش�.
		row = q.front().first; // queue�� �� �տ� �ִ� ��ġ�� �������ְ� pop���ش�.
		col = q.front().second;
		q.pop();

		if (row == HEIGHT - 2 && col == WIDTH - 2) { // �������� �����ߴٸ�
			break; // �ݺ����� �������ش�.
		}

		for (int i = 0; i < 4; i++) { // �̵��� ������ ��, �Ʒ�, ����, ������ �� 4�� �����Ƿ� 4�� �ݺ��Ѵ�.
			nrow = row + dx[i]; // ���� ��ġ�� �̵��� ���⿡ ���� �̵��� ��ġ�� �������ش�.
			ncol = col + dy[i];

			if (maze[nrow][ncol] == 0) { // �̵��� ��ġ�� �̵��� �� �ִ� ���̶��
				q.push(make_pair(nrow, ncol)); //�̵��� ��ġ�� queue�� �־��ش�.
				maze[nrow][ncol] = num; // �̵��� ��ġ�� �湮�� ���̶�� ǥ���ϴµ� �ݺ����� �ݺ��� Ƚ���� ǥ�ø� ���ش�.
			}
		}
		num++; // �ݺ����� �ݺ��Ǿ����Ƿ� �ݺ����� �ݺ��� Ƚ���� �������ִ� ������ 1�� �����ش�. 
	}

	row = HEIGHT - 2; // ������ ������ ã�� ���� �������������� �̵��� ���̹Ƿ� ���� ��ġ�� �������� �ٲ��ش�.
	col = WIDTH - 2;
	while (1) {
		for (int i = 0; i < 4; i++) { // �̵��� ������ ��, �Ʒ�, ����, ������ �� 4�� �����Ƿ� 4�� �ݺ��Ѵ�.
			mrow = row + dx[i]; // ���� ��ġ�� �̵��� ���⿡ ���� �̵��� ��ġ�� �� ���̿� �ִ� ��ġ�� �������ش�.
			nrow = row + dx[i] * 2;
			mcol = col + dy[i];
			ncol = col + dy[i] * 2;

			if (nrow >= 1 && nrow <= HEIGHT - 2 && ncol >= 1 && ncol <= WIDTH - 2) { // �̵��� ��ġ�� ���� ����� �ʰ�
				if (maze[row][col] > maze[nrow][ncol] && maze[mrow][mcol] > 0 && maze[nrow][ncol] > 0) { // �̵��� ��ġ�� ���� ��ġ���� �ݺ����� �ݺ��� Ƚ���� ���� (���ٸ� ������� ����� ���� ���� �ƴϹǷ� ������ ������ �ƴϰ� �ȴ�.) �̵��� ��ġ�� �߰��� �ִ� ��ġ�� ��� �̵��� �� �ִ� ���̶�� (�̵��� ��ġ�� ���� ��ġ�� �߰��� ���� ������ �̵��� �� ����.)
					ans++; // �̷θ� ����ϱ� ���� �ʿ��� �������� �ּҰ��� 1�� �����ش�.
					row = nrow; // �̵��� ��ġ�� ���� ��ġ�� �������ش�.
					col = ncol;
					break; // �̵��� �� �ִ� ��ġ�� �ϳ��ۿ� �����Ƿ� �̵��� ��ġ�� ã���� �������ش�. (BFS�� Ư�� �� �̵��� ��ġ �� �ݺ����� �ݺ��� Ƚ���� ���� ��ġ���� ���� ���� �ϳ��ۿ� ����.)
				}
			}
		}

		if (row == 1 && col == 1) { // ������� �����ߴٸ�
			break; // �ݺ����� �������ش�.
		}
	}
}

void ofApp::freeMemory() { // ���� �Ҵ��� �޸𸮸� �������ִ� �Լ�
	for (int i = 0; i < HEIGHT; i++) { // ���� �Ҵ��� �迭�� �ʱ�ȭ���ش�.
		delete[] maze[i];
	}
	delete[] maze;
}

void ofApp::gameStart() { // ������ �����ϱ� ���� �ʿ��� �͵��� ���ִ� �Լ�
	input(); // �Է��� �޾��ش�.
	init(); // �̷θ� ������ �迭�� ���� �Ҵ����ְ� �������� �ʱ�ȭ ���ش�.
	makeMaze(); // �̷θ� ������ش�.
	mazeSolve(); // �������� �ּҰ��� �����ش�.
	printf("Game Start!\n"); // ������ ���۵Ǿ��ٴ� �޽����� ������ش�.
	game_flag = 1; // ������ ���۵Ǿ��ٰ� ǥ�ø� ���ش�.
}

void ofApp::drawShadow() { // ��忡 ���� �̷ο� �׸��ڸ� �׷��ִ� �Լ�
	int area = 10; // ��� ũ�⸦ 10���� �������ش�.

	ofSetColor(0); // �׸����� ���� ���������� �������ش�.
	if (mode == 2) { // ��尡 Normal�̶��
		ofDrawRectangle(5, 5, WIDTH * area - 5, HEIGHT * area - 5); // �̷θ� ���� �׸��ڷ� �����ش�.
		ofSetColor(255); // ����� ���� ������� �������ش�.
		ofDrawRectangle((px - 10) * area + 5, (py - 10) * area + 5, 20 * area, 20 * area); // �÷��̾��� ��ġ�κ��� ��, �Ʒ�, ����, ���������� 10ĭ�� �����ش�.
	}
	else if (mode == 3) { // ��尡 Hard���
		ofDrawRectangle(5, 5, WIDTH * area - 5, HEIGHT * area - 5); // �̷θ� ���� �׸��ڷ� �����ش�.
		ofSetColor(255); // ����� ���� ������� �������ش�.
		ofDrawRectangle((px - 5) * area + 5, (py - 5) * area + 5, 10 * area, 10 * area); // �÷��̾��� ��ġ�κ��� ��, �Ʒ�, ����, ���������� 5ĭ�� �����ش�.
	}
	else if (mode == 4) { // ��尡 Extreme Hard���
		ofDrawRectangle(5, 5, WIDTH * area - 5, HEIGHT * area - 5); // �̷θ� ���� �׸��ڷ� �����ش�.
		ofSetColor(255); // ����� ���� ������� �������ش�.
		ofDrawRectangle((px - 3) * area + 5, (py - 3) * area + 5, 6 * area, 6 * area); // �÷��̾��� ��ġ�κ��� ��, �Ʒ�, ����, ���������� 3ĭ�� �����ش�.
	}
}

void ofApp::gameClear() { // ������ ���� �� �ʿ��� �͵��� ���ִ� �Լ�
	game_flag = 0; // ������ ����Ǿ��ٰ� ǥ�ø� ���ش�.

	printf("Game Clear!\n"); // ������ ����Ǿ��ٴ� �޽����� ������ش�.
	printf("Your score is %d.\n", cnt); // �÷��̾ �̵��� Ƚ���� ������ش�.
	if (cnt <= ans * 1.5) { // �÷��̾ �̵��� Ƚ���� ������ ������ ������ �������� ��ũ�� ������ش�.
		printf("Your rank is A.\n");
	}
	else if (cnt <= ans * 2) {
		printf("Your rank is B.\n");
	}
	else if (cnt <= ans * 2.5) {
		printf("Your rank is C.\n");
	}
	else if (cnt <= ans * 3) {
		printf("Your rank is D.\n");
	}
	else {
		printf("Your rank is F.\n");
	}
	printf("If you want to play again, please press R.\n"); // �ٽ� �ϰ� ������ r, �����ϰ� ������ q�� ������� �޽����� ������ش�.
	printf("Or if you want to exit, please press Q.\n");
}