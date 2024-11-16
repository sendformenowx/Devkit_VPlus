#pragma once
#include "IFMainFrame.h"
#include "IFNormalTile.h"

class CIFCharAnalyzer : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFCharAnalyzer)
GFX_DECLARE_MESSAGE_MAP(CIFCharAnalyzer)



public:
    void UpdateMenuSize();
    bool OnCreate(long ln) override;
    void OnUpdate() override;

private:
    void On_BtnClick();

public:
    CIFFrame* frame;
    CIFNormalTile* tile;
    CIFStatic* rankbox;
    CIFStatic* istatikler;
    CIFStatic* Icon1;
    CIFStatic* taksim;
    CIFStatic* survkill;
    CIFStatic* ctfkill;
    CIFStatic* battlekill;
    CIFStatic* jobkill;
    CIFStatic* globalrank;
    CIFStatic* honor;
    CIFStatic* survkillslot;
    CIFStatic* ctfkillslot;
    CIFStatic* battlekillslot;
    CIFStatic* jobkillslot;
    CIFStatic* globalrankslot;
    CIFStatic* honorslot;

};
