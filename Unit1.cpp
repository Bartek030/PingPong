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
int numberOfSecondsToStart = 3;
bool isBallInGame = true;

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
    if(isBallInGame) {
        // RUCH PILKI
        ball -> Top += ballTopMove;
        ball -> Left += ballLeftMove;

        // ODBICIE OD GÓRNEJ I DOLNEJ KRAWEDZI
        if(ball -> Top <= board -> Top + 5 || ball -> Top + ball -> Height >= board -> Height - 5) {
            ballTopMove = -ballTopMove;
        }

        // ODBICIE OD LEWEJ PALETKI
        if (ball -> Left <= firstPalette -> Left + firstPalette -> Width &&
            ball -> Top + (ball -> Height) >= firstPalette -> Top &&
            ball -> Top <= firstPalette -> Top + firstPalette -> Height) {
                ballLeftMove = -ballLeftMove;
        }
        // ODBICIE OD PRAWEJ PALETKI
        else if(ball -> Left + ball -> Width >= secondPalette -> Left &&
                ball -> Top + (ball -> Height) >= secondPalette -> Top &&
                ball -> Top <= secondPalette -> Top + secondPalette -> Height) {
                    ballLeftMove = -ballLeftMove;
        } else {
            if(ball -> Left < firstPalette -> Left + firstPalette -> Width || ball -> Left + ball -> Width > secondPalette -> Left) {
                isBallInGame = false;
            }
        }
   } else {
        if(ball -> Left > board -> Left + 5 && ball -> Left + ball -> Width < board -> Width - 5) {
            ball -> Top += ballTopMove;
            ball -> Left += ballLeftMove;
        }
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::exitButtonClick(TObject *Sender)
{
    exit(0);    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rulesButtonClick(TObject *Sender) {
    AnsiString line1 = "                            STEROWANIE";
    AnsiString line2 = "Gracz 1                                                     Gracz 2";
    AnsiString line3 = "    W                           W GÓRÊ                      8";
    AnsiString line4 = "     S                             W DÓ£                       2";
    AnsiString line5 = "SPACJA                      BONUS                   LCTRL";
    AnsiString line6 = "Gra toczy siê do 3 wygranych pi³ek.";
    AnsiString line7 = "Traf w œrodek aby aktywowaæ losowy bonus.";
    AnsiString line8 = "Traf 3 razy w ma³e pola aby otrzymaæ losowy bonus.";
    AnsiString line9 = "                                Mi³ej zabawy! :-)";

    ShowMessage(line1 + sLineBreak
                + line2 + sLineBreak
                + line3 + sLineBreak
                + line4 + sLineBreak
                + line5 + sLineBreak + sLineBreak
                + line6 + sLineBreak
                + line7 + sLineBreak
                + line8 + sLineBreak + sLineBreak
                + line9);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameButtonClick(TObject *Sender) {
    titleImage -> Visible = false;
    newGameButton -> Visible = false;
    newGameButton -> Enabled = false;
    rulesButton -> Visible = false;
    rulesButton -> Enabled = false;
    exitButton -> Visible = false;
    exitButton -> Enabled = false;

    ball -> Visible = true;
    ball -> Enabled = true;
    firstPalette -> Visible = true;
    firstPalette -> Enabled = true;
    secondPalette -> Visible = true;
    secondPalette -> Enabled = true;
    midPoint -> Visible = true;
    midPoint -> Enabled = true;
    littlePoint1 -> Visible = true;
    littlePoint1 -> Enabled = true;
    littlePoint2 -> Visible = true;
    littlePoint2 -> Enabled = true;
    littlePoint3 -> Visible = true;
    littlePoint3 -> Enabled = true;
    littlePoint4 -> Visible = true;
    littlePoint4 -> Enabled = true;
}
//---------------------------------------------------------------------------

