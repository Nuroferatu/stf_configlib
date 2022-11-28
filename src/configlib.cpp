//                                    .-""-.
//                                   / _  _ \
//                                   |(_)(_)|
// .------------------------------ooO(_ /\ _)Ooo-----------------------------.
// |                                  |====|                                 |
// |                                  '-..-'                                 |
// | Desc: ConfigLib - main include                                          |
// |                                                                         |
// | By: Nuroferatu - https://github.com/Nuroferatu                          |
// |                                                                         |
// | Copyright (C)2022 SoftwareToolsFactory                                  |
// |                   http://softwaretoolsfactory.com                       |
// '-------------------------------------------------------------------------'
#include "configlib.h"
#include <iostream>

namespace stf {

Settings& Settings::get( void ) {
    static Settings     settings{};
    return settings;
}

template<> void Settings::registerSetting( SettingParam<bool>& param ) {
    std::cout << "registerSetting( SettingParam<bool>& param )" << std::endl;
    _registry.emplace_back( param );
}

template<> void Settings::registerSetting( SettingParam<std::uint32_t>& param ) {
    std::cout << "registerSetting( SettingParam<std::int32_t>& param )" << std::endl;
    _registry.emplace_back( param );
}

template<> void Settings::registerSetting( SettingParam<float>& param ) {
    std::cout << "registerSetting( SettingParam<float>& param )" << std::endl;
    _registry.emplace_back( param );
}

template<> void Settings::registerSetting( SettingParam<std::string>& param ) {
    std::cout << "registerSetting( SettingParam<std::string>& param )" << std::endl;
    _registry.emplace_back( param );
}

}; // ns:stf

// vim: ts=4:sw=4:et:nowrap
