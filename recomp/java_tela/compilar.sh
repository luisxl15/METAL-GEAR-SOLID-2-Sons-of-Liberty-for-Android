#!/bin/bash
# Compila a casca Java (java_tela/src) em classes2.dex.
#   bash recomp/java_tela/compilar.sh      -> recomp/java_tela/classes2.dex
# Usa o SDK do Android de ANDROID_HOME (ou %LOCALAPPDATA%/Android/Sdk) e o javac do PATH.
set -eu
cd "$(dirname "$0")"
SDK=${ANDROID_HOME:-${ANDROID_SDK_ROOT:-${LOCALAPPDATA:-$HOME}/Android/Sdk}}
SDK=${SDK//\\//}
JAR=$(ls -d "$SDK"/platforms/android-*/android.jar | sort -V | tail -1)
BT=$(ls -d "$SDK"/build-tools/* | sort -V | tail -1)
[ -f "$JAR" ] || { echo "android.jar nao encontrado em $SDK/platforms"; exit 1; }
# no Windows (Git Bash) o classpath usa ';' e o d8 e um .bat
if command -v cygpath >/dev/null 2>&1; then
    W() { cygpath -w "$1"; }; SEP=';'; D8() { cmd //c "$(W "$BT/d8.bat")" "$@"; }
else
    W() { echo "$1"; }; SEP=':'; D8() { "$BT/d8" "$@"; }
fi
rm -rf obj stubobj dex && mkdir -p obj stubobj dex
# os stubs (classes que ja existem no classes.dex do jogo) so servem para compilar
javac -encoding UTF-8 --release 8 -cp "$(W "$JAR")" -d stubobj $(find stub -name '*.java') 2>&1 | grep -v "warning: \[options\]" || true
javac -encoding UTF-8 --release 8 -cp "$(W "$JAR")${SEP}stubobj" -d obj $(find src -name '*.java') 2>&1 | grep -v "warning: \[options\]" || true
D8 --release --min-api 26 --lib "$(W "$JAR")" --classpath stubobj --output dex $(find obj -name '*.class')
mv dex/classes.dex classes2.dex
rm -rf obj stubobj dex
ls -la classes2.dex
