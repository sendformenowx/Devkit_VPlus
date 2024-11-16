#include "CObjAnimation.h"
#include <ICPlayer.h>

void CCObjAnimation::SetResource(const std::n_string &path, undefined4 a2) {
    reinterpret_cast<void(__thiscall *)(CCObjAnimation *, const std::n_string *, undefined4)>(0x00a5b4b0)(this, &path, 2);
}

void CCObjAnimation::SetLocation(const D3DVECTOR &position) {
    reinterpret_cast<void(__thiscall *)(CCObjAnimation *, const D3DVECTOR &)>(0x00a5a880)(this, position);
}

void CCObjAnimation::SetRotation(float rotation) {
    reinterpret_cast<void(__thiscall *)(CCObjAnimation *, float)>(0x00a5a8c0)(this, rotation);
}


void CCObjAnimation::SetOptimizeCloth(int clothId) 
{
    reinterpret_cast<void(__thiscall*)(CCObjAnimation*, int)>(0x00A60F90)(this, clothId);
}

void CCObjAnimation::SetClothesApply() {
    reinterpret_cast<void(__thiscall*)(CCObjAnimation*)>(0x00A61C60)(this);
}