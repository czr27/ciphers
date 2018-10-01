/* SEED Cipher
Copyright (C) Hye-Shik Chang.
Copyright (C) Kim Hyun.
Copyright (C) 2007 Korea Information Security Agency (KISA).
Copyright (C) 2011-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#if defined(CIPHER_SEED_HIDE_API)
#	define CIPHER_SEED_API static
#elif defined(CIPHER_SEED_STATIC)
#	define CIPHER_SEED_API
#else
#	define CIPHER_SEED_API Z_API_EXPORT
#endif

#if defined(CIPHER_SEED_HIDE_ABI)
#	define CIPHER_SEED_ABI static
#elif defined(CIPHER_SEED_STATIC)
#	define CIPHER_SEED_ABI
#else
#	define CIPHER_SEED_ABI Z_API_EXPORT
#endif

#define CIPHER_SEED_OMIT_FUNCTION_PROTOTYPES

#if defined(CIPHER_SEED_USE_LOCAL_HEADER)
#	include "SEED.h"
#else
#	include <cipher/SEED.h>
#endif

#include <Z/functions/base/value.h>

#define K_CONSTANT_COUNT 16

#define C(value) Z_UINT32(0x##value)

static zuint32 const ss0[256] = {
	C(2989A1A8), C(05858184), C(16C6D2D4), C(13C3D3D0),
	C(14445054), C(1D0D111C), C(2C8CA0AC), C(25052124),
	C(1D4D515C), C(03434340), C(18081018), C(1E0E121C),
	C(11415150), C(3CCCF0FC), C(0ACAC2C8), C(23436360),
	C(28082028), C(04444044), C(20002020), C(1D8D919C),
	C(20C0E0E0), C(22C2E2E0), C(08C8C0C8), C(17071314),
	C(2585A1A4), C(0F8F838C), C(03030300), C(3B4B7378),
	C(3B8BB3B8), C(13031310), C(12C2D2D0), C(2ECEE2EC),
	C(30407070), C(0C8C808C), C(3F0F333C), C(2888A0A8),
	C(32023230), C(1DCDD1DC), C(36C6F2F4), C(34447074),
	C(2CCCE0EC), C(15859194), C(0B0B0308), C(17475354),
	C(1C4C505C), C(1B4B5358), C(3D8DB1BC), C(01010100),
	C(24042024), C(1C0C101C), C(33437370), C(18889098),
	C(10001010), C(0CCCC0CC), C(32C2F2F0), C(19C9D1D8),
	C(2C0C202C), C(27C7E3E4), C(32427270), C(03838380),
	C(1B8B9398), C(11C1D1D0), C(06868284), C(09C9C1C8),
	C(20406060), C(10405050), C(2383A3A0), C(2BCBE3E8),
	C(0D0D010C), C(3686B2B4), C(1E8E929C), C(0F4F434C),
	C(3787B3B4), C(1A4A5258), C(06C6C2C4), C(38487078),
	C(2686A2A4), C(12021210), C(2F8FA3AC), C(15C5D1D4),
	C(21416160), C(03C3C3C0), C(3484B0B4), C(01414140),
	C(12425250), C(3D4D717C), C(0D8D818C), C(08080008),
	C(1F0F131C), C(19899198), C(00000000), C(19091118),
	C(04040004), C(13435350), C(37C7F3F4), C(21C1E1E0),
	C(3DCDF1FC), C(36467274), C(2F0F232C), C(27072324),
	C(3080B0B0), C(0B8B8388), C(0E0E020C), C(2B8BA3A8),
	C(2282A2A0), C(2E4E626C), C(13839390), C(0D4D414C),
	C(29496168), C(3C4C707C), C(09090108), C(0A0A0208),
	C(3F8FB3BC), C(2FCFE3EC), C(33C3F3F0), C(05C5C1C4),
	C(07878384), C(14041014), C(3ECEF2FC), C(24446064),
	C(1ECED2DC), C(2E0E222C), C(0B4B4348), C(1A0A1218),
	C(06060204), C(21012120), C(2B4B6368), C(26466264),
	C(02020200), C(35C5F1F4), C(12829290), C(0A8A8288),
	C(0C0C000C), C(3383B3B0), C(3E4E727C), C(10C0D0D0),
	C(3A4A7278), C(07474344), C(16869294), C(25C5E1E4),
	C(26062224), C(00808080), C(2D8DA1AC), C(1FCFD3DC),
	C(2181A1A0), C(30003030), C(37073334), C(2E8EA2AC),
	C(36063234), C(15051114), C(22022220), C(38083038),
	C(34C4F0F4), C(2787A3A4), C(05454144), C(0C4C404C),
	C(01818180), C(29C9E1E8), C(04848084), C(17879394),
	C(35053134), C(0BCBC3C8), C(0ECEC2CC), C(3C0C303C),
	C(31417170), C(11011110), C(07C7C3C4), C(09898188),
	C(35457174), C(3BCBF3F8), C(1ACAD2D8), C(38C8F0F8),
	C(14849094), C(19495158), C(02828280), C(04C4C0C4),
	C(3FCFF3FC), C(09494148), C(39093138), C(27476364),
	C(00C0C0C0), C(0FCFC3CC), C(17C7D3D4), C(3888B0B8),
	C(0F0F030C), C(0E8E828C), C(02424240), C(23032320),
	C(11819190), C(2C4C606C), C(1BCBD3D8), C(2484A0A4),
	C(34043034), C(31C1F1F0), C(08484048), C(02C2C2C0),
	C(2F4F636C), C(3D0D313C), C(2D0D212C), C(00404040),
	C(3E8EB2BC), C(3E0E323C), C(3C8CB0BC), C(01C1C1C0),
	C(2A8AA2A8), C(3A8AB2B8), C(0E4E424C), C(15455154),
	C(3B0B3338), C(1CCCD0DC), C(28486068), C(3F4F737C),
	C(1C8C909C), C(18C8D0D8), C(0A4A4248), C(16465254),
	C(37477374), C(2080A0A0), C(2DCDE1EC), C(06464244),
	C(3585B1B4), C(2B0B2328), C(25456164), C(3ACAF2F8),
	C(23C3E3E0), C(3989B1B8), C(3181B1B0), C(1F8F939C),
	C(1E4E525C), C(39C9F1F8), C(26C6E2E4), C(3282B2B0),
	C(31013130), C(2ACAE2E8), C(2D4D616C), C(1F4F535C),
	C(24C4E0E4), C(30C0F0F0), C(0DCDC1CC), C(08888088),
	C(16061214), C(3A0A3238), C(18485058), C(14C4D0D4),
	C(22426260), C(29092128), C(07070304), C(33033330),
	C(28C8E0E8), C(1B0B1318), C(05050104), C(39497178),
	C(10809090), C(2A4A6268), C(2A0A2228), C(1A8A9298)
};

static zuint32 const ss1[256] = {
	C(38380830), C(E828C8E0), C(2C2D0D21), C(A42686A2),
	C(CC0FCFC3), C(DC1ECED2), C(B03383B3), C(B83888B0),
	C(AC2F8FA3), C(60204060), C(54154551), C(C407C7C3),
	C(44044440), C(6C2F4F63), C(682B4B63), C(581B4B53),
	C(C003C3C3), C(60224262), C(30330333), C(B43585B1),
	C(28290921), C(A02080A0), C(E022C2E2), C(A42787A3),
	C(D013C3D3), C(90118191), C(10110111), C(04060602),
	C(1C1C0C10), C(BC3C8CB0), C(34360632), C(480B4B43),
	C(EC2FCFE3), C(88088880), C(6C2C4C60), C(A82888A0),
	C(14170713), C(C404C4C0), C(14160612), C(F434C4F0),
	C(C002C2C2), C(44054541), C(E021C1E1), C(D416C6D2),
	C(3C3F0F33), C(3C3D0D31), C(8C0E8E82), C(98188890),
	C(28280820), C(4C0E4E42), C(F436C6F2), C(3C3E0E32),
	C(A42585A1), C(F839C9F1), C(0C0D0D01), C(DC1FCFD3),
	C(D818C8D0), C(282B0B23), C(64264662), C(783A4A72),
	C(24270723), C(2C2F0F23), C(F031C1F1), C(70324272),
	C(40024242), C(D414C4D0), C(40014141), C(C000C0C0),
	C(70334373), C(64274763), C(AC2C8CA0), C(880B8B83),
	C(F437C7F3), C(AC2D8DA1), C(80008080), C(1C1F0F13),
	C(C80ACAC2), C(2C2C0C20), C(A82A8AA2), C(34340430),
	C(D012C2D2), C(080B0B03), C(EC2ECEE2), C(E829C9E1),
	C(5C1D4D51), C(94148490), C(18180810), C(F838C8F0),
	C(54174753), C(AC2E8EA2), C(08080800), C(C405C5C1),
	C(10130313), C(CC0DCDC1), C(84068682), C(B83989B1),
	C(FC3FCFF3), C(7C3D4D71), C(C001C1C1), C(30310131),
	C(F435C5F1), C(880A8A82), C(682A4A62), C(B03181B1),
	C(D011C1D1), C(20200020), C(D417C7D3), C(00020202),
	C(20220222), C(04040400), C(68284860), C(70314171),
	C(04070703), C(D81BCBD3), C(9C1D8D91), C(98198991),
	C(60214161), C(BC3E8EB2), C(E426C6E2), C(58194951),
	C(DC1DCDD1), C(50114151), C(90108090), C(DC1CCCD0),
	C(981A8A92), C(A02383A3), C(A82B8BA3), C(D010C0D0),
	C(80018181), C(0C0F0F03), C(44074743), C(181A0A12),
	C(E023C3E3), C(EC2CCCE0), C(8C0D8D81), C(BC3F8FB3),
	C(94168692), C(783B4B73), C(5C1C4C50), C(A02282A2),
	C(A02181A1), C(60234363), C(20230323), C(4C0D4D41),
	C(C808C8C0), C(9C1E8E92), C(9C1C8C90), C(383A0A32),
	C(0C0C0C00), C(2C2E0E22), C(B83A8AB2), C(6C2E4E62),
	C(9C1F8F93), C(581A4A52), C(F032C2F2), C(90128292),
	C(F033C3F3), C(48094941), C(78384870), C(CC0CCCC0),
	C(14150511), C(F83BCBF3), C(70304070), C(74354571),
	C(7C3F4F73), C(34350531), C(10100010), C(00030303),
	C(64244460), C(6C2D4D61), C(C406C6C2), C(74344470),
	C(D415C5D1), C(B43484B0), C(E82ACAE2), C(08090901),
	C(74364672), C(18190911), C(FC3ECEF2), C(40004040),
	C(10120212), C(E020C0E0), C(BC3D8DB1), C(04050501),
	C(F83ACAF2), C(00010101), C(F030C0F0), C(282A0A22),
	C(5C1E4E52), C(A82989A1), C(54164652), C(40034343),
	C(84058581), C(14140410), C(88098981), C(981B8B93),
	C(B03080B0), C(E425C5E1), C(48084840), C(78394971),
	C(94178793), C(FC3CCCF0), C(1C1E0E12), C(80028282),
	C(20210121), C(8C0C8C80), C(181B0B13), C(5C1F4F53),
	C(74374773), C(54144450), C(B03282B2), C(1C1D0D11),
	C(24250521), C(4C0F4F43), C(00000000), C(44064642),
	C(EC2DCDE1), C(58184850), C(50124252), C(E82BCBE3),
	C(7C3E4E72), C(D81ACAD2), C(C809C9C1), C(FC3DCDF1),
	C(30300030), C(94158591), C(64254561), C(3C3C0C30),
	C(B43686B2), C(E424C4E0), C(B83B8BB3), C(7C3C4C70),
	C(0C0E0E02), C(50104050), C(38390931), C(24260622),
	C(30320232), C(84048480), C(68294961), C(90138393),
	C(34370733), C(E427C7E3), C(24240420), C(A42484A0),
	C(C80BCBC3), C(50134353), C(080A0A02), C(84078783),
	C(D819C9D1), C(4C0C4C40), C(80038383), C(8C0F8F83),
	C(CC0ECEC2), C(383B0B33), C(480A4A42), C(B43787B3)
};

static zuint32 const ss2[256] = {
	C(A1A82989), C(81840585), C(D2D416C6), C(D3D013C3),
	C(50541444), C(111C1D0D), C(A0AC2C8C), C(21242505),
	C(515C1D4D), C(43400343), C(10181808), C(121C1E0E),
	C(51501141), C(F0FC3CCC), C(C2C80ACA), C(63602343),
	C(20282808), C(40440444), C(20202000), C(919C1D8D),
	C(E0E020C0), C(E2E022C2), C(C0C808C8), C(13141707),
	C(A1A42585), C(838C0F8F), C(03000303), C(73783B4B),
	C(B3B83B8B), C(13101303), C(D2D012C2), C(E2EC2ECE),
	C(70703040), C(808C0C8C), C(333C3F0F), C(A0A82888),
	C(32303202), C(D1DC1DCD), C(F2F436C6), C(70743444),
	C(E0EC2CCC), C(91941585), C(03080B0B), C(53541747),
	C(505C1C4C), C(53581B4B), C(B1BC3D8D), C(01000101),
	C(20242404), C(101C1C0C), C(73703343), C(90981888),
	C(10101000), C(C0CC0CCC), C(F2F032C2), C(D1D819C9),
	C(202C2C0C), C(E3E427C7), C(72703242), C(83800383),
	C(93981B8B), C(D1D011C1), C(82840686), C(C1C809C9),
	C(60602040), C(50501040), C(A3A02383), C(E3E82BCB),
	C(010C0D0D), C(B2B43686), C(929C1E8E), C(434C0F4F),
	C(B3B43787), C(52581A4A), C(C2C406C6), C(70783848),
	C(A2A42686), C(12101202), C(A3AC2F8F), C(D1D415C5),
	C(61602141), C(C3C003C3), C(B0B43484), C(41400141),
	C(52501242), C(717C3D4D), C(818C0D8D), C(00080808),
	C(131C1F0F), C(91981989), C(00000000), C(11181909),
	C(00040404), C(53501343), C(F3F437C7), C(E1E021C1),
	C(F1FC3DCD), C(72743646), C(232C2F0F), C(23242707),
	C(B0B03080), C(83880B8B), C(020C0E0E), C(A3A82B8B),
	C(A2A02282), C(626C2E4E), C(93901383), C(414C0D4D),
	C(61682949), C(707C3C4C), C(01080909), C(02080A0A),
	C(B3BC3F8F), C(E3EC2FCF), C(F3F033C3), C(C1C405C5),
	C(83840787), C(10141404), C(F2FC3ECE), C(60642444),
	C(D2DC1ECE), C(222C2E0E), C(43480B4B), C(12181A0A),
	C(02040606), C(21202101), C(63682B4B), C(62642646),
	C(02000202), C(F1F435C5), C(92901282), C(82880A8A),
	C(000C0C0C), C(B3B03383), C(727C3E4E), C(D0D010C0),
	C(72783A4A), C(43440747), C(92941686), C(E1E425C5),
	C(22242606), C(80800080), C(A1AC2D8D), C(D3DC1FCF),
	C(A1A02181), C(30303000), C(33343707), C(A2AC2E8E),
	C(32343606), C(11141505), C(22202202), C(30383808),
	C(F0F434C4), C(A3A42787), C(41440545), C(404C0C4C),
	C(81800181), C(E1E829C9), C(80840484), C(93941787),
	C(31343505), C(C3C80BCB), C(C2CC0ECE), C(303C3C0C),
	C(71703141), C(11101101), C(C3C407C7), C(81880989),
	C(71743545), C(F3F83BCB), C(D2D81ACA), C(F0F838C8),
	C(90941484), C(51581949), C(82800282), C(C0C404C4),
	C(F3FC3FCF), C(41480949), C(31383909), C(63642747),
	C(C0C000C0), C(C3CC0FCF), C(D3D417C7), C(B0B83888),
	C(030C0F0F), C(828C0E8E), C(42400242), C(23202303),
	C(91901181), C(606C2C4C), C(D3D81BCB), C(A0A42484),
	C(30343404), C(F1F031C1), C(40480848), C(C2C002C2),
	C(636C2F4F), C(313C3D0D), C(212C2D0D), C(40400040),
	C(B2BC3E8E), C(323C3E0E), C(B0BC3C8C), C(C1C001C1),
	C(A2A82A8A), C(B2B83A8A), C(424C0E4E), C(51541545),
	C(33383B0B), C(D0DC1CCC), C(60682848), C(737C3F4F),
	C(909C1C8C), C(D0D818C8), C(42480A4A), C(52541646),
	C(73743747), C(A0A02080), C(E1EC2DCD), C(42440646),
	C(B1B43585), C(23282B0B), C(61642545), C(F2F83ACA),
	C(E3E023C3), C(B1B83989), C(B1B03181), C(939C1F8F),
	C(525C1E4E), C(F1F839C9), C(E2E426C6), C(B2B03282),
	C(31303101), C(E2E82ACA), C(616C2D4D), C(535C1F4F),
	C(E0E424C4), C(F0F030C0), C(C1CC0DCD), C(80880888),
	C(12141606), C(32383A0A), C(50581848), C(D0D414C4),
	C(62602242), C(21282909), C(03040707), C(33303303),
	C(E0E828C8), C(13181B0B), C(01040505), C(71783949),
	C(90901080), C(62682A4A), C(22282A0A), C(92981A8A)
};

static zuint32 const ss3[256] = {
	C(08303838), C(C8E0E828), C(0D212C2D), C(86A2A426),
	C(CFC3CC0F), C(CED2DC1E), C(83B3B033), C(88B0B838),
	C(8FA3AC2F), C(40606020), C(45515415), C(C7C3C407),
	C(44404404), C(4F636C2F), C(4B63682B), C(4B53581B),
	C(C3C3C003), C(42626022), C(03333033), C(85B1B435),
	C(09212829), C(80A0A020), C(C2E2E022), C(87A3A427),
	C(C3D3D013), C(81919011), C(01111011), C(06020406),
	C(0C101C1C), C(8CB0BC3C), C(06323436), C(4B43480B),
	C(CFE3EC2F), C(88808808), C(4C606C2C), C(88A0A828),
	C(07131417), C(C4C0C404), C(06121416), C(C4F0F434),
	C(C2C2C002), C(45414405), C(C1E1E021), C(C6D2D416),
	C(0F333C3F), C(0D313C3D), C(8E828C0E), C(88909818),
	C(08202828), C(4E424C0E), C(C6F2F436), C(0E323C3E),
	C(85A1A425), C(C9F1F839), C(0D010C0D), C(CFD3DC1F),
	C(C8D0D818), C(0B23282B), C(46626426), C(4A72783A),
	C(07232427), C(0F232C2F), C(C1F1F031), C(42727032),
	C(42424002), C(C4D0D414), C(41414001), C(C0C0C000),
	C(43737033), C(47636427), C(8CA0AC2C), C(8B83880B),
	C(C7F3F437), C(8DA1AC2D), C(80808000), C(0F131C1F),
	C(CAC2C80A), C(0C202C2C), C(8AA2A82A), C(04303434),
	C(C2D2D012), C(0B03080B), C(CEE2EC2E), C(C9E1E829),
	C(4D515C1D), C(84909414), C(08101818), C(C8F0F838),
	C(47535417), C(8EA2AC2E), C(08000808), C(C5C1C405),
	C(03131013), C(CDC1CC0D), C(86828406), C(89B1B839),
	C(CFF3FC3F), C(4D717C3D), C(C1C1C001), C(01313031),
	C(C5F1F435), C(8A82880A), C(4A62682A), C(81B1B031),
	C(C1D1D011), C(00202020), C(C7D3D417), C(02020002),
	C(02222022), C(04000404), C(48606828), C(41717031),
	C(07030407), C(CBD3D81B), C(8D919C1D), C(89919819),
	C(41616021), C(8EB2BC3E), C(C6E2E426), C(49515819),
	C(CDD1DC1D), C(41515011), C(80909010), C(CCD0DC1C),
	C(8A92981A), C(83A3A023), C(8BA3A82B), C(C0D0D010),
	C(81818001), C(0F030C0F), C(47434407), C(0A12181A),
	C(C3E3E023), C(CCE0EC2C), C(8D818C0D), C(8FB3BC3F),
	C(86929416), C(4B73783B), C(4C505C1C), C(82A2A022),
	C(81A1A021), C(43636023), C(03232023), C(4D414C0D),
	C(C8C0C808), C(8E929C1E), C(8C909C1C), C(0A32383A),
	C(0C000C0C), C(0E222C2E), C(8AB2B83A), C(4E626C2E),
	C(8F939C1F), C(4A52581A), C(C2F2F032), C(82929012),
	C(C3F3F033), C(49414809), C(48707838), C(CCC0CC0C),
	C(05111415), C(CBF3F83B), C(40707030), C(45717435),
	C(4F737C3F), C(05313435), C(00101010), C(03030003),
	C(44606424), C(4D616C2D), C(C6C2C406), C(44707434),
	C(C5D1D415), C(84B0B434), C(CAE2E82A), C(09010809),
	C(46727436), C(09111819), C(CEF2FC3E), C(40404000),
	C(02121012), C(C0E0E020), C(8DB1BC3D), C(05010405),
	C(CAF2F83A), C(01010001), C(C0F0F030), C(0A22282A),
	C(4E525C1E), C(89A1A829), C(46525416), C(43434003),
	C(85818405), C(04101414), C(89818809), C(8B93981B),
	C(80B0B030), C(C5E1E425), C(48404808), C(49717839),
	C(87939417), C(CCF0FC3C), C(0E121C1E), C(82828002),
	C(01212021), C(8C808C0C), C(0B13181B), C(4F535C1F),
	C(47737437), C(44505414), C(82B2B032), C(0D111C1D),
	C(05212425), C(4F434C0F), C(00000000), C(46424406),
	C(CDE1EC2D), C(48505818), C(42525012), C(CBE3E82B),
	C(4E727C3E), C(CAD2D81A), C(C9C1C809), C(CDF1FC3D),
	C(00303030), C(85919415), C(45616425), C(0C303C3C),
	C(86B2B436), C(C4E0E424), C(8BB3B83B), C(4C707C3C),
	C(0E020C0E), C(40505010), C(09313839), C(06222426),
	C(02323032), C(84808404), C(49616829), C(83939013),
	C(07333437), C(C7E3E427), C(04202424), C(84A0A424),
	C(CBC3C80B), C(43535013), C(0A02080A), C(87838407),
	C(C9D1D819), C(4C404C0C), C(83838003), C(8F838C0F),
	C(CEC2CC0E), C(0B33383B), C(4A42480A), C(87B3B437)
};

static zuint32 const kc[K_CONSTANT_COUNT] = {
	C(9E3779B9), C(3C6EF373), C(78DDE6E6), C(F1BBCDCC),
	C(E3779B99), C(C6EF3733), C(8DDE6E67), C(1BBCDCCF),
	C(3779B99E), C(6EF3733C), C(DDE6E678), C(BBCDCCF1),
	C(779B99E3), C(EF3733C6), C(DE6E678D), C(BCDCCF1B)
};


Z_INLINE zuint8 byte(zuint32 x, zuint n)
	{return x >> (n << 3);}


#define F(x1, x2, x3, x4, r_base)		\
						\
	t0  = x3 ^ ks[r_base];			\
	t1  = x4 ^ ks[r_base + 1];		\
	t1 ^= t0;				\
						\
	t1  =					\
	ss0[byte(t1, 0)] ^ ss1[byte(t1, 1)] ^	\
	ss2[byte(t1, 2)] ^ ss3[byte(t1, 3)];	\
						\
	t0 += t1;				\
						\
	t0  =					\
	ss0[byte(t0, 0)] ^ ss1[byte(t0, 1)] ^	\
	ss2[byte(t0, 2)] ^ ss3[byte(t0, 3)];	\
						\
	t1 += t0;				\
						\
	t1  =					\
	ss0[byte(t1, 0)] ^ ss1[byte(t1, 1)] ^	\
	ss2[byte(t1, 2)] ^ ss3[byte(t1, 3)];	\
						\
	t0 += t1;				\
	x1 ^= t0;				\
	x2 ^= t1;


CIPHER_SEED_API
void seed_set_key(SEED *object, zuint32 const *key, zusize key_size)
	{
	zuint32 i, t0, t1, x1, x2, x3, x4, *ks = object->ks;

	x1 = z_uint32_big_endian(key[0]);
	x2 = z_uint32_big_endian(key[1]);
	x3 = z_uint32_big_endian(key[2]);
	x4 = z_uint32_big_endian(key[3]);

	for (i = 0; i < K_CONSTANT_COUNT; i++)
		{
		t0 = x1 + x3 - kc[i];
		t1 = x2 + kc[i] - x4;

		*(ks++) =
		ss0[byte(t0, 0)] ^ ss1[byte(t0, 1)] ^
		ss2[byte(t0, 2)] ^ ss3[byte(t0, 3)];

		*(ks++) =
		ss0[byte(t1, 0)] ^ ss1[byte(t1, 1)] ^
		ss2[byte(t1, 2)] ^ ss3[byte(t1, 3)];

		if (i % 2)
			{
			t0 = x3;
			x3 = (x3 << 8) ^ (x4 >> 24);
			x4 = (x4 << 8) ^ (t0 >> 24);
			}

		else	{
			t0 = x1;
			x1 = (x1 >> 8) ^ (x2 << 24);
			x2 = (x2 >> 8) ^ (t0 << 24);
			}
		}
	}


CIPHER_SEED_API
void seed_encipher(SEED *object, zuint32 const *block, zusize block_size, zuint32 *output)
	{
	zuint32 x1, x2, x3, x4, t0, t1, *ks = object->ks;

	for (block_size >>= 4; block_size; block_size--, block += 4, output += 4)
		{
		x1 = z_uint32_big_endian(block[0]);
		x2 = z_uint32_big_endian(block[1]);
		x3 = z_uint32_big_endian(block[2]);
		x4 = z_uint32_big_endian(block[3]);

		F(x1, x2, x3, x4,  0);
		F(x3, x4, x1, x2,  2);
		F(x1, x2, x3, x4,  4);
		F(x3, x4, x1, x2,  6);
		F(x1, x2, x3, x4,  8);
		F(x3, x4, x1, x2, 10);
		F(x1, x2, x3, x4, 12);
		F(x3, x4, x1, x2, 14);
		F(x1, x2, x3, x4, 16);
		F(x3, x4, x1, x2, 18);
		F(x1, x2, x3, x4, 20);
		F(x3, x4, x1, x2, 22);
		F(x1, x2, x3, x4, 24);
		F(x3, x4, x1, x2, 26);
		F(x1, x2, x3, x4, 28);
		F(x3, x4, x1, x2, 30);

		output[0] = z_uint32_big_endian(x3);
		output[1] = z_uint32_big_endian(x4);
		output[2] = z_uint32_big_endian(x1);
		output[3] = z_uint32_big_endian(x2);
		}
	}


CIPHER_SEED_API
void seed_decipher(SEED *object, zuint32 const *block, zusize block_size, zuint32 *output)
	{
	zuint32 x1, x2, x3, x4, t0, t1, *ks = object->ks;

	for (block_size >>= 4; block_size; block_size--, block += 4, output += 4)
		{
		x1 = z_uint32_big_endian(block[0]);
		x2 = z_uint32_big_endian(block[1]);
		x3 = z_uint32_big_endian(block[2]);
		x4 = z_uint32_big_endian(block[3]);

		F(x1, x2, x3, x4, 30);
		F(x3, x4, x1, x2, 28);
		F(x1, x2, x3, x4, 26);
		F(x3, x4, x1, x2, 24);
		F(x1, x2, x3, x4, 22);
		F(x3, x4, x1, x2, 20);
		F(x1, x2, x3, x4, 18);
		F(x3, x4, x1, x2, 16);
		F(x1, x2, x3, x4, 14);
		F(x3, x4, x1, x2, 12);
		F(x1, x2, x3, x4, 10);
		F(x3, x4, x1, x2,  8);
		F(x1, x2, x3, x4,  6);
		F(x3, x4, x1, x2,  4);
		F(x1, x2, x3, x4,  2);
		F(x3, x4, x1, x2,  0);

		output[0] = z_uint32_big_endian(x3);
		output[1] = z_uint32_big_endian(x4);
		output[2] = z_uint32_big_endian(x1);
		output[3] = z_uint32_big_endian(x2);
		}
	}


#if defined(CIPHER_SEED_BUILD_ABI) || defined(CIPHER_SEED_BUILD_MODULE_ABI)

	CIPHER_SEED_ABI ZCipherABI const abi_cipher_seed = {
		/* test_key		 */ NULL,
		/* set_key		 */ (ZCipherSetKey )seed_set_key,
		/* encipher		 */ (ZCipherProcess)seed_encipher,
		/* decipher		 */ (ZCipherProcess)seed_decipher,
		/* enciphering_size	 */ NULL,
		/* deciphering_size	 */ NULL,
		/* instance_size	 */ sizeof(SEED),
		/* key_minimum_size	 */ SEED_KEY_SIZE,
		/* key_maximum_size	 */ SEED_KEY_SIZE,
		/* key_word_size	 */ SEED_KEY_SIZE,
		/* enciphering_word_size */ SEED_WORD_SIZE,
		/* deciphering_word_size */ SEED_WORD_SIZE,
		/* features		 */ FALSE
	};

#endif

#if defined(CIPHER_SEED_BUILD_MODULE_ABI)

#	include <Z/ABIs/generic/module.h>

	static ZModuleUnit const unit = {
		"SEED", "SEED", Z_VERSION(1, 0, 0), &abi_cipher_seed
	};

	static ZModuleDomain const domain = {"Cipher", Z_VERSION(1, 0, 0), 1, &unit};
	Z_API_WEAK_EXPORT ZModuleABI const __module_abi__ = {1, &domain};

#endif


/* SEED.c EOF */