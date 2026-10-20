package com.nvidia.forge;

/* So para compilar: a classe de verdade (natives do jogo) esta no classes.dex. */
public class DeviceInfo {
    public native void addDevice(int id, int slot, boolean vibra, boolean dpad, boolean comFio, boolean carregando,
                                 int vendor, int produto, int nBotoes, int nEixos, boolean avisa);
    public native void removeDevice(int slot);
    public native void updateDeviceFlags(int slot, boolean a, boolean b, boolean c);
}
