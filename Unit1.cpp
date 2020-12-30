//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int ballTopMove = 5;
int ballLeftMove = 5;

void paletteMovement(TObject *Sender, int topMove) {
    TImage *palette = (TImage *)Sender;
    palette -> Top += topMove;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift) {
    if (Key == 'S' || Key == 's') {
        firstPaletteDown -> Enabled = true;
    }
    if (Key == 'W' || Key == 'w') {
        firstPaletteUp -> Enabled = true;
    }
    if (Key == VK_DOWN) {
        secondPaletteDown -> Enabled = true;
    }
    if (Key == VK_UP) {
        secondPaletteUp -> Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == 'S' || Key == 's') {
        firstPaletteDown -> Enabled = false;
    }
    if (Key == 'W' || Key == 'w') {
        firstPaletteUp -> Enabled = false;
    }
    if (Key == VK_DOWN) {
        secondPaletteDown -> Enabled = false;
    }
    if (Key == VK_UP) {
        secondPaletteUp -> Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::firstPaletteUpTimer(TObject *Sender) {
    if(firstPalette -> Top >= board -> Top + 10) {
        paletteMovement(firstPalette, -5);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::firstPaletteDownTimer(TObject *Sender) {
    if(firstPalette -> Top + firstPalette -> Height <= board -> Height - 10) {
        paletteMovement(firstPalette, 5);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::secondPaletteUpTimer(TObject *Sender) {
    if(secondPalette -> Top >= board -> Top + 10) {
        paletteMovement(secondPalette, -5);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::secondPaletteDownTimer(TObject *Sender) {
    if(secondPalette -> Top + secondPalette -> Height <= board -> Height - 10) {
        paletteMovement(secondPalette, 5);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballTimerTimer(TObject *Sender) {
    ball -> Top += ballTopMove;
    ball -> Left += ballLeftMove;

    if(ball -> Top <= board -> Top + 10 || ball -> Top + ball -> Height >= board -> Height - 10) {
        ballTopMove = -ballTopMove;
    }

    if((ball -> Left < firstPalette -> Left + firstPalette -> Width &&
        ball -> Top + (ball -> Height / 2) > firstPalette -> Top &&
        ball -> Top + (ball -> Height / 2) < firstPalette -> Top + firstPalette -> Height) ||
       (ball -> Left + ball -> Width > secondPalette -> Left &&
        ball -> Top + (ball -> Height / 2) > secondPalette -> Top &&
        ball -> Top + (ball -> Height / 2) < secondPalette -> Top + secondPalette -> Height))
    {
        if(ballLeftMove != 0) {
            ballLeftMove = -ballLeftMove;
        }
    }
}
//---------------------------------------------------------------------------

