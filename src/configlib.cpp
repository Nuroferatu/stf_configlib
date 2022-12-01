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
#include <sstream>

namespace stf {

const std::string& settingTypeToStr( const eSettingType& type, std::uint32_t userType ) {
    static const std::string    strUndefined{"UNDEFINED"};
    static const std::string    strBool{"BOOL"};
    static const std::string    strInt32{"INT32"};
    static const std::string    strInt64{"INT64"};
    static const std::string    strFloat{"FLOAT"};
    static const std::string    strString{"STRING"};
    static const std::string    strUnknown{"UNKNOWN"};
    static std::string          strUser;    // This is not thread safe :) 

    switch( type ) {
        case eSettingType::UNDEFINED:    return strUndefined;
        case eSettingType::BOOL:         return strBool;
        case eSettingType::INT32:        return strInt32; 
        case eSettingType::INT64:        return strInt64;
        case eSettingType::FLOAT:        return strFloat;
        case eSettingType::STRING:       return strString;
        case eSettingType::USER:
        {
            std::stringstream   ss;
            ss << "USER_" << userType;
            strUser = ss.str();
            return strUser;
        }
    }
    return strUnknown;
}

const std::string& settingLevelToStr( const eSettingLevel& type ) {
    static const std::string    strUndefined{"UNDEFINED"};
    static const std::string    strApp{"APP"};
    static const std::string    strSys{"SYS"};
    static const std::string    strUser{"USER"};

    switch( type ) {
        case eSettingLevel::APP:   return strApp;
        case eSettingLevel::SYS:   return strSys;
        case eSettingLevel::USER:  return strUser;
    }
    return strUndefined;
}

Settings& Settings::get( void ) {
    static Settings settings{};
    return settings;
}

void Settings::registerSetting( stf::SettingVarBase* param ) {
    _registry.push_back( param );
}

SettingVarBase::SettingVarBase( const std::string& name, const stf::eSettingLevel level, const stf::eSettingType type )
    : _name(name), _level(level), _type(type), _userType(UNDEFINED_USER_TYPE) {
    Settings::get().registerSetting( this );
}

SettingVarBase::SettingVarBase( const std::string& name, const stf::eSettingLevel level, const std::uint32_t type )
    : _name(name), _level(level), _type(stf::eSettingType::USER), _userType(type) {
    Settings::get().registerSetting( this );
}

template<class T> SettingParam<T>::SettingParam( const std::string& name, const stf::eSettingLevel level, T defaultVal ) : SettingVarBase(name, level, stf::eSettingType::UNKNOWN), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<bool>::SettingParam( const std::string& name, const stf::eSettingLevel level, bool defaultVal ) : SettingVarBase(name, level, stf::eSettingType::BOOL), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<float>::SettingParam( const std::string& name, const stf::eSettingLevel level, float defaultVal ) : SettingVarBase(name, level, stf::eSettingType::BOOL), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<std::int32_t>::SettingParam( const std::string& name, const stf::eSettingLevel level, std::int32_t defaultVal ) : SettingVarBase(name, level, stf::eSettingType::INT32), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<std::int64_t>::SettingParam( const std::string& name, const stf::eSettingLevel level, std::int64_t defaultVal ) : SettingVarBase(name, level, stf::eSettingType::INT64), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<std::string>::SettingParam( const std::string& name, const stf::eSettingLevel level, std::string defaultVal ) : SettingVarBase(name, level, stf::eSettingType::INT64), _defaultVal(defaultVal), _val(_defaultVal) {}


}; // ns:stf

// vim: ts=4:sw=4:et:nowrap
