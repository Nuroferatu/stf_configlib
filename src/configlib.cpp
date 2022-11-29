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

#if 0

namespace stf {

const std::string& settingTypeToStr( const SettingType& type ) {
    static const std::string    strUndefined{"UNDEFINED"};
    static const std::string    strBool{"BOOL"};
    static const std::string    strInt32{"INT32"};
    static const std::string    strInt64{"INT64"};
    static const std::string    strFloat{"FLOAT"};
    static const std::string    strString{"STRING"};
    static const std::string    strUnknown{"UNKNOWN"};

    switch( type ) {
        case SettingType::UNDEFINED:    return strUndefined;
        case SettingType::BOOL:         return strBool;
        case SettingType::INT32:        return strInt32; 
        case SettingType::INT64:        return strInt64;
        case SettingType::FLOAT:        return strFloat;
        case SettingType::STRING:       return strString;
    }
    return strUnknown;
}

Settings& Settings::get( void ) {
    static Settings     settings{};
    return settings;
}

template<typename T>
void Settings::registerSetting( SettingParam<T>& param ) {
    std::cout << "registerSetting( SettingParam<UNDEFINED>& param )" << std::endl;
    _registry.emplace_back( param );
}

template<> void Settings::registerSetting( SettingParam<bool>& param ) {
    std::cout << "registerSetting( SettingParam<bool>& param )" << std::endl;
    _registry.emplace_back( param );
}

template<> void Settings::registerSetting( SettingParam<std::int32_t>& param ) {
    std::cout << "registerSetting( SettingParam<std::int32_t>& param )" << std::endl;
    _registry.emplace_back( param );
}

template<> void Settings::registerSetting( SettingParam<std::int64_t>& param ) {
    std::cout << "registerSetting( SettingParam<std::int64_t>& param )" << std::endl;
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
#endif

// vim: ts=4:sw=4:et:nowrap
