//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *background;
        TImage *paddleLeft;
        TImage *paddleRight;
        TTimer *paddleLeftUp;
        TTimer *paddleLeftDown;
        TTimer *paddleRightUp;
        TTimer *paddleRightDown;
        TImage *ball;
        TTimer *ballMoving;
        TButton *newGame;
        TLabel *winnerInfo;
        TLabel *bouncesInfo;
        TLabel *scoreTable;
        TButton *nextRound;
        void __fastcall paddleLeftUpTimer(TObject *Sender);
        void __fastcall paddleLeftDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall paddleRightUpTimer(TObject *Sender);
        void __fastcall paddleRightDownTimer(TObject *Sender);
        void __fastcall ballMovingTimer(TObject *Sender);
        void __fastcall newGameClick(TObject *Sender);
        void __fastcall nextRoundClick(TObject *Sender);
private:	// User declarations
        void cornerHit();
        void loss();
        void gameRefresh();
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
