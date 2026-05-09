#include <catch2/catch_test_macros.hpp>
#include "MainAppHelpActions.hpp"
#include "MainApp.hpp"
#include "MainAppTestAccess.hpp"
#include "TestHelpers.hpp"
#include "TranslationManager.hpp"
#include "Language.hpp"

#include <QCoreApplication>

#include <vector>

#ifndef _WIN32
TEST_CASE("MainApp retranslate reflects language changes") {
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", "offscreen");
    QtAppContext qt_context;

    Settings settings;
    settings.load();

    MainApp window(settings, /*development_mode=*/false);
    struct ExpectedTranslation {
        Language language;
        QString analyze_label;
        QString folder_label;
    };

    const std::vector<ExpectedTranslation> expected = {
        {Language::English, QStringLiteral("Analyze folder"), QStringLiteral("Folder:")},
        {Language::French, QStringLiteral("Analyser le dossier"), QStringLiteral("Dossier :")},
        {Language::German, QStringLiteral("Ordner analysieren"), QStringLiteral("Ordner:")},
        {Language::Hindi, QStringLiteral("फ़ोल्डर का विश्लेषण करें"), QStringLiteral("फ़ोल्डर:")},
        {Language::Italian, QStringLiteral("Analizza cartella"), QStringLiteral("Cartella:")},
        {Language::Spanish, QStringLiteral("Analizar carpeta"), QStringLiteral("Carpeta:")},
        {Language::Dutch, QStringLiteral("Map analyseren"), QStringLiteral("Map:")},
        {Language::Turkish, QStringLiteral("Klasörü analiz et"), QStringLiteral("Klasör:")},
        {Language::Korean, QStringLiteral("폴더 분석"), QStringLiteral("폴더:")}
    };

    for (const auto& entry : expected) {
        settings.set_language(entry.language);
        TranslationManager::instance().set_language(entry.language);
        MainAppTestAccess::trigger_retranslate(window);

        const auto analyze_text = MainAppTestAccess::analyze_button_text(window);
        const auto folder_text = MainAppTestAccess::path_label_text(window);
        CAPTURE(static_cast<int>(entry.language), analyze_text, folder_text);

        REQUIRE(analyze_text == entry.analyze_label);
        REQUIRE(folder_text == entry.folder_label);
    }
}

TEST_CASE("Top-level menu titles are translated for all supported UI languages")
{
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", "offscreen");
    QtAppContext qt_context;

    struct ExpectedTranslation {
        Language language;
        QString file_menu;
        QString edit_menu;
        QString view_menu;
        QString settings_menu;
        QString plugins_menu;
        QString development_menu;
        QString tests_menu;
        QString interface_language_menu;
        QString category_language_menu;
    };

    const std::vector<ExpectedTranslation> expected = {
        {Language::English,
         QStringLiteral("&File"),
         QStringLiteral("&Edit"),
         QStringLiteral("&View"),
         QStringLiteral("&Settings"),
         QStringLiteral("&Plugins"),
         QStringLiteral("&Development"),
         QStringLiteral("&Tests"),
         QStringLiteral("Interface &language"),
         QStringLiteral("Category &language")},
        {Language::French,
         QStringLiteral("&Fichier"),
         QStringLiteral("&Édition"),
         QStringLiteral("&Affichage"),
         QStringLiteral("&Paramètres"),
         QStringLiteral("&Plugins"),
         QStringLiteral("&Développement"),
         QStringLiteral("&Tests"),
         QStringLiteral("Langue de l'&interface"),
         QStringLiteral("Langue des &catégories")},
        {Language::German,
         QStringLiteral("&Datei"),
         QStringLiteral("&Bearbeiten"),
         QStringLiteral("&Ansicht"),
         QStringLiteral("&Einstellungen"),
         QStringLiteral("&Plugins"),
         QStringLiteral("&Entwicklung"),
         QStringLiteral("&Tests"),
         QStringLiteral("&Sprache der Benutzeroberfläche"),
         QStringLiteral("&Kategoriesprache")},
        {Language::Hindi,
         QStringLiteral("&फ़ाइल"),
         QStringLiteral("&संपादन"),
         QStringLiteral("&दृश्य"),
         QStringLiteral("&सेटिंग्स"),
         QStringLiteral("&प्लगइन्स"),
         QStringLiteral("&विकास"),
         QStringLiteral("&परीक्षण"),
         QStringLiteral("इंटरफ़ेस &भाषा"),
         QStringLiteral("श्रेणी &भाषा")},
        {Language::Italian,
         QStringLiteral("&File"),
         QStringLiteral("&Modifica"),
         QStringLiteral("&Visualizza"),
         QStringLiteral("&Impostazioni"),
         QStringLiteral("&Plugin"),
         QStringLiteral("&Sviluppo"),
         QStringLiteral("&Test"),
         QStringLiteral("Lingua dell'&interfaccia"),
         QStringLiteral("Lingua delle &categorie")},
        {Language::Spanish,
         QStringLiteral("&Archivo"),
         QStringLiteral("&Editar"),
         QStringLiteral("&Ver"),
         QStringLiteral("&Configuración"),
         QStringLiteral("&Plugins"),
         QStringLiteral("&Desarrollo"),
         QStringLiteral("&Pruebas"),
         QStringLiteral("Idioma de la &interfaz"),
         QStringLiteral("Idioma de la &categoría")},
        {Language::Dutch,
         QStringLiteral("&Bestand"),
         QStringLiteral("&Bewerken"),
         QStringLiteral("&Beeld"),
         QStringLiteral("&Instellingen"),
         QStringLiteral("&Plugins"),
         QStringLiteral("&Ontwikkeling"),
         QStringLiteral("&Tests"),
         QStringLiteral("&Interfacetaal"),
         QStringLiteral("&Categorietaal")},
        {Language::Turkish,
         QStringLiteral("&Dosya"),
         QStringLiteral("&Düzen"),
         QStringLiteral("&Görünüm"),
         QStringLiteral("&Ayarlar"),
         QStringLiteral("&Eklentiler"),
         QStringLiteral("&Geliştirme"),
         QStringLiteral("&Testler"),
         QStringLiteral("Arayüz &dili"),
         QStringLiteral("Kategori &dili")},
        {Language::Korean,
         QStringLiteral("&파일"),
         QStringLiteral("&편집"),
         QStringLiteral("&보기"),
         QStringLiteral("&설정"),
         QStringLiteral("&플러그인"),
         QStringLiteral("&개발"),
         QStringLiteral("&테스트"),
         QStringLiteral("인터페이스 &언어"),
         QStringLiteral("분류 &언어")}
    };

    for (const auto& entry : expected) {
        TranslationManager::instance().set_language(entry.language);

        const auto file_menu = QCoreApplication::translate("UiTranslator", "&File");
        const auto edit_menu = QCoreApplication::translate("UiTranslator", "&Edit");
        const auto view_menu = QCoreApplication::translate("UiTranslator", "&View");
        const auto settings_menu = QCoreApplication::translate("UiTranslator", "&Settings");
        const auto plugins_menu = QCoreApplication::translate("UiTranslator", "&Plugins");
        const auto development_menu = QCoreApplication::translate("UiTranslator", "&Development");
        const auto tests_menu = QCoreApplication::translate("UiTranslator", "&Tests");
        const auto interface_language_menu =
            QCoreApplication::translate("UiTranslator", "Interface &language");
        const auto category_language_menu =
            QCoreApplication::translate("UiTranslator", "Category &language");

        CAPTURE(static_cast<int>(entry.language),
                file_menu,
                edit_menu,
                view_menu,
                settings_menu,
                plugins_menu,
                development_menu,
                tests_menu,
                interface_language_menu,
                category_language_menu);

        REQUIRE(file_menu == entry.file_menu);
        REQUIRE(edit_menu == entry.edit_menu);
        REQUIRE(view_menu == entry.view_menu);
        REQUIRE(settings_menu == entry.settings_menu);
        REQUIRE(plugins_menu == entry.plugins_menu);
        REQUIRE(development_menu == entry.development_menu);
        REQUIRE(tests_menu == entry.tests_menu);
        REQUIRE(interface_language_menu == entry.interface_language_menu);
        REQUIRE(category_language_menu == entry.category_language_menu);
    }
}

TEST_CASE("Settings menu actions are translated for all supported UI languages")
{
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", "offscreen");
    QtAppContext qt_context;

    struct ExpectedTranslation {
        Language language;
        QString system_compatibility_check;
        QString select_llm;
        QString manage_category_whitelists;
        QString interface_language;
        QString category_language;
        QString reset_learned_behavior;
        QString clear_cache;
    };

    const std::vector<ExpectedTranslation> expected = {
        {Language::English,
         QStringLiteral("System compatibility check…"),
         QStringLiteral("Select &LLM…"),
         QStringLiteral("Manage category whitelists…"),
         QStringLiteral("Interface &language"),
         QStringLiteral("Category &language"),
         QStringLiteral("Reset learned behavior…"),
         QStringLiteral("Clear cache…")},
        {Language::French,
         QStringLiteral("Vérification de la compatibilité du système…"),
         QStringLiteral("Sélectionner le &LLM…"),
         QStringLiteral("Gérer les listes blanches de catégories…"),
         QStringLiteral("Langue de l'&interface"),
         QStringLiteral("Langue des &catégories"),
         QStringLiteral("Réinitialiser le comportement appris…"),
         QStringLiteral("Vider le cache…")},
        {Language::German,
         QStringLiteral("Systemkompatibilitätsprüfung…"),
         QStringLiteral("&LLM auswählen…"),
         QStringLiteral("Kategorie-Whitelists verwalten…"),
         QStringLiteral("&Sprache der Benutzeroberfläche"),
         QStringLiteral("&Kategoriesprache"),
         QStringLiteral("Gelerntes Verhalten zurücksetzen…"),
         QStringLiteral("Cache leeren…")},
        {Language::Hindi,
         QStringLiteral("सिस्टम संगतता जाँच…"),
         QStringLiteral("&LLM चुनें…"),
         QStringLiteral("श्रेणी श्वेतसूचियाँ प्रबंधित करें…"),
         QStringLiteral("इंटरफ़ेस &भाषा"),
         QStringLiteral("श्रेणी &भाषा"),
         QStringLiteral("सीखे गए व्यवहार को रीसेट करें…"),
         QStringLiteral("कैश साफ़ करें…")},
        {Language::Italian,
         QStringLiteral("Verifica compatibilità del sistema…"),
         QStringLiteral("Seleziona &LLM…"),
         QStringLiteral("Gestisci whitelist delle categorie…"),
         QStringLiteral("Lingua dell'&interfaccia"),
         QStringLiteral("Lingua delle &categorie"),
         QStringLiteral("Reimposta il comportamento appreso…"),
         QStringLiteral("Svuota cache…")},
        {Language::Spanish,
         QStringLiteral("Comprobación de compatibilidad del sistema…"),
         QStringLiteral("Seleccionar &LLM…"),
         QStringLiteral("Gestionar listas blancas de categorías…"),
         QStringLiteral("Idioma de la &interfaz"),
         QStringLiteral("Idioma de la &categoría"),
         QStringLiteral("Restablecer el comportamiento aprendido…"),
         QStringLiteral("Borrar caché…")},
        {Language::Dutch,
         QStringLiteral("Systeemcompatibiliteitscontrole…"),
         QStringLiteral("Selecteer &LLM…"),
         QStringLiteral("Categoriewhitelists beheren…"),
         QStringLiteral("&Interfacetaal"),
         QStringLiteral("&Categorietaal"),
         QStringLiteral("Aangeleerd gedrag resetten…"),
         QStringLiteral("Cache wissen…")},
        {Language::Turkish,
         QStringLiteral("Sistem uyumluluk denetimi…"),
         QStringLiteral("&LLM seç…"),
         QStringLiteral("Kategori beyaz listelerini yönet…"),
         QStringLiteral("Arayüz &dili"),
         QStringLiteral("Kategori &dili"),
         QStringLiteral("Öğrenilen davranışı sıfırla…"),
         QStringLiteral("Önbelleği temizle…")},
        {Language::Korean,
         QStringLiteral("시스템 호환성 검사…"),
         QStringLiteral("&LLM 선택…"),
         QStringLiteral("카테고리 화이트리스트 관리…"),
         QStringLiteral("인터페이스 &언어"),
         QStringLiteral("분류 &언어"),
         QStringLiteral("학습된 동작 재설정…"),
         QStringLiteral("캐시 비우기…")}
    };

    for (const auto& entry : expected) {
        TranslationManager::instance().set_language(entry.language);

        const auto system_compatibility_check =
            QCoreApplication::translate("UiTranslator", "System compatibility check…");
        const auto select_llm = QCoreApplication::translate("UiTranslator", "Select &LLM…");
        const auto manage_category_whitelists =
            QCoreApplication::translate("UiTranslator", "Manage category whitelists…");
        const auto interface_language =
            QCoreApplication::translate("UiTranslator", "Interface &language");
        const auto category_language =
            QCoreApplication::translate("UiTranslator", "Category &language");
        const auto reset_learned_behavior =
            QCoreApplication::translate("UiTranslator", "Reset learned behavior…");
        const auto clear_cache =
            QCoreApplication::translate("UiTranslator", "Clear cache…");

        CAPTURE(static_cast<int>(entry.language),
                system_compatibility_check,
                select_llm,
                manage_category_whitelists,
                interface_language,
                category_language,
                reset_learned_behavior,
                clear_cache);

        REQUIRE(system_compatibility_check == entry.system_compatibility_check);
        REQUIRE(select_llm == entry.select_llm);
        REQUIRE(manage_category_whitelists == entry.manage_category_whitelists);
        REQUIRE(interface_language == entry.interface_language);
        REQUIRE(category_language == entry.category_language);
        REQUIRE(reset_learned_behavior == entry.reset_learned_behavior);
        REQUIRE(clear_cache == entry.clear_cache);
    }
}

TEST_CASE("Updater strings are translated for all supported UI languages") {
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", "offscreen");
    QtAppContext qt_context;

    struct ExpectedTranslation {
        Language language;
        QString update_failed;
        QString update_manually;
        QString prepare_failed;
        QString installer_launch_failed;
        QString no_download_target;
        QString downloading_update;
        QString downloading_installer;
        QString installer_ready;
        QString quit_and_launch_message;
        QString quit_and_launch_button;
        QString whats_new_in_version;
    };

    const std::vector<ExpectedTranslation> expected = {
        {Language::English,
         QStringLiteral("Update Failed"),
         QStringLiteral("Update manually"),
         QStringLiteral("Failed to prepare the update installer.\n%1"),
         QStringLiteral("The installer could not be launched."),
         QStringLiteral("No download target is available for this update."),
         QStringLiteral("Downloading Update"),
         QStringLiteral("Downloading the update installer..."),
         QStringLiteral("Installer Ready"),
         QStringLiteral("Quit the app and launch the installer to update"),
         QStringLiteral("Quit and Launch Installer"),
         QStringLiteral("What's new in version %1:")},
        {Language::French,
         QStringLiteral("Échec de la mise à jour"),
         QStringLiteral("Mettre à jour manuellement"),
         QStringLiteral("Échec de la préparation du programme d'installation de la mise à jour.\n%1"),
         QStringLiteral("Le programme d'installation n'a pas pu être lancé."),
         QStringLiteral("Aucune cible de téléchargement n'est disponible pour cette mise à jour."),
         QStringLiteral("Téléchargement de la mise à jour"),
         QStringLiteral("Téléchargement du programme d'installation de la mise à jour..."),
         QStringLiteral("Programme d'installation prêt"),
         QStringLiteral("Quittez l'application et lancez le programme d'installation pour effectuer la mise à jour"),
         QStringLiteral("Quitter et lancer le programme d'installation"),
         QStringLiteral("Nouveautés de la version %1 :")},
        {Language::German,
         QStringLiteral("Update fehlgeschlagen"),
         QStringLiteral("Manuell aktualisieren"),
         QStringLiteral("Das Update-Installationsprogramm konnte nicht vorbereitet werden.\n%1"),
         QStringLiteral("Das Installationsprogramm konnte nicht gestartet werden."),
         QStringLiteral("Für dieses Update ist kein Download-Ziel verfügbar."),
         QStringLiteral("Update wird heruntergeladen"),
         QStringLiteral("Das Update-Installationsprogramm wird heruntergeladen..."),
         QStringLiteral("Installationsprogramm bereit"),
         QStringLiteral("Beenden Sie die App und starten Sie das Installationsprogramm, um zu aktualisieren"),
         QStringLiteral("Beenden und Installationsprogramm starten"),
         QStringLiteral("Neuerungen in Version %1:")},
        {Language::Hindi,
         QStringLiteral("अपडेट विफल"),
         QStringLiteral("मैन्युअल रूप से अपडेट करें"),
         QStringLiteral("अपडेट इंस्टॉलर तैयार नहीं किया जा सका।\n%1"),
         QStringLiteral("इंस्टॉलर शुरू नहीं किया जा सका।"),
         QStringLiteral("इस अपडेट के लिए कोई डाउनलोड लक्ष्य उपलब्ध नहीं है।"),
         QStringLiteral("अपडेट डाउनलोड हो रहा है"),
         QStringLiteral("अपडेट इंस्टॉलर डाउनलोड किया जा रहा है..."),
         QStringLiteral("इंस्टॉलर तैयार है"),
         QStringLiteral("अपडेट करने के लिए ऐप बंद करें और इंस्टॉलर चलाएँ"),
         QStringLiteral("बंद करें और इंस्टॉलर चलाएँ"),
         QStringLiteral("संस्करण %1 में नया क्या है:")},
        {Language::Italian,
         QStringLiteral("Aggiornamento non riuscito"),
         QStringLiteral("Aggiorna manualmente"),
         QStringLiteral("Impossibile preparare il programma di installazione dell'aggiornamento.\n%1"),
         QStringLiteral("Impossibile avviare il programma di installazione."),
         QStringLiteral("Nessuna destinazione di download disponibile per questo aggiornamento."),
         QStringLiteral("Download aggiornamento"),
         QStringLiteral("Download del programma di installazione dell'aggiornamento..."),
         QStringLiteral("Programma di installazione pronto"),
         QStringLiteral("Chiudi l'app e avvia il programma di installazione per aggiornare"),
         QStringLiteral("Chiudi e avvia il programma di installazione"),
         QStringLiteral("Novità della versione %1:")},
        {Language::Spanish,
         QStringLiteral("La actualización falló"),
         QStringLiteral("Actualizar manualmente"),
         QStringLiteral("No se pudo preparar el instalador de la actualización.\n%1"),
         QStringLiteral("No se pudo ejecutar el instalador."),
         QStringLiteral("No hay un destino de descarga disponible para esta actualización."),
         QStringLiteral("Descargando actualización"),
         QStringLiteral("Descargando el instalador de la actualización..."),
         QStringLiteral("Instalador listo"),
         QStringLiteral("Cierra la aplicación y ejecuta el instalador para actualizar"),
         QStringLiteral("Cerrar y ejecutar instalador"),
         QStringLiteral("Novedades de la versión %1:")},
        {Language::Dutch,
         QStringLiteral("Bijwerken mislukt"),
         QStringLiteral("Handmatig bijwerken"),
         QStringLiteral("Het installatieprogramma van de update kon niet worden voorbereid.\n%1"),
         QStringLiteral("Het installatieprogramma kon niet worden gestart."),
         QStringLiteral("Er is geen downloaddoel beschikbaar voor deze update."),
         QStringLiteral("Update downloaden"),
         QStringLiteral("Het installatieprogramma van de update wordt gedownload..."),
         QStringLiteral("Installatieprogramma gereed"),
         QStringLiteral("Sluit de app af en start het installatieprogramma om bij te werken"),
         QStringLiteral("Afsluiten en installatieprogramma starten"),
         QStringLiteral("Nieuw in versie %1:")},
        {Language::Turkish,
         QStringLiteral("Güncelleme başarısız oldu"),
         QStringLiteral("Elle güncelle"),
         QStringLiteral("Güncelleme yükleyicisi hazırlanamadı.\n%1"),
         QStringLiteral("Yükleyici başlatılamadı."),
         QStringLiteral("Bu güncelleme için kullanılabilir bir indirme hedefi yok."),
         QStringLiteral("Güncelleme indiriliyor"),
         QStringLiteral("Güncelleme yükleyicisi indiriliyor..."),
         QStringLiteral("Yükleyici hazır"),
         QStringLiteral("Güncellemek için uygulamadan çıkın ve yükleyiciyi başlatın"),
         QStringLiteral("Çık ve yükleyiciyi başlat"),
         QStringLiteral("%1 sürümündeki yenilikler:")},
        {Language::Korean,
         QStringLiteral("업데이트 실패"),
         QStringLiteral("수동으로 업데이트"),
         QStringLiteral("업데이트 설치 프로그램을 준비하지 못했습니다.\n%1"),
         QStringLiteral("설치 프로그램을 실행할 수 없습니다."),
         QStringLiteral("이 업데이트에 사용할 다운로드 대상이 없습니다."),
         QStringLiteral("업데이트 다운로드 중"),
         QStringLiteral("업데이트 설치 프로그램을 다운로드하는 중..."),
         QStringLiteral("설치 프로그램 준비 완료"),
         QStringLiteral("업데이트하려면 앱을 종료하고 설치 프로그램을 실행하세요"),
         QStringLiteral("종료 후 설치 프로그램 실행"),
         QStringLiteral("%1 버전의 새로운 기능:")}
    };

    for (const auto& entry : expected) {
        TranslationManager::instance().set_language(entry.language);

        const auto update_failed = QCoreApplication::translate("QObject", "Update Failed");
        const auto update_manually = QCoreApplication::translate("QObject", "Update manually");
        const auto prepare_failed = QCoreApplication::translate("QObject", "Failed to prepare the update installer.\n%1");
        const auto installer_launch_failed = QCoreApplication::translate("QObject", "The installer could not be launched.");
        const auto no_download_target = QCoreApplication::translate("QObject", "No download target is available for this update.");
        const auto downloading_update = QCoreApplication::translate("QObject", "Downloading Update");
        const auto downloading_installer = QCoreApplication::translate("QObject", "Downloading the update installer...");
        const auto installer_ready = QCoreApplication::translate("QObject", "Installer Ready");
        const auto quit_and_launch_message = QCoreApplication::translate("QObject", "Quit the app and launch the installer to update");
        const auto quit_and_launch_button = QCoreApplication::translate("QObject", "Quit and Launch Installer");
        const auto whats_new_in_version = QCoreApplication::translate("QObject", "What's new in version %1:");

        CAPTURE(static_cast<int>(entry.language),
                update_failed,
                update_manually,
                prepare_failed,
                installer_launch_failed,
                no_download_target,
                downloading_update,
                downloading_installer,
                installer_ready,
                quit_and_launch_message,
                quit_and_launch_button,
                whats_new_in_version);

        REQUIRE(update_failed == entry.update_failed);
        REQUIRE(update_manually == entry.update_manually);
        REQUIRE(prepare_failed == entry.prepare_failed);
        REQUIRE(installer_launch_failed == entry.installer_launch_failed);
        REQUIRE(no_download_target == entry.no_download_target);
        REQUIRE(downloading_update == entry.downloading_update);
        REQUIRE(downloading_installer == entry.downloading_installer);
        REQUIRE(installer_ready == entry.installer_ready);
        REQUIRE(quit_and_launch_message == entry.quit_and_launch_message);
        REQUIRE(quit_and_launch_button == entry.quit_and_launch_button);
        REQUIRE(whats_new_in_version == entry.whats_new_in_version);
    }
}

TEST_CASE("Quick Start guide content follows the selected app language")
{
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", "offscreen");
    QtAppContext qt_context;

    TranslationManager::instance().set_language(Language::English);
    const QString english = MainAppHelpActions::quick_start_markdown_for_language(
        TranslationManager::instance().current_language());
    REQUIRE(english.contains(QStringLiteral("# Quick Start Guide")));
    REQUIRE(english.contains(QStringLiteral("Choose a Folder")));

    TranslationManager::instance().set_language(Language::French);
    const QString french = MainAppHelpActions::quick_start_markdown_for_language(
        TranslationManager::instance().current_language());
    REQUIRE(french.contains(QStringLiteral("# Guide de demarrage rapide")));
    REQUIRE(french.contains(QStringLiteral("Choisir un dossier")));

    TranslationManager::instance().set_language(Language::Korean);
    const QString korean = MainAppHelpActions::quick_start_markdown_for_language(
        TranslationManager::instance().current_language());
    REQUIRE(korean.contains(QStringLiteral("# 빠른 시작 가이드")));
    REQUIRE(korean.contains(QStringLiteral("폴더 선택")));

    TranslationManager::instance().set_language(Language::Hindi);
    const QString hindi = MainAppHelpActions::quick_start_markdown_for_language(
        TranslationManager::instance().current_language());
    REQUIRE(hindi.contains(QStringLiteral("# त्वरित प्रारंभ मार्गदर्शिका")));
    REQUIRE(hindi.contains(QStringLiteral("फ़ोल्डर चुनें")));
}

TEST_CASE("Quick Start and FAQ help labels are translated for all supported UI languages")
{
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", "offscreen");
    QtAppContext qt_context;

    struct ExpectedTranslation {
        Language language;
        QString quick_start_menu;
        QString faq_menu;
        QString quick_start_title;
    };

    const std::vector<ExpectedTranslation> expected = {
        {Language::English,
         QStringLiteral("&Quick Start Guide"),
         QStringLiteral("&FAQ"),
         QStringLiteral("Quick Start Guide")},
        {Language::French,
         QStringLiteral("&Guide de démarrage rapide"),
         QStringLiteral("&FAQ"),
         QStringLiteral("Guide de démarrage rapide")},
        {Language::German,
         QStringLiteral("&Schnellstartanleitung"),
         QStringLiteral("&FAQ"),
         QStringLiteral("Schnellstartanleitung")},
        {Language::Hindi,
         QStringLiteral("&त्वरित प्रारंभ मार्गदर्शिका"),
         QStringLiteral("&सामान्य प्रश्न"),
         QStringLiteral("त्वरित प्रारंभ मार्गदर्शिका")},
        {Language::Italian,
         QStringLiteral("&Guida rapida"),
         QStringLiteral("&FAQ"),
         QStringLiteral("Guida rapida")},
        {Language::Spanish,
         QStringLiteral("&Guía de inicio rápido"),
         QStringLiteral("&FAQ"),
         QStringLiteral("Guía de inicio rápido")},
        {Language::Dutch,
         QStringLiteral("&Snelstartgids"),
         QStringLiteral("&FAQ"),
         QStringLiteral("Snelstartgids")},
        {Language::Turkish,
         QStringLiteral("&Hızlı Başlangıç Kılavuzu"),
         QStringLiteral("&SSS"),
         QStringLiteral("Hızlı Başlangıç Kılavuzu")},
        {Language::Korean,
         QStringLiteral("&빠른 시작 가이드"),
         QStringLiteral("&FAQ"),
         QStringLiteral("빠른 시작 가이드")}
    };

    for (const auto& entry : expected) {
        TranslationManager::instance().set_language(entry.language);

        const auto quick_start_menu =
            QCoreApplication::translate("UiTranslator", "&Quick Start Guide");
        const auto faq_menu = QCoreApplication::translate("UiTranslator", "&FAQ");
        const auto quick_start_title =
            QCoreApplication::translate("QObject", "Quick Start Guide");

        CAPTURE(static_cast<int>(entry.language),
                quick_start_menu,
                faq_menu,
                quick_start_title);

        REQUIRE(quick_start_menu == entry.quick_start_menu);
        REQUIRE(faq_menu == entry.faq_menu);
        REQUIRE(quick_start_title == entry.quick_start_title);
    }
}
#endif
