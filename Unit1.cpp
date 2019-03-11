//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <cmath>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//sk³adowe szybkoœci pi³ki
int v_x = -4;
int v_y = 4;
//bool'e do wykrywania ruchu paletki podczas odbicia w celu przyspieszenia v_y
bool leftUpBoost = 0;
bool leftDownBoost = 0;
bool rightUpBoost = 0;
bool rightDownBoost = 0;
//-----------------------
int leftPoints = 0;
int rightPoints = 0;
int ballBounces = 0;
AnsiString servingPlayer = "left";

void TForm1::cornerHit() {
        int pom = v_x;
        if (v_x * v_y >= 0) {
                v_x = -v_y;
                v_y = -pom;
        } else if (v_x *v_y < 0) {
                v_x = v_y;
                v_y = pom;
        }
}
void TForm1::loss() {
        bouncesInfo->Caption = "Iloœæ odbiæ: " + IntToStr(ballBounces);
        scoreTable->Caption = IntToStr(leftPoints) + ":" + IntToStr(rightPoints);
        ballMoving->Enabled = false;
        ball->Visible = false;
        bouncesInfo->Visible = true;
        newGame->Visible = true;
        winnerInfo->Visible = true;
        scoreTable->Visible = true;
        nextRound->Default = true;
        nextRound->Visible = true;
        ballBounces = 0;

}
void TForm1::gameRefresh() {
        ball->Top = background->Height/2 - ball->Height/2;
        ball->Left = background->Width/2 - ball->Width/2;
        ball->Enabled = true;
        ball->Visible = true;
        ballMoving->Enabled = true;
        newGame->Visible = false;
        winnerInfo->Visible = false;
        bouncesInfo->Visible = false;
        scoreTable->Visible = false;
        nextRound->Visible = false;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Application -> MessageBox("Witaj w grze PingPong.\n\n"
        "Lewy gracz steruje wciskaj¹c klawisze A oraz Z.\n"
        "Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\n\n"
        "Dla urozmaicenia zabawy:\n"
        "       *Kiedy odbijasz pi³kê paletk¹ w ruchu lub na jej œrodku, \n"
        "        wówczas zmienisz k¹t odbicia i prêdkoœæ pi³ki.\n"
        "       *Mo¿esz dowolnie zmieniaæ pole gry.\n\n"
        "Mi³ej zabawy!", "PingPong", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleLeftUpTimer(TObject *Sender)
{
        if (paddleLeft->Top -10 > background->Top) paddleLeft -> Top -= background->Height/50;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddleLeftDownTimer(TObject *Sender)
{
        if (paddleLeft->Top +10 < background->Top + background -> Height - paddleLeft->Height) paddleLeft -> Top += background->Height/50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') {
                paddleLeftUp -> Enabled = true;
                leftUpBoost = true;
        }
        if (Key == 'Z') {
                paddleLeftDown -> Enabled = true;
                leftDownBoost = true;
        }
        if (Key == VK_UP) {
                paddleRightUp -> Enabled = true;
                rightUpBoost = true;
        }
        if (Key == VK_DOWN) {
                paddleRightDown -> Enabled = true;
                rightDownBoost = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') {
                paddleLeftUp -> Enabled = false;
                leftUpBoost = false;
        }
        if (Key == 'Z') {
                paddleLeftDown -> Enabled = false;
                leftDownBoost = false;
        }
        if (Key == VK_UP) {
                paddleRightUp -> Enabled = false;
                rightUpBoost = false;
        }
        if (Key == VK_DOWN) {
                paddleRightDown -> Enabled = false;
                rightDownBoost = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleRightUpTimer(TObject *Sender)
{
        if (paddleRight->Top -10 > background->Top) paddleRight -> Top -= background->Height/50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleRightDownTimer(TObject *Sender)
{
        if (paddleRight->Top +10 < background->Top + background -> Height - paddleRight->Height) paddleRight -> Top += background->Height/50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ballMovingTimer(TObject *Sender)
{
        int ballCenterX = ball->Top + ball->Width/2;
        int LeftPaddleCenterX = paddleLeft->Top + paddleLeft->Height/2;
        int RightPaddleCenterX = paddleRight->Top + paddleRight->Height/2;

        //odbicie od gornej i dolnej sciany
        if ((ball->Top <= background->Top) || (ball->Top >= background->Top + background->Height - ball->Height)) {
                v_y = -v_y;
        }

        //odbicie od lewej paletki
        if (ball->Left >= paddleLeft->Left
            && ball->Left <= paddleLeft->Left + paddleLeft->Width
            && ball->Top >= paddleLeft->Top - ball->Height/2
            && ball->Top <= paddleLeft->Top + paddleLeft->Height - ball->Height/2) {
            v_x = -v_x;
            ballBounces++;
            //boost na srodku paletki
            if (abs(ballCenterX - LeftPaddleCenterX) < 50) {
                v_x +=1;
            }
            if (leftUpBoost) v_y -= 1; //przyspieszenie przy ruchu
            if (leftDownBoost) v_y += 1;
        }
        //odbicie od rogów lewej paletki
        if (ball->Left >= paddleLeft->Left
            && ball->Left <= paddleLeft->Left + paddleLeft->Width
            && ((v_y >= 0 && (ball->Top < paddleLeft->Top - ball->Height/2)
                && (ball->Top >= paddleLeft->Top - ball->Height))
                || (v_y <= 0 && (ball->Top > paddleLeft->Top + paddleLeft->Height - ball->Height/2)
                && (ball->Top <= paddleLeft->Top + paddleLeft->Height)))) {
            cornerHit();
            ballBounces++;
        }
        //odbicie od górnej lub dolnej œcianki paletki
        if (ball->Left < paddleLeft->Left
            && ball->Left >= paddleLeft->Left - paddleLeft->Width
            && (((ball->Top <= paddleLeft->Top - ball->Height/2)
                && (ball->Top >= paddleLeft->Top - ball->Height))
                || ((ball->Top >= paddleLeft->Top + paddleLeft->Height - ball->Height/2)
                && (ball->Top <= paddleLeft->Top + paddleLeft->Height)))) {
            v_y = -v_y;
            ballBounces++;
        }
        //skucie po lewej stronie
        if (ball->Left < background->Left) {
                servingPlayer = "right";
                rightPoints++;
                winnerInfo->Caption = "Punkt dla gracza prawego >";
                loss();
                return;
        }
        //----------------------------------------------------------------------

        //odbicie od prawej paletki
        if (ball->Left + ball->Width >= paddleRight->Left
            && ball->Left + ball->Width <= paddleRight->Left + paddleRight->Width
            && ball->Top >= paddleRight->Top - ball->Height/2
            && ball->Top <= paddleRight->Top + paddleRight->Height - ball->Height/2) {
            v_x = -v_x;
            ballBounces++;
            //boost na srodku paletki
            if (abs(ballCenterX - RightPaddleCenterX) < 50) {
                v_x -=1;
            }
            if (leftUpBoost) v_y -= 1; //przyspieszenie przy ruchu
            if (leftDownBoost) v_y += 1;
        }
        //odbicie od rogów prawej paletki
        if (ball->Left + ball->Width >= paddleRight->Left
            && ball->Left + ball->Width <= paddleRight->Left + paddleRight->Width
            && ((v_y >= 0 && (ball->Top < paddleRight->Top - ball->Height/2)
                && (ball->Top >= paddleRight->Top - ball->Height))
                || (v_y <= 0 &&(ball->Top > paddleRight->Top + paddleRight->Height - ball->Height/2)
                && (ball->Top <= paddleRight->Top + paddleRight->Height)))) {
            cornerHit();
            ballBounces++;
        }
        //odbicie od górnej lub dolnej œcianki paletki
        if (ball->Left + ball->Width > paddleRight->Left + paddleRight->Width
            && ball->Left + ball->Width <= paddleRight->Left + paddleRight->Width*2
            && (((ball->Top <= paddleRight->Top - ball->Height/2)
                && (ball->Top >= paddleRight->Top - ball->Height))
                || ((ball->Top >= paddleRight->Top + paddleRight->Height - ball->Height/2)
                && (ball->Top <= paddleRight->Top + paddleRight->Height)))) {
            v_y = -v_y;
            ballBounces++;
        }
        //skucie po prawej stronie
        if (ball->Left + ball->Width > background->Left + background->Width) {
                servingPlayer = "left";
                leftPoints++;
                winnerInfo->Caption = "< Punkt dla gracza lewego";
                loss();
                return;
        }
        //----------------------------------------------------------------------
        ball -> Left += v_x;
        ball -> Top += v_y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::newGameClick(TObject *Sender)
{
        gameRefresh();
        newGame->Default = false;
        v_y = -4;
        v_x = -4;
        leftPoints = 0;
        rightPoints = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
        gameRefresh();
        v_y = 4;
        if (servingPlayer == "left") v_x = -4;
        else v_x = 4;
}
//---------------------------------------------------------------------------


