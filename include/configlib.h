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
#pragma once
#ifndef __STF_CONFIGLIB_H__
#define __STF_CONFIGLIB_H__

#include <string>

namespace stf {

// Concept - Want something that will work a bit like console variables in games
enum class eSettingLevel {
    APP,        // Application level setting is defined in application and can not be modified by config file or by user when app is running - it's read only setting
    SYS,        // System level can be modyfied only by config file that cames from system directory - it's read only
    USER        // User level can be modified by user and system configuration files - it's RW and might also be saved back to config file
};


template<typename T>
class SettingParam {
public:
    using type = T;

    //    enum class Type { BOOL, INT, FLOAT, STRING };
    SettingParam( const std::string& name, eSettingLevel level, T defaultValue ) : _name(name), _level(level), _defaultVal(defaultValue), _val(defaultValue) {}

    const std::string&  getName( void ) const { return _name; }
    T   getVal( void ) const { return _val; }

private:
    // Once set can not be changed
    const std::string   _name;
    eSettingLevel   _level;
    T       _defaultVal;
    T       _val;
};

// Container for SettingParam
class Settings {
public:

};

}; // ns:stf

#endif /* ndef __STF_CONFIGLIB_H__ */
// vim: ts=4:sw=4:et:nowrap
