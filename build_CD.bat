set pc1=NBL042045
set pc2=PCL038442
set pc3=DAVIDV-AIRPC

set demoName=Eira
set audioName=audio
set driveMount=E

if %computername%==%pc1% set NEODEV=C:\Users\davidv\Dropbox\NeoDev
if %computername%==%pc2% set NEODEV=C:\Users\10015228\Dropbox\NeoDev
if %computername%==%pc3% set NEODEV=X:\NeoDev

set daemonToolsBin="C:\Program Files\DAEMON Tools Lite\DTAgent.exe"
set mkisofs=%NEODEV%\_nainainTools\cdrtools\mkisofs.exe
set outputIso=%temp%\%demoName%.iso
set outputCue=%temp%\%demoName%.cue

set cdFlatPath=%temp%\output\cd\

set audioTrack=%NEODEV%\src\%demoName%\%audioName%.wav

@set path=%NEODEV%\m68k\bin;%path%
set buildErrLog=%NEODEV%\src\%demoName%\buildErr.log

rem daemon tools umount all drive
%daemonToolsBin% -unmount_all

md %cdFlatPath%

@REM Clean
del %outputIso% /q
del %outputCue% /q

if exist %outputIso% echo suppression erreur
if exist %outputIso% pause
if exist %outputCue% echo suppression erreur
if exist %outputCue% pause

del %NEODEV%\tmp\*.o
del *.pal
del *.o
del *.fix
del *.spr
del *.map
del *.bin
del *.prg
del dev_p1.rom

@REM Compile CRT0 (C Run Time library)
as -m68000 --register-prefix-optional crt0_cd.s -o %NEODEV%\tmp\crt0_cd.o

@REM Compile program
gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -c main.c -o %NEODEV%\tmp\main.o 2>%buildErrLog%
gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -c neo_core.c -o %NEODEV%\tmp\neo_core.o 2>>%buildErrLog%
gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -c neo_db.c -o %NEODEV%\tmp\neo_db.o 2>>%buildErrLog%
gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -c logoEffect.c -o %NEODEV%\tmp\logoEffect.o 2>>%buildErrLog%
gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -c neo_texter.c -o %NEODEV%\tmp\neo_texter.o 2>>%buildErrLog%
gcc -I%NEODEV%\m68k\include -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -c snowfield.c -o %NEODEV%\tmp\snowfield.o 2>>%buildErrLog%

rem gfx definition
call build_gfx.bat

@REM Link
gcc -L%NEODEV%\m68k\lib -m68000 -O3 -Wall -fomit-frame-pointer -ffast-math -fno-builtin -nostartfiles -nodefaultlibs -D__cd__ -Wl,-T%NEODEV%\src\system\neocd.x %NEODEV%\tmp\crt0_cd.o %NEODEV%\tmp\main.o %NEODEV%\tmp\neo_core.o %NEODEV%\tmp\neo_db.o %NEODEV%\tmp\logoEffect.o %NEODEV%\tmp\neo_texter.o %NEODEV%\tmp\snowfield.o %gfxObjectList% %NEODEV%\tmp\palettes.o -lcddactrl -lmath -linput -lvideo -lc -lgcc -o test.o

@REM Pad program rom
objcopy -O binary test.o test.prg

pause

@REM Pad modified roms. These are the result of the compilation
romwak /f dev_p1.rom 202-p1.bin 
romwak /p 202-p1.bin 202-p1.bin 1024 255 
romwak /w test.spr 202-c1.bin 202-c2.bin 
romwak /f 202-c1.bin 
romwak /f 202-c2.bin 
romwak /p 202-c1.bin 202-c1.bin 1024 255 
romwak /p 202-c2.bin 202-c2.bin 1024 255 
copy test.fix 202-s1.bin 

@REM Copy modified game roms to CD output directory
del %cdFlatPath%\*.spr
del %cdFlatPath%\*.fix
del %cdFlatPath%\*.prg
ren test.spr PB_CHR.SPR
ren test.fix PB_FIX.FIX
ren test.prg PB_PROG.PRG
move PB_CHR.SPR %cdFlatPath%\
move PB_FIX.FIX %cdFlatPath%\
move PB_PROG.PRG %cdFlatPath%\

@REM Clean
del %NEODEV%\tmp\*.o
del *.pal
del *.o
del *.fix
del *.spr
del *.map
del *.bin
del *.prg
del dev_p1.rom

rem Make ISO struct
copy %NEODEV%\src\%demoName%\output\cd\* %cdFlatPath%

rem mkisofs
%mkisofs% -o %outputIso% -pad %cdFlatPath%

rem cue gen
echo CATALOG 0000000000000 				>  %outputCue%
echo FILE "%demoName%.iso" BINARY		>> %outputCue%
echo  TRACK 01 MODE1/2048				>> %outputCue%
echo    INDEX 01 00:00:00				>> %outputCue%
echo FILE "%audioName%.wav" WAVE		>> %outputCue%
echo  TRACK 02 AUDIO					>> %outputCue%
echo    PREGAP 00:00:59					>> %outputCue%
echo    INDEX 01 00:00:00				>> %outputCue%

rem copy audio track
copy %audioTrack% %temp%
rem copy %audioTrack%  %NEODEV%\src\%demoName%\output\iso\

rem daemontoosl mount
%daemonToolsBin%  -mount dt, %driveMount%, %outputCue%

rem check
ping 127.0.0.1 -n 2
if not exist %driveMount%:\PB_PROG.PRG goto error_prg

rem launch emulator
pause
cd %NEODEV%\NeoCD_V0.20_win\ 
neocd.exe
goto end

:error_prg
notepad %buildErrLog%
goto end

goto end

:end
pause