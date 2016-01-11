#pragma once
#include <cstdint>
#include <functional>
#include "triangle.hpp"
#include "directiverectcover.hpp"

#pragma pack(push, 1)
typedef struct{
    // for door or dynamic tile
    // conceptually they are different
    // but they are the same in view of bit set
    //
    // for door or dynamic tile we only need 3 byte
    // here we have 4 byte so use 1 byte as descriptor
    //
    // use dwDesc == 0 to indicate currently it's a null block
    // why not use dwObject1/2 & 0XFF00FFFF == 0
    // because here not-null doesn't means no obj
    // also means no light, no door etc.
    //
    // but dwObject1/2 & 0XFF00FFFF can only indicate there is no obj
    uint32_t    dwDesc;
    uint32_t    dwObject1;
    uint32_t    dwObject2;
    uint32_t    dwLight;
}CELLDESC;

// hard to design!!!
// 
// dwDesc Door | Light | Object1Ani | Object2Ani
#pragma pack(pop)

class Monster;
class Mir2ClientMap
{
    public:
        Mir2ClientMap();
        ~Mir2ClientMap();

    public:
        bool Valid();
        int  W();
        int  H();
        int  ViewX();
        int  ViewY();

    public:
        bool NewLoadMap(const char *);

    private:
        uint32_t   *m_BaseTileInfo;
        uint32_t   *m_GroundInfo;
        CELLDESC   *m_CellDesc;

    private:
        bool        m_Valid;
        uint16_t    m_W;
        uint16_t    m_H;
        int         m_ViewX;
        int         m_ViewY;

    private:
        uint32_t    m_dwAniSaveTime[8];
        uint8_t     m_bAniTileFrame[8][16];

    private:
        uint32_t    BitPickOne(uint32_t *, uint32_t);


    private:
        bool LoadGroundInfo(uint32_t *, uint32_t, uint32_t *, uint32_t);
        void SetOneGroundInfoGrid(int, int, int, uint32_t);
        void SetGroundInfoBlock(int, int, int, uint32_t);
        void ParseGroundInfoStream(int, int, int, uint32_t *, uint32_t &, uint32_t *, uint32_t &);

    private:
        bool LoadCellDesc(uint32_t *, uint32_t, CELLDESC *, uint32_t);
        void SetCellDescBlock(int, int, int, const CELLDESC &);
        void ParseCellDescStream(int, int, int, uint32_t *, uint32_t &, CELLDESC *, uint32_t &);

    private:
        void SetBaseTileBlock(int, int, int, uint32_t);
        bool LoadBaseTileInfo(uint32_t *, uint32_t, uint32_t *, uint32_t);
        void ParseBaseTileStream(int, int, int, uint32_t *, uint32_t &, uint32_t *, uint32_t &);

    public:
        bool ValidPosition(int, int, Monster *);

    public:
        void DrawBaseTile(int, int, int, int);
        void DrawGroundObject(int, int, int, int);
        void DrawOverGroundObject(int, int, int, int, std::function<void(int, int)>);

    public:
        bool Overlap(const DirectiveRectCover &);
        bool Overlap(const Triangle &);

    public:
        void SetViewPoint(int nX, int nY);

    private:
        uint32_t GetDoorImageIndex(int, int);

    private:
        void DrawObject(int, int, int, int,
                std::function<bool(int, int)>,
                std::function<void(int, int)>);
    private:
        uint32_t BaseTileInfo(int, int);
};
