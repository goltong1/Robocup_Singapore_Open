////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2016
//	Copyright (C) 2016 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif//The robot ID : It must be two char, such as '00','kl' or 'Cr'.
char AI_MyID[2] = {'0','2'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int wHead = 1;
int tForward = 0;
int CornerStress = 0;
int TargetTheta = 0;
int ModeEscape = 0;
int Steering = 0;
int bInitial = 0;
int WTC = 0;
int tDeposit = 10000;
int tLoad = 0;
int NowDirection = 0;
int wDirection = 0;
int bSwamp = 0;
int dCollectionBox = 0;
int NeedY = 0;
int NeedX = 0;
int DX = 0;
int DY = 0;
int GuessX = 0;
int GuessY = 0;
int CountPush = 0;
int TX = 0;
int TY = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;

#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
    char info[1024];
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;wHead=%d;tForward=%d;CornerStress=%d;TargetTheta=%d;ModeEscape=%d;Steering=%d;bInitial=%d;WTC=%d;tDeposit=%d;tLoad=%d;NowDirection=%d;wDirection=%d;bSwamp=%d;dCollectionBox=%d;NeedY=%d;NeedX=%d;DX=%d;DY=%d;GuessX=%d;GuessY=%d;CountPush=%d;TX=%d;TY=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,wHead,tForward,CornerStress,TargetTheta,ModeEscape,Steering,bInitial,WTC,tDeposit,tLoad,NowDirection,wDirection,bSwamp,dCollectionBox,NeedY,NeedX,DX,DY,GuessX,GuessY,CountPush,TX,TY,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
     return "";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}

#endif CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void Game0()
{

    if(SuperDuration>0)
    {
        SuperDuration--;
    }
    else if(Duration>0)
    {
        Duration--;
    }
    else if(bInitial==0)
    {
        Duration = 0;
        CurAction =1;
    }
    else if(Time>=181 && Time<=1000&&(LoadedObjects<2&&(Time>tDeposit+3)))
    {
        Duration = 0;
        CurAction =2;
    }
    else if(Time>=240 && Time<=1000)
    {
        Duration = 0;
        CurAction =3;
    }
    else if(LoadedObjects>0&&
((CSLeft_R>50&&CSLeft_R<70&&CSLeft_G>86&&CSLeft_G<119&&CSLeft_B>210)||
(CSRight_R>50&&CSRight_R<70&&CSRight_G>86&&CSRight_G<119&&CSRight_B>210)))
    {
        Duration = 3;
        CurAction =4;
    }
    else if((LoadedObjects>0)&&((CSLeft_R>190&&CSLeft_G>170&&CSLeft_B<40)||
(CSRight_R>190&&CSRight_G>170&&CSRight_B<40))



)
    {
        Duration = 0;
        CurAction =5;
    }
    else if(LoadedObjects<6&&((CSLeft_R<100&&CSLeft_G<100&&CSLeft_B<100)
||(CSRight_R<100&&CSRight_G<100&CSRight_B<100)))
    {
        Duration = 44;
        CurAction =6;
    }
    else if(LoadedObjects<6&&((CSLeft_R<70&&CSLeft_G>200&&CSLeft_B<70)||
(CSRight_R<70&&CSRight_G>200&&CSRight_B<70)))
    {
        Duration = 46;
        CurAction =7;
    }
    else if(LoadedObjects<6&&
((CSLeft_R>175&&CSLeft_G<50&&CSLeft_B<50)||
(CSRight_R>175&&CSRight_G<50&&CSRight_B<50)))
    {
        Duration = 46;
        CurAction =8;
    }
    else if((CSLeft_R>200&&CSLeft_G>200&&(CSLeft_B<80&&CSLeft_B>41))||
(CSRight_R>200&&CSRight_G>200&&(CSRight_B<80&&CSRight_B>41))
)
    {
        Duration = 0;
        CurAction =9;
    }
    else if(CSLeft_R>=190 && CSLeft_R<=255 && CSLeft_G>=110 && CSLeft_G<=160 && CSLeft_B>=0 && CSLeft_B<=20 && CSRight_R>=190 && CSRight_R<=255 && CSRight_G>=110 && CSRight_G<=160 && CSRight_B>=0 && CSRight_B<=20&&(LoadedObjects>0))
    {
        Duration = 49;
        CurAction =10;
    }
    else if(CSLeft_R>=180 && CSLeft_R<=255 && CSLeft_G>=100 && CSLeft_G<=160 && CSLeft_B>=0 && CSLeft_B<=30&&(LoadedObjects>0))
    {
        Duration = 0;
        CurAction =11;
    }
    else if(CSRight_R>=180 && CSRight_R<=255 && CSRight_G>=100 && CSRight_G<=160 && CSRight_B>=0 && CSRight_B<=30&&(LoadedObjects>0))
    {
        Duration = 0;
        CurAction =12;
    }
    else if((US_Left<8||US_Right<8||US_Front<20))
    {
        Duration = 0;
        CurAction =13;
        if(US_Front>=0 && US_Front<=12)
        {
            Duration = 0;
            CurAction =14;
        }
        else if(US_Front<13||US_Left<8||US_Right<8)
        {
            Duration = 0;
            CurAction =15;
        }
    }
    else if(true)
    {
        Duration = 0;
        CurAction =16;
    }
    switch(CurAction)
    {
        case 1:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            bInitial=1;
                    
WTC=0;
                    
TargetTheta=50;
                    
sleep(30000);
                    
/*
//When Start, Turn Degrees
WheelLeft=-2;
                    WheelRight=2;
                    Duration=1;
                    
if(abs(TargetTheta-Compass)<15){Duration=0;
                    }
*/


            break;
        case 2:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            bInitial=0;
                    
             Teleport =2;  
            LoadedObjects = 0;
            WheelLeft = 0;  WheelRight = 0;  LED_1=0;
            Duration = 0;   SuperDuration = 0;
            break;
        case 3:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            bInitial=0;
                    
             Teleport =2;  
            LoadedObjects = 0;
            WheelLeft = 0;  WheelRight = 0;  LED_1=0;
            Duration = 0;   SuperDuration = 0;
            break;
        case 4:
            WheelLeft=-5;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            LoadedObjects=0;
                    
printf("Oh! My Got!!\n");
                    
            break;
        case 5:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(CSLeft_B>=CSRight_B){wHead=-1;
                    }

Duration=1;
                    
if(wHead==1)
{WheelLeft=1;
                    WheelRight=-2;
                    }else{WheelLeft=-2;
                    WheelRight=1;
                    }

if(CSLeft_B>200&&CSRight_B>200)
{//WheelLeft=0;
                    //WheelRight=0;
                    Duration=0;
                    
printf("Trap!! Run Away!! Head=%d\n", wHead);
                    }


            break;
        case 6:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==0)printf("I Got a Lucky!! - LoadedObjects=%d\n", LoadedObjects);
                    

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 7:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration<8){WheelLeft=4;
                    WheelRight=4;
                    }
if(Duration==0)printf("I Got a Green - LoadedObjects=%d\n", LoadedObjects);
                    
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 8:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration<8){WheelLeft=4;
                    WheelRight=4;
                    }
if(Duration==0)printf("I Got a Red - LoadedObjects=%d\n", LoadedObjects);
                    

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 9:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(CSRight_B<=CSLeft_B){wHead=-1;
                    }

if(wHead==1)
{WheelLeft=1;
                    WheelRight=-2;
                    }else{WheelLeft=-2;
                    WheelRight=1;
                    }
Duration=1;
                    

if(CSLeft_B>200&&CSRight_B>200)
{WheelLeft=0;
                    WheelRight=0;
                    Duration=0;
                    
printf("Don't Worry..^^ Head=%d\n", wHead);
                    }




            break;
        case 10:
            WheelLeft=1;
            WheelRight=1;
            LED_1=2;
            MyState=0;
            tDeposit=1000;
                    LoadedObjects=0;
                    
if(Duration==49){printf("D-Red:%d-%d\n",CSLeft_R,CSRight_R);
                    }
if(Duration==48){printf("D-Green:%d-%d\n",CSLeft_G,CSRight_G);
                    }
if(Duration==47){printf("D-Blue:%d-%d\n",CSLeft_B,CSRight_B);
                    }

if(Duration<48){WheelLeft=0;
                    WheelRight=0;
                    }
if(Duration<4){Duration=0;
                    }
if(Duration==0){tDeposit=Time;
                    printf("yeh Deposit!!?\n");
                    }

/*
if((CSLeft_G>170||CSLeft_B>100)&&(CSRight_G>170||CSRight_B>100))
{Duration=0;
                    tDeposit=Time;
                    printf("yeh Deposit!!?\n");
                    }
*/


            if(Duration == 1) {LoadedObjects = 0; } 
            break;
        case 11:
            WheelLeft=-1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            if(Duration==0)printf("It Is Seems to be Around Here?!! ^^\n");
                    
            break;
        case 12:
            WheelLeft=3;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            if(Duration==0)printf("It Is Seems to be Around Here?!! ^^\n");
                    
            break;
        case 13:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            //tForward=0;
                    
//printf("Be Careful!!! \n");
                    
            break;
        case 14:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(US_Right<20&&(US_Right<US_Left)){wHead=-1;
                    }
if(wHead==1)
{WheelLeft=0;
                    WheelRight=-2;
                    }else{WheelLeft=-2;
                    WheelRight=0;
                    }
//printf("too Close!!-%d\n",tForward);
                    


//Start Corner
if(tForward!=0){
 if(tForward<45){CornerStress++;
                    printf("%d\n",CornerStress);
                    }
 else{ModeEscape=0;
                    CornerStress=0;
                    } 
 if(CornerStress>2)
 {CornerStress=0;
                    ModeEscape=1;
                    TargetTheta=(Compass+150)%360;
                    
 Duration=1;
                    printf("no!!!-%d\n",(Compass+150)%360);
                    }
}tForward=0;
                    
if(ModeEscape==1){Duration=1;
                    WheelLeft=2;
                    WheelRight=-2;
                    
 if(abs(TargetTheta-Compass)<15){Duration=0;
                    ModeEscape=0;
                    }}

//End Corner
            break;
        case 15:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(US_Right<US_Left){wHead=-1;
                    }

if(wHead==1)
{Steering=US_Front/US_Left;
                     //if over 2, over 50degrees
 WheelLeft=2;
                    WheelRight=-2;
                    
 if(Steering>4){WheelLeft=1;
                    WheelRight=-1;
                    }
}
else
{Steering=US_Front/US_Right;
                     //if over 2, over 50degrees
 WheelLeft=-2;
                    WheelRight=1;
                    
 if(Steering>4){WheelLeft=-1;
                    WheelRight=1;
                    }
}

printf("wHead=%d  Steering=%d\n",wHead, Steering);
                    
 
            break;
        case 16:
            WheelLeft=3;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            if(tForward<8000)tForward++;
                    
//printf("go\n");
                    
            break;
        default:
            break;
    }

}

void Game1()
{

    if(SuperDuration>0)
    {
        SuperDuration--;
    }
    else if(Duration>0)
    {
        Duration--;
    }
    else if(bInitial==0)
    {
        Duration = 0;
        CurAction =1;
    }
    else if(LoadedObjects<6&&(CSLeft_R>150&&CSLeft_G<15&&CSLeft_B>230)
||(CSLeft_R>180&&CSRight_G<15&&CSRight_B>230))
    {
        Duration = 44;
        CurAction =2;
    }
    else if(CSLeft_R>=120 && CSLeft_R<=165 && CSLeft_G>=130 && CSLeft_G<=170 && CSLeft_B>=170 && CSLeft_B<=220)
    {
        Duration = 0;
        CurAction =3;
    }
    else if(CSRight_R>=120 && CSRight_R<=165 && CSRight_G>=130 && CSRight_G<=170 && CSRight_B>=170 && CSRight_B<=220)
    {
        Duration = 0;
        CurAction =4;
    }
    else if(bSwamp==1)
    {
        Duration = 0;
        CurAction =5;
    }
    else if(LoadedObjects>0&&
((CSLeft_R>50&&CSLeft_R<70&&CSLeft_G>86&&CSLeft_G<119&&CSLeft_B>210)||
(CSRight_R>50&&CSRight_R<70&&CSRight_G>86&&CSRight_G<119&&CSRight_B>210)))
    {
        Duration = 0;
        CurAction =6;
    }
    else if(LoadedObjects>0&&
((CSLeft_R>190&&CSLeft_G>190&&CSLeft_B<20)||
(CSRight_R>190&&CSRight_G>190&&CSRight_B<20))



)
    {
        Duration = 0;
        CurAction =7;
    }
    else if(LoadedObjects<6&&((CSLeft_R<100&&CSLeft_G<100&CSLeft_B<100)
||(CSRight_R<100&&CSRight_G<100&CSRight_B<100)))
    {
        Duration = 44;
        CurAction =8;
    }
    else if(LoadedObjects<6&&((CSLeft_R<70&&CSLeft_G>200&&CSLeft_B<70)||
(CSRight_R<70&&CSRight_G>200&&CSRight_B<70)))
    {
        Duration = 44;
        CurAction =9;
    }
    else if(LoadedObjects<6&&
((CSLeft_R>175&&CSLeft_G<50&&CSLeft_B<50)||
(CSRight_R>175&&CSRight_G<50&&CSRight_B<50)))
    {
        Duration = 44;
        CurAction =10;
    }
    else if(CSLeft_R>=190 && CSLeft_R<=255 && CSLeft_G>=110 && CSLeft_G<=160 && CSLeft_B>=0 && CSLeft_B<=20 && CSRight_R>=190 && CSRight_R<=255 && CSRight_G>=110 && CSRight_G<=160 && CSRight_B>=0 && CSRight_B<=20&&(LoadedObjects>0))
    {
        Duration = 49;
        CurAction =11;
    }
    else if(CSLeft_R>=180 && CSLeft_R<=255 && CSLeft_G>=100 && CSLeft_G<=160 && CSLeft_B>=0 && CSLeft_B<=30&&(LoadedObjects>0))
    {
        Duration = 0;
        CurAction =12;
    }
    else if(CSRight_R>=180 && CSRight_R<=255 && CSRight_G>=100 && CSRight_G<=160 && CSRight_B>=0 && CSRight_B<=30&&(LoadedObjects>0))
    {
        Duration = 0;
        CurAction =13;
    }
    else if(PositionX>=150 && PositionX<=200 && PositionY>=190 && PositionY<=270)
    {
        Duration = 0;
        CurAction =14;
    }
    else if(PositionX>=1 && PositionX<=1000 && PositionY>=200 && PositionY<=270&&(WTC==0&&(PositionX<18||PositionX>347||PositionY>252||PositionY<50)
))
    {
        Duration = 0;
        CurAction =15;
    }
    else if(PositionX>=1 && PositionX<=1000 && PositionY>=1 && PositionY<=210&&(WTC==0&&(PositionX<16||PositionX>344||PositionY<16||PositionY>190)
))
    {
        Duration = 0;
        CurAction =16;
    }
    else if((US_Left<10||US_Right<10||US_Front<20))
    {
        Duration = 0;
        CurAction =17;
        if(US_Front>=0 && US_Front<=12)
        {
            Duration = 0;
            CurAction =18;
        }
        else if(US_Front<15||US_Left<10||US_Right<10)
        {
            Duration = 0;
            CurAction =19;
        }
    }
    else if(true)
    {
        Duration = 0;
        CurAction =20;
        if(PositionX>=176 && PositionX<=220 && PositionY>=10 && PositionY<=250&&((LoadedObjects>3&&WTC==0)||(Time>460&&WTC==0&&LoadedObjects>0)))
        {
            Duration = 0;
            CurAction =21;
        }
        else if(PositionX>=1 && PositionX<=230 && PositionY>=1 && PositionY<=40&&((LoadedObjects>3&&WTC==0)||(Time>460&&WTC==0&&LoadedObjects>0)))
        {
            Duration = 0;
            CurAction =22;
        }
        else if(WTC==1)
        {
            Duration = 0;
            CurAction =23;
        }
        else if(WTC==2)
        {
            Duration = 0;
            CurAction =24;
        }
        else if(WTC==3)
        {
            Duration = 0;
            CurAction =25;
        }
        else if(WTC==4)
        {
            Duration = 0;
            CurAction =26;
        }
        else if(WTC==5)
        {
            Duration = 0;
            CurAction =27;
        }
    }
    switch(CurAction)
    {
        case 1:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            bInitial=1;
                    
WTC=0;
                    
TargetTheta=50;
                    

/*
//When Start, Turn Degrees
WheelLeft=-2;
                    WheelRight=2;
                    Duration=1;
                    
if(abs(TargetTheta-Compass)<15){Duration=0;
                    }
*/


            break;
        case 2:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==0)printf("I Got a Lucky!! - LoadedObjects=%d\n", LoadedObjects);
                    

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 3:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            Duration=1;
                    
if((CSLeft_R<120||CSLeft_R>170||CSLeft_B<160||CSLeft_B>230)&&
(CSRight_R<120||CSRight_R>170||CSRight_B<160||CSRight_B>230))
{Duration=0;
                    }

bSwamp=1;
                    
TargetTheta=1000;
                    //reset
if(Duration==0){printf("Swamp!!-L\n");
                    }
            break;
        case 4:
            WheelLeft=-5;
            WheelRight=-5;
            LED_1=0;
            MyState=0;
            Duration=1;
                    
if((CSLeft_R<120||CSLeft_R>170||CSLeft_B<160||CSLeft_B>230)&&
(CSRight_R<120||CSRight_R>170||CSRight_B<160||CSRight_B>230))
{Duration=0;
                    }

bSwamp=1;
                    TargetTheta=1000;
                    //reset
if(Duration==0){printf("Swamp!!-R\n");
                    }
            break;
        case 5:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            bSwamp=0;
                    
if(TargetTheta==1000&&PositionX==0&&PositionY==0)
{WheelLeft=-2;
                    WheelRight=-2;
                    Duration=1;
                    printf("Block\n");
                    }else{

 //Set Avoid Degrees
 if(PositionX<200)
 {if(PositionY<42){TargetTheta=230;
                    }else{TargetTheta=0;
                    }}
 else
 {if(PositionY<50){TargetTheta=150;
                    }else{TargetTheta=30;
                    }}

 printf("TargetTheta-%d\n",TargetTheta);
                    

 wHead=1;
                    
 WheelLeft=2;
                     WheelRight=-2;
                    
 if(TargetTheta==0){if(Compass>180){wHead=-1;
                    }}
 if(TargetTheta==180){if(Compass<180){wHead=-1;
                    }}
 if(TargetTheta==230){if(Compass>50&&Compass<230){wHead=-1;
                    }} 
 if(TargetTheta==30){if(Compass>210||Compass<30){wHead=-1;
                    }}
 if(TargetTheta==150){if(Compass>330||Compass<150){wHead=-1;
                    }}

 if(wHead==-1){WheelLeft=-2;
                    WheelRight=2;
                    }
 Duration=1;
                    

 if(abs(TargetTheta-Compass)<20){
 Duration=0;
                    WheelLeft=0;
                    WheelRight=0;
                    WTC=0;
                    
 printf("Turned Enough %d\n",TargetTheta);
                    }
}


            break;
        case 6:
            WheelLeft=-5;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            LoadedObjects=0;
                    
printf("Oh! My Got!!\n");
                    
            break;
        case 7:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(CSLeft_B>CSRight_B){wHead=-1;
                    }

Duration=1;
                    
if(wHead==1)
{WheelLeft=1;
                    WheelRight=-2;
                    }else{WheelLeft=-3;
                    WheelRight=2;
                    }

if(CSLeft_B>100&&CSRight_B>100)
{//WheelLeft=0;
                    //WheelRight=0;
                    Duration=0;
                    
printf("Trap!! Run Away!! Head=%d\n", wHead);
                    }

WTC=0;
                    

            break;
        case 8:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==0)printf("I Got a Black!! - LoadedObjects=%d\n", LoadedObjects);
                    

            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 9:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration==0)printf("I Got a Green - LoadedObjects=%d\n", LoadedObjects);
                    
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            
if(Duration==0)printf("I Got a Red - LoadedObjects=%d\n", LoadedObjects);
                    
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 2;
                WheelRight = 2;
            }
            break;
        case 11:
            WheelLeft=1;
            WheelRight=1;
            LED_1=2;
            MyState=0;
            
tDeposit=1000;
                    LoadedObjects=0;
                    WTC=0;
                    
if(Duration==49){printf("D-Red:%d-%d\n",CSLeft_R,CSRight_R);
                    }
if(Duration==48){printf("D-Green:%d-%d\n",CSLeft_G,CSRight_G);
                    }
if(Duration==47){printf("D-Blue:%d-%d\n",CSLeft_B,CSRight_B);
                    }

if(Duration<48){WheelLeft=0;
                    WheelRight=0;
                    }
if(Duration<4){Duration=0;
                    }
if(Duration==0){tDeposit=Time;
                    printf("yeh Deposit!!?\n");
                    }

/*
if((CSLeft_G>170||CSLeft_B>100)&&(CSRight_G>170||CSRight_B>100))
{Duration=0;
                    tDeposit=Time;
                    printf("yeh Deposit!!?\n");
                    }
*/





            if(Duration == 1) {LoadedObjects = 0; } 
            break;
        case 12:
            WheelLeft=-1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            if(Duration==0)printf("It Is Seems to be Around Here?!! ^^\n");
                    
            break;
        case 13:
            WheelLeft=3;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            if(Duration==0)printf("It Is Seems to be Around Here?!! ^^\n");
                    
            break;
        case 14:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            TargetTheta=180;
                    

if(TargetTheta<Compass){WheelLeft=2;
                    WheelRight=-2;
                    }
else{WheelLeft=-2;
                    WheelRight=2;
                    }

if(abs(TargetTheta-Compass)<10){
Duration=1;
                    
WheelLeft=4;
                    WheelRight=4;
                    WTC=0;
                    
printf("Go To Safety Zone %d\a\n",TargetTheta);
                    }

if(PositionY>0&&PositionY<180){Duration=0;
                    }






            break;
        case 15:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            
wHead=1;
                    NowDirection=Compass/90;
                    
//printf("Danger!-%d\n",NowDirection);
                    
if(PositionX<20){
 if(NowDirection==0){WheelLeft=2;
                    WheelRight=-2;
                    }
 if(NowDirection==1){WheelLeft=-2;
                    WheelRight=2;
                    }}
if(PositionX>340){
 if(NowDirection==2){WheelLeft=2;
                    WheelRight=-2;
                    }
 if(NowDirection==3){WheelLeft=-2;
                    WheelRight=2;
                    }}

if(PositionY<230){
 if(NowDirection==1){WheelLeft=1;
                    WheelRight=-1;
                    }
 if(NowDirection==2){WheelLeft=-2;
                    WheelRight=2;
                    }}
if(PositionY>250){
 if(NowDirection==3){WheelLeft=1;
                    WheelRight=-1;
                    }
 if(NowDirection==0){WheelLeft=-2;
                    WheelRight=2;
                    }}









            break;
        case 16:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            
wHead=1;
                    NowDirection=Compass/90;
                    
//printf("Danger!-%d\n",NowDirection);
                    
if(PositionX<20){
 if(NowDirection==0){WheelLeft=2;
                    WheelRight=-2;
                    }
 if(NowDirection==1){WheelLeft=-2;
                    WheelRight=2;
                    }}
if(PositionX>340){
 if(NowDirection==2){WheelLeft=2;
                    WheelRight=-2;
                    }
 if(NowDirection==3){WheelLeft=-2;
                    WheelRight=2;
                    }}

if(PositionY<20){
 if(NowDirection==1){WheelLeft=1;
                    WheelRight=-1;
                    }
 if(NowDirection==2){WheelLeft=-2;
                    WheelRight=2;
                    }}
if(PositionY>180){
 if(NowDirection==3){WheelLeft=1;
                    WheelRight=-1;
                    }
 if(NowDirection==0){WheelLeft=-2;
                    WheelRight=2;
                    }}









            break;
        case 17:
            WheelLeft=1;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            //tForward=0;
                    
//printf("Be Careful!!! \n");
                    
            break;
        case 18:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(US_Right<20&&(US_Right<US_Left)){wHead=-1;
                    }
if(wHead==1)
{WheelLeft=1;
                    WheelRight=-2;
                    }else{WheelLeft=-2;
                    WheelRight=1;
                    }

if(tForward!=0){
 if(tForward<45){CornerStress++;
                    printf("%d\n",CornerStress);
                    }
 else{ModeEscape=0;
                    CornerStress=0;
                    } 
 if(CornerStress>2)
 {CornerStress=0;
                    ModeEscape=1;
                    TargetTheta=(Compass+150)%360;
                    
 Duration=1;
                    printf("Corner!!!-%d\n",(Compass+150)%360);
                    }
}tForward=0;
                    
if(ModeEscape==1){Duration=1;
                    WheelLeft=2;
                    WheelRight=-2;
                    
 if(abs(TargetTheta-Compass)<15){Duration=0;
                    ModeEscape=0;
                    }}

WTC=0;
                    printf("too Close!!-%d\n",wHead);
                    

            break;
        case 19:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    
if(US_Right<US_Left){wHead=-1;
                    }

if(wHead==1)
{Steering=US_Front/US_Left;
                     //if over 2, over 50degrees
 WheelLeft=2;
                    WheelRight=-2;
                    
 if(Steering>5){WheelLeft=1;
                    WheelRight=-1;
                    }
}
else
{Steering=US_Front/US_Right;
                     //if over 2, over 50degrees
 WheelLeft=-2;
                    WheelRight=2;
                    
 if(Steering>5){WheelLeft=-1;
                    WheelRight=1;
                    }
}

printf("wHead=%d  Steering=%d\n",wHead, Steering);
                    
 
            break;
        case 20:
            WheelLeft=3;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            if(tForward<8000)tForward++;
                    

//printf("%d-%d\n",WheelLeft,WheelRight);
                    
            break;
        case 21:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            TX=234;
                    
TY=121;
                    
wDirection=-1;
                    
WTC=1;
                    
dCollectionBox=270;
                    

GuessX=PositionX;
                    GuessY=PositionY;
                    

if(Duration==0)printf("Try To Deposit-%d\n\a",wDirection);
                    
            break;
        case 22:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            TX=18;
                    
TY=18;
                    
wDirection=1;
                    
WTC=1;
                    
dCollectionBox=90;
                    

GuessX=PositionX;
                    GuessY=PositionY;
                    
if(Duration==0)printf("Try To Deposit-%d\n\a",wDirection);
                    
            break;
        case 23:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            NeedX=TX-PositionX;
                    NeedY=TY-PositionY;
                    
if(PositionX==0&&PositionY==0){NeedX=TX-GuessX;
                    NeedY=TY-GuessY;
                    }

if(abs(NeedX)<6&&abs(NeedY)<6){WTC=4;
                    printf("Arrival!!\n");
                    }
else{
 WTC=2;
                    
 if(wDirection==1){
  if(NeedX>0){TargetTheta=270;
                    }else{TargetTheta=90;
                    }
 }else{
  if(NeedY>0){TargetTheta=0;
                    }else{TargetTheta=180;
                    }
 }
}
DX=0;
                    DY=0;
                    CountPush=0;
                    
printf("NeedX=%d NeedY=%d TargetTheta=%d %d %d\n", NeedX,NeedY,TargetTheta,GuessX,GuessY);
                    sleep(20);
                     


            break;
        case 24:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            wHead=1;
                    Duration=1;
                    
WheelLeft=1;
                     WheelRight=-1;
                    
if(TargetTheta==0){if(Compass>180){wHead=-1;
                    }}
if(TargetTheta==90){if(Compass>270||Compass<90){wHead=-1;
                    }}
if(TargetTheta==180){if(Compass<180){wHead=-1;
                    }}
if(TargetTheta==270){if(Compass>90&&Compass<270){wHead=-1;
                    }}

if(wHead==-1){WheelLeft=-1;
                    WheelRight=1;
                    }

if(abs(TargetTheta-Compass)<3){
Duration=0;
                    WheelLeft=0;
                    WheelRight=0;
                    WTC=3;
                    
printf("Turned Enough(d) TargetTheta-%d\n",TargetTheta);
                    }

            break;
        case 25:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            WheelLeft=3;
                    WheelRight=1;
                    
if(TargetTheta==0){
 if(Compass>180){WheelLeft=1;
                    WheelRight=3;
                    }
}else{
 if(Compass<TargetTheta){WheelLeft=1;
                    WheelRight=3;
                    }
}
if(abs(TargetTheta-Compass)<2){WheelLeft=3;
                    WheelRight=3;
                    }

if(PositionX==0&&PositionY==0){//On The Block
 if(wDirection==1&&DX!=0){GuessX=GuessX+(DX/abs(DX))*2;
                    }//increase 
 if(wDirection==-1&&DY!=0){GuessY=GuessY+(DY/abs(DY))*2;
                    }
 DX=TX-GuessX;
                    DY=TY-GuessY;
                    
}else{
 DX=TX-PositionX;
                    DY=TY-PositionY;
                    
 GuessX=PositionX;
                    GuessY=PositionY;
                    
}

if(wDirection==1){
 if(abs(DX)<5){
 WheelLeft=0;
                    WheelRight=0;
                    wDirection=wDirection*-1;
                    
 WTC=1;
                    printf("X End!!\n");
                    
 }else if(NeedX*DX<0){
 WheelLeft=0;
                    WheelRight=0;
                    wDirection=wDirection*-1;
                    
 WTC=1;
                    printf("X Direction Changed!!\n");
                    }
}else{
 if(abs(DY)<5){
 WheelLeft=0;
                    WheelRight=0;
                    wDirection=wDirection*-1;
                    
 WTC=1;
                    printf("Y End!!\n");
                    
 }else if(NeedY*DY<0){
 WheelLeft=0;
                    WheelRight=0;
                    wDirection=wDirection*-1;
                    
 WTC=1;
                    printf("Y Direction Changed!!\n");
                    }
}

            break;
        case 26:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            
wHead=1;
                    Duration=1;
                    
if(dCollectionBox==0){if(Compass>180){wHead=-1;
                    }}
if(dCollectionBox==110){if(Compass>270||Compass<110){wHead=-1;
                    }}
if(dCollectionBox==180){if(Compass<180){wHead=-1;
                    }}
if(dCollectionBox==270){if(Compass>90&&Compass<270){wHead=-1;
                    }}

WheelLeft=1;
                     WheelRight=-1;
                    
if(wHead==-1){WheelLeft=-1;
                    WheelRight=1;
                    }

if(abs(dCollectionBox-Compass)<3){
WheelLeft=4;
                    WheelRight=4;
                    WTC=5;
                    Duration=0;
                    
printf("Push My Car-%d\n",dCollectionBox);
                    }





            break;
        case 27:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            WheelLeft=4;
                    WheelRight=4;
                    
WTC=4;
                    

if(CountPush>3){WTC=0;
                    }
CountPush++;
                     //Reset At CalcuPath
            break;
        default:
            break;
    }

}


DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        case 0:
            Game0();
            break;
        case 1:
            Game1();
            break;
        default:
            break;
    }
}

