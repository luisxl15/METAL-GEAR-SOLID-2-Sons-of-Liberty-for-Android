package com.nvidia.forge;

/* So para compilar: a classe de verdade (com o setState nativo) esta no classes.dex do jogo. */
public class DeviceState {
    public int mButtons;
    public float mLTrigger, mRTrigger, mThumbLX, mThumbLY, mThumbRX, mThumbRY;
    public void refresh(int slot) { }
    public native void setState(int slot, int botoes, float lt, float rt, float lx, float ly, float rx, float ry);
}
