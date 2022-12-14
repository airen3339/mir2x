#pragma once
#include <string>
#include <cstdint>
#include <optional>
#include <string_view>
#include "protocoldef.hpp"

struct ItemRecord
{
    const char8_t * const name   = nullptr;
    const char8_t * const type   = nullptr;
    const char8_t * const rarity = nullptr;

    const int weight = 0;
    const int pkgGfxID = 0;
    const uint32_t shape = 0;

    const struct EquipAttribute
    {
        const int duration = 0;

        const int dc[2] = {0, 0};
        const int mc[2] = {0, 0};
        const int sc[2] = {0, 0};

        const int  ac[2] = {0, 0};
        const int mac[2] = {0, 0};

        const int dcHit = 0;
        const int mcHit = 0;

        const int dcDodge = 0;
        const int mcDodge = 0;

        const int speed = 0;
        const int comfort = 0;
        const int luckCurse = 0;

        struct ExtHealth
        {
            const int add     = 0;
            const int steal   = 0;
            const int recover = 0;
        };

        const ExtHealth hp {};
        const ExtHealth mp {};

        struct AddElem
        {
            const int fire    = 0;
            const int ice     = 0;
            const int light   = 0;
            const int wind    = 0;
            const int holy    = 0;
            const int dark    = 0;
            const int phantom = 0;
        };

        const AddElem dcElem {};
        const AddElem acElem {};

        const struct AddLoad
        {
            const int body      = 0;
            const int weapon    = 0;
            const int inventory = 0;
        }
        load {};

        const struct EquipReq
        {
            const int dc = 0;
            const int mc = 0;
            const int sc = 0;
            const int level = 0;
            const char8_t * const job = nullptr;
        }
        req {};

        const struct WeaponAttr
        {
            const int mine = 0;
            const int doubleHand = 0;
            const std::u8string_view category {}; // weapon category, used for sound effect
                                                  // etorth/CBWCQ3 doesn't have this, possible values:
                                                  //
                                                  //     ??????   ?????????????????????
                                                  //     ??????   : ???????????????
                                                  //     ??????   : ??????????????????????????????
                                                  //     ???     :
                                                  //     ???     :
                                                  //     ???     :
                                                  //     ???     : ????????????
                                                  //     ???     : ???????????????????????????
                                                  //     ???     : ?????????
                                                  //     ???     : ?????????
                                                  //     ??????   ?????????????????????????????????
                                                  //
                                                  // still there are some weapons hard to give a category like ????????????????????????etc
                                                  // take them as ?????? for now
        }
        weapon {};
    }
    equip {};

    const struct PotionAttribute
    {
        const int hp   = 0;
        const int mp   = 0;
        const int time = 0;
    }
    potion {};

    const struct DopeAttribute
    {
        const int  hp = 0;
        const int  mp = 0;

        const int dc = 0;
        const int mc = 0;
        const int sc = 0;

        const int speed = 0;
        const int time  = 0;
    }
    dope {};

    const struct PoisonAttribute
    {
        const int dose = 0;
    }
    poison {};

    const struct BookAttribute
    {
        const char8_t * job = nullptr;
        const int level = 0;
    }
    book {};

    const char8_t * const description = nullptr;

    operator bool() const
    {
        return true
            && name && !std::u8string_view(name).empty()
            && type && !std::u8string_view(type).empty();
    }

    constexpr bool packable() const
    {
        return false
            || std::u8string_view(type) == u8"????????????"
            || std::u8string_view(type) == u8"????????????"
            || std::u8string_view(type) == u8"?????????"
            || std::u8string_view(type) == u8"??????";
    }

    constexpr bool beltable() const
    {
        return false
            || std::u8string_view(type) == u8"????????????"
            || std::u8string_view(type) == u8"????????????";
    }

    constexpr bool wearable(int wltype) const
    {
        switch(wltype){
            case WLG_DRESS   : return std::u8string_view(u8"??????") == type;
            case WLG_HELMET  : return std::u8string_view(u8"??????") == type;
            case WLG_WEAPON  : return std::u8string_view(u8"??????") == type;
            case WLG_SHOES   : return std::u8string_view(u8"???"  ) == type;
            case WLG_NECKLACE: return std::u8string_view(u8"??????") == type;
            case WLG_ARMRING0: return std::u8string_view(u8"??????") == type;
            case WLG_ARMRING1: return std::u8string_view(u8"??????") == type;
            case WLG_RING0   : return std::u8string_view(u8"??????") == type;
            case WLG_RING1   : return std::u8string_view(u8"??????") == type;
            case WLG_TORCH   : return std::u8string_view(u8"??????") == type;
            case WLG_CHARM   : return std::u8string_view(u8"??????|?????????|??????").find(type) != std::u8string_view::npos;
            default          : return false;
        }
    }

    constexpr bool isItem(const char8_t *itemName) const
    {
        return name && itemName && std::u8string_view(name) == itemName;
    }

    constexpr bool isGold() const
    {
        return std::u8string_view(type) == u8"??????";
    }

    constexpr bool isDress() const
    {
        return std::u8string_view(type) == u8"??????";
    }

    constexpr bool isWeapon() const
    {
        return std::u8string_view(type) == u8"??????";
    }

    constexpr bool isRing() const
    {
        return std::u8string_view(type) == u8"??????";
    }

    constexpr bool isHelmet() const
    {
        return std::u8string_view(type) == u8"??????";
    }

    constexpr bool isBook() const
    {
        return std::u8string_view(type) == u8"?????????";
    }

    constexpr bool isPotion() const
    {
        return std::u8string_view(type) == u8"????????????";
    }

    constexpr bool isDope() const
    {
        return std::u8string_view(type) == u8"????????????";
    }

    constexpr std::optional<bool> clothGender() const
    {
        if(type && (std::u8string_view(type) == u8"??????")){
            if(name){
                if(std::u8string_view(name).find(u8"?????????") != std::u8string_view::npos){
                    return true;
                }
                else if(std::u8string_view(name).find(u8"?????????") != std::u8string_view::npos){
                    return false;
                }
            }
        }
        return {};
    }
};
