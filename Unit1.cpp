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
int paletteTopMove = 5;
int numberOfSecondsToStart;
bool isBallInGame = true;
int firstPlayerPoints = 0;
int secondPlayerPoints = 0;
int firstPlayerBonus = 0;
int secondPlayerBonus = 0;

void showMatchResult() {
    Form1 -> pointInfo -> Visible = true;
    if(Form1 -> ball -> Left <= Form1 -> board -> Left + 5) {
        secondPlayerPoints++;
        Form1 -> pointInfo -> Caption = "Punkt dla drugiego gracza";
    } else if(Form1 -> ball -> Left + Form1 -> ball -> Width >= Form1 -> board -> Width -5) {
        firstPlayerPoints++;
        Form1 -> pointInfo -> Caption = "Punkt dla pierwszego gracza";
    }
    Form1 -> pointInfo2 -> Visible = true;
    Form1 -> result -> Visible = true;
    Form1 -> result -> Caption = IntToStr(firstPlayerPoints) + " : " + IntToStr(secondPlayerPoints);

}

void paletteMovement(TObject *Sender, int topMove) {
    TImage *palette = (TImage *)Sender;
    palette -> Top += topMove;
}

void ballMovement(TObject *Sender, TObject *Sender2) {
    TImage *firstPalette = (TImage *)Sender;
    TImage *secondPalette = (TImage *)Sender2;
    if(isBallInGame) {
        // RUCH PILKI
        Form1 -> ball -> Top += ballTopMove;
        Form1 -> ball -> Left += ballLeftMove;

        // ODBICIE OD GORNEJ I DOLNEJ KRAWEDZI
        if(Form1 -> ball -> Top <= Form1 -> board -> Top + 5 || Form1 -> ball -> Top + Form1 -> ball -> Height >= Form1 -> board -> Height - 5) {
            ballTopMove = -ballTopMove;
        }

        // ODBICIE OD LEWEJ PALETKI
        if (Form1 -> ball -> Left <= firstPalette -> Left + firstPalette -> Width &&
            Form1 -> ball -> Top + (Form1 -> ball -> Height) >= firstPalette -> Top &&
            Form1 -> ball -> Top <= firstPalette -> Top + firstPalette -> Height) {
                ballLeftMove = -ballLeftMove;
        }
        // ODBICIE OD PRAWEJ PALETKI
        else if(Form1 -> ball -> Left + Form1 -> ball -> Width >= secondPalette -> Left &&
                Form1 -> ball -> Top + (Form1 -> ball -> Height) >= secondPalette -> Top &&
                Form1 -> ball -> Top <= secondPalette -> Top + secondPalette -> Height) {
                    ballLeftMove = -ballLeftMove;
        } else {
            if(Form1 -> ball -> Left < firstPalette -> Left + firstPalette -> Width || Form1 -> ball -> Left + Form1 -> ball -> Width > secondPalette -> Left) {
                isBallInGame = false;
            }
        }
   } else {
        if(Form1 -> ball -> Left > Form1 -> board -> Left + 5 && Form1 -> ball -> Left + Form1 -> ball -> Width < Form1 -> board -> Width - 5) {
            Form1 -> ball -> Top += ballTopMove;
            Form1 -> ball -> Left += ballLeftMove;
        } else {
            Form1 -> ballTimer -> Enabled = false;
            showMatchResult();
        }
   }
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
        paletteMovement(firstPalette, -paletteTopMove);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::firstPaletteDownTimer(TObject *Sender) {
    if(firstPalette -> Top + firstPalette -> Height <= board -> Height - 10) {
        paletteMovement(firstPalette, paletteTopMove);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::secondPaletteUpTimer(TObject *Sender) {
    if(secondPalette -> Top >= board -> Top + 10) {
        paletteMovement(secondPalette, -paletteTopMove);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::secondPaletteDownTimer(TObject *Sender) {
    if(secondPalette -> Top + secondPalette -> Height <= board -> Height - 10) {
        paletteMovement(secondPalette, paletteTopMove);
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
    //WYLACZANIE ELEMENTOW MENU GLOWNEGO
    titleImage -> Visible = false;
    newGameButton -> Visible = false;
    newGameButton -> Enabled = false;
    rulesButton -> Visible = false;
    rulesButton -> Enabled = false;
    exitButton -> Visible = false;
    exitButton -> Enabled = false;

    // WLACZANIE ELEMENTÓW GRY
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

    //USTAWIENIE PILKI I PALETEK W POZYCJI SRODKOWEJ
    ball -> Left = (board -> Width / 2) - (ball -> Width / 2);
    ball -> Top =  (board -> Height / 2) - (ball -> Height / 2);

    firstPalette -> Top = (board -> Height / 2) - (firstPalette -> Height / 2);
    secondPalette -> Top = (board -> Height / 2) - (secondPalette -> Height / 2);

    //ZEROWANIE PUNKTOW
    firstPlayerPoints = 0;
    secondPlayerPoints = 0;
    firstPlayerBonus = 0;
    secondPlayerBonus = 0;

    // ODLICZANIE DO STARTU
    numberOfSecondsToStart = 3;
    counterToStart -> Enabled = true;
    counterToStart -> Visible = true;
    while(numberOfSecondsToStart >= 0) {
        if(numberOfSecondsToStart > 0) {
            counterToStart -> Caption = IntToStr(numberOfSecondsToStart);
            Application -> ProcessMessages();
            Sleep(1000);
            numberOfSecondsToStart--;
        } else {
            counterToStart -> Caption = "START";
            Application -> ProcessMessages();
            Sleep(1000);
            counterToStart -> Enabled = false;
            counterToStart -> Visible = false;
            numberOfSecondsToStart--;
        }
    }

    // URUCHOMIENIE PILKI
    ballTimer -> Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ballTimerTimer(TObject *Sender) {
    ballMovement(firstPalette, secondPalette);
}
//---------------------------------------------------------------------------

