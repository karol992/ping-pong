//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <cmath>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int v_x = -4;
int v_y = 4;
bool leftUpBoost = 0;
bool leftDownBoost = 0;
bool rightUpBoost = 0;
bool rightDownBoost = 0;
int leftPoints = 0;
int rightPoints = 0;
int ballBounces = 0;
AnsiString playmaker = "left";

void corner_hit() {
        v_y = -v_y;
        v_x = (-v_x/v_x)*abs(v_y);
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
        nextRound->Visible = true;
        ballBounces =0;
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
        ballBounces = 0;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle1upTimer(TObject *Sender)
{
        if (paddle1->Top -10 > background->Top) paddle1 -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddle1downTimer(TObject *Sender)
{
        if (paddle1->Top +10 < background->Top + background -> Height - paddle1->Height) paddle1 -> Top += 10;
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
        if (paddle2->Top -10 > background->Top) paddle2 -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2downTimer(TObject *Sender)
{
        if (paddle2->Top +10 < background->Top + background -> Height - paddle2->Height) paddle2 -> Top += 10;
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
        if (ball->Left <= paddle1->Left+paddle1->Width) {

                //boost na srodku paletki
                if (abs(ball_center_x - paddle1_centre_x) < 50) {
                        v_x -=1;
                }
                if (leftUpBoost) v_y -= 1;
                if (leftDownBoost) v_y += 1;

                if((ball_center_x >= paddle1->Top)
                && (ball_center_x <= paddle1->Top+paddle1->Height)) {
                        v_x = -v_x;
                } else if ((ball_center_x + ball->Height/2 >= paddle1->Top) //odbicie od gornego rogu
                           && (ball_center_x <= paddle1->Top)
                           && v_y > 0) {
                        corner_hit();
                } else if ((ball_center_x + ball->Height/2 >= paddle1->Top) //odbicie od gornego rogu
                           && (ball_center_x <= paddle1->Top)
                           && v_y < 0) {
                        v_x = -v_x;
                } else if ((ball_center_x >= paddle1->Top + paddle1->Height) //odbicie od dolnego rogu
                           && (ball_center_x <= paddle1->Top + paddle1->Height + ball->Height/2)
                           && v_y < 0) {
                        corner_hit();
                } else if ((ball_center_x >= paddle1->Top + paddle1->Height) //odbicie od dolnego rogu
                           && (ball_center_x <= paddle1->Top + paddle1->Height + ball->Height/2)
                           && v_y > 0) {
                        v_x = -v_x;
                } else { //skucie
                        playmaker = "right";
                        rightPoints++;
                        winnerInfo->Caption = "Punkt dla gracza prawego >";
                        loss();
                        return;
                }
                ballBounces++;
        }

        //odbicie od prawej paletki
        if (ball->Left + ball->Width >= paddle2->Left) {
                if (abs(ball_center_x - paddle2_centre_x) < 50) {
                        v_x +=1;
                }
                if (rightUpBoost) v_y -= 1;
                if (rightDownBoost) v_y += 1;


                if((ball_center_x >= paddle2->Top ) //
                && (ball_center_x <= paddle2->Top+paddle2->Height)) {
                        v_x = -v_x;
                } else if ((ball_center_x + ball->Height/2 >= paddle2->Top)
                           && (ball_center_x <= paddle2->Top)
                           && v_y > 0) {
                        corner_hit();
                } else if ((ball_center_x + ball->Height/2 >= paddle2->Top)
                           && (ball_center_x <= paddle2->Top)
                           && v_y < 0) {
                        v_x = -v_x;
                } else if ((ball_center_x >= paddle2->Top + paddle2->Height)
                           && (ball_center_x <= paddle2->Top + paddle2->Height + ball->Height/2)
                           && v_y < 0) {
                        corner_hit();
                } else if ((ball_center_x >= paddle2->Top + paddle2->Height)
                           && (ball_center_x <= paddle2->Top + paddle2->Height + ball->Height/2)
                           && v_y > 0) {
                        v_x = -v_x;
                } else {
                        playmaker = "left";
                        leftPoints++;
                        winnerInfo->Caption = "< Punkt dla gracza lewego";
                        loss();
                        return;
                }
                ballBounces++;
        }
        ball -> Left += v_x;
        ball -> Top += v_y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nowaGraClick(TObject *Sender)
{
        gameRefresh();
        nowaGra->Default = false;
        nextRound->Default = true;
        v_y = 4;
        v_x = -4;
        leftPoints = 0;
        rightPoints = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
        gameRefresh();
        if (playmaker == "left") v_x = -4;
        else v_x = 4;
}
//---------------------------------------------------------------------------

