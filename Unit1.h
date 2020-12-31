//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *board;
    TImage *midPoint;
    TImage *littlePoint1;
    TImage *littlePoint2;
    TImage *littlePoint3;
    TImage *littlePoint4;
    TImage *firstPalette;
    TImage *secondPalette;
    TImage *ball;
    TTimer *firstPaletteUp;
    TTimer *secondPaletteUp;
    TTimer *ballTimer;
    TTimer *firstPaletteDown;
    TTimer *secondPaletteDown;
    TImage *titleImage;
    TButton *newGameButton;
    TButton *rulesButton;
    TButton *exitButton;
    TLabel *counterToStart;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall firstPaletteUpTimer(TObject *Sender);
    void __fastcall firstPaletteDownTimer(TObject *Sender);
    void __fastcall secondPaletteUpTimer(TObject *Sender);
    void __fastcall secondPaletteDownTimer(TObject *Sender);
    void __fastcall ballTimerTimer(TObject *Sender);
    void __fastcall exitButtonClick(TObject *Sender);
    void __fastcall rulesButtonClick(TObject *Sender);
    void __fastcall newGameButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
