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

static stf::SettingParam<bool>          sampleBoolParam   { "sampleBoolParam", stf::eSettingLevel::APP, false };
static stf::SettingParam<std::int32_t>  sampleInt32Param  { "sampleIntParam32", stf::eSettingLevel::SYS, 100 };
static stf::SettingParam<std::int64_t>  sampleInt64Param  { "sampleIntParam64", stf::eSettingLevel::SYS, 100 };
static stf::SettingParam<float>         sampleFloatParam  { "sampleFloatParam", stf::eSettingLevel::USER, 1.1234f };
static stf::SettingParam<std::string>   sampleStringParam { "sampleStringParam", stf::eSettingLevel::USER, "sampleDefaultValue" };
static stf::SettingParam<std::string>   sampleStringParam2{ "sampleStringParam2", stf::eSettingLevel::USER, std::string("sampleDefaultValue") };

int main( int argc, char* argv, char* env[] ) {
    // Planed usage
    // 1. Direct in place of declatarion
    bool bVal = sampleBoolParam.getVal();
    std::cout << bVal << std::endl;

    static stf::Settings& ref = stf::Settings::get();

    // 2. Indirect using Settings find
    // int iVal = stf::Settings::Get().Find( "sampleIntParam" ).GetVal();
    // stf::Settings::Get().Find( "sampleStringParam" ).SetVal( "otherValue" );
    ref.registerSetting( sampleBoolParam );
    ref.registerSetting( sampleInt32Param );
    ref.registerSetting( sampleInt64Param );
    ref.registerSetting( sampleFloatParam );
    ref.registerSetting( sampleStringParam );
    ref.registerSetting( sampleStringParam2 );

    // This works
    for( auto& item : ref._registry ) {
        std::cout << item.ptr.spAll->getName() << " TypeOf: " << item.ptr.spAll->getTypeAsStr() << std::endl;
    }
    return 0;
}

#ifdef _WIN32

#include <windows.h>

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
    return 0;
}

#endif // def _WIN32

// vim: ts=4:sw=4:et:nowrap
