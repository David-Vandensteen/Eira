rem GFX Def
set gfxList=triangle03down triangle03up triangle02down triangle02up triangle01down triangle01up snow
set gfxList=%gfxList% logo_76 logo_75 logo_74 logo_73 logo_72 logo_71 logo_70 logo_69 logo_68 logo_67 logo_66 logo_65 logo_64 logo_63 logo_62 logo_61 logo_60 logo_59 logo_58 logo_57 logo_56 logo_55 logo_54 logo_53 logo_52 logo_51 logo_50
set gfxList=%gfxList% fontA16 fontB16 shadow

set gfxBmpList=triangle03down.bmp triangle03up.bmp triangle02down.bmp triangle02up.bmp triangle01down.bmp triangle01up.bmp snow.bmp
set gfxBmpList=%gfxBmpList% logo_76.bmp logo_75.bmp logo_74.bmp logo_73.bmp logo_72.bmp logo_71.bmp logo_70.bmp logo_69.bmp logo_68.bmp logo_67.bmp logo_66.bmp logo_65.bmp logo_64.bmp logo_63.bmp logo_62.bmp logo_61.bmp logo_60.bmp logo_59.bmp logo_58.bmp logo_57.bmp logo_56.bmp logo_55.bmp logo_54.bmp logo_53.bmp logo_52.bmp logo_51.bmp logo_50.bmp
set gfxBmpList=%gfxBmpList% fontA16.bmp fontB16.bmp shadow.bmp

set gfxObjectList=%NEODEV%\tmp\triangle03down.o %NEODEV%\tmp\triangle02down.o %NEODEV%\tmp\triangle02up.o %NEODEV%\tmp\triangle03up.o %NEODEV%\tmp\triangle01down.o %NEODEV%\tmp\triangle01up.o %NEODEV%\tmp\snow.o
set gfxObjectList=%gfxObjectList% %NEODEV%\tmp\logo_76.o %NEODEV%\tmp\logo_75.o %NEODEV%\tmp\logo_74.o %NEODEV%\tmp\logo_73.o %NEODEV%\tmp\logo_72.o %NEODEV%\tmp\logo_71.o %NEODEV%\tmp\logo_70.o %NEODEV%\tmp\logo_69.o %NEODEV%\tmp\logo_68.o %NEODEV%\tmp\logo_67.o %NEODEV%\tmp\logo_66.o %NEODEV%\tmp\logo_65.o %NEODEV%\tmp\logo_64.o %NEODEV%\tmp\logo_63.o %NEODEV%\tmp\logo_62.o %NEODEV%\tmp\logo_61.o %NEODEV%\tmp\logo_60.o %NEODEV%\tmp\logo_59.o %NEODEV%\tmp\logo_58.o %NEODEV%\tmp\logo_57.o %NEODEV%\tmp\logo_56.o %NEODEV%\tmp\logo_55.o %NEODEV%\tmp\logo_54.o %NEODEV%\tmp\logo_53.o %NEODEV%\tmp\logo_52.o %NEODEV%\tmp\logo_51.o %NEODEV%\tmp\logo_50.o
set gfxObjectList=%gfxObjectList% %NEODEV%\tmp\fontA16.o %NEODEV%\tmp\fontB16.o %NEODEV%\tmp\shadow.o

@REM Generated palettes and fix
fixcnv fix_font.bmp -o test.fix -pal fix.pal
gfxcc -black fix.pal %gfxBmpList% -o test.spr
rem gfxcc -black fix.pal %gfx000%.bmp %gfx01%.bmp %gfx02%.bmp -o test.spr

@REM "Compile" images
bin2elf test.pal palettes %NEODEV%\tmp\palettes.o
rem bin2elf %gfx000%.map %gfx000% %NEODEV%\tmp\%gfx000%.o
for %%i in (%gfxList%) do bin2elf %%i.map %%i %NEODEV%\tmp\%%i.o
