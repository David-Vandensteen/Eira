if "%1"=="install" (
  echo Install NeoDev SDK...
  pushd scripts
  powershell -ExecutionPolicy Bypass -File neocore-setup.ps1 %appdata%\neocore
  popd
  goto :end
)

pushd src
set demoName=Eira
set output=%temp%\%demoName%
set outputIso=%output%\%demoName%.iso
set outputCue=%output%\%demoName%.cue

if "%1"=="run" (
  echo Trying to kill raine32.exe process...
  powershell "try { taskkill /IM raine32.exe /f } catch { }; exit 0"
  echo Choose Play Game on Raine menu
  timeout /t 2
  %appdata%\neocore\raine\raine32.exe %outputIso%
  popd
  goto :end
)

set NEODEV=%appdata%\neocore\neodev-sdk
set cdFlatPath=%output%\cdflat\
set buildTemp=%output%\build
set buildErrLog=%output%\build-error.log

set backupPath=%path%
set path=%NEODEV%\m68k\bin;%SystemRoot%\System32

:clean
rd /s /q %output%
if exist %output% echo clean error && goto :error

md %cdFlatPath%
md %buildTemp%

:compile-runtime
as -m68000 --register-prefix-optional crt0_cd.s -o %buildTemp%\crt0_cd.o
if not exist %buildTemp%\crt0_cd.o echo build crt error && goto :error

:compile-program
set gc0=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc0=%gc0% -nostartfiles -nodefaultlibs -D__cd__ -c main.c -o %buildTemp%\main.o 2>%buildErrLog%

set gc1=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc1=%gc1% -nostartfiles -nodefaultlibs -D__cd__ -c neo_core.c -o %buildTemp%\neo_core.o 2>>%buildErrLog%

set gc2=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc2=%gc2% -nostartfiles -nodefaultlibs -D__cd__ -c neo_db.c -o %buildTemp%\neo_db.o 2>>%buildErrLog%

set gc3=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc3=%gc3% -nostartfiles -nodefaultlibs -D__cd__ -c logoEffect.c -o %buildTemp%\logoEffect.o 2>>%buildErrLog%

set gc4=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc4=%gc4% -nostartfiles -nodefaultlibs -D__cd__ -c neo_texter.c -o %buildTemp%\neo_texter.o 2>>%buildErrLog%

set gc5=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc5=%gc5% -nostartfiles -nodefaultlibs -D__cd__ -c snowfield.c -o %buildTemp%\snowfield.o 2>>%buildErrLog%

set gc6=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc6=%gc6% -nostartfiles -nodefaultlibs -D__cd__ -c triangles.c -o %buildTemp%\triangles.o 2>>%buildErrLog%

set gc7=gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin
set gc7=%gc7% -nostartfiles -nodefaultlibs -D__cd__ -c backdropcolor.c -o %buildTemp%\backdropcolor.o 2>>%buildErrLog%

%gc0% && %gc1% && %gc2% && %gc3% && %gc4% && %gc5% && %gc6% && %gc7%

if not exist %buildTemp%\main.o echo build error && goto :error
if not exist %buildTemp%\neo_core.o echo build error && goto :error
if not exist %buildTemp%\neo_db.o echo build error && goto :error
if not exist %buildTemp%\logoEffect.o echo build error && goto :error
if not exist %buildTemp%\neo_texter.o echo build error && goto :error
if not exist %buildTemp%\snowfield.o echo build error && goto :error
if not exist %buildTemp%\triangles.o echo build error && goto :error
if not exist %buildTemp%\backdropcolor.o echo build error && goto :error

:define-gfx
set gfxList=triangle03down triangle03up triangle02down triangle02up triangle01down triangle01up snow
set gfxList=%gfxList% logo_76 logo_75 logo_74 logo_73 logo_72 logo_71 logo_70 logo_69 logo_68 logo_67
set gfxList=%gfxList% logo_66 logo_65 logo_64 logo_63 logo_62 logo_61 logo_60 logo_59 logo_58 logo_57
set gfxList=%gfxList% logo_56 logo_55 logo_54 logo_53 logo_52 logo_51 logo_50
set gfxList=%gfxList% fontA16 fontB16 shadow

set gfxBmpList=triangle03down.bmp triangle03up.bmp triangle02down.bmp triangle02up.bmp triangle01down.bmp triangle01up.bmp snow.bmp
set gfxBmpList=%gfxBmpList% logo_76.bmp logo_75.bmp logo_74.bmp logo_73.bmp logo_72.bmp logo_71.bmp logo_70.bmp logo_69.bmp logo_68.bmp
set gfxBmpList=%gfxBmpList% logo_67.bmp logo_66.bmp logo_65.bmp logo_64.bmp logo_63.bmp logo_62.bmp logo_61.bmp logo_60.bmp logo_59.bmp
set gfxBmpList=%gfxBmpList% logo_58.bmp logo_57.bmp logo_56.bmp logo_55.bmp logo_54.bmp logo_53.bmp logo_52.bmp logo_51.bmp logo_50.bmp
set gfxBmpList=%gfxBmpList% fontA16.bmp fontB16.bmp shadow.bmp

set gfxObjectList=%buildTemp%\triangle03down.o %buildTemp%\triangle02down.o %buildTemp%\triangle02up.o %buildTemp%\triangle03up.o
set gfxObjectList=%gfxObjectList% %buildTemp%\triangle01down.o %buildTemp%\triangle01up.o %buildTemp%\snow.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_76.o %buildTemp%\logo_75.o %buildTemp%\logo_74.o %buildTemp%\logo_73.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_72.o %buildTemp%\logo_71.o %buildTemp%\logo_70.o %buildTemp%\logo_69.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_68.o %buildTemp%\logo_67.o %buildTemp%\logo_66.o %buildTemp%\logo_65.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_64.o %buildTemp%\logo_63.o %buildTemp%\logo_62.o %buildTemp%\logo_61.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_60.o %buildTemp%\logo_59.o %buildTemp%\logo_58.o %buildTemp%\logo_57.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_56.o %buildTemp%\logo_55.o %buildTemp%\logo_54.o %buildTemp%\logo_53.o
set gfxObjectList=%gfxObjectList% %buildTemp%\logo_52.o %buildTemp%\logo_51.o %buildTemp%\logo_50.o
set gfxObjectList=%gfxObjectList% %buildTemp%\fontA16.o %buildTemp%\fontB16.o %buildTemp%\shadow.o

:generated-palettes
fixcnv fix_font.bmp -o %buildTemp%\test.fix -pal %buildTemp%\fix.pal
gfxcc -black %buildTemp%\fix.pal %gfxBmpList% -o %buildTemp%\test.spr
move *.map %buildTemp%

:compile-images
bin2elf %buildTemp%\test.pal palettes %buildTemp%\palettes.o
for %%i in (%gfxList%) do bin2elf %buildTemp%\%%i.map %%i %buildTemp%\%%i.o

:link
set link=gcc -L%NEODEV%\m68k\lib -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles
set link=%link% -nodefaultlibs -D__cd__ -Wl,-T%NEODEV%\src\system\neocd.x %buildTemp%\crt0_cd.o %buildTemp%\main.o
set link=%link% %buildTemp%\neo_core.o %buildTemp%\neo_db.o %buildTemp%\logoEffect.o %buildTemp%\neo_texter.o
set link=%link% %buildTemp%\snowfield.o %buildTemp%\palettes.o %buildTemp%\triangles.o %buildTemp%\backdropcolor.o
set link=%link% %gfxObjectList% -lcddactrl -lmath -linput -lvideo -lc -lgcc -o %buildTemp%\DEMO.o

%link%

if not exist %buildTemp%\DEMO.o echo link error && goto :error

:pad
objcopy -O binary %buildTemp%\DEMO.o %buildTemp%\DEMO.PRG
if not exist %buildTemp%\DEMO.PRG echo pad error && goto :error

:make-cdflat
copy %buildTemp%\test.spr %cdFlatPath%\DEMO.SPR
copy %buildTemp%\test.fix %cdFlatPath%\DEMO.FIX
copy %buildTemp%\DEMO.PRG %cdFlatPath%\DEMO.PRG
copy cd_template\* %cdFlatPath%

:make-iso
%NEODEV%\..\bin\mkisofs.exe -o %outputIso% -pad %cdFlatPath%

:restore-path
set %path%=%backupPath%

popd
goto :end

:error
set path=%backupPath%
popd
goto :end

:error_prg
notepad %buildErrLog%
goto :end

goto :end

:end