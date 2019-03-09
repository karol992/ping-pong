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
        TImage *paddle1;
        TImage *paddle2;
        TTimer *paddle1up;
        TTimer *paddle1down;
        TTimer *paddle2up;
        TTimer *paddle2down;
        TImage *ball;
        TTimer *ball_moving;
        TButton *nowaGra;
        TLabel *winnerInfo;
        TLabel *bouncesInfo;
        TLabel *scoreTable;
        TButton *nextRound;
        void __fastcall paddle1upTimer(TObject *Sender);
        void __fastcall paddle1downTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall paddle2upTimer(TObject *Sender);
        void __fastcall paddle2downTimer(TObject *Sender);
        void __fastcall ball_movingTimer(TObject *Sender);
        void __fastcall nowaGraClick(TObject *Sender);
        void __fastcall nextRoundClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
