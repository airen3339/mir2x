local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 生死关_D6015
{
    {
        name = '守卫虫',
        loc = {
            {x = 76, y = 170, w = 10, h = 10, count = 20, time = 300, cratio = 0},
        }
    },
    {
        name = '蜈蚣',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 40, time = 600, cratio = 0},
        }
    },
    {
        name = '蝴蝶虫',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 40, time = 600, cratio = 0},
        }
    },
    {
        name = '蝴蝶虫0',
        loc = {
            {x = 100, y = 100, w = 90, h = 90, count = 1, time = 3600, cratio = 0},
        }
    },
    {
        name = '触龙神',
        loc = {
            {x = 83, y = 168, w = 1, h = 1, count = 1, time = 18000, cratio = 0},
        }
    },
    {
        name = '跳跳蜂',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 40, time = 600, cratio = 0},
        }
    },
    {
        name = '跳跳蜂0',
        loc = {
            {x = 100, y = 100, w = 90, h = 90, count = 1, time = 3600, cratio = 0},
        }
    },
    {
        name = '钳虫',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 40, time = 600, cratio = 0},
        }
    },
    {
        name = '钳虫0',
        loc = {
            {x = 100, y = 100, w = 90, h = 90, count = 1, time = 3600, cratio = 0},
        }
    },
    {
        name = '黑色恶蛆',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 40, time = 600, cratio = 0},
        }
    },
})

function main()
    while true do
        coroutine.resume(addMonCo)
        asyncWait(1000 * 5)
    end
end
