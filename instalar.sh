#!/bin/bash
# Poe o MGS2 recompilado (ARM64) no celular: APK + as duas OBBs do SHIELD.
# NAO abre o aplicativo.   bash instalar.sh [apk] [--dados]   (padrao: o sabor adreno)
# Os arquivos de dentro das OBBs o PROPRIO APP extrai na 1a vez (ExtratorObb.java);
# --dados empurra os ja extraidos no PC (dados_jogo/, extrair_obb.py), mais rapido no cabo.
# CUIDADO: o adb grava como uid 2000 (shell), modo rws---. Em alguns aparelhos (ex.: Xiaomi) o app NAO
# entra nessas pastas e o jogo fecha no 1o arquivo. Prefira deixar o app extrair.
set -u
cd "$(dirname "$0")"
export MSYS_NO_PATHCONV=1
PKG=jp.konami.mgs2hd.shield
DADOS_PC=0; ARGS=()
for x in "$@"; do if [ "$x" = --dados ]; then DADOS_PC=1; else ARGS+=("$x"); fi; done
APK=${ARGS[0]:-recomp/build/MGS2-ARM64.apk}   # bash instalar.sh [caminho do apk] [--dados]
OBB_PC=${MGS2_JOGO:-jogo}     # pasta com main.14.<pacote>.obb e patch.14.<pacote>.obb (ver README)
OBB_CEL=/sdcard/Android/obb/$PKG

echo "== aparelho"
adb devices | tail -n +2 | grep -q device || { echo "   nenhum aparelho conectado"; exit 1; }
echo "   abis: $(adb shell getprop ro.product.cpu.abilist | tr -d '\r')"

echo "== APK ($(du -h "$APK" | cut -f1))"
adb install -r "$APK" 2>&1 | tail -1

echo "== OBBs"
adb shell mkdir -p $OBB_CEL
for f in main.14.$PKG.obb patch.14.$PKG.obb; do
    t_pc=$(stat -c %s "$OBB_PC/$f")
    t_cel=$(adb shell "stat -c %s $OBB_CEL/$f 2>/dev/null" | tr -d '\r')
    if [ "$t_pc" = "$t_cel" ]; then echo "   $f ja esta la"; else adb push "$OBB_PC/$f" $OBB_CEL/ 2>&1 | tail -1; fi
done

echo "== dados soltos em files/ (o motor le dali)"
DADOS_CEL=/sdcard/Android/data/$PKG/files
if [ -n "$(adb shell "ls $DADOS_CEL/.extraido 2>/dev/null" | tr -d '\r')" ]; then
    echo "   ja estao la"
elif [ "$DADOS_PC" != 1 ]; then
    echo "   o APP extrai as OBBs na primeira vez que tocar Jogar (ExtratorObb.java)"
    echo "   (para empurrar do PC em vez disso: bash instalar.sh [apk] --dados)"
else
    [ -f dados_jogo/.extraido ] || python -u extrair_obb.py || exit 1
    adb shell mkdir -p $DADOS_CEL
    adb push dados_jogo/. $DADOS_CEL/ 2>&1 | tail -1
fi

echo "== permissoes"
adb shell pm grant $PKG android.permission.READ_EXTERNAL_STORAGE 2>&1
adb shell pm grant $PKG android.permission.WRITE_EXTERNAL_STORAGE 2>&1
echo
echo "pronto. Para ver o log quando abrir:  adb logcat -s MGS2-RT MGS2-stdout MGS2-NVSI DEBUG"
