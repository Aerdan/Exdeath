#pragma once

#include <QMap>

enum Skill {
    // Action skills
    Guard     = 0x06,
    Kick      = 0x07,
    Focus     = 0x08,
    Chakra    = 0x09,
    Flee      = 0x0A,
    Steal     = 0x0B,
    Mug       = 0x0C,
    Jump      = 0x0D,
    Lancet    = 0x0E,
    Smoke     = 0x0F,
    Image     = 0x10,
    Throw     = 0x11,
    Mineuchi  = 0x12,
    GilToss   = 0x13,
    Iainuki   = 0x14,
    Animals   = 0x15,
    Aim       = 0x16,
    RapidFire = 0x17,
    Call      = 0x18,
    Check     = 0x19,
    Scan      = 0x1A,
    Calm      = 0x1B,
    Control   = 0x1C,
    Catch     = 0x1D,
    Mix       = 0x1F,
    Drink     = 0x20,
    Recover   = 0x21,
    Revive    = 0x22,
    Gaia      = 0x23,
    Hide      = 0x25,
    Sing      = 0x28,
    Flirt     = 0x29,
    Dance     = 0x2A,
    DualCast  = 0x4C,
    Blue      = 0x4D,

    // Magic-tier Action skills
    Spellblade1 = 0x2C,
    Spellblade2 = 0x2D,
    Spellblade3 = 0x2E,
    Spellblade4 = 0x2F,
    Spellblade5 = 0x30,
    Spellblade6 = 0x31,
    White1      = 0x32,
    White2      = 0x33,
    White3      = 0x34,
    White4      = 0x35,
    White5      = 0x36,
    White6      = 0x37,
    Black1      = 0x38,
    Black2      = 0x39,
    Black3      = 0x3A,
    Black4      = 0x3B,
    Black5      = 0x3C,
    Black6      = 0x3D,
    Time1       = 0x3E,
    Time2       = 0x3F,
    Time3       = 0x40,
    Time4       = 0x41,
    Time5       = 0x42,
    Time6       = 0x43,
    Summon1     = 0x44,
    Summon2     = 0x45,
    Summon3     = 0x46,
    Summon4     = 0x47,
    Summon5     = 0x48,
    Red1        = 0x49,
    Red2        = 0x4A,
    Red3        = 0x4B,

    // Passive/innate skills
    EquipShield  = 0x80,
    EquipArmor   = 0x81,
    EquipRibbon  = 0x82,
    EquipSword   = 0x83,
    EquipSpear   = 0x84,
    EquipKatana  = 0x85,
    EquipAxe     = 0x86,
    EquipBow     = 0x87,
    EquipWhip    = 0x88,
    EquipHarp    = 0x89,
    ArtfulDodger = 0x8A,
    HP10         = 0x8B,
    HP20         = 0x8C,
    HP30         = 0x8D,
    MP10         = 0x8E,
    MP30         = 0x8F,
    Barehanded   = 0x90,
    TwoHanded    = 0x91,
    DualWield    = 0x92,
    Pharmacology = 0x93,
    Cover        = 0x94,
    Counter      = 0x95,
    Shirahadori  = 0x96,
    Learning     = 0x97,
    MagicShield  = 0x98,
    Berserk      = 0x99,
    Vigilance    = 0x9A,
    FirstStrike  = 0x9B,
    FindPassages = 0x9C,
    LightStep    = 0x9D,
    FindPits     = 0x9E,
    EquipRods    = 0x9F,
    Sprint       = 0xA0
};

#define JOB_COUNT 20

const int tier1_jobs[] = {9, 10, 11, 12, 16, 17, 18};
const int tier2_jobs[] = {1,  2, 13, 14, 15, 19};
const int tier3_jobs[] = {0,  3,  4,  5,  7,  8, 15};

const int job_tier[] = {
    3, 2, 2, 3, 3, 3, 0, 3, 3, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2
};

extern const QMap<QString, int> *JobsList;
