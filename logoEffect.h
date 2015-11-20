#ifndef LOGOEFFECT_H
#define LOGOEFFECT_H
extern TILEMAP logo, logo_99, logo_98, logo_97, logo_96, logo_95, logo_94, logo_93, logo_92, logo_91, logo_90, logo_89, logo_88, logo_87, logo_86, logo_85, logo_84, logo_83, logo_82, logo_81, logo_80, logo_79, logo_78, logo_77, logo_76, logo_75, logo_74, logo_73, logo_72, logo_71, logo_70, logo_69, logo_68, logo_67, logo_66, logo_65, logo_64, logo_63, logo_62, logo_61, logo_60, logo_59, logo_58, logo_57, logo_56, logo_55, logo_54, logo_53, logo_52, logo_51, logo_50;
extern TILEMAP shadow;

typedef struct logoZoomEffect logoZoomEffect;
struct logoZoomEffect{
	WORD spriteId;
	WORD zoom;
	WORD vblSkip;
};
typedef struct logoZoomEffectShadow logoZoomEffectShadow;
logoZoomEffect logoZoomEffectMake(WORD spriteId, WORD zoom, WORD vblSkip);
void logoZoomEffectUpdate(logoZoomEffect logozoomeffect);

#endif