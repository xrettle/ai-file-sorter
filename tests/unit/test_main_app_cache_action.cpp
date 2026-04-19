#include <catch2/catch_test_macros.hpp>

#include "MainApp.hpp"
#include "MainAppTestAccess.hpp"
#include "Settings.hpp"
#include "TestHelpers.hpp"

#include <QAction>
#include <QMenu>

#ifndef _WIN32
TEST_CASE("Settings clear cache action stays last and follows analysis state")
{
    EnvVarGuard platform_guard("QT_QPA_PLATFORM", std::string("offscreen"));
    QtAppContext qt_context;

    TempDir temp;
    EnvVarGuard home_guard("HOME", temp.path().string());
    EnvVarGuard config_guard("AI_FILE_SORTER_CONFIG_DIR", temp.path().string());

    Settings settings;
    REQUIRE(settings.save());

    MainApp window(settings, /*development_mode=*/false);

    QAction* clear_cache_action = MainAppTestAccess::clear_cache_action(window);
    QMenu* settings_menu = MainAppTestAccess::settings_menu(window);

    REQUIRE(clear_cache_action != nullptr);
    REQUIRE(settings_menu != nullptr);
    REQUIRE_FALSE(settings_menu->actions().isEmpty());
    CHECK(settings_menu->actions().back() == clear_cache_action);
    CHECK(clear_cache_action->isEnabled());

    MainAppTestAccess::set_analysis_in_progress(window, true);
    CHECK_FALSE(clear_cache_action->isEnabled());

    MainAppTestAccess::set_analysis_in_progress(window, false);
    CHECK(clear_cache_action->isEnabled());
}
#endif
