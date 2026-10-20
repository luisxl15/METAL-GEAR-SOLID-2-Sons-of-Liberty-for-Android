package com.nvidia.forge;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

/**
 * Textos das telas do app (menu, ajustes, editor de controles, preparo dos dados, medidor de
 * FPS) no idioma do sistema. A chave e o texto em portugues do Brasil; cada linha da tabela e
 * { pt, en, es, fr, it, de, ja }. Idioma sem coluna (ou celula vazia) cai no ingles.
 *
 *   Textos.t("Jogar")                       -> "Play" num aparelho em ingles
 *   Textos.f("Falhou: %s", erro)            -> String.format no idioma do aparelho
 */
final class Textos {
    private static final String[] IDIOMAS = { "pt", "en", "es", "fr", "it", "de", "ja" };

    private static final String[][] T = {
        // ---- menu inicial
        { "Jogar", "Play", "Jugar", "Jouer", "Gioca", "Spielen", "プレイ" },
        { "Ajustes", "Settings", "Ajustes", "Paramètres", "Impostazioni", "Einstellungen", "設定" },
        { "Controles na tela", "On-screen controls", "Controles en pantalla", "Commandes tactiles", "Comandi su schermo", "Bildschirmsteuerung", "画面コントローラー" },
        // ---- preparo dos dados (1a vez)
        { "PREPARANDO OS DADOS DO JOGO", "PREPARING GAME DATA", "PREPARANDO LOS DATOS DEL JUEGO", "PRÉPARATION DES DONNÉES DU JEU",
          "PREPARAZIONE DEI DATI DI GIOCO", "SPIELDATEN WERDEN VORBEREITET", "ゲームデータを準備中" },
        { "Só na primeira vez: tirando os arquivos de dentro das OBBs (cerca de 7 GB). Deixe o app aberto.",
          "First launch only: extracting the files from the OBBs (about 7 GB). Keep the app open.",
          "Solo la primera vez: extrayendo los archivos de los OBB (unos 7 GB). Deja la app abierta.",
          "Uniquement au premier lancement : extraction des fichiers des OBB (environ 7 Go). Laissez l'application ouverte.",
          "Solo al primo avvio: estrazione dei file dagli OBB (circa 7 GB). Lascia l'app aperta.",
          "Nur beim ersten Start: Dateien werden aus den OBBs entpackt (ca. 7 GB). App geöffnet lassen.",
          "初回のみ：OBB からファイルを展開しています（約 7 GB）。アプリを開いたままにしてください。" },
        { "lendo as OBBs...", "reading the OBBs...", "leyendo los OBB...", "lecture des OBB...", "lettura degli OBB...", "OBBs werden gelesen...", "OBB を読み込み中..." },
        { "%.1f / %.1f GB  ·  %d / %d arquivos%s", "%.1f / %.1f GB  ·  %d / %d files%s", "%.1f / %.1f GB  ·  %d / %d archivos%s",
          "%.1f / %.1f Go  ·  %d / %d fichiers%s", "%.1f / %.1f GB  ·  %d / %d file%s", "%.1f / %.1f GB  ·  %d / %d Dateien%s", "%.1f / %.1f GB  ·  %d / %d ファイル%s" },
        { "  ·  falta ~%d s", "  ·  ~%d s left", "  ·  faltan ~%d s", "  ·  encore ~%d s", "  ·  mancano ~%d s", "  ·  noch ~%d s", "  ·  残り約 %d 秒" },
        { "NÃO FOI POSSÍVEL PREPARAR", "COULD NOT PREPARE THE DATA", "NO SE PUDO PREPARAR", "PRÉPARATION IMPOSSIBLE", "IMPOSSIBILE PREPARARE", "VORBEREITUNG FEHLGESCHLAGEN", "準備できませんでした" },
        { "Tentar de novo", "Try again", "Reintentar", "Réessayer", "Riprova", "Erneut versuchen", "再試行" },
        { "Voltar", "Back", "Volver", "Retour", "Indietro", "Zurück", "戻る" },
        { "Salvar", "Save", "Guardar", "Enregistrer", "Salva", "Speichern", "保存" },
        // ---- erros do extrator
        { "Armazenamento do app indisponível.", "App storage unavailable.", "Almacenamiento de la app no disponible.", "Stockage de l'application indisponible.",
          "Memoria dell'app non disponibile.", "App-Speicher nicht verfügbar.", "アプリのストレージを利用できません。" },
        { "Faltam as OBBs do jogo. Copie main.14 e patch.14 para Android/obb/jp.konami.mgs2hd.shield/ e abra de novo.",
          "The game OBBs are missing. Copy main.14 and patch.14 to Android/obb/jp.konami.mgs2hd.shield/ and open the app again.",
          "Faltan los OBB del juego. Copia main.14 y patch.14 en Android/obb/jp.konami.mgs2hd.shield/ y vuelve a abrir.",
          "Les OBB du jeu sont absents. Copiez main.14 et patch.14 dans Android/obb/jp.konami.mgs2hd.shield/ puis relancez.",
          "Mancano gli OBB del gioco. Copia main.14 e patch.14 in Android/obb/jp.konami.mgs2hd.shield/ e riapri l'app.",
          "Die OBBs des Spiels fehlen. Kopiere main.14 und patch.14 nach Android/obb/jp.konami.mgs2hd.shield/ und starte neu.",
          "ゲームの OBB がありません。main.14 と patch.14 を Android/obb/jp.konami.mgs2hd.shield/ にコピーして再度開いてください。" },
        { "OBB ilegível: %s", "Unreadable OBB: %s", "OBB ilegible: %s", "OBB illisible : %s", "OBB illeggibile: %s", "OBB nicht lesbar: %s", "OBB を読み込めません: %s" },
        { "Espaço insuficiente: precisa de %.1f GB livres, há %.1f GB.", "Not enough space: %.1f GB free needed, %.1f GB available.",
          "Espacio insuficiente: se necesitan %.1f GB libres, hay %.1f GB.", "Espace insuffisant : %.1f Go libres requis, %.1f Go disponibles.",
          "Spazio insufficiente: servono %.1f GB liberi, disponibili %.1f GB.", "Zu wenig Speicher: %.1f GB frei nötig, %.1f GB verfügbar.",
          "空き容量が不足しています：%.1f GB 必要ですが、空きは %.1f GB です。" },
        { "Falha ao extrair: %s", "Extraction failed: %s", "Error al extraer: %s", "Échec de l'extraction : %s", "Estrazione non riuscita: %s", "Entpacken fehlgeschlagen: %s", "展開に失敗しました: %s" },
        { "Não gravou o marcador: %s", "Could not write the marker file: %s", "No se pudo escribir el marcador: %s", "Impossible d'écrire le marqueur : %s",
          "Impossibile scrivere il marcatore: %s", "Markierungsdatei nicht schreibbar: %s", "マーカーを書き込めません: %s" },
        // ---- editor de controles
        { "Toque num botão para escolher. Arraste para mover, pinça para mudar o tamanho.",
          "Tap a button to select it. Drag to move, pinch to resize.",
          "Toca un botón para elegirlo. Arrastra para moverlo, pellizca para cambiar el tamaño.",
          "Touchez un bouton pour le choisir. Glissez pour le déplacer, pincez pour le redimensionner.",
          "Tocca un pulsante per sceglierlo. Trascina per spostarlo, pizzica per ridimensionarlo.",
          "Tippe auf eine Taste, um sie zu wählen. Ziehen zum Verschieben, Zwei-Finger-Geste für die Größe.",
          "ボタンをタップして選択。ドラッグで移動、ピンチでサイズ変更。" },
        { "Tamanho geral  ", "Overall size  ", "Tamaño general  ", "Taille globale  ", "Dimensione generale  ", "Gesamtgröße  ", "全体サイズ  " },
        { "   Opacidade  ", "   Opacity  ", "   Opacidad  ", "   Opacité  ", "   Opacità  ", "   Deckkraft  ", "   不透明度  " },
        { "Restaurar padrão", "Restore defaults", "Restaurar valores", "Par défaut", "Ripristina", "Standard", "初期設定に戻す" },
        { "Nenhum selecionado. Toque num botão.", "Nothing selected. Tap a button.", "Nada seleccionado. Toca un botón.", "Aucune sélection. Touchez un bouton.",
          "Nessuna selezione. Tocca un pulsante.", "Nichts ausgewählt. Tippe auf eine Taste.", "未選択です。ボタンをタップしてください。" },
        { " — arraste para mover, pinça para o tamanho", " — drag to move, pinch to resize", " — arrastra para mover, pellizca para el tamaño",
          " — glissez pour déplacer, pincez pour la taille", " — trascina per spostare, pizzica per la dimensione", " — ziehen zum Verschieben, Geste für die Größe",
          " — ドラッグで移動、ピンチでサイズ" },
        { "Direcional", "D-pad", "Cruceta", "Croix directionnelle", "Croce direzionale", "Steuerkreuz", "十字キー" },
        { "Analógico esquerdo", "Left stick", "Stick izquierdo", "Stick gauche", "Levetta sinistra", "Linker Stick", "左スティック" },
        { "Analógico direito", "Right stick", "Stick derecho", "Stick droit", "Levetta destra", "Rechter Stick", "右スティック" },
        { "Botão %s", "%s button", "Botón %s", "Bouton %s", "Pulsante %s", "Taste %s", "%s ボタン" },
        // ---- medidor de FPS
        { "JOGO", "GAME", "JUEGO", "JEU", "GIOCO", "SPIEL", "ゲーム" },
        { "TELA", "SCREEN", "PANTALLA", "ÉCRAN", "SCHERMO", "BILD", "画面" },
        // ---- ajustes
        { "AJUSTES", "SETTINGS", "AJUSTES", "PARAMÈTRES", "IMPOSTAZIONI", "EINSTELLUNGEN", "設定" },
        { "VÍDEO", "VIDEO", "VÍDEO", "VIDÉO", "VIDEO", "VIDEO", "ビデオ" },
        { "Limite de quadros", "Frame limit", "Límite de fotogramas", "Limite d'images", "Limite fotogrammi", "Bildratenlimit", "フレームレート上限" },
        { "O MGS2 foi feito para 60. Sem limite segue a tela (até 120 Hz) e pode acelerar o jogo.",
          "MGS2 was made for 60. Unlimited follows the display (up to 120 Hz) and can speed the game up.",
          "MGS2 se hizo para 60. Sin límite sigue la pantalla (hasta 120 Hz) y puede acelerar el juego.",
          "MGS2 a été conçu pour 60. Sans limite suit l'écran (jusqu'à 120 Hz) et peut accélérer le jeu.",
          "MGS2 è stato fatto per 60. Senza limite segue lo schermo (fino a 120 Hz) e può accelerare il gioco.",
          "MGS2 ist für 60 gemacht. Unbegrenzt folgt dem Display (bis 120 Hz) und kann das Spiel beschleunigen.",
          "MGS2 は 60 用に作られています。無制限は画面（最大 120 Hz）に合わせ、ゲームが速くなることがあります。" },
        { "Sem limite", "Unlimited", "Sin límite", "Illimité", "Illimitato", "Unbegrenzt", "無制限" },
        { "Imagem", "Image", "Imagen", "Image", "Immagine", "Bild", "画面表示" },
        { "16:9 mantém a proporção do jogo. Esticar ocupa a tela toda, deformando um pouco.",
          "16:9 keeps the game's aspect ratio. Stretch fills the whole screen, distorting it slightly.",
          "16:9 mantiene la proporción del juego. Estirar ocupa toda la pantalla, deformando un poco.",
          "16:9 conserve les proportions du jeu. Étirer remplit l'écran, avec une légère déformation.",
          "16:9 mantiene le proporzioni del gioco. Allarga riempie lo schermo, deformando un po'.",
          "16:9 behält das Seitenverhältnis bei. Strecken füllt den Bildschirm, leicht verzerrt.",
          "16:9 はゲームの比率を保ちます。引き伸ばしは画面全体に表示し、少し歪みます。" },
        { "Esticar", "Stretch", "Estirar", "Étirer", "Allarga", "Strecken", "引き伸ばし" },
        { "Medidor de FPS", "FPS counter", "Contador de FPS", "Compteur de FPS", "Contatore FPS", "FPS-Anzeige", "FPS 表示" },
        { "No canto da tela: quadros do jogo e, com a geração ligada, quadros na tela (reais + gerados).",
          "In the corner of the screen: game frames and, with frame generation on, frames on screen (real + generated).",
          "En la esquina de la pantalla: fotogramas del juego y, con la generación activa, fotogramas en pantalla (reales + generados).",
          "Dans le coin de l'écran : images du jeu et, avec la génération activée, images affichées (réelles + générées).",
          "Nell'angolo dello schermo: fotogrammi del gioco e, con la generazione attiva, fotogrammi a schermo (reali + generati).",
          "In der Bildschirmecke: Spielbilder und, mit Bildgenerierung, Bilder auf dem Display (echte + generierte).",
          "画面の隅に表示：ゲームのフレーム数と、フレーム生成オン時は画面のフレーム数（実フレーム＋生成）。" },
        { "GERAÇÃO DE QUADROS (LSFG)", "FRAME GENERATION (LSFG)", "GENERACIÓN DE FOTOGRAMAS (LSFG)", "GÉNÉRATION D'IMAGES (LSFG)",
          "GENERAZIONE FOTOGRAMMI (LSFG)", "BILDGENERIERUNG (LSFG)", "フレーム生成（LSFG）" },
        { "Geração de quadros", "Frame generation", "Generación de fotogramas", "Génération d'images", "Generazione fotogrammi", "Bildgenerierung", "フレーム生成" },
        { "Cria um quadro intermediário entre cada quadro do jogo: 60 viram 120 sem acelerar o jogo. Usa os shaders do Lossless Scaling (Steam) e acrescenta cerca de 1 quadro de atraso no controle.",
          "Creates an in-between frame for every game frame: 60 becomes 120 without speeding the game up. Uses the Lossless Scaling shaders (Steam) and adds about 1 frame of input lag.",
          "Crea un fotograma intermedio entre cada fotograma del juego: 60 pasan a 120 sin acelerar el juego. Usa los shaders de Lossless Scaling (Steam) y añade cerca de 1 fotograma de retraso en el control.",
          "Crée une image intermédiaire entre chaque image du jeu : 60 deviennent 120 sans accélérer le jeu. Utilise les shaders de Lossless Scaling (Steam) et ajoute environ 1 image de latence.",
          "Crea un fotogramma intermedio tra ogni fotogramma del gioco: 60 diventano 120 senza accelerare il gioco. Usa gli shader di Lossless Scaling (Steam) e aggiunge circa 1 fotogramma di ritardo.",
          "Erzeugt ein Zwischenbild zwischen den Spielbildern: aus 60 werden 120, ohne das Spiel zu beschleunigen. Nutzt die Shader von Lossless Scaling (Steam), ca. 1 Bild mehr Eingabeverzögerung.",
          "ゲームのフレーム間に中間フレームを作り、ゲームを速めずに 60 を 120 にします。Lossless Scaling（Steam）のシェーダーを使い、操作に約 1 フレームの遅延が加わります。" },
        { "Desligada", "Off", "Desactivada", "Désactivée", "Disattivata", "Aus", "オフ" },
        { "Precisão do movimento", "Motion accuracy", "Precisión del movimiento", "Précision du mouvement", "Precisione del movimento", "Bewegungsgenauigkeit", "動きの精度" },
        { "Menor deixa a GPU mais livre, com mais erro nas bordas de objetos rápidos.",
          "Lower frees up the GPU, with more errors around fast-moving objects.",
          "Menor libera la GPU, con más errores en los bordes de objetos rápidos.",
          "Plus bas soulage le GPU, avec plus d'erreurs autour des objets rapides.",
          "Più basso alleggerisce la GPU, con più errori ai bordi degli oggetti veloci.",
          "Niedriger entlastet die GPU, mit mehr Fehlern an schnellen Objekten.",
          "低いほど GPU の負荷が下がり、速い物体の縁に誤差が増えます。" },
        { "Importar", "Import", "Importar", "Importer", "Importa", "Importieren", "読み込む" },
        { "Instalado. Os shaders são lidos do seu arquivo, nunca executados.",
          "Installed. The shaders are read from your file, never executed.",
          "Instalado. Los shaders se leen de tu archivo, nunca se ejecutan.",
          "Installé. Les shaders sont lus depuis votre fichier, jamais exécutés.",
          "Installato. Gli shader vengono letti dal tuo file, mai eseguiti.",
          "Installiert. Die Shader werden aus deiner Datei gelesen, nie ausgeführt.",
          "インストール済み。シェーダーはファイルから読み取るだけで、実行はされません。" },
        { "Não instalado. Copie o Lossless.dll da pasta do Lossless Scaling no PC (Steam > Lossless Scaling > Gerenciar > Ver arquivos locais) para o celular e importe aqui.",
          "Not installed. Copy Lossless.dll from the Lossless Scaling folder on your PC (Steam > Lossless Scaling > Manage > Browse local files) to the phone and import it here.",
          "No instalado. Copia Lossless.dll de la carpeta de Lossless Scaling en el PC (Steam > Lossless Scaling > Administrar > Ver archivos locales) al móvil e impórtalo aquí.",
          "Non installé. Copiez Lossless.dll depuis le dossier de Lossless Scaling sur le PC (Steam > Lossless Scaling > Gérer > Parcourir les fichiers locaux) vers le téléphone et importez-le ici.",
          "Non installato. Copia Lossless.dll dalla cartella di Lossless Scaling sul PC (Steam > Lossless Scaling > Gestisci > Sfoglia i file locali) sul telefono e importalo qui.",
          "Nicht installiert. Kopiere Lossless.dll aus dem Lossless-Scaling-Ordner am PC (Steam > Lossless Scaling > Verwalten > Lokale Dateien durchsuchen) aufs Handy und importiere sie hier.",
          "未インストール。PC の Lossless Scaling フォルダー（Steam > Lossless Scaling > 管理 > ローカルファイルを閲覧）から Lossless.dll をスマホにコピーし、ここで読み込んでください。" },
        { "Sem seletor de arquivos: %s", "No file picker: %s", "Sin selector de archivos: %s", "Aucun sélecteur de fichiers : %s", "Nessun selettore di file: %s", "Keine Dateiauswahl: %s", "ファイル選択がありません: %s" },
        { "arquivo inacessível", "file not accessible", "archivo inaccesible", "fichier inaccessible", "file non accessibile", "Datei nicht zugänglich", "ファイルにアクセスできません" },
        { "Lossless.dll importado (%d KB).", "Lossless.dll imported (%d KB).", "Lossless.dll importado (%d KB).", "Lossless.dll importé (%d Ko).",
          "Lossless.dll importato (%d KB).", "Lossless.dll importiert (%d KB).", "Lossless.dll を読み込みました（%d KB）。" },
        { "Falhou: %s", "Failed: %s", "Falló: %s", "Échec : %s", "Non riuscito: %s", "Fehlgeschlagen: %s", "失敗しました: %s" },
        { "CONTROLES NA TELA", "ON-SCREEN CONTROLS", "CONTROLES EN PANTALLA", "COMMANDES TACTILES", "COMANDI SU SCHERMO", "BILDSCHIRMSTEUERUNG", "画面コントローラー" },
        { "Mostrar", "Show", "Mostrar", "Afficher", "Mostra", "Anzeigen", "表示" },
        { "Automático esconde os botões quando um controle Bluetooth ou USB está ligado.",
          "Automatic hides the buttons when a Bluetooth or USB controller is connected.",
          "Automático oculta los botones cuando hay un mando Bluetooth o USB conectado.",
          "Automatique masque les boutons quand une manette Bluetooth ou USB est connectée.",
          "Automatico nasconde i pulsanti quando è collegato un controller Bluetooth o USB.",
          "Automatisch blendet die Tasten aus, wenn ein Bluetooth- oder USB-Controller verbunden ist.",
          "自動：Bluetooth または USB コントローラー接続中はボタンを隠します。" },
        { "Automático", "Automatic", "Automático", "Automatique", "Automatico", "Automatisch", "自動" },
        { "Sempre", "Always", "Siempre", "Toujours", "Sempre", "Immer", "常に" },
        { "Nunca", "Never", "Nunca", "Jamais", "Mai", "Nie", "表示しない" },
        { "Opacidade dos botões", "Button opacity", "Opacidad de los botones", "Opacité des boutons", "Opacità dei pulsanti", "Tastendeckkraft", "ボタンの不透明度" },
        { "Mais baixo deixa os botões discretos por cima do jogo.", "Lower makes the buttons more discreet over the game.",
          "Más bajo hace los botones más discretos sobre el juego.", "Plus bas rend les boutons plus discrets sur le jeu.",
          "Più basso rende i pulsanti più discreti sopra il gioco.", "Niedriger macht die Tasten unauffälliger.",
          "低いほどボタンが目立たなくなります。" },
        { "Vibrar ao tocar", "Vibrate on touch", "Vibrar al tocar", "Vibrer au toucher", "Vibra al tocco", "Vibration bei Berührung", "タッチで振動" },
        { "Um toque curto de vibração em cada botão.", "A short vibration on every button press.", "Una vibración corta en cada botón.",
          "Une courte vibration à chaque bouton.", "Una breve vibrazione a ogni pulsante.", "Kurze Vibration bei jeder Taste.", "ボタンを押すたびに短く振動します。" },
        { "A posição e o tamanho de cada botão se ajustam em \"Controles na tela\", na tela inicial.",
          "Each button's position and size are adjusted in \"On-screen controls\" on the start screen.",
          "La posición y el tamaño de cada botón se ajustan en \"Controles en pantalla\", en la pantalla inicial.",
          "La position et la taille de chaque bouton se règlent dans « Commandes tactiles », sur l'écran d'accueil.",
          "Posizione e dimensione di ogni pulsante si regolano in \"Comandi su schermo\", nella schermata iniziale.",
          "Position und Größe jeder Taste stellst du unter „Bildschirmsteuerung“ auf dem Startbildschirm ein.",
          "各ボタンの位置とサイズは、スタート画面の「画面コントローラー」で調整できます。" },
    };

    private static Map<String, String> tabela;

    private Textos() { }

    private static synchronized Map<String, String> tabela() {
        if (tabela != null) return tabela;
        String lingua = Locale.getDefault().getLanguage();
        int col = 1;                                          // padrao: ingles
        for (int i = 0; i < IDIOMAS.length; i++) if (IDIOMAS[i].equals(lingua)) col = i;
        Map<String, String> m = new HashMap<>();
        for (String[] l : T) {
            String v = col < l.length && l[col] != null && !l[col].isEmpty() ? l[col] : l[1];
            m.put(l[0], v);
        }
        tabela = m;
        return m;
    }

    /** texto no idioma do aparelho; a chave e o texto em portugues */
    static String t(String pt) {
        String v = tabela().get(pt);
        return v != null ? v : pt;
    }

    /** t() + String.format */
    static String f(String pt, Object... args) {
        return String.format(Locale.getDefault(), t(pt), args);
    }
}
