#include <stdlib.h>
#include <video.h>
#include <input.h>
#include <cddactrl.h>
#include "neo_core.h"
#include "logoEffect.h"



logoZoomEffect logoZoomEffectMake(WORD spriteId, WORD zoom, WORD vblSkip){
	logoZoomEffect r;
	r.spriteId = spriteId;
	r.zoom = zoom;
	r.vblSkip = vblSkip;
	return r;
}
void logoZoomEffectUpdate(logoZoomEffect logozoomeffect){	
//	WORD curSpriteId = get_current_sprite() + tileSizeNB(304) + tileSizeNB(304);
	WORD curSpriteId = get_current_sprite() + tileSizeNB(304);
	set_current_sprite(logozoomeffect.spriteId);
/*
	write_sprite_data((XPOS - 40) + (logozoomeffect.zoom / 2),
					  (YPOS + 15) - (logozoomeffect.zoom / 4),
					   15, (255 - logozoomeffect.zoom * 2) + 90,
					   tileSizeClipping(96), tileSizeNB(304),
					   (const PTILEMAP)&shadow);
*/
	switch (logozoomeffect.zoom){
	case 100:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo);
		set_current_sprite(curSpriteId);
		break;
	case 99:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_99);
		set_current_sprite(curSpriteId);
		break;
	case 98:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_98);
		set_current_sprite(curSpriteId);
		break;
	case 97:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_97);
		set_current_sprite(curSpriteId);
		break;
	case 96:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_96);
		set_current_sprite(curSpriteId);
		break;
	case 95:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_95);
		set_current_sprite(curSpriteId);
		break;
	case 94:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_94);
		set_current_sprite(curSpriteId);
		break;
	case 93:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_93);
		set_current_sprite(curSpriteId);
		break;
	case 92:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_92);
		set_current_sprite(curSpriteId);
		break;
	case 91:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_91);
		set_current_sprite(curSpriteId);
		break;
	case 90:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_90);
		set_current_sprite(curSpriteId);
		break;
	case 89:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_89);
		set_current_sprite(curSpriteId);
		break;
	case 88:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_88);
		set_current_sprite(curSpriteId);
		break;
	case 87:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_87);
		set_current_sprite(curSpriteId);
		break;
	case 86:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_86);
        set_current_sprite(curSpriteId);
		break;
	case 85:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_85);
        set_current_sprite(curSpriteId);
		break;
	case 84:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_84);
        set_current_sprite(curSpriteId);
		break;
	case 83:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_83);
        set_current_sprite(curSpriteId);
		break;
	case 82:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_82);
        set_current_sprite(curSpriteId);
		break;
	case 81:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_81);
        set_current_sprite(curSpriteId);
		break;
	case 80:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_80);
		set_current_sprite(curSpriteId);
		break;
	case 79:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_79);
		set_current_sprite(curSpriteId);
		break;
	case 78:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_78);
		set_current_sprite(curSpriteId);
		break;
	case 77:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_77);
		set_current_sprite(curSpriteId);
		break;
	case 76:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_76);
		set_current_sprite(curSpriteId);
		break;
	case 75:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_75);
		set_current_sprite(curSpriteId);
		break;
	case 74:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_74);
		set_current_sprite(curSpriteId);
		break;
	case 73:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_73);
		set_current_sprite(curSpriteId);
		break;
	case 72:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_72);
		set_current_sprite(curSpriteId);
		break;
	case 71:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_71);
		set_current_sprite(curSpriteId);
		break;
	case 70:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_70);
		set_current_sprite(curSpriteId);
		break;
	case 69:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_69);
		set_current_sprite(curSpriteId);
		break;
	case 68:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_68);
		set_current_sprite(curSpriteId);
		break;
	case 67:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_67);
		set_current_sprite(curSpriteId);
		break;
	case 66:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_66);
		set_current_sprite(curSpriteId);
		break;
	case 65:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_65);
		set_current_sprite(curSpriteId);
		break;
	case 64:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_64);
		set_current_sprite(curSpriteId);
		break;
	case 63:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_63);
		set_current_sprite(curSpriteId);
		break;
	case 62:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_62);
		set_current_sprite(curSpriteId);
		break;
	case 61:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_61);
		set_current_sprite(curSpriteId);
		break;
	case 60:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_60);
		set_current_sprite(curSpriteId);
		break;
	case 59:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_59);
		set_current_sprite(curSpriteId);
		break;
	case 58:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_58);
		set_current_sprite(curSpriteId);
		break;
	case 57:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_57);
		set_current_sprite(curSpriteId);
		break;
	case 56:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_56);
		set_current_sprite(curSpriteId);
		break;
	case 55:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_55);
		set_current_sprite(curSpriteId);
		break;
	case 54:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_54);
		set_current_sprite(curSpriteId);
		break;
	case 53:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_53);
		set_current_sprite(curSpriteId);
		break;
	case 52:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_52);
		set_current_sprite(curSpriteId);
		break;
	case 51:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_51);
		set_current_sprite(curSpriteId);
		break;
	case 50:
		write_sprite_data(LOGO_XPOS, LOGO_YPOS, 15, 255, tileSizeClipping(96), tileSizeNB(304), (const PTILEMAP)&logo_50);
		set_current_sprite(curSpriteId);
		break;
	default:
		break;
	}
}
