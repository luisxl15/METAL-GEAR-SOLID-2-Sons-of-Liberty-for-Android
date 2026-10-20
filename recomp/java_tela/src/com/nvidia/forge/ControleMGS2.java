package com.nvidia.forge;

import android.util.Log;
import android.view.InputDevice;

/**
 * O controle virtual, do lado do jogo.
 *
 * A Forge guarda o estado de cada controle num DeviceState (bits do XInput,
 * gatilhos 0..1, analogicos -1..1 com Y para baixo, como os eixos do Android) e o
 * entrega ao jogo com o metodo nativo setState(slot, ...). O controle na tela usa
 * o MESMO caminho no slot 0: para o jogo e so um controle de Xbox.
 *
 * Os bits sao os mesmos do controle do MGR/RE5 (Controle.kt).
 */
public final class ControleMGS2 {
    public static final int CIMA = 0x0001, BAIXO = 0x0002, ESQUERDA = 0x0004, DIREITA = 0x0008;
    public static final int START = 0x0010, BACK = 0x0020, ANALOG_E = 0x0040, ANALOG_D = 0x0080;
    public static final int LB = 0x0100, RB = 0x0200, A = 0x1000, B = 0x2000, X = 0x4000, Y = 0x8000;

    private static final DeviceState estado = new DeviceState();
    private static boolean falhou;

    private ControleMGS2() { }

    private static boolean conectado;

    /**
     * O jogo so le um slot que esteja CONECTADO (bit 1 em +0x04 da tabela de
     * controles do lado nativo). A Forge conecta com DeviceInfo.addDevice quando
     * um controle de verdade aparece; o virtual precisa se apresentar do mesmo
     * jeito: um controle de Xbox 360 com fio no slot 0.
     */
    public static synchronized void conecta() {
        if (conectado) return;
        try {
            new DeviceInfo().addDevice(0x7f00ce11, 0, false, true, true, false,
                    0x045e, 0x028e, 15, 6, true);
            conectado = true;
            Log.i("MGS2-Controle", "controle virtual conectado no slot 0");
        } catch (Throwable t) {
            Log.w("MGS2-Controle", "addDevice indisponivel: " + t);
        }
    }

    /** Um controle de verdade tomou o slot: o proximo aparecimento reconecta. */
    public static synchronized void esquece() { conectado = false; }

    private static synchronized void envia() {
        if (falhou) return;
        if (!conectado) conecta();
        try {
            estado.refresh(0);      /* -> DeviceState.setState(0, ...) nativo do jogo */
        } catch (Throwable t) {     /* biblioteca do jogo ainda nao carregada */
            Log.w("MGS2-Controle", "setState indisponivel: " + t);
        }
    }

    public static synchronized void botao(int bit, boolean apertado) {
        int b = apertado ? (estado.mButtons | bit) : (estado.mButtons & ~bit);
        if (b == estado.mButtons) return;
        estado.mButtons = b;
        envia();
    }

    public static synchronized void gatilho(boolean esquerdo, float valor) {
        if (esquerdo) estado.mLTrigger = valor; else estado.mRTrigger = valor;
        envia();
    }

    public static synchronized void analogico(boolean esquerdo, float x, float y) {
        if (esquerdo) { estado.mThumbLX = x; estado.mThumbLY = y; }
        else { estado.mThumbRX = x; estado.mThumbRY = y; }
        envia();
    }

    /** Solta tudo (ao sair do jogo ou esconder os controles). */
    public static synchronized void solta() {
        estado.mButtons = 0;
        estado.mLTrigger = estado.mRTrigger = 0;
        estado.mThumbLX = estado.mThumbLY = estado.mThumbRX = estado.mThumbRY = 0;
        envia();
    }

    /** Ha um controle de verdade ligado? Com ele, os botoes da tela somem.
     *  Conta quem tem analogico (eixos X/Y de joystick) ou e externo (Bluetooth/USB). O sensor de
     *  digital do Redmi 13C ("uinput-goodix") se anuncia GAMEPAD, interno e sem eixo nenhum: antes
     *  ele escondia os botoes da tela num celular sem controle. */
    public static boolean temControleFisico() {
        for (int id : InputDevice.getDeviceIds()) {
            InputDevice d = InputDevice.getDevice(id);
            if (d == null || d.isVirtual()) continue;
            int s = d.getSources();
            boolean joystick = (s & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK
                    && d.getMotionRange(android.view.MotionEvent.AXIS_X, InputDevice.SOURCE_JOYSTICK) != null
                    && d.getMotionRange(android.view.MotionEvent.AXIS_Y, InputDevice.SOURCE_JOYSTICK) != null;
            boolean gamepad = (s & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD;
            boolean externo = android.os.Build.VERSION.SDK_INT < 29 || d.isExternal();
            if (joystick || (gamepad && externo)) return true;
        }
        return false;
    }
}
