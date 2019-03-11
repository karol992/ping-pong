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
//bool'e do wykrywania ruchu paletki podczas odbicia
bool leftUpBoost = 0;
bool leftDownBoost = 0;
bool rightUpBoost = 0;
bool rightDownBoost = 0;
//-----------------------
int leftPoints = 0;
int rightPoints = 0;
int ballBounces = 0;
AnsiString playmaker = "left";

void corner_hit() {
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
        ball_moving->Enabled = false;
        ball->Visible = false;
        bouncesInfo->Visible = true;
        nowaGra->Visible = true;
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
        ball_moving->Enabled = true;
        nowaGra->Visible = false;
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
void __fastcall TForm1::paddle1upTimer(TObject *Sender)
{
        if (paddle1->Top -10 > background->Top) paddle1 -> Top -= background->Height/50;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddle1downTimer(TObject *Sender)
{
        if (paddle1->Top +10 < background->Top + background -> Height - paddle1->Height) paddle1 -> Top += background->Height/50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') {
                paddle1up -> Enabled = true;
                leftUpBoost = true;
        }
        if (Key == 'Z') {
                paddle1down -> Enabled = true;
                leftDownBoost = true;
        }
        if (Key == VK_UP) {
                paddle2up -> Enabled = true;
                rightUpBoost = true;
        }
        if (Key == VK_DOWN) {
                paddle2down -> Enabled = true;
                rightDownBoost = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') {
                paddle1up -> Enabled = false;
                leftUpBoost = false;
        }
        if (Key == 'Z') {
                paddle1down -> Enabled = false;
                leftDownBoost = false;
        }
        if (Key == VK_UP) {
                paddle2up -> Enabled = false;
                rightUpBoost = false;
        }
        if (Key == VK_DOWN) {
                paddle2down -> Enabled = false;
                rightDownBoost = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2upTimer(TObject *Sender)
{
        if (paddle2->Top -10 > background->Top) paddle2 -> Top -= background->Height/50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2downTimer(TObject *Sender)
{
        if (paddle2->Top +10 < background->Top + background -> Height - paddle2->Height) paddle2 -> Top += background->Height/50;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ball_movingTimer(TObject *Sender)
{
        int ball_center_x = ball->Top + ball->Width/2;
        int paddle1_centre_x = paddle1->Top + paddle1->Height/2;
        int paddle2_centre_x = paddle2->Top + paddle2->Height/2;

        //odbicie od gornej i dolnej sciany
        if ((ball->Top <= background->Top) || (ball->Top >= background->Top + background->Height - ball->Height)) {
                v_y = -v_y;
        }

        //odbicie od lewej paletki
        if (ball->Left >= paddle1->Left
            && ball->Left <= paddle1->Left + paddle1->Width
            && ball->Top >= paddle1->Top - ball->Height/2
            && ball->Top <= paddle1->Top + paddle1->Height - ball->Height/2) {
            v_x = -v_x;
            ballBounces++;
            //boost na srodku paletki
            if (abs(ball_center_x - paddle1_centre_x) < 50) {
                v_x +=1;
            }
            if (leftUpBoost) v_y -= 1; //przyspieszenie przy ruchu
            if (leftDownBoost) v_y += 1;
        }
        //odbicie od rogów lewej paletki
        if (ball->Left >= paddle1->Left
            && ball->Left <= paddle1->Left + paddle1->Width
            && ((v_y >= 0 && (ball->Top < paddle1->Top - ball->Height/2)
                && (ball->Top >= paddle1->Top - ball->Height))
                || (v_y <= 0 && (ball->Top > paddle1->Top + paddle1->Height - ball->Height/2)
                && (ball->Top <= paddle1->Top + paddle1->Height)))) {
            corner_hit();
            ballBounces++;
        }
        //odbicie od górnej lub dolnej œcianki paletki
        if (ball->Left < paddle1->Left
            && ball->Left >= paddle1->Left - paddle1->Width
            && (((ball->Top <= paddle1->Top - ball->Height/2)
                && (ball->Top >= paddle1->Top - ball->Height))
                || ((ball->Top >= paddle1->Top + paddle1->Height - ball->Height/2)
                && (ball->Top <= paddle1->Top + paddle1->Height)))) {
            v_y = -v_y;
            ballBounces++;
        }
        //skucie po lewej stronie
        if (ball->Left < background->Left) {
                playmaker = "right";
                rightPoints++;
                winnerInfo->Caption = "Punkt dla gracza prawego >";
                loss();
                return;
        }
        //----------------------------------------------------------------------

        //odbicie od prawej paletki
        if (ball->Left + ball->Width >= paddle2->Left
            && ball->Left + ball->Width <= paddle2->Left + paddle2->Width
            && ball->Top >= paddle2->Top - ball->Height/2
            && ball->Top <= paddle2->Top + paddle2->Height - ball->Height/2) {
            v_x = -v_x;
            ballBounces++;
            //boost na srodku paletki
            if (abs(ball_center_x - paddle2_centre_x) < 50) {
                v_x -=1;
            }
            if (leftUpBoost) v_y -= 1; //przyspieszenie przy ruchu
            if (leftDownBoost) v_y += 1;
        }
        //odbicie od rogów prawej paletki
        if (ball->Left + ball->Width >= paddle2->Left
            && ball->Left + ball->Width <= paddle2->Left + paddle2->Width
            && ((v_y >= 0 && (ball->Top < paddle2->Top - ball->Height/2)
                && (ball->Top >= paddle2->Top - ball->Height))
                || (v_y <= 0 &&(ball->Top > paddle2->Top + paddle2->Height - ball->Height/2)
                && (ball->Top <= paddle2->Top + paddle2->Height)))) {
            corner_hit();
            ballBounces++;
        }
        //odbicie od górnej lub dolnej œcianki paletki
        if (ball->Left + ball->Width > paddle2->Left + paddle2->Width
            && ball->Left + ball->Width <= paddle2->Left + paddle2->Width*2
            && (((ball->Top <= paddle2->Top - ball->Height/2)
                && (ball->Top >= paddle2->Top - ball->Height))
                || ((ball->Top >= paddle2->Top + paddle2->Height - ball->Height/2)
                && (ball->Top <= paddle2->Top + paddle2->Height)))) {
            v_y = -v_y;
            ballBounces++;
        }
        //skucie po prawej stronie
        if (ball->Left + ball->Width > background->Left + background->Width) {
                playmaker = "left";
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
void __fastcall TForm1::nowaGraClick(TObject *Sender)
{
        gameRefresh();
        nowaGra->Default = false;
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
        if (playmaker == "left") v_x = -4;
        else v_x = 4;
}
//---------------------------------------------------------------------------


