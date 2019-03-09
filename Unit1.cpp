//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int v_x = 3;
int v_y = -3;

void corner_hit() {
        v_x = -v_x;
        v_y = -v_y;
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
        if (Key == 'A') paddle1up -> Enabled = true;
        if (Key == 'Z') paddle1down -> Enabled = true;
        if (Key == VK_UP) paddle2up -> Enabled = true;
        if (Key == VK_DOWN) paddle2down -> Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') paddle1up -> Enabled = false;
        if (Key == 'Z') paddle1down -> Enabled = false;
        if (Key == VK_UP) paddle2up -> Enabled = false;
        if (Key == VK_DOWN) paddle2down -> Enabled = false;
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
        int ball_radius = ball->Width/2;
        int ball_center_x = ball->Top + ball_radius;
        //int ball_center_y = ball->Left + ball_radius;

        if ((ball->Top <= background->Top) || (ball->Top >= background->Top + background->Height - ball->Height)) {
                v_y = -v_y;
        }
        if (ball->Left <= paddle1->Left+paddle1->Width) {
                if((ball_center_x >= paddle1->Top)
                && (ball_center_x <= paddle1->Top+paddle1->Height)) {
                        v_x = -v_x;
                } else if ((ball_center_x + ball->Height/2 >= paddle1->Top)
                           && (ball_center_x <= paddle1->Top) && v_y > 0) {
                        corner_hit();
                } else if ((ball_center_x >= paddle1->Top + paddle1->Height)
                           && (ball->Top <= paddle1->Top + paddle1->Height + ball->Height) && v_y < 0) {
                        corner_hit();
                } else {
                        ball_moving->Enabled = false;
                }
        }

        if (ball->Left >= paddle2->Left-paddle2->Width) {
                if((ball_center_x >= paddle2->Top )
                && (ball_center_x <= paddle2->Top+paddle2->Height)) {
                        v_x = -v_x;
                }  else if ((ball_center_x + ball->Height/2 >= paddle2->Top)
                           && (ball_center_x <= paddle2->Top) && v_y > 0) {
                        corner_hit();
                } else if ((ball_center_x >= paddle2->Top + paddle2->Height)
                           && (ball->Top <= paddle2->Top + paddle2->Height + ball->Height) && v_y < 0) {
                        corner_hit();
                } else {
                        ball_moving->Enabled = false;
                }
        }
        ball -> Left += v_x;
        ball -> Top += v_y;
}
//---------------------------------------------------------------------------
