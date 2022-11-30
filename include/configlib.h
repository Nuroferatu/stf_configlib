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
#include <iostream>

namespace stf {

// Concept - Want something that will work a bit like console variables in games
enum class eSettingLevel {
    UNDEFINED,
    APP,        // Application level setting is defined in application and can not be modified by config file or by user when app is running - it's read only setting
    SYS,        // System level can be modyfied only by config file that cames from system directory - it's read only
    USER        // User level can be modified by user and system configuration files - it's RW and might also be saved back to config file
};

enum class eSettingType {
    UNDEFINED,
    BOOL,
    INT32,
    INT64,
    FLOAT,
    STRING,
    USER        // Dedicated for user defined types
};

class SettingVarBase {
public:
    SettingVarBase( const std::string& name, const stf::eSettingLevel level, const stf::eSettingType type ) : _name(name), _level(level), _type(type) {}

    const std::string&  getName( void ) const { return _name; }
    const stf::eSettingLevel    getSettingsLevel( void ) const { return _level; }

protected:
    const std::string           _name;
    const stf::eSettingLevel    _level;
    const stf::eSettingType     _type;
};

#if 0
const std::string& settingTypeToStr( const SettingType& type );

class Settings;

// This is bad... it will require specialization for every type... :(
// And then everythig is duplicated in Settings for every type...
// I do not like it
template<typename T>
class SettingParam {
public:
    // All other templates
    template<typename T>
    SettingParam( const std::string& name, eSettingLevel level, T defaultValue ) : _name(name), _level(level), _type(SettingType::UNDEFINED), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "undefined ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    // Specializations
    template<> SettingParam( const std::string& name, eSettingLevel level, bool defaultValue ) : _name(name), _level(level), _type(SettingType::BOOL), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "bool ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    template<> SettingParam( const std::string& name, eSettingLevel level, float defaultValue ) : _name(name), _level(level), _type(SettingType::FLOAT), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "float ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    template<> SettingParam( const std::string& name, eSettingLevel level, const char* defaultValue ) : _name(name), _level(level), _type(SettingType::STRING), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "const char* ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    template<> SettingParam( const std::string& name, eSettingLevel level, std::int32_t defaultValue ) : _name(name), _level(level), _type(SettingType::INT32), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "int32_t ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    template<> SettingParam( const std::string& name, eSettingLevel level, std::int64_t defaultValue ) : _name(name), _level(level), _type(SettingType::INT64), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "int64_t ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    template<> SettingParam( const std::string& name, eSettingLevel level, std::string defaultValue ) : _name(name), _level(level), _type(SettingType::STRING), _defaultVal(defaultValue), _val(defaultValue) {
        std::cout << "std::string ctor: " << name << std::endl;
        Settings::get().registerSetting( *this );
    }

    const std::string&  getName( void ) const { return _name; }
    const SettingType&  getType( void ) const { return _type; }
    const std::string&  getTypeAsStr( void ) const { return settingTypeToStr(_type); }

    T   getVal( void ) const { return _val; }

private:
    // Once set can not be changed
    const std::string   _name;
    eSettingLevel   _level;
    SettingType     _type;
    T               _defaultVal;
    T               _val;
};

// Singleton that is container for SettingParam's
class Settings {
public:
    static Settings&    get( void );

    // Not implemented template - I want it to fail if type used is not covered here, compiler error is better then run time error :)
    template<typename T>
    void registerSetting( SettingParam<T>& param );

    // For every supported type there is dedicated register
    template<> void registerSetting( SettingParam<bool>& param );
    template<> void registerSetting( SettingParam<std::int32_t>& param );
    template<> void registerSetting( SettingParam<std::int64_t>& param );
    template<> void registerSetting( SettingParam<float>& param );
    template<> void registerSetting( SettingParam<std::string>& param );

    struct SettingsStore {
        SettingsStore(SettingParam<bool>& val) : ptr(val) {}
        SettingsStore(SettingParam<std::int32_t>& val) : ptr(val) {}
        SettingsStore(SettingParam<std::int64_t>& val) : ptr(val) {}
        SettingsStore(SettingParam<float>& val) : ptr(val) {}
        SettingsStore(SettingParam<std::string>& val) : ptr(val) {}

        union Item {
            Item( SettingParam<bool>& ptr ) : spBool(&ptr) {} 
            Item( SettingParam<std::int32_t>& ptr ) : spU32Int(&ptr) {} 
            Item( SettingParam<std::int64_t>& ptr ) : spU64Int(&ptr) {} 
            Item( SettingParam<float>& ptr ) : spFloat(&ptr) {} 
            Item( SettingParam<std::string>& ptr ) : spString(&ptr) {} 

            SettingParam<bool>*             spBool;
            SettingParam<std::int32_t>*     spU32Int;
            SettingParam<std::int64_t>*     spU64Int;
            SettingParam<float>*            spFloat;
            SettingParam<std::string>*      spString;
            SettingParam<void*>*            spAll;      // Item is union so all types start at this same address, this one is just to represent all other
                                                        // without dedicated type, but to get Param name any of this items might be used. This is just syntax suger.
        };
        Item        ptr;
    };
    std::vector<SettingsStore>  _registry;
};
#endif

}; // ns:stf

#endif /* ndef __STF_CONFIGLIB_H__ */
// vim: ts=4:sw=4:et:nowrap
