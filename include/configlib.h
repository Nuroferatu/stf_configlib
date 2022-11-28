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
#include <vector>

namespace stf {

// Concept - Want something that will work a bit like console variables in games
enum class eSettingLevel {
    APP,        // Application level setting is defined in application and can not be modified by config file or by user when app is running - it's read only setting
    SYS,        // System level can be modyfied only by config file that cames from system directory - it's read only
    USER        // User level can be modified by user and system configuration files - it's RW and might also be saved back to config file
};

class SettingParamBase {
};

template<typename T>
class SettingParam : public SettingParamBase {
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

// Singleton that is container for SettingParam's
class Settings {
public:
    static Settings&    get( void );

    // Not implemented template - want it to fail
    template<typename T>
    void registerSetting( SettingParam<T>& param );

    template<> void registerSetting( SettingParam<bool>& param );
    template<> void registerSetting( SettingParam<std::uint32_t>& param );
    template<> void registerSetting( SettingParam<float>& param );
    template<> void registerSetting( SettingParam<std::string>& param );

    struct SettingsStore {
        SettingsStore(SettingParam<bool>& val) : ptr(val) {}
        SettingsStore(SettingParam<std::uint32_t>& val) : ptr(val) {}
        SettingsStore(SettingParam<float>& val) : ptr(val) {}
        SettingsStore(SettingParam<std::string>& val) : ptr(val) {}

        union Item {
            Item( SettingParam<bool>& ptr ) : spBool(&ptr) {} 
            Item( SettingParam<std::uint32_t>& ptr ) : spUInt(&ptr) {} 
            Item( SettingParam<float>& ptr ) : spFloat(&ptr) {} 
            Item( SettingParam<std::string>& ptr ) : spString(&ptr) {} 

            SettingParam<bool>*             spBool;
            SettingParam<std::uint32_t>*    spUInt;
            SettingParam<float>*            spFloat;
            SettingParam<std::string>*      spString;
            SettingParam<void*>*            spAll;      // Item is union so all types start at this same address, this one is just to represent all other
                                                        // without dedicated type, but to get Param name any of this items might be used. This is just syntax suger.
        };
        Item        ptr;
    };
    std::vector<SettingsStore>  _registry;
};

}; // ns:stf

#endif /* ndef __STF_CONFIGLIB_H__ */
// vim: ts=4:sw=4:et:nowrap
