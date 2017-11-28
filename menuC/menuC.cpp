//	============================================================
//	Arduino�̃A���S���Y�����l���邽�߂̂��
//	programmed by KOH / RAY-NET.
//	date written 2017-11-20 03:31
//	============================================================

#include "stdio.h"
#include "conio.h"
#include "string.h"
#include <windows.h>


//	------------------------------
//	�v���g�^�C�v�錾
//	------------------------------
int menuSelect(char *cp);				// ���j���[�I�ȃA��

void lcdInit();							// LCD������
void lcdDisp1(char *cp);				// LCD�\��(1�s��)
void lcdDisp2(char *cp);				// LCD�\��(2�s��)

int ajoyGet();							// �W���C�X�e�B�b�N����
void setCursorPos(int x, int y);		// �J�[�\���ʒu�̎w��
char *menuGet();
int menuTopGet(int n);


//	------------------------------
//	�ϐ�
//	------------------------------
//char Menu[] = "Austin Baldwin Chandler Delite Elliot Festival "
//	"Gloria Hpmebell Ira Jewel Kestorel Liberty Misty Nobilis "
//	"Ono Powder Q... Reka Spartan Tifblue Utsugiao Vernon Whitu X.. Yadkin Z...";

char Menu[] = "Austin Bwin Chan Delite Eliot Fuku Ggem "
"Hbell Ira Jewel Kiso Legacy Maru Nui Ono Powder Reka "
"Sptan Tif UK Vernon Whitu Xevi Yadkin Zzz..";


//	------------------------------
//	�߂���
//	------------------------------
int main() {
	int sel;
	lcdInit();
	menuSelect(Menu);

	while (1) {
		sel = menuSelect(NULL);
		if (sel >= 0) {
			lcdDisp2(menuGet() + menuTopGet(sel));
		}
		Sleep(100);
	}

	return 0;
}



//	------------------------------------------------------------
//	Arduino���G�~����֐��Q
//	------------------------------------------------------------

//	------------------------------
//	LCD������
//	------------------------------
void lcdInit() {
	setCursorPos(0, 0);
	printf("��12345678��\n");
	printf("��        ��\n");
	printf("��        ��\n");
	printf("��12345678��\n");
}

//	------------------------------
//	LCD�\��(1�s��)
//	------------------------------
void lcdDisp1(char *cp) {
	char buf[20];
	strncpy_s(buf, cp, 8);
	strcat_s(buf, "        ");
	buf[8] = 0x00;
	setCursorPos(2, 1);
	printf(buf);
	setCursorPos(0, 4);
}

//	------------------------------
//	LCD�\��(2�s��)
//	------------------------------
void lcdDisp2(char *cp) {
	char buf[20];
	strncpy_s(buf, cp, 8);
	strcat_s(buf, "        ");
	buf[8] = 0x00;
	setCursorPos(2, 2);
	printf(buf);
	setCursorPos(0, 4);
}

//	------------------------------
//	�J�[�\���L�[
//	------------------------------
int ajoyGet() {
	int ret = 0;
	int k;
	if (_kbhit() == 0) return 0;

	ret = 0;
	k = _getch();
	if (k == 0xe0) {
		k = _getch();
		if (k == 0x48) ret |= 0x08;
		if (k == 0x50) ret |= 0x04;
		if (k == 0x4b) ret |= 0x02;
		if (k == 0x4d) ret |= 0x01;
	}
	return ret;
}


//	------------------------------------------------------------
//	DOS���ŕ֗������Ȋ֐��Q
//	------------------------------------------------------------

//	------------------------------
//	�J�[�\���ʒu�̎w��
//	------------------------------
void setCursorPos(int x, int y) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hCons, pos);
}















































//	------------------------------------------------------------
//	���j���[�Ƃ�
//	------------------------------------------------------------
#define __MENU_MAX	(30)

int menuItem;							// ���j���[�̍��ڐ�
unsigned char menuTop[__MENU_MAX];		// ���ڂ̐擪
char *menu;								// �������̃��j���[

int menuSelect(char *cp) {
	static int menuPos;					// ���ݐ擪�ɕ\������Ă��郁�j���[�ʒu(�I�t�Z�b�g)
	static int menuTarget;				// �I������Ă���(�擪�ɕ\�������ׂ�)���ڂ̔ԍ�
	int dist;
	int i, r;

	//	--------------------
	//	���j���[�̏���
	//	--------------------
	if (cp != NULL) {
		menu = cp;
		menuPos = 0;
		menuTarget = 0;
		menuTop[0] = 0;
		menuItem = 1;
		for (i = 0;; i++) {
			if (*(cp + i) == 0x00) break;
			if (*(cp + i) == ' ') {
				menuTop[menuItem] = i + 1;
				//				printf("%d, ", i + 1);

				menuItem++;
				if (menuItem > __MENU_MAX - 1) break;
			}
		}
		return 0;
	}

	//	--------------------
	//	���j���[�̑I��
	//	--------------------
	int aj = ajoyGet();
	if (aj & 0x02) menuTarget--;
	if (aj & 0x01) menuTarget++;
	if (aj & 0x04) {
		menuPos = menuTop[menuTarget];
		return menuTarget;
	}

	if (menuTarget < 0) {
		menuTarget = 0;
	}
	if (menuTarget > menuItem - 1) {
		menuTarget = menuItem - 1;
	}

	dist = menuPos - menuTop[menuTarget];
	if (dist < 0) dist = 0 - dist;
	if (menuPos < menuTop[menuTarget]) {
		if (dist > 6) menuPos += (dist / 2);
		menuPos++;
	}
	if (menuPos > menuTop[menuTarget]) {
		if (dist > 6) menuPos -= (dist / 2);
		menuPos--;
	}
	lcdDisp1(menu + menuPos);

	return -1;
}
char *menuGet(){
	return menu;
}

int menuTopGet(int n){
	return menuTop[n];
}
