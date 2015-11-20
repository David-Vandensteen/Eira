rem GFX Def
set gfxList=background triangle03down triangle03up triangle02down triangle02up triangle01down triangle01up snow
set gfxList=%gfxList% logo logo_99 logo_98 logo_97 logo_96 logo_95 logo_94 logo_93 logo_92 logo_91 logo_90 logo_89 logo_88 logo_87 logo_86 logo_85 logo_84 logo_83 logo_82 logo_81 logo_80 logo_79 logo_78 logo_77 logo_76 logo_75 logo_74 logo_73 logo_72 logo_71 logo_70 logo_69 logo_68 logo_67 logo_66 logo_65 logo_64 logo_63 logo_62 logo_61 logo_60 logo_59 logo_58 logo_57 logo_56 logo_55 logo_54 logo_53 logo_52 logo_51 logo_50
set gfxList=%gfxList% fontA16 fontB16 shadow

set gfxBmpList=background.bmp triangle03down.bmp triangle03up.bmp triangle02down.bmp triangle02up.bmp triangle01down.bmp triangle01up.bmp snow.bmp
set gfxBmpList=%gfxBmpList% logo.bmp logo_99.bmp logo_98.bmp logo_97.bmp logo_96.bmp logo_95.bmp logo_94.bmp logo_93.bmp logo_92.bmp logo_91.bmp logo_90.bmp logo_89.bmp logo_88.bmp logo_87.bmp logo_86.bmp logo_85.bmp logo_84.bmp logo_83.bmp logo_82.bmp logo_81.bmp logo_80.bmp logo_79.bmp logo_78.bmp logo_77.bmp logo_76.bmp logo_75.bmp logo_74.bmp logo_73.bmp logo_72.bmp logo_71.bmp logo_70.bmp logo_69.bmp logo_68.bmp logo_67.bmp logo_66.bmp logo_65.bmp logo_64.bmp logo_63.bmp logo_62.bmp logo_61.bmp logo_60.bmp logo_59.bmp logo_58.bmp logo_57.bmp logo_56.bmp logo_55.bmp logo_54.bmp logo_53.bmp logo_52.bmp logo_51.bmp logo_50.bmp
set gfxBmpList=%gfxBmpList% fontA16.bmp fontB16.bmp shadow.bmp

set gfxObjectList=%NEODEV%\tmp\background.o %NEODEV%\tmp\triangle03down.o %NEODEV%\tmp\triangle02down.o %NEODEV%\tmp\triangle02up.o %NEODEV%\tmp\triangle03up.o %NEODEV%\tmp\triangle01down.o %NEODEV%\tmp\triangle01up.o %NEODEV%\tmp\snow.o
set gfxObjectList=%gfxObjectList% %NEODEV%\tmp\logo.o %NEODEV%\tmp\logo_99.o %NEODEV%\tmp\logo_98.o %NEODEV%\tmp\logo_97.o %NEODEV%\tmp\logo_96.o %NEODEV%\tmp\logo_95.o %NEODEV%\tmp\logo_94.o %NEODEV%\tmp\logo_93.o %NEODEV%\tmp\logo_92.o %NEODEV%\tmp\logo_91.o %NEODEV%\tmp\logo_90.o %NEODEV%\tmp\logo_89.o %NEODEV%\tmp\logo_88.o %NEODEV%\tmp\logo_87.o %NEODEV%\tmp\logo_86.o %NEODEV%\tmp\logo_85.o %NEODEV%\tmp\logo_84.o %NEODEV%\tmp\logo_83.o %NEODEV%\tmp\logo_82.o %NEODEV%\tmp\logo_81.o %NEODEV%\tmp\logo_80.o %NEODEV%\tmp\logo_79.o %NEODEV%\tmp\logo_78.o %NEODEV%\tmp\logo_77.o %NEODEV%\tmp\logo_76.o %NEODEV%\tmp\logo_75.o %NEODEV%\tmp\logo_74.o %NEODEV%\tmp\logo_73.o %NEODEV%\tmp\logo_72.o %NEODEV%\tmp\logo_71.o %NEODEV%\tmp\logo_70.o %NEODEV%\tmp\logo_69.o %NEODEV%\tmp\logo_68.o %NEODEV%\tmp\logo_67.o %NEODEV%\tmp\logo_66.o %NEODEV%\tmp\logo_65.o %NEODEV%\tmp\logo_64.o %NEODEV%\tmp\logo_63.o %NEODEV%\tmp\logo_62.o %NEODEV%\tmp\logo_61.o %NEODEV%\tmp\logo_60.o %NEODEV%\tmp\logo_59.o %NEODEV%\tmp\logo_58.o %NEODEV%\tmp\logo_57.o %NEODEV%\tmp\logo_56.o %NEODEV%\tmp\logo_55.o %NEODEV%\tmp\logo_54.o %NEODEV%\tmp\logo_53.o %NEODEV%\tmp\logo_52.o %NEODEV%\tmp\logo_51.o %NEODEV%\tmp\logo_50.o
set gfxObjectList=%gfxObjectList% %NEODEV%\tmp\fontA16.o %NEODEV%\tmp\fontB16.o %NEODEV%\tmp\shadow.o

@REM Generated palettes and fix
fixcnv fix_font.bmp -o test.fix -pal fix.pal
gfxcc -black fix.pal %gfxBmpList% -o test.spr
rem gfxcc -black fix.pal %gfx000%.bmp %gfx01%.bmp %gfx02%.bmp -o test.spr

@REM "Compile" images
bin2elf test.pal palettes %NEODEV%\tmp\palettes.o
rem bin2elf %gfx000%.map %gfx000% %NEODEV%\tmp\%gfx000%.o
for %%i in (%gfxList%) do bin2elf %%i.map %%i %NEODEV%\tmp\%%i.o
