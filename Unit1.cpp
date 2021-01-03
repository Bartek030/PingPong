//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int ballTopMove = 0;
int ballLeftMove = 0;
int paletteTopMove = 5;
int numberOfSecondsToStart = 0;
bool isBallInGame = true;
int firstPlayerPoints = 0;
int secondPlayerPoints = 0;
int firstPlayerBonus = 0;
int secondPlayerBonus = 0;
int bonusDuration = 0;
char whoHitTheBall = 'n'; // 1 dla pierwszego gracza, 2 dla drugiego
bool isFirstPaletteDirectionChanged = false;
bool isSecondPaletteDirectionChanged = false;

void showBonusPoints() {
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

void hideMainMenuElements() {
    Form1 -> titleImage -> Visible = false;
    Form1 -> newGameButton -> Visible = false;
    Form1 -> newGameButton -> Enabled = false;
    Form1 -> rulesButton -> Visible = false;
    Form1 -> rulesButton -> Enabled = false;
    Form1 -> exitButton -> Visible = false;
    Form1 -> exitButton -> Enabled = false;
}

void showMainMenuElements() {
    Form1 -> titleImage -> Visible = true;
    Form1 -> newGameButton -> Visible = true;
    Form1 -> newGameButton -> Enabled = true;
    Form1 -> rulesButton -> Visible = true;
    Form1 -> rulesButton -> Enabled = true;
    Form1 -> exitButton -> Visible = true;
    Form1 -> exitButton -> Enabled = true;
}

 void showGameElements() {
    Form1 -> ball -> Visible = true;
    Form1 -> ball -> Enabled = true;
    Form1 -> firstPalette -> Visible = true;
    Form1 -> firstPalette -> Enabled = true;
    Form1 -> secondPalette -> Visible = true;
    Form1 -> secondPalette -> Enabled = true;
    Form1 -> firstPlayerBonusImage -> Visible = true;
    Form1 -> firstPlayerBonusImage -> Enabled = true;
    Form1 -> secondPlayerBonusImage -> Visible = true;
    Form1 -> secondPlayerBonusImage -> Enabled = true;
    showBonusPoints();
}

void hideGameElements() {
    Form1 -> ball -> Visible = false;
    Form1 -> ball -> Enabled = false;
    Form1 -> firstPalette -> Visible = false;
    Form1 -> firstPalette -> Enabled = false;
    Form1 -> secondPalette -> Visible = false;
    Form1 -> secondPalette -> Enabled = false;
    Form1 -> midPoint -> Visible = false;
    Form1 -> midPoint -> Enabled = false;
    Form1 -> littlePoint1 -> Visible = false;
    Form1 -> littlePoint1 -> Enabled = false;
    Form1 -> littlePoint2 -> Visible = false;
    Form1 -> littlePoint2 -> Enabled = false;
    Form1 -> littlePoint3 -> Visible = false;
    Form1 -> littlePoint3 -> Enabled = false;
    Form1 -> littlePoint4 -> Visible = false;
    Form1 -> pointInfo -> Visible = false;
    Form1 -> pointInfo2 -> Visible = false;
    Form1 -> result -> Visible = false;
    Form1 -> mainMenuButton -> Enabled = false;
    Form1 -> mainMenuButton -> Visible = false;
    Form1 -> newRoundButton -> Enabled = false;
    Form1 -> newRoundButton -> Visible = false;
    Form1 -> firstPlayerBonusImage -> Visible = false;
    Form1 -> firstPlayerBonusImage -> Enabled = false;
    Form1 -> secondPlayerBonusImage -> Visible = false;
    Form1 -> secondPlayerBonusImage -> Enabled = false;
}

void hideResultInformationsAndButtons() {
    Form1 -> mainMenuButton -> Enabled = false;
    Form1 -> mainMenuButton -> Visible = false;
    Form1 -> newRoundButton -> Enabled = false;
    Form1 -> newRoundButton -> Visible = false;
    Form1 -> pointInfo -> Visible = false;
    Form1 -> pointInfo2 -> Visible = false;
    Form1 -> result -> Visible = false;
}

void setBallAndPalettesInMiddlePosition() {
    Form1 -> ball -> Left = (Form1 -> board -> Width / 2) - (Form1 -> ball -> Width / 2);
    Form1 -> ball -> Top =  (Form1 -> board -> Height / 2) - (Form1 -> ball -> Height / 2);

    Form1 -> firstPalette -> Top = (Form1 -> board -> Height / 2) - (Form1 -> firstPalette -> Height / 2);
    Form1 -> secondPalette -> Top = (Form1 -> board -> Height / 2) - (Form1 -> secondPalette -> Height / 2);
}

void countDownToStart() {
    numberOfSecondsToStart = 3;
    sndPlaySound("snd/countdown.wav", SND_ASYNC);
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

void setBallStartMove() {
    randomize();
    ballTopMove = random(11) - 5;
    ballLeftMove = random(11) - 5;

    while(ballTopMove >= -2 && ballTopMove <= 2) {
        ballTopMove = random(11) - 5;
    }
    while(ballLeftMove >= -2 && ballLeftMove <= 2) {
        ballLeftMove = random(11) - 5;
    }
    Form1 -> ballTimer -> Enabled = true;
}

void changePalettesMovementDirection() {
    if(whoHitTheBall == '1') {
        isSecondPaletteDirectionChanged = true;
    } else if (whoHitTheBall == '2') {
        isFirstPaletteDirectionChanged = true;
    }
}

void changePaletteToSmallerOne() {
    if(whoHitTheBall == '1') {
        Form1 -> secondPalette -> Picture -> LoadFromFile("img/malaPaletka.bmp");
    } else if (whoHitTheBall == '2') {
        Form1 -> firstPalette -> Picture -> LoadFromFile("img/malaPaletka.bmp");
    }
}

void randomBonusActivation() {
    int bonusNumber = 0;

    randomize();
    bonusNumber = random(3) + 1;

    switch(bonusNumber) {
        case 1:
            bonusDuration = 5;
            changePalettesMovementDirection();
            break;
        case 2:
            bonusDuration = 5;
            changePaletteToSmallerOne();
            break;
        case 3:
            bonusDuration = 1;
            setBallStartMove();
            break;
    }
    Form1 -> bonusTimer -> Enabled = true;
}

void bonusDeactivation() {
    // DEZAKTYWACJA ZMIANY KIERUNKU RUCHU PALETEK
    isFirstPaletteDirectionChanged = false;
    isSecondPaletteDirectionChanged = false;
    // DEZAKTYWACJA ZMIANY WIELKOSCI PALETKI
    Form1 -> firstPalette -> Picture -> LoadFromFile("img/paletka.bmp");
    Form1 -> secondPalette -> Picture -> LoadFromFile("img/paletka.bmp");
}

void startNewRound () {
    hideResultInformationsAndButtons();
    showBonusPoints();

    firstPlayerBonus = 0;
    secondPlayerBonus = 0;
    whoHitTheBall = 'n';

    Form1 -> firstPlayerBonusImage -> Picture -> LoadFromFile("img/pustyBonus.bmp");
    Form1 -> secondPlayerBonusImage -> Picture -> LoadFromFile("img/pustyBonus.bmp");

    setBallAndPalettesInMiddlePosition();
    countDownToStart();
    setBallStartMove();
    isBallInGame = true;
    Form1 -> bonusTimer -> Enabled = false;
}

void showMatchSummary() {
    sndPlaySound("snd/endGame.wav", SND_ASYNC);
    if(firstPlayerPoints > secondPlayerPoints) {
        Form1 -> pointInfo -> Caption = "Mecz wygrywa gracz pierwszy";
    } else {
        Form1 -> pointInfo -> Caption = "Mecz wygrywa gracz drugi";
    }
    Form1 -> pointInfo2 -> Caption = "Wynikiem:";
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
        showMatchSummary();
    } else {
        Form1 -> newRoundButton -> Enabled = true;
        Form1 -> newRoundButton -> Visible = true;
    }
}

bool isBallHitPoint(TObject *Sender) {
    TImage *point = (TImage *)Sender;
        if(point -> Enabled) {
            if( point -> Left + (point -> Width / 2) >= Form1 -> ball -> Left &&
                point -> Left + (point -> Width / 2) <= Form1 -> ball -> Left + Form1 -> ball -> Width &&
                point -> Top + (point -> Height / 2) >= Form1 -> ball -> Top &&
                point -> Top + (point -> Height / 2) <= Form1 -> ball -> Top + Form1 -> ball -> Height) {
                    point -> Visible = false;
                    point -> Enabled = false;
                    return true;
            } else {
                    return false;
            }
        } else {
            return false;
        }
}

void updateBonusImage(TObject *Sender, int points) {
    TImage *image = (TImage *)Sender;
    if(points == 1) {
        image -> Picture -> LoadFromFile("img/polowaBonus.bmp");
    } else if(points == 2) {
        image -> Picture -> LoadFromFile("img/pelnyBonus.bmp");
    }
}

void countBonusPoints() {
    if(isBallHitPoint(Form1 -> littlePoint1) || isBallHitPoint(Form1 -> littlePoint2) || isBallHitPoint(Form1 -> littlePoint3) || isBallHitPoint(Form1 -> littlePoint4)) {
        if(whoHitTheBall == '1'){
            firstPlayerBonus++;
            updateBonusImage(Form1 -> firstPlayerBonusImage, firstPlayerBonus);
        } else if (whoHitTheBall == '2'){
            secondPlayerBonus++;
            updateBonusImage(Form1 -> secondPlayerBonusImage, secondPlayerBonus);
        }
    }
}

bool ballHitPaletteCenter(TObject *Sender){
    TImage *palette = (TImage *)Sender;
    if(palette -> Top + (palette -> Height / 2) >= Form1 -> ball -> Top && palette -> Top + (palette -> Height / 2) <= Form1 -> ball -> Top + Form1 -> ball -> Height) {
        return true;
    } else {
        return false;
    }
}

void increaseBallSpeed() {
    if(ballLeftMove >= 0) {
            ballLeftMove += 1;
        } else if(ballLeftMove < 0) {
            ballLeftMove -= 1;
        }
        if(ballTopMove >= 0) {
            ballTopMove += 1;
        } else if(ballTopMove < 0) {
            ballTopMove -= 1;
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
            sndPlaySound("snd/boardHit.wav", SND_ASYNC);
        }

        // ODBICIE OD LEWEJ PALETKI
        if (Form1 -> ball -> Left <= firstPalette -> Left + firstPalette -> Width &&
            Form1 -> ball -> Top + (Form1 -> ball -> Height) >= firstPalette -> Top &&
            Form1 -> ball -> Top <= firstPalette -> Top + firstPalette -> Height) {
                ballLeftMove = -ballLeftMove;
                whoHitTheBall = '1';
                sndPlaySound("snd/paletteHit.wav", SND_ASYNC);
                if(ballHitPaletteCenter(firstPalette)) {
                    increaseBallSpeed();
                }
        }
        // ODBICIE OD PRAWEJ PALETKI
        else if(Form1 -> ball -> Left + Form1 -> ball -> Width >= secondPalette -> Left &&
                Form1 -> ball -> Top + (Form1 -> ball -> Height) >= secondPalette -> Top &&
                Form1 -> ball -> Top <= secondPalette -> Top + secondPalette -> Height) {
                    ballLeftMove = -ballLeftMove;
                    whoHitTheBall = '2';
                    sndPlaySound("snd/paletteHit.wav", SND_ASYNC);
                    if(ballHitPaletteCenter(secondPalette)) {
                    increaseBallSpeed();
                }
        } else {
            if(Form1 -> ball -> Left < firstPalette -> Left + firstPalette -> Width || Form1 -> ball -> Left + Form1 -> ball -> Width > secondPalette -> Left) {
                isBallInGame = false;
            }
        }
        countBonusPoints();

        // AKTYWACJA BONUSU PRZY TRAFIENIU W SRODEK PLANSZY
        if(isBallHitPoint(Form1 -> midPoint) && !(Form1 -> bonusTimer -> Enabled)) {
            randomBonusActivation();
        }
   } else {
        if( Form1 -> ball -> Left > Form1 -> board -> Left + 5 && Form1 -> ball -> Left + Form1 -> ball -> Width < Form1 -> board -> Width - 5) {
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
    if(!isFirstPaletteDirectionChanged) {
        if (Key == 'S' || Key == 's') {
            firstPaletteDown -> Enabled = true;
        }
        if (Key == 'W' || Key == 'w') {
            firstPaletteUp -> Enabled = true;
        }
    } else {
        if (Key == 'W' || Key == 'w') {
            firstPaletteDown -> Enabled = true;
        }
        if (Key == 'S' || Key == 's') {
            firstPaletteUp -> Enabled = true;
        }
    }

    if(!isSecondPaletteDirectionChanged) {
        if (Key == VK_DOWN) {
            secondPaletteDown -> Enabled = true;
        }
        if (Key == VK_UP) {
            secondPaletteUp -> Enabled = true;
        }
    } else {
        if (Key == VK_UP) {
            secondPaletteDown -> Enabled = true;
        }
        if (Key == VK_DOWN) {
            secondPaletteUp -> Enabled = true;
        }
    }

    if(firstPlayerBonus >= 2 && !(bonusTimer -> Enabled) && (Key == 'a' || Key == 'A') && whoHitTheBall == '1') {
        Form1 -> firstPlayerBonusImage -> Picture -> LoadFromFile("img/aktywnyBonus.bmp");
        randomBonusActivation();
    }
    if(secondPlayerBonus >= 2 && !(bonusTimer -> Enabled) && Key == VK_LEFT && whoHitTheBall == '2') {
        Form1 -> secondPlayerBonusImage -> Picture -> LoadFromFile("img/aktywnyBonus.bmp");
        randomBonusActivation();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(!isFirstPaletteDirectionChanged) {
        if (Key == 'S' || Key == 's') {
            firstPaletteDown -> Enabled = false;
        }
        if (Key == 'W' || Key == 'w') {
            firstPaletteUp -> Enabled = false;
        }
    } else {
        if (Key == 'W' || Key == 'w') {
            firstPaletteDown -> Enabled = false;
        }
        if (Key == 'S' || Key == 's') {
            firstPaletteUp -> Enabled = false;
        }
    }

    if(!isSecondPaletteDirectionChanged) {
        if (Key == VK_DOWN) {
            secondPaletteDown -> Enabled = false;
        }
        if (Key == VK_UP) {
            secondPaletteUp -> Enabled = false;
        }
    } else {
        if (Key == VK_UP) {
            secondPaletteDown -> Enabled = false;
        }
        if (Key == VK_DOWN) {
            secondPaletteUp -> Enabled = false;
        }
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
    AnsiString line1 = "                                        STEROWANIE";
    AnsiString line2 = "Gracz 1                                                                      Gracz 2";
    AnsiString line3 = "    W                                    W GÓRÊ                       W GÓRÊ";
    AnsiString line4 = "     S                                      W DÓ£                          W DÓ£";
    AnsiString line5 = "     A                                     BONUS                        W LEWO";
    AnsiString line6 = "Gra toczy siê do 3 wygranych pi³ek.";
    AnsiString line7 = "Traf w œrodek aby aktywowaæ losowy bonus.";
    AnsiString line8 = "Traf 2 razy w ma³e pola aby otrzymaæ losowy bonus.";
    AnsiString line9 = "Ostro¿nie! U¿yty bonus mo¿e odwróci siê przeciw Tobie :-)";
    AnsiString line10 = "                                   Mi³ej zabawy! :-)";

    ShowMessage(line1 + sLineBreak
                + line2 + sLineBreak
                + line3 + sLineBreak
                + line4 + sLineBreak
                + line5 + sLineBreak + sLineBreak
                + line6 + sLineBreak
                + line7 + sLineBreak
                + line8 + sLineBreak
                + line9 + sLineBreak + sLineBreak
                + line10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameButtonClick(TObject *Sender) {
    hideMainMenuElements();
    showGameElements();

    //ZEROWANIE PUNKTOW
    firstPlayerPoints = 0;
    secondPlayerPoints = 0;

    startNewRound();
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


void __fastcall TForm1::mainMenuButtonClick(TObject *Sender) {
    if(Application -> MessageBox("Czy na pewno chcesz wrócic do menu g³ównego?", "Potwierdz", MB_YESNO | MB_ICONQUESTION) == IDYES) {
        hideGameElements();
        showMainMenuElements();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bonusTimerTimer(TObject *Sender) {
    bonusDuration--;
    if(bonusDuration <= 0) {
        bonusDeactivation();
        if(firstPlayerBonus >= 2) {
            firstPlayerBonus = 0;
            Form1 -> firstPlayerBonusImage -> Picture -> LoadFromFile("img/pustyBonus.bmp");
        } else if(secondPlayerBonus >= 2) {
            secondPlayerBonus = 0;
            Form1 -> secondPlayerBonusImage -> Picture -> LoadFromFile("img/pustyBonus.bmp");
        }
        showBonusPoints();
        bonusTimer -> Enabled = false;
    }
}
//---------------------------------------------------------------------------

