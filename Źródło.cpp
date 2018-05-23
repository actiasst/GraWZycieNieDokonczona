#include <iostream>
#include <Windows.h>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

#define ROZMIAR_N 20
#define ROZMIAR_M 20

bool tab[ROZMIAR_N][ROZMIAR_M];
bool tmp[ROZMIAR_N][ROZMIAR_M];

void inicjuj();
void wypisz();
void zamien();
void licz();


void Display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	double x = -1;
	double y = 1;
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (tab[i][j])
				glColor3f(0.0, 0.0, 0.0);
			else 
				glColor3f(1.0, 1.0, 1.0);

			glBegin(GL_POLYGON);
	glVertex3f(x, y - 0.1, 0.0);
	glVertex3f(x, y, 0.0);
	glVertex3f(x + 0.1, y, 0.0);
	glVertex3f(x + 0.1, y - 0.1, 0.0);
	glEnd();
			x += 0.1;
		}
		x = -1;
		y -= 0.1;
	}
	glFlush();
	glutSwapBuffers();
}

void symuluj() {
	while (true) {
		wypisz();
		licz();
		Display();
		Sleep(100);
		system("cls");
	}
}

void cos() {
	tab[10][7] = true;
	tab[10][8] = true;
	tab[10][9] = true;
}

void glider() {
	tab[3][0] = true;
	tab[3][1] = true;
	tab[3][2] = true;
	tab[2][2] = true;
	tab[1][1] = true;
}

void moje_cos() {
	tab[10][8] = true;
	tab[11][9] = true;
	tab[11][10] = true;
	tab[11][11] = true;
	tab[11][12] = true;
	tab[11][13] = true;
	tab[9][9] = true;
	tab[9][10] = true;
	tab[9][11] = true;
	tab[9][12] = true;
	tab[9][13] = true;
	tab[10][14] = true;
}

void Reshape(int width, int height)
{
	Display();
}

void kwadrat() {
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 0.0);
	glVertex3f(1, 0, 0.0);
	glVertex3f(0, 0, 0.0);
	glVertex3f(0, 1, 0.0);
	glEnd();
	glFlush();
	glColor3f(1.0, 1.0, 1.0);
	glutSwapBuffers();
}

enum
{
	SYMULUJ,
	COS,
	GLIDER,
	MOJE_COS,
	KWADRAT,
};


void Menu(int value)
{
	switch (value)
	{
	case SYMULUJ:
		symuluj();
		break;
	case COS:
		cos();
		Sleep(100);
		symuluj();
		break;
	case GLIDER:
		glider();
		Sleep(100);
		symuluj();
		break;
	case MOJE_COS:
		moje_cos();
		Sleep(100);
		symuluj();
		break;
	case KWADRAT:
		kwadrat();
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Gra w Zycie");
	glutCreateMenu(Menu);

	glutAddMenuEntry("Symuluj", SYMULUJ);
	glutAddMenuEntry("Cos", COS);
	glutAddMenuEntry("Glider", GLIDER);
	glutAddMenuEntry("Moje Cos", MOJE_COS);
	glutAddMenuEntry("Kwadrat", KWADRAT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	inicjuj();

	Display();
	glutMainLoop();
	system("pause");
}

void inicjuj() {
	for (int i = 0; i < ROZMIAR_N; i++)
		for (int j = 0; j < ROZMIAR_M; j++)
			tab[i][j] = false;
}

void wypisz() {
	for (int i = 0; i < ROZMIAR_N; i++) {
		for (int j = 0; j < ROZMIAR_M; j++)
			if (tab[i][j])
				cout << char(177);
			else
				cout << " ";
		cout << endl;
	}
}

void zamien() {
	for (int i = 0; i < ROZMIAR_N; i++)
		for (int j = 0; j < ROZMIAR_M; j++)
			tab[i][j] = tmp[i][j];
}

void licz() {
	int wynik = 0;
	for (int i = 1; i < ROZMIAR_N - 1; i++) {
		wynik += tab[i - 1][ROZMIAR_N - 1];
		wynik += tab[i - 1][0];
		wynik += tab[i - 1][1];
		wynik += tab[i][ROZMIAR_N - 1];
		wynik += tab[i][1];
		wynik += tab[i + 1][ROZMIAR_N - 1];
		wynik += tab[i + 1][0];
		wynik += tab[i + 1][1];
		if (tab[i][0])
			if (wynik != 2 && wynik != 3)
				tmp[i][0] = false;
			else
				tmp[i][0] = true;
		else
			if (wynik == 3)
				tmp[i][0] = true;
			else
				tmp[i][0] = false;
		wynik = 0;
	}

	for (int i = 1; i < ROZMIAR_N - 1; i++) {
		wynik += tab[i - 1][ROZMIAR_N - 2];
		wynik += tab[i - 1][ROZMIAR_N - 1];
		wynik += tab[i - 1][0];
		wynik += tab[i][ROZMIAR_N - 2];
		wynik += tab[i][0];
		wynik += tab[i + 1][ROZMIAR_N - 2];
		wynik += tab[i + 1][ROZMIAR_N - 1];
		wynik += tab[i + 1][0];
		if (tab[i][ROZMIAR_N-1])
			if (wynik != 2 && wynik != 3)
				tmp[i][ROZMIAR_N - 1] = false;
			else
				tmp[i][ROZMIAR_N - 1] = true;
		else
			if (wynik == 3)
				tmp[i][ROZMIAR_N - 1] = true;
			else
				tmp[i][ROZMIAR_N - 1] = false;
		wynik = 0;
	}

	for (int i = 1; i < ROZMIAR_M - 1; i++) {
		wynik += tab[ROZMIAR_M - 1][i - 1];
		wynik += tab[ROZMIAR_M - 1][i];
		wynik += tab[ROZMIAR_M - 1][i + 1];
		wynik += tab[0][i - 1];
		wynik += tab[0][i + 1];
		wynik += tab[1][i - 1];
		wynik += tab[1][i];
		wynik += tab[1][i + 1];
		if (tab[0][i])
			if (wynik != 2 && wynik != 3)
				tmp[0][i] = false;
			else
				tmp[0][i] = true;
		else
			if (wynik == 3)
				tmp[0][i] = true;
			else
				tmp[0][i] = false;
		wynik = 0;
	}

	for (int i = 1; i < ROZMIAR_M - 1; i++) {
		wynik += tab[ROZMIAR_M - 2][i - 1];
		wynik += tab[ROZMIAR_M - 2][i];
		wynik += tab[ROZMIAR_M - 2][i + 1];
		wynik += tab[ROZMIAR_M - 1][i - 1];
		wynik += tab[ROZMIAR_M - 1][i + 1];
		wynik += tab[0][i - 1];
		wynik += tab[0][i];
		wynik += tab[0][i + 1];
		if (tab[ROZMIAR_M - 1][i])
			if (wynik != 2 && wynik != 3)
				tmp[ROZMIAR_M - 1][i] = false;
			else
				tmp[ROZMIAR_M - 1][i] = true;
		else
			if (wynik == 3)
				tmp[ROZMIAR_M - 1][i] = true;
			else
				tmp[ROZMIAR_M - 1][i] = false;
		wynik = 0;
	}

	wynik += tab[ROZMIAR_N - 1][0];
	wynik += tab[ROZMIAR_N - 1][1];
	wynik += tab[0][1];
	wynik += tab[0][ROZMIAR_M - 1];
	wynik += tab[ROZMIAR_N-1][ROZMIAR_M - 1];
	wynik += tab[1][ROZMIAR_M - 1];
	wynik += tab[1][0];
	wynik += tab[1][1];
	if (tab[0][0])
		if (wynik != 2 && wynik != 3)
			tmp[0][0] = false;
		else
			tmp[0][0] = true;
	else
		if (wynik == 3)
			tmp[0][0] = true;
		else
			tmp[0][0] = false;
	wynik = 0;

	wynik += tab[ROZMIAR_N - 1][ROZMIAR_M - 2];
	wynik += tab[ROZMIAR_N - 1][ROZMIAR_M - 1];
	wynik += tab[ROZMIAR_N - 1][0];
	wynik += tab[0][ROZMIAR_M - 2];
	wynik += tab[0][0];
	wynik += tab[1][ROZMIAR_M - 2];
	wynik += tab[1][ROZMIAR_M - 1];
	wynik += tab[1][0];
	if (tab[0][ROZMIAR_M - 1])
		if (wynik != 2 && wynik != 3)
			tmp[0][ROZMIAR_M - 1] = false;
		else
			tmp[0][ROZMIAR_M - 1] = true;
	else
		if (wynik == 3)
			tmp[0][ROZMIAR_M - 1] = true;
		else
			tmp[0][ROZMIAR_M - 1] = false;
	wynik = 0;

	wynik += tab[ROZMIAR_N - 2][ROZMIAR_M - 1];
	wynik += tab[ROZMIAR_N - 2][0];
	wynik += tab[ROZMIAR_N - 2][1];
	wynik += tab[ROZMIAR_N - 1][ROZMIAR_M - 1];
	wynik += tab[ROZMIAR_N - 1][1];
	wynik += tab[0][ROZMIAR_M - 1];
	wynik += tab[0][0];
	wynik += tab[0][1];
	if (tab[ROZMIAR_N - 1][0])
		if (wynik != 2 && wynik != 3)
			tmp[ROZMIAR_N - 1][0] = false;
		else
			tmp[ROZMIAR_N - 1][0] = true;
	else
		if (wynik == 3)
			tmp[ROZMIAR_N - 1][0] = true;
		else
			tmp[ROZMIAR_N - 1][0] = false;
	wynik = 0;
	
	wynik += tab[ROZMIAR_N - 2][ROZMIAR_M - 2];
	wynik += tab[ROZMIAR_N - 2][ROZMIAR_M - 1];
	wynik += tab[ROZMIAR_N - 2][0];
	wynik += tab[ROZMIAR_N - 1][ROZMIAR_M - 2];
	wynik += tab[ROZMIAR_N - 1][0];
	wynik += tab[0][ROZMIAR_M - 2];
	wynik += tab[0][ROZMIAR_M - 1];
	wynik += tab[0][0];
	if (tab[ROZMIAR_N - 1][ROZMIAR_M - 1])
		if (wynik != 2 && wynik != 3)
			tmp[ROZMIAR_N - 1][ROZMIAR_M - 1] = false;
		else
			tmp[ROZMIAR_N - 1][ROZMIAR_M - 1] = true;
	else
		if (wynik == 3)
			tmp[ROZMIAR_N - 1][ROZMIAR_M - 1] = true;
		else
			tmp[ROZMIAR_N - 1][ROZMIAR_M - 1] = false;
	wynik = 0;
	
	for (int i = 1; i < ROZMIAR_N - 1; i++)
		for (int j = 1; j < ROZMIAR_M - 1; j++) {
			wynik += tab[i - 1][j - 1];
			wynik += tab[i - 1][j];
			wynik += tab[i - 1][j + 1];
			wynik += tab[i][j - 1];
			wynik += tab[i][j + 1];
			wynik += tab[i + 1][j - 1];
			wynik += tab[i + 1][j];
			wynik += tab[i + 1][j + 1];
			if (tab[i][j])
				if (wynik != 2 && wynik != 3)
					tmp[i][j] = false;
				else
					tmp[i][j] = true;
			else
				if (wynik == 3)
					tmp[i][j] = true;
				else
					tmp[i][j] = false;
			wynik = 0;
		}
	zamien();
}