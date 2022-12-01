//                                    .-""-.
//                                   / _  _ \
//                                   |(_)(_)|
// .------------------------------ooO(_ /\ _)Ooo-----------------------------.
// |                                  |====|                                 |
// |                                  '-..-'                                 |
// | Desc: Sandbox main - to test ConfigLIB                                  |
// |                                                                         |
// | By: Nuroferatu - https://github.com/Nuroferatu                          |
// |                                                                         |
// | Copyright (C)2022 SoftwareToolsFactory                                  |
// |                   http://softwaretoolsfactory.com                       |
// '-------------------------------------------------------------------------'
#include <iostream>
#include "configlib.h"

#include <vector>
#include <list>

// Sample user data type that can be stored as setting
struct UserType {
    static constexpr std::uint32_t SETTINGS_USER_ID = stf::eSettingUserID<0>::val;
    UserType( int i, int j, int k ) : x(i), y(j), z(k) {}
    ~UserType() = default;

    int x;
    int y;
    int z;
};

template<> stf::SettingParam<UserType>::SettingParam( const std::string& name, const stf::eSettingLevel level, UserType defaultVal ) :
    SettingVarBase(name, level, UserType::SETTINGS_USER_ID),
    _defaultVal(defaultVal),
    _val(_defaultVal) {}

int main( int argc, char* argv, char* env[] ) {
    static stf::SettingParam<UserType>       sampleUserTypeParam      { "SettingParam<UserType>",   stf::eSettingLevel::APP,  UserType(0,1,2) };
    static stf::SettingParam<bool>           sampleBoolParam          { "SettingParam<bool>",       stf::eSettingLevel::SYS,  false };
    static stf::SettingParam<float>          sampleFloatParam         { "SettingParam<float>",      stf::eSettingLevel::USER, 1.2345f };
    static stf::SettingParam<std::int32_t>   sampleInt32SmallNumParam { "SettingParam<int32_t>",    stf::eSettingLevel::USER, 100 };
    static stf::SettingParam<std::int64_t>   sampleInt64SmallNumParam { "SettingParam<int64_t>",    stf::eSettingLevel::USER, 101 };
    static stf::SettingParam<std::int32_t>   sampleInt32SMaxNumParam  { "SettingParam<int32_t>",    stf::eSettingLevel::USER, INT32_MAX };
    static stf::SettingParam<std::int64_t>   sampleInt64SMaxlNumParam { "SettingParam<int64_t>",    stf::eSettingLevel::USER, INT64_MAX };
    static stf::SettingParam<std::string>    sampleStringParam        { "SettingParam<string>",     stf::eSettingLevel::USER, "SampleValue" };

    //// Planed usage
    //// 1. Direct in place of declatarion
    //bool bVal = sampleBoolParam.getVal();
    //std::cout << std::endl << bVal << std::endl;
    //std::cout << sampleStringParam2.getVal() << std::endl << std::endl;
    static stf::Settings& ref = stf::Settings::get();
    for( auto val : ref.getRegistry() ) {
        std::cout << "Registry [" << val->getName() << "] " << "Level [" << val->getSettingsLevelAsStr() << "] Type [" << val->getTypeAsStr() << "]" << std::endl;
    }


    ////// 2. Indirect using Settings
    ////// int iVal = stf::Settings::Get().Find( "sampleIntParam" ).GetVal();
    ////// stf::Settings::Get().Find( "sampleStringParam" ).SetVal( "otherValue" );
    ////ref.registerSetting( sampleBoolParam );
    ////ref.registerSetting( sampleInt32Param );
    ////ref.registerSetting( sampleInt64Param );
    ////ref.registerSetting( sampleFloatParam );
    ////ref.registerSetting( sampleStringParam );
    ////ref.registerSetting( sampleStringParam2 );

    //// This works
    //for( auto& item : ref._registry ) {
    //    std::cout << item.ptr.spAll->getName() << " TypeOf: " << item.ptr.spAll->getTypeAsStr() << std::endl;
    //}
    return 0;
}

#ifdef _WIN32

#include <windows.h>

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
    return 0;
}

#endif // def _WIN32

// vim: ts=4:sw=4:et:nowrap
