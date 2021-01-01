//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int ballTopMove = 0;
int ballLeftMove = 0;
int paletteTopMove = 5;
int numberOfSecondsToStart;
bool isBallInGame = true;
int firstPlayerPoints = 0;
int secondPlayerPoints = 0;
int firstPlayerBonus = 0;
int secondPlayerBonus = 0;

void hideMainMenuElements() {
    Form1 -> titleImage -> Visible = false;
    Form1 -> newGameButton -> Visible = false;
    Form1 -> newGameButton -> Enabled = false;
    Form1 -> rulesButton -> Visible = false;
    Form1 -> rulesButton -> Enabled = false;
    Form1 -> exitButton -> Visible = false;
    Form1 -> exitButton -> Enabled = false;
}

void showGameElements() {
    Form1 -> ball -> Visible = true;
    Form1 -> ball -> Enabled = true;
    Form1 -> firstPalette -> Visible = true;
    Form1 -> firstPalette -> Enabled = true;
    Form1 -> secondPalette -> Visible = true;
    Form1 -> secondPalette -> Enabled = true;
    Form1 -> midPoint -> Visible = true;
    Form1 -> midPoint -> Enabled = true;
    Form1 -> littlePoint1 -> Visible = true;
    Form1 -> littlePoint1 -> Enabled = true;
    Form1 -> littlePoint2 -> Visible = true;
    Form1 -> littlePoint2 -> Enabled = true;
    Form1 -> littlePoint3 -> Visible = true;
    Form1 -> littlePoint3 -> Enabled = true;
    Form1 -> littlePoint4 -> Visible = true;
    Form1 -> littlePoint4 -> Enabled = true;
}

void setBallAndPalettesInMiddlePosition() {
    Form1 -> ball -> Left = (Form1 -> board -> Width / 2) - (Form1 -> ball -> Width / 2);
    Form1 -> ball -> Top =  (Form1 -> board -> Height / 2) - (Form1 -> ball -> Height / 2);

    Form1 -> firstPalette -> Top = (Form1 -> board -> Height / 2) - (Form1 -> firstPalette -> Height / 2);
    Form1 -> secondPalette -> Top = (Form1 -> board -> Height / 2) - (Form1 -> secondPalette -> Height / 2);
}

void countDownToStart() {
    numberOfSecondsToStart = 3;
    Form1 -> counterToStart -> Enabled = true;
    Form1 -> counterToStart -> Visible = true;
    while(numberOfSecondsToStart >= 0) {
        if(numberOfSecondsToStart > 0) {
            Form1 -> counterToStart -> Caption = IntToStr(numberOfSecondsToStart);
            Application -> ProcessMessages();
            Sleep(1000);
            numberOfSecondsToStart--;
        } else {
            Form1 -> counterToStart -> Caption = "START";
            Application -> ProcessMessages();
            Sleep(1000);
            Form1 -> counterToStart -> Enabled = false;
            Form1 -> counterToStart -> Visible = false;
            numberOfSecondsToStart--;
        }
    }
}

void setBallMovement() {
    randomize();
    while(ballTopMove == 0) {
        ballTopMove = random(11) - 5;
    }
    while(ballLeftMove == 0) {
        ballLeftMove = random(11) - 5;
    }
    Form1 -> ballTimer -> Enabled = true;
}

void startNewRound () {
    Form1 -> mainMenuButton -> Enabled = false;
    Form1 -> mainMenuButton -> Visible = false;
    Form1 -> newRoundButton -> Enabled = false;
    Form1 -> newRoundButton -> Visible = false;
    Form1 -> pointInfo -> Visible = false;
    Form1 -> pointInfo2 -> Visible = false;
    Form1 -> result -> Visible = false;

    setBallAndPalettesInMiddlePosition();
    countDownToStart();
    setBallMovement();
    isBallInGame = true;
}

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

    Application -> ProcessMessages();
    Sleep(1000);

    Form1 -> mainMenuButton -> Enabled = true;
    Form1 -> mainMenuButton -> Visible = true;

    if(firstPlayerPoints >= 3 || secondPlayerPoints >= 3) {
        //showMatchSummary();
    } else {
        Form1 -> newRoundButton -> Enabled = true;
        Form1 -> newRoundButton -> Visible = true;
    }
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
    hideMainMenuElements();
    showGameElements();
    setBallAndPalettesInMiddlePosition();
    isBallInGame = true;

    //ZEROWANIE PUNKTOW
    firstPlayerPoints = 0;
    secondPlayerPoints = 0;
    firstPlayerBonus = 0;
    secondPlayerBonus = 0;

    countDownToStart();
    setBallMovement();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ballTimerTimer(TObject *Sender) {
    ballMovement(firstPalette, secondPalette);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::newRoundButtonClick(TObject *Sender) {
    startNewRound();
}
//---------------------------------------------------------------------------

