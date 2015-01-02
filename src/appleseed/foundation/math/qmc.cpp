
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2015 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "qmc.h"

namespace foundation
{

//
// The first N points of the 4D Halton sequence.
//

const double PrecomputedHaltonSequence[4 * PrecomputedHaltonSequenceSize] =
{
    0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000,
    0.5000000000000000, 0.3333333333333333, 0.2000000000000000, 0.1428571428571429,
    0.2500000000000000, 0.6666666666666666, 0.4000000000000000, 0.2857142857142857,
    0.7500000000000000, 0.1111111111111111, 0.6000000000000001, 0.4285714285714286,
    0.1250000000000000, 0.4444444444444444, 0.8000000000000000, 0.5714285714285714,
    0.6250000000000000, 0.7777777777777777, 0.0400000000000000, 0.7142857142857142,
    0.3750000000000000, 0.2222222222222222, 0.2400000000000000, 0.8571428571428571,
    0.8750000000000000, 0.5555555555555556, 0.4400000000000001, 0.0204081632653061,
    0.0625000000000000, 0.8888888888888888, 0.6400000000000001, 0.1632653061224490,
    0.5625000000000000, 0.0370370370370370, 0.8400000000000001, 0.3061224489795918,
    0.3125000000000000, 0.3703703703703704, 0.0800000000000000, 0.4489795918367347,
    0.8125000000000000, 0.7037037037037037, 0.2800000000000000, 0.5918367346938775,
    0.1875000000000000, 0.1481481481481481, 0.4800000000000000, 0.7346938775510203,
    0.6875000000000000, 0.4814814814814815, 0.6800000000000002, 0.8775510204081632,
    0.4375000000000000, 0.8148148148148147, 0.8800000000000001, 0.0408163265306122,
    0.9375000000000000, 0.2592592592592592, 0.1200000000000000, 0.1836734693877551,
    0.0312500000000000, 0.5925925925925926, 0.3200000000000001, 0.3265306122448979,
    0.5312500000000000, 0.9259259259259258, 0.5200000000000000, 0.4693877551020408,
    0.2812500000000000, 0.0740740740740741, 0.7200000000000001, 0.6122448979591837,
    0.7812500000000000, 0.4074074074074074, 0.9200000000000000, 0.7551020408163265,
    0.1562500000000000, 0.7407407407407407, 0.1600000000000000, 0.8979591836734694,
    0.6562500000000000, 0.1851851851851852, 0.3600000000000000, 0.0612244897959184,
    0.4062500000000000, 0.5185185185185185, 0.5600000000000001, 0.2040816326530612,
    0.9062500000000000, 0.8518518518518518, 0.7600000000000001, 0.3469387755102041,
    0.0937500000000000, 0.2962962962962963, 0.9600000000000001, 0.4897959183673469,
    0.5937500000000000, 0.6296296296296297, 0.0080000000000000, 0.6326530612244897,
    0.3437500000000000, 0.9629629629629629, 0.2080000000000000, 0.7755102040816325,
    0.8437500000000000, 0.0123456790123457, 0.4080000000000000, 0.9183673469387754,
    0.2187500000000000, 0.3456790123456790, 0.6080000000000001, 0.0816326530612245,
    0.7187500000000000, 0.6790123456790123, 0.8080000000000001, 0.2244897959183673,
    0.4687500000000000, 0.1234567901234568, 0.0480000000000000, 0.3673469387755102,
    0.9687500000000000, 0.4567901234567901, 0.2480000000000000, 0.5102040816326531,
    0.0156250000000000, 0.7901234567901234, 0.4480000000000001, 0.6530612244897959,
    0.5156250000000000, 0.2345679012345679, 0.6480000000000001, 0.7959183673469387,
    0.2656250000000000, 0.5679012345679013, 0.8480000000000001, 0.9387755102040816,
    0.7656250000000000, 0.9012345679012346, 0.0880000000000000, 0.1020408163265306,
    0.1406250000000000, 0.0493827160493827, 0.2880000000000000, 0.2448979591836735,
    0.6406250000000000, 0.3827160493827160, 0.4880000000000000, 0.3877551020408163,
    0.3906250000000000, 0.7160493827160495, 0.6880000000000002, 0.5306122448979591,
    0.8906250000000000, 0.1604938271604938, 0.8880000000000001, 0.6734693877551020,
    0.0781250000000000, 0.4938271604938271, 0.1280000000000000, 0.8163265306122448,
    0.5781250000000000, 0.8271604938271604, 0.3280000000000001, 0.9591836734693877,
    0.3281250000000000, 0.2716049382716049, 0.5280000000000000, 0.1224489795918367,
    0.8281250000000000, 0.6049382716049383, 0.7280000000000001, 0.2653061224489796,
    0.2031250000000000, 0.9382716049382716, 0.9280000000000001, 0.4081632653061225,
    0.7031250000000000, 0.0864197530864197, 0.1680000000000000, 0.5510204081632653,
    0.4531250000000000, 0.4197530864197531, 0.3680000000000001, 0.6938775510204082,
    0.9531250000000000, 0.7530864197530864, 0.5680000000000001, 0.8367346938775510,
    0.0468750000000000, 0.1975308641975309, 0.7680000000000001, 0.9795918367346939,
    0.5468750000000000, 0.5308641975308641, 0.9680000000000001, 0.0029154518950437,
    0.2968750000000000, 0.8641975308641974, 0.0160000000000000, 0.1457725947521866,
    0.7968750000000000, 0.3086419753086420, 0.2160000000000000, 0.2886297376093294,
    0.1718750000000000, 0.6419753086419753, 0.4160000000000000, 0.4314868804664723,
    0.6718750000000000, 0.9753086419753085, 0.6160000000000001, 0.5743440233236151,
    0.4218750000000000, 0.0246913580246914, 0.8160000000000001, 0.7172011661807579,
    0.9218750000000000, 0.3580246913580247, 0.0560000000000000, 0.8600583090379008,
    0.1093750000000000, 0.6913580246913580, 0.2560000000000000, 0.0233236151603499,
    0.6093750000000000, 0.1358024691358025, 0.4560000000000001, 0.1661807580174927,
    0.3593750000000000, 0.4691358024691358, 0.6560000000000001, 0.3090379008746356,
    0.8593750000000000, 0.8024691358024690, 0.8560000000000001, 0.4518950437317784,
    0.2343750000000000, 0.2469135802469136, 0.0960000000000000, 0.5947521865889213,
    0.7343750000000000, 0.5802469135802469, 0.2960000000000000, 0.7376093294460641,
    0.4843750000000000, 0.9135802469135802, 0.4960000000000001, 0.8804664723032070,
    0.9843750000000000, 0.0617283950617284, 0.6960000000000002, 0.0437317784256560,
    0.0078125000000000, 0.3950617283950617, 0.8960000000000001, 0.1865889212827988,
    0.5078125000000000, 0.7283950617283951, 0.1360000000000000, 0.3294460641399417,
    0.2578125000000000, 0.1728395061728395, 0.3360000000000001, 0.4723032069970845,
    0.7578125000000000, 0.5061728395061729, 0.5360000000000000, 0.6151603498542274,
    0.1328125000000000, 0.8395061728395060, 0.7360000000000001, 0.7580174927113702,
    0.6328125000000000, 0.2839506172839506, 0.9360000000000001, 0.9008746355685131,
    0.3828125000000000, 0.6172839506172839, 0.1760000000000001, 0.0641399416909621,
    0.8828125000000000, 0.9506172839506172, 0.3760000000000001, 0.2069970845481050,
    0.0703125000000000, 0.0987654320987654, 0.5760000000000001, 0.3498542274052478,
    0.5703125000000000, 0.4320987654320987, 0.7760000000000001, 0.4927113702623907,
    0.3203125000000000, 0.7654320987654321, 0.9760000000000001, 0.6355685131195334,
    0.8203125000000000, 0.2098765432098765, 0.0240000000000000, 0.7784256559766762,
    0.1953125000000000, 0.5432098765432099, 0.2240000000000000, 0.9212827988338191,
    0.6953125000000000, 0.8765432098765431, 0.4240000000000000, 0.0845481049562682,
    0.4453125000000000, 0.3209876543209876, 0.6240000000000001, 0.2274052478134110,
    0.9453125000000000, 0.6543209876543210, 0.8240000000000001, 0.3702623906705539,
    0.0390625000000000, 0.9876543209876543, 0.0640000000000000, 0.5131195335276968,
    0.5390625000000000, 0.0041152263374486, 0.2640000000000000, 0.6559766763848396,
    0.2890625000000000, 0.3374485596707819, 0.4640000000000001, 0.7988338192419824,
    0.7890625000000000, 0.6707818930041152, 0.6640000000000002, 0.9416909620991253,
    0.1640625000000000, 0.1152263374485597, 0.8640000000000001, 0.1049562682215743,
    0.6640625000000000, 0.4485596707818930, 0.1040000000000000, 0.2478134110787172,
    0.4140625000000000, 0.7818930041152262, 0.3040000000000001, 0.3906705539358600,
    0.9140625000000000, 0.2263374485596708, 0.5040000000000000, 0.5335276967930028,
    0.1015625000000000, 0.5596707818930041, 0.7040000000000002, 0.6763848396501457,
    0.6015625000000000, 0.8930041152263374, 0.9040000000000001, 0.8192419825072885,
    0.3515625000000000, 0.0411522633744856, 0.1440000000000000, 0.9620991253644314,
    0.8515625000000000, 0.3744855967078189, 0.3440000000000001, 0.1253644314868805,
    0.2265625000000000, 0.7078189300411523, 0.5440000000000000, 0.2682215743440233,
    0.7265625000000000, 0.1522633744855967, 0.7440000000000001, 0.4110787172011662,
    0.4765625000000000, 0.4855967078189300, 0.9440000000000001, 0.5539358600583090,
    0.9765625000000000, 0.8189300411522632, 0.1840000000000001, 0.6967930029154519,
    0.0234375000000000, 0.2633744855967078, 0.3840000000000001, 0.8396501457725947,
    0.5234375000000000, 0.5967078189300411, 0.5840000000000001, 0.9825072886297376,
    0.2734375000000000, 0.9300411522633744, 0.7840000000000001, 0.0058309037900875,
    0.7734375000000000, 0.0781893004115226, 0.9840000000000001, 0.1486880466472303,
    0.1484375000000000, 0.4115226337448559, 0.0320000000000000, 0.2915451895043731,
    0.6484375000000000, 0.7448559670781892, 0.2320000000000000, 0.4344023323615160,
    0.3984375000000000, 0.1893004115226337, 0.4320000000000001, 0.5772594752186588,
    0.8984375000000000, 0.5226337448559670, 0.6320000000000001, 0.7201166180758016,
    0.0859375000000000, 0.8559670781893003, 0.8320000000000001, 0.8629737609329445,
    0.5859375000000000, 0.3004115226337448, 0.0720000000000000, 0.0262390670553936,
    0.3359375000000000, 0.6337448559670782, 0.2720000000000000, 0.1690962099125364,
    0.8359375000000000, 0.9670781893004115, 0.4720000000000001, 0.3119533527696793,
    0.2109375000000000, 0.0164609053497942, 0.6720000000000002, 0.4548104956268221,
    0.7109375000000000, 0.3497942386831275, 0.8720000000000001, 0.5976676384839650,
    0.4609375000000000, 0.6831275720164608, 0.1120000000000000, 0.7405247813411078,
    0.9609375000000000, 0.1275720164609054, 0.3120000000000001, 0.8833819241982507,
    0.0546875000000000, 0.4609053497942386, 0.5120000000000000, 0.0466472303206997,
    0.5546875000000000, 0.7942386831275720, 0.7120000000000002, 0.1895043731778426,
    0.3046875000000000, 0.2386831275720165, 0.9120000000000001, 0.3323615160349854,
    0.8046875000000000, 0.5720164609053499, 0.1520000000000000, 0.4752186588921282,
    0.1796875000000000, 0.9053497942386831, 0.3520000000000001, 0.6180758017492711,
    0.6796875000000000, 0.0534979423868313, 0.5520000000000001, 0.7609329446064139,
    0.4296875000000000, 0.3868312757201646, 0.7520000000000001, 0.9037900874635568,
    0.9296875000000000, 0.7201646090534980, 0.9520000000000001, 0.0670553935860058,
    0.1171875000000000, 0.1646090534979424, 0.1920000000000000, 0.2099125364431487,
    0.6171875000000000, 0.4979423868312757, 0.3920000000000001, 0.3527696793002915,
    0.3671875000000000, 0.8312757201646089, 0.5920000000000001, 0.4956268221574344,
    0.8671875000000000, 0.2757201646090535, 0.7920000000000002, 0.6384839650145772,
    0.2421875000000000, 0.6090534979423868, 0.9920000000000001, 0.7813411078717200,
    0.7421875000000000, 0.9423868312757201, 0.0016000000000000, 0.9241982507288629,
    0.4921875000000000, 0.0905349794238683, 0.2016000000000000, 0.0874635568513119,
    0.9921875000000000, 0.4238683127572016, 0.4016000000000000, 0.2303206997084548,
    0.0039062500000000, 0.7572016460905350, 0.6016000000000001, 0.3731778425655976,
    0.5039062500000000, 0.2016460905349794, 0.8016000000000001, 0.5160349854227405,
    0.2539062500000000, 0.5349794238683127, 0.0416000000000000, 0.6588921282798833,
    0.7539062500000000, 0.8683127572016459, 0.2416000000000000, 0.8017492711370261,
    0.1289062500000000, 0.3127572016460905, 0.4416000000000001, 0.9446064139941690,
    0.6289062500000000, 0.6460905349794238, 0.6416000000000002, 0.1078717201166181,
    0.3789062500000000, 0.9794238683127571, 0.8416000000000001, 0.2507288629737609,
    0.8789062500000000, 0.0288065843621399, 0.0816000000000000, 0.3935860058309038,
    0.0664062500000000, 0.3621399176954732, 0.2816000000000000, 0.5364431486880465,
    0.5664062500000000, 0.6954732510288065, 0.4816000000000000, 0.6793002915451895,
    0.3164062500000000, 0.1399176954732510, 0.6816000000000002, 0.8221574344023322,
    0.8164062500000000, 0.4732510288065843, 0.8816000000000002, 0.9650145772594752,
    0.1914062500000000, 0.8065843621399176, 0.1216000000000000, 0.1282798833819242,
    0.6914062500000000, 0.2510288065843621, 0.3216000000000001, 0.2711370262390670,
    0.4414062500000000, 0.5843621399176955, 0.5216000000000001, 0.4139941690962099,
    0.9414062500000000, 0.9176954732510287, 0.7216000000000001, 0.5568513119533527,
    0.0351562500000000, 0.0658436213991769, 0.9216000000000001, 0.6997084548104956,
    0.5351562500000000, 0.3991769547325103, 0.1616000000000000, 0.8425655976676384,
    0.2851562500000000, 0.7325102880658436, 0.3616000000000000, 0.9854227405247813,
    0.7851562500000000, 0.1769547325102881, 0.5616000000000001, 0.0087463556851312,
    0.1601562500000000, 0.5102880658436214, 0.7616000000000002, 0.1516034985422740,
    0.6601562500000000, 0.8436213991769546, 0.9616000000000001, 0.2944606413994169,
    0.4101562500000000, 0.2880658436213991, 0.0096000000000000, 0.4373177842565598,
    0.9101562500000000, 0.6213991769547325, 0.2096000000000000, 0.5801749271137026,
    0.0976562500000000, 0.9547325102880657, 0.4096000000000000, 0.7230320699708454,
    0.5976562500000000, 0.1028806584362140, 0.6096000000000001, 0.8658892128279883,
    0.3476562500000000, 0.4362139917695473, 0.8096000000000001, 0.0291545189504373,
    0.8476562500000000, 0.7695473251028806, 0.0496000000000000, 0.1720116618075802,
    0.2226562500000000, 0.2139917695473251, 0.2496000000000000, 0.3148688046647231,
    0.7226562500000000, 0.5473251028806584, 0.4496000000000001, 0.4577259475218659,
    0.4726562500000000, 0.8806584362139917, 0.6496000000000002, 0.6005830903790087,
    0.9726562500000000, 0.3251028806584362, 0.8496000000000001, 0.7434402332361515,
    0.0195312500000000, 0.6584362139917696, 0.0896000000000000, 0.8862973760932944,
    0.5195312500000000, 0.9917695473251028, 0.2896000000000000, 0.0495626822157434,
    0.2695312500000000, 0.0082304526748971, 0.4896000000000000, 0.1924198250728863,
    0.7695312500000000, 0.3415637860082305, 0.6896000000000002, 0.3352769679300292,
    0.1445312500000000, 0.6748971193415637, 0.8896000000000002, 0.4781341107871720,
    0.6445312500000000, 0.1193415637860082, 0.1296000000000000, 0.6209912536443148,
    0.3945312500000000, 0.4526748971193416, 0.3296000000000001, 0.7638483965014576,
    0.8945312500000000, 0.7860082304526748, 0.5296000000000001, 0.9067055393586005,
    0.0820312500000000, 0.2304526748971193, 0.7296000000000001, 0.0699708454810496,
    0.5820312500000000, 0.5637860082304527, 0.9296000000000001, 0.2128279883381924,
    0.3320312500000000, 0.8971193415637859, 0.1696000000000000, 0.3556851311953353,
    0.8320312500000000, 0.0452674897119342, 0.3696000000000000, 0.4985422740524781,
    0.2070312500000000, 0.3786008230452675, 0.5696000000000001, 0.6413994169096209,
    0.7070312500000000, 0.7119341563786008, 0.7696000000000002, 0.7842565597667637,
    0.4570312500000000, 0.1563786008230453, 0.9696000000000001, 0.9271137026239066,
    0.9570312500000000, 0.4897119341563786, 0.0176000000000000, 0.0903790087463557,
    0.0507812500000000, 0.8230452674897117, 0.2176000000000000, 0.2332361516034985,
    0.5507812500000000, 0.2674897119341564, 0.4176000000000000, 0.3760932944606414,
    0.3007812500000000, 0.6008230452674896, 0.6176000000000002, 0.5189504373177842,
    0.8007812500000000, 0.9341563786008229, 0.8176000000000001, 0.6618075801749270,
    0.1757812500000000, 0.0823045267489712, 0.0576000000000000, 0.8046647230320698,
    0.6757812500000000, 0.4156378600823045, 0.2576000000000000, 0.9475218658892127,
    0.4257812500000000, 0.7489711934156378, 0.4576000000000001, 0.1107871720116618,
    0.9257812500000000, 0.1934156378600823, 0.6576000000000002, 0.2536443148688047,
    0.1132812500000000, 0.5267489711934156, 0.8576000000000001, 0.3965014577259475,
    0.6132812500000000, 0.8600823045267488, 0.0976000000000000, 0.5393586005830903,
    0.3632812500000000, 0.3045267489711934, 0.2976000000000000, 0.6822157434402332,
    0.8632812500000000, 0.6378600823045267, 0.4976000000000000, 0.8250728862973760,
    0.2382812500000000, 0.9711934156378600, 0.6976000000000002, 0.9679300291545189,
    0.7382812500000000, 0.0205761316872428, 0.8976000000000002, 0.1311953352769679,
    0.4882812500000000, 0.3539094650205761, 0.1376000000000000, 0.2740524781341108,
    0.9882812500000000, 0.6872427983539093, 0.3376000000000001, 0.4169096209912537,
    0.0117187500000000, 0.1316872427983539, 0.5376000000000001, 0.5597667638483964,
    0.5117187500000000, 0.4650205761316872, 0.7376000000000001, 0.7026239067055393,
    0.2617187500000000, 0.7983539094650205, 0.9376000000000001, 0.8454810495626821,
    0.7617187500000000, 0.2427983539094650, 0.1776000000000000, 0.9883381924198250,
    0.1367187500000000, 0.5761316872427984, 0.3776000000000001, 0.0116618075801749,
    0.6367187500000000, 0.9094650205761317, 0.5776000000000001, 0.1545189504373178,
    0.3867187500000000, 0.0576131687242798, 0.7776000000000002, 0.2973760932944606,
    0.8867187500000000, 0.3909465020576132, 0.9776000000000001, 0.4402332361516035,
    0.0742187500000000, 0.7242798353909465, 0.0256000000000000, 0.5830903790087463,
    0.5742187500000000, 0.1687242798353909, 0.2256000000000000, 0.7259475218658891,
    0.3242187500000000, 0.5020576131687242, 0.4256000000000000, 0.8688046647230320,
    0.8242187500000000, 0.8353909465020575, 0.6256000000000002, 0.0320699708454810,
    0.1992187500000000, 0.2798353909465021, 0.8256000000000001, 0.1749271137026239,
    0.6992187500000000, 0.6131687242798354, 0.0656000000000000, 0.3177842565597668,
    0.4492187500000000, 0.9465020576131686, 0.2656000000000000, 0.4606413994169096,
    0.9492187500000000, 0.0946502057613169, 0.4656000000000001, 0.6034985422740524,
    0.0429687500000000, 0.4279835390946502, 0.6656000000000002, 0.7463556851311952,
    0.5429687500000000, 0.7613168724279835, 0.8656000000000002, 0.8892128279883381,
    0.2929687500000000, 0.2057613168724280, 0.1056000000000000, 0.0524781341107872,
    0.7929687500000000, 0.5390946502057612, 0.3056000000000000, 0.1953352769679300,
    0.1679687500000000, 0.8724279835390945, 0.5056000000000001, 0.3381924198250729,
    0.6679687500000000, 0.3168724279835391, 0.7056000000000002, 0.4810495626822157,
    0.4179687500000000, 0.6502057613168724, 0.9056000000000002, 0.6239067055393586,
    0.9179687500000000, 0.9835390946502056, 0.1456000000000000, 0.7667638483965014,
    0.1054687500000000, 0.0329218106995885, 0.3456000000000001, 0.9096209912536443,
    0.6054687500000000, 0.3662551440329218, 0.5456000000000001, 0.0728862973760933,
    0.3554687500000000, 0.6995884773662551, 0.7456000000000002, 0.2157434402332362,
    0.8554687500000000, 0.1440329218106996, 0.9456000000000001, 0.3586005830903790,
    0.2304687500000000, 0.4773662551440329, 0.1856000000000000, 0.5014577259475218,
    0.7304687500000000, 0.8106995884773661, 0.3856000000000001, 0.6443148688046646,
    0.4804687500000000, 0.2551440329218107, 0.5856000000000001, 0.7871720116618074,
    0.9804687500000000, 0.5884773662551440, 0.7856000000000002, 0.9300291545189503,
    0.0273437500000000, 0.9218106995884773, 0.9856000000000001, 0.0932944606413994,
    0.5273437500000000, 0.0699588477366255, 0.0336000000000000, 0.2361516034985423,
    0.2773437500000000, 0.4032921810699588, 0.2336000000000000, 0.3790087463556851,
    0.7773437500000000, 0.7366255144032922, 0.4336000000000000, 0.5218658892128280,
    0.1523437500000000, 0.1810699588477366, 0.6336000000000002, 0.6647230320699707,
    0.6523437500000000, 0.5144032921810700, 0.8336000000000001, 0.8075801749271135,
    0.4023437500000000, 0.8477366255144031, 0.0736000000000000, 0.9504373177842564,
    0.9023437500000000, 0.2921810699588477, 0.2736000000000000, 0.1137026239067055,
    0.0898437500000000, 0.6255144032921810, 0.4736000000000001, 0.2565597667638484,
    0.5898437500000000, 0.9588477366255143, 0.6736000000000002, 0.3994169096209913,
    0.3398437500000000, 0.1069958847736626, 0.8736000000000002, 0.5422740524781340,
    0.8398437500000000, 0.4403292181069959, 0.1136000000000000, 0.6851311953352769,
    0.2148437500000000, 0.7736625514403291, 0.3136000000000001, 0.8279883381924197,
    0.7148437500000000, 0.2181069958847736, 0.5136000000000001, 0.9708454810495626,
    0.4648437500000000, 0.5514403292181069, 0.7136000000000002, 0.1341107871720117,
    0.9648437500000000, 0.8847736625514402, 0.9136000000000002, 0.2769679300291545,
    0.0585937500000000, 0.3292181069958848, 0.1536000000000000, 0.4198250728862974,
    0.5585937500000000, 0.6625514403292181, 0.3536000000000001, 0.5626822157434401,
    0.3085937500000000, 0.9958847736625514, 0.5536000000000001, 0.7055393586005830,
    0.8085937500000000, 0.0013717421124829, 0.7536000000000002, 0.8483965014577258,
    0.1835937500000000, 0.3347050754458162, 0.9536000000000001, 0.9912536443148687,
    0.6835937500000000, 0.6680384087791494, 0.1936000000000000, 0.0145772594752187,
    0.4335937500000000, 0.1124828532235940, 0.3936000000000001, 0.1574344023323615,
    0.9335937500000000, 0.4458161865569273, 0.5936000000000001, 0.3002915451895044,
    0.1210937500000000, 0.7791495198902605, 0.7936000000000002, 0.4431486880466472,
    0.6210937500000000, 0.2235939643347051, 0.9936000000000002, 0.5860058309037901,
    0.3710937500000000, 0.5569272976680384, 0.0032000000000000, 0.7288629737609329,
    0.8710937500000000, 0.8902606310013717, 0.2032000000000000, 0.8717201166180758,
    0.2460937500000000, 0.0384087791495199, 0.4032000000000000, 0.0349854227405248,
    0.7460937500000000, 0.3717421124828532, 0.6032000000000001, 0.1778425655976676,
    0.4960937500000000, 0.7050754458161865, 0.8032000000000000, 0.3206997084548105,
    0.9960937500000000, 0.1495198902606310, 0.0432000000000000, 0.4635568513119533
};

}   // namespace foundation
