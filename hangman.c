#include <stdio.h>
#include <Windows.h>

void init(); //콘솔창 등장 및 크기 조절
void game(); //게임 진행
int check(char sol[], char ans[], char ch);//solution, answer 비교

int main() {
    init();
    game();
    getchar(); //계속하려면~~~ 안보이게 하려고 임시로.

    return 0;
}

void init() {
    system("mode con cols=50 lines=20 | title Hangman Game");//콘솔창 크기 조절(폭 94문자, 높이 25줄), 콘솔창 이름 설정
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0; //커서 숨기기
    ConsoleCursor.dwSize = 1; //커서 크기 1로 설정
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void game() {
    int HP = 10; //생명 10개
    char solution[100] = "happy friday"; //정답
    char answer[100] = "_____ ______"; //플레이어가 입력할 곳(현재까지 맞춘 것)
    char ch; //문자 입력(맞추기)

    while (1) {
        for (int i = 1; i <= HP; i++) {
            printf("♥🕵️");
        }
        printf("\n진행 상황: %s\n", answer);
        printf("문자 입력: ");
        ch = getchar(); //getchar(): 입력한 문자 버퍼O, echo 즉, 엔터 쳐야 전달됨
        if (check(solution, answer, ch) == 1) {//1: 모든 문자 일치 정답! => 게임 종료 0:이어서 입력 받기
            printf("정답! %s\n", answer);
            break;
        }
        else if (check(solution, answer, ch) == 0) {
            HP -= 1;
        }
        if (HP == 0) {
            printf("HP 소진! 게임 종료\n");
            break;
        }
        getchar(); //줄바꿈 문자
    }

}

int check(char sol[], char ans[], char ch) {//solution[], answer[], ch
    int tmp = 0;
    for (int i = 0; sol[i] != 0; i++) {
        if (sol[i] == ch) {//soution에 입력한 문자와 일치하는 것이 있다면
            ans[i] = ch; //answer의 해당 위치에 문자 넣어주기(ex. ___ -> __a_)
            tmp = 1;
        }
    }

    if (strcmp(sol, ans) == 0) return 1; //solution, answer 모든 문자 일치 정답!!!
    else if (tmp == 0) return 0;
    else return 2; //solution에 있는 문자를 answer에 넣기.
}
