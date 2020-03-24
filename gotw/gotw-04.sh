#!/bin/sh
# This script was generated using Makeself 2.3.0

ORIG_UMASK=`umask`
if test "n" = n; then
    umask 077
fi

CRCsum="3008917204"
MD5="f633fdfc565494f5e9d2f936aa1047b8"
TMPROOT=${TMPDIR:=/tmp}
USER_PWD="$PWD"; export USER_PWD

label="Extracting gotw-04.sh"
script="echo"
scriptargs="The initial files can be found in the newly created directory: gotw-04/"
licensetxt=""
helpheader=''
targetdir="gotw-04"
filesizes="4120"
keep="y"
nooverwrite="n"
quiet="n"
nodiskspace="n"

print_cmd_arg=""
if type printf > /dev/null; then
    print_cmd="printf"
elif test -x /usr/ucb/echo; then
    print_cmd="/usr/ucb/echo"
else
    print_cmd="echo"
fi

unset CDPATH

MS_Printf()
{
    $print_cmd $print_cmd_arg "$1"
}

MS_PrintLicense()
{
  if test x"$licensetxt" != x; then
    echo "$licensetxt"
    while true
    do
      MS_Printf "Please type y to accept, n otherwise: "
      read yn
      if test x"$yn" = xn; then
        keep=n
	eval $finish; exit 1
        break;
      elif test x"$yn" = xy; then
        break;
      fi
    done
  fi
}

MS_diskspace()
{
	(
	if test -d /usr/xpg4/bin; then
		PATH=/usr/xpg4/bin:$PATH
	fi
	df -kP "$1" | tail -1 | awk '{ if ($4 ~ /%/) {print $3} else {print $4} }'
	)
}

MS_dd()
{
    blocks=`expr $3 / 1024`
    bytes=`expr $3 % 1024`
    dd if="$1" ibs=$2 skip=1 obs=1024 conv=sync 2> /dev/null | \
    { test $blocks -gt 0 && dd ibs=1024 obs=1024 count=$blocks ; \
      test $bytes  -gt 0 && dd ibs=1 obs=1024 count=$bytes ; } 2> /dev/null
}

MS_dd_Progress()
{
    if test x"$noprogress" = xy; then
        MS_dd $@
        return $?
    fi
    file="$1"
    offset=$2
    length=$3
    pos=0
    bsize=4194304
    while test $bsize -gt $length; do
        bsize=`expr $bsize / 4`
    done
    blocks=`expr $length / $bsize`
    bytes=`expr $length % $bsize`
    (
        dd ibs=$offset skip=1 2>/dev/null
        pos=`expr $pos \+ $bsize`
        MS_Printf "     0%% " 1>&2
        if test $blocks -gt 0; then
            while test $pos -le $length; do
                dd bs=$bsize count=1 2>/dev/null
                pcent=`expr $length / 100`
                pcent=`expr $pos / $pcent`
                if test $pcent -lt 100; then
                    MS_Printf "\b\b\b\b\b\b\b" 1>&2
                    if test $pcent -lt 10; then
                        MS_Printf "    $pcent%% " 1>&2
                    else
                        MS_Printf "   $pcent%% " 1>&2
                    fi
                fi
                pos=`expr $pos \+ $bsize`
            done
        fi
        if test $bytes -gt 0; then
            dd bs=$bytes count=1 2>/dev/null
        fi
        MS_Printf "\b\b\b\b\b\b\b" 1>&2
        MS_Printf " 100%%  " 1>&2
    ) < "$file"
}

MS_Help()
{
    cat << EOH >&2
${helpheader}Makeself version 2.3.0
 1) Getting help or info about $0 :
  $0 --help   Print this message
  $0 --info   Print embedded info : title, default target directory, embedded script ...
  $0 --lsm    Print embedded lsm entry (or no LSM)
  $0 --list   Print the list of files in the archive
  $0 --check  Checks integrity of the archive

 2) Running $0 :
  $0 [options] [--] [additional arguments to embedded script]
  with following options (in that order)
  --confirm             Ask before running embedded script
  --quiet		Do not print anything except error messages
  --noexec              Do not run embedded script
  --keep                Do not erase target directory after running
			the embedded script
  --noprogress          Do not show the progress during the decompression
  --nox11               Do not spawn an xterm
  --nochown             Do not give the extracted files to the current user
  --nodiskspace         Do not check for available disk space
  --target dir          Extract directly to a target directory
                        directory path can be either absolute or relative
  --tar arg1 [arg2 ...] Access the contents of the archive through the tar command
  --                    Following arguments will be passed to the embedded script
EOH
}

MS_Check()
{
    OLD_PATH="$PATH"
    PATH=${GUESS_MD5_PATH:-"$OLD_PATH:/bin:/usr/bin:/sbin:/usr/local/ssl/bin:/usr/local/bin:/opt/openssl/bin"}
	MD5_ARG=""
    MD5_PATH=`exec <&- 2>&-; which md5sum || command -v md5sum || type md5sum`
    test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which md5 || command -v md5 || type md5`
	test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which digest || command -v digest || type digest`
    PATH="$OLD_PATH"

    if test x"$quiet" = xn; then
		MS_Printf "Verifying archive integrity..."
    fi
    offset=`head -n 532 "$1" | wc -c | tr -d " "`
    verb=$2
    i=1
    for s in $filesizes
    do
		crc=`echo $CRCsum | cut -d" " -f$i`
		if test -x "$MD5_PATH"; then
			if test x"`basename $MD5_PATH`" = xdigest; then
				MD5_ARG="-a md5"
			fi
			md5=`echo $MD5 | cut -d" " -f$i`
			if test x"$md5" = x00000000000000000000000000000000; then
				test x"$verb" = xy && echo " $1 does not contain an embedded MD5 checksum." >&2
			else
				md5sum=`MS_dd_Progress "$1" $offset $s | eval "$MD5_PATH $MD5_ARG" | cut -b-32`;
				if test x"$md5sum" != x"$md5"; then
					echo "Error in MD5 checksums: $md5sum is different from $md5" >&2
					exit 2
				else
					test x"$verb" = xy && MS_Printf " MD5 checksums are OK." >&2
				fi
				crc="0000000000"; verb=n
			fi
		fi
		if test x"$crc" = x0000000000; then
			test x"$verb" = xy && echo " $1 does not contain a CRC checksum." >&2
		else
			sum1=`MS_dd_Progress "$1" $offset $s | CMD_ENV=xpg4 cksum | awk '{print $1}'`
			if test x"$sum1" = x"$crc"; then
				test x"$verb" = xy && MS_Printf " CRC checksums are OK." >&2
			else
				echo "Error in checksums: $sum1 is different from $crc" >&2
				exit 2;
			fi
		fi
		i=`expr $i + 1`
		offset=`expr $offset + $s`
    done
    if test x"$quiet" = xn; then
		echo " All good."
    fi
}

UnTAR()
{
    if test x"$quiet" = xn; then
		tar $1vf - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    else

		tar $1f - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    fi
}

finish=true
xterm_loop=
noprogress=n
nox11=n
copy=none
ownership=y
verbose=n

initargs="$@"

while true
do
    case "$1" in
    -h | --help)
	MS_Help
	exit 0
	;;
    -q | --quiet)
	quiet=y
	noprogress=y
	shift
	;;
    --info)
	echo Identification: "$label"
	echo Target directory: "$targetdir"
	echo Uncompressed size: 32 KB
	echo Compression: gzip
	echo Date of packaging: Thu Apr 18 12:08:47 CDT 2019
	echo Built with Makeself version 2.3.0 on darwin16
	echo Build command was: "../../../scripts/generateCodingQuestion/makeself/makeself.sh \\
    \"--notemp\" \\
    \"../gotw-04/\" \\
    \"gotw-04.sh\" \\
    \"Extracting gotw-04.sh\" \\
    \"echo\" \\
    \"The initial files can be found in the newly created directory: gotw-04/\""
	if test x"$script" != x; then
	    echo Script run after extraction:
	    echo "    " $script $scriptargs
	fi
	if test x"" = xcopy; then
		echo "Archive will copy itself to a temporary location"
	fi
	if test x"n" = xy; then
		echo "Root permissions required for extraction"
	fi
	if test x"y" = xy; then
	    echo "directory $targetdir is permanent"
	else
	    echo "$targetdir will be removed after extraction"
	fi
	exit 0
	;;
    --dumpconf)
	echo LABEL=\"$label\"
	echo SCRIPT=\"$script\"
	echo SCRIPTARGS=\"$scriptargs\"
	echo archdirname=\"gotw-04\"
	echo KEEP=y
	echo NOOVERWRITE=n
	echo COMPRESS=gzip
	echo filesizes=\"$filesizes\"
	echo CRCsum=\"$CRCsum\"
	echo MD5sum=\"$MD5\"
	echo OLDUSIZE=32
	echo OLDSKIP=533
	exit 0
	;;
    --lsm)
cat << EOLSM
No LSM.
EOLSM
	exit 0
	;;
    --list)
	echo Target directory: $targetdir
	offset=`head -n 532 "$0" | wc -c | tr -d " "`
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | UnTAR t
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
	--tar)
	offset=`head -n 532 "$0" | wc -c | tr -d " "`
	arg1="$2"
    if ! shift 2; then MS_Help; exit 1; fi
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | tar "$arg1" - "$@"
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
    --check)
	MS_Check "$0" y
	exit 0
	;;
    --confirm)
	verbose=y
	shift
	;;
	--noexec)
	script=""
	shift
	;;
    --keep)
	keep=y
	shift
	;;
    --target)
	keep=y
	targetdir=${2:-.}
    if ! shift 2; then MS_Help; exit 1; fi
	;;
    --noprogress)
	noprogress=y
	shift
	;;
    --nox11)
	nox11=y
	shift
	;;
    --nochown)
	ownership=n
	shift
	;;
    --nodiskspace)
	nodiskspace=y
	shift
	;;
    --xwin)
	if test "n" = n; then
		finish="echo Press Return to close this window...; read junk"
	fi
	xterm_loop=1
	shift
	;;
    --phase2)
	copy=phase2
	shift
	;;
    --)
	shift
	break ;;
    -*)
	echo Unrecognized flag : "$1" >&2
	MS_Help
	exit 1
	;;
    *)
	break ;;
    esac
done

if test x"$quiet" = xy -a x"$verbose" = xy; then
	echo Cannot be verbose and quiet at the same time. >&2
	exit 1
fi

if test x"n" = xy -a `id -u` -ne 0; then
	echo "Administrative privileges required for this archive (use su or sudo)" >&2
	exit 1	
fi

if test x"$copy" \!= xphase2; then
    MS_PrintLicense
fi

case "$copy" in
copy)
    tmpdir=$TMPROOT/makeself.$RANDOM.`date +"%y%m%d%H%M%S"`.$$
    mkdir "$tmpdir" || {
	echo "Could not create temporary directory $tmpdir" >&2
	exit 1
    }
    SCRIPT_COPY="$tmpdir/makeself"
    echo "Copying to a temporary location..." >&2
    cp "$0" "$SCRIPT_COPY"
    chmod +x "$SCRIPT_COPY"
    cd "$TMPROOT"
    exec "$SCRIPT_COPY" --phase2 -- $initargs
    ;;
phase2)
    finish="$finish ; rm -rf `dirname $0`"
    ;;
esac

if test x"$nox11" = xn; then
    if tty -s; then                 # Do we have a terminal?
	:
    else
        if test x"$DISPLAY" != x -a x"$xterm_loop" = x; then  # No, but do we have X?
            if xset q > /dev/null 2>&1; then # Check for valid DISPLAY variable
                GUESS_XTERMS="xterm gnome-terminal rxvt dtterm eterm Eterm xfce4-terminal lxterminal kvt konsole aterm terminology"
                for a in $GUESS_XTERMS; do
                    if type $a >/dev/null 2>&1; then
                        XTERM=$a
                        break
                    fi
                done
                chmod a+x $0 || echo Please add execution rights on $0
                if test `echo "$0" | cut -c1` = "/"; then # Spawn a terminal!
                    exec $XTERM -title "$label" -e "$0" --xwin "$initargs"
                else
                    exec $XTERM -title "$label" -e "./$0" --xwin "$initargs"
                fi
            fi
        fi
    fi
fi

if test x"$targetdir" = x.; then
    tmpdir="."
else
    if test x"$keep" = xy; then
	if test x"$nooverwrite" = xy && test -d "$targetdir"; then
            echo "Target directory $targetdir already exists, aborting." >&2
            exit 1
	fi
	if test x"$quiet" = xn; then
	    echo "Creating directory $targetdir" >&2
	fi
	tmpdir="$targetdir"
	dashp="-p"
    else
	tmpdir="$TMPROOT/selfgz$$$RANDOM"
	dashp=""
    fi
    mkdir $dashp $tmpdir || {
	echo 'Cannot create target directory' $tmpdir >&2
	echo 'You should try option --target dir' >&2
	eval $finish
	exit 1
    }
fi

location="`pwd`"
if test x"$SETUP_NOCHECK" != x1; then
    MS_Check "$0"
fi
offset=`head -n 532 "$0" | wc -c | tr -d " "`

if test x"$verbose" = xy; then
	MS_Printf "About to extract 32 KB in $tmpdir ... Proceed ? [Y/n] "
	read yn
	if test x"$yn" = xn; then
		eval $finish; exit 1
	fi
fi

if test x"$quiet" = xn; then
	MS_Printf "Uncompressing $label"
fi
res=3
if test x"$keep" = xn; then
    trap 'echo Signal caught, cleaning up >&2; cd $TMPROOT; /bin/rm -rf $tmpdir; eval $finish; exit 15' 1 2 3 15
fi

if test x"$nodiskspace" = xn; then
    leftspace=`MS_diskspace $tmpdir`
    if test -n "$leftspace"; then
        if test "$leftspace" -lt 32; then
            echo
            echo "Not enough space left in "`dirname $tmpdir`" ($leftspace KB) to decompress $0 (32 KB)" >&2
            echo "Use --nodiskspace option to skip this check and proceed anyway" >&2
            if test x"$keep" = xn; then
                echo "Consider setting TMPDIR to a directory with more free space."
            fi
            eval $finish; exit 1
        fi
    fi
fi

for s in $filesizes
do
    if MS_dd_Progress "$0" $offset $s | eval "gzip -cd" | ( cd "$tmpdir"; umask $ORIG_UMASK ; UnTAR xp ) 1>/dev/null; then
		if test x"$ownership" = xy; then
			(PATH=/usr/xpg4/bin:$PATH; cd "$tmpdir"; chown -R `id -u` .;  chgrp -R `id -g` .)
		fi
    else
		echo >&2
		echo "Unable to decompress $0" >&2
		eval $finish; exit 1
    fi
    offset=`expr $offset + $s`
done
if test x"$quiet" = xn; then
	echo
fi

cd "$tmpdir"
res=0
if test x"$script" != x; then
    if test x"$verbose" = x"y"; then
		MS_Printf "OK to execute: $script $scriptargs $* ? [Y/n] "
		read yn
		if test x"$yn" = x -o x"$yn" = xy -o x"$yn" = xY; then
			eval "\"$script\" $scriptargs \"\$@\""; res=$?;
		fi
    else
		eval "\"$script\" $scriptargs \"\$@\""; res=$?
    fi
    if test "$res" -ne 0; then
		test x"$verbose" = xy && echo "The program '$script' returned an error code ($res)" >&2
    fi
fi
if test x"$keep" = xn; then
    cd $TMPROOT
    /bin/rm -rf $tmpdir
fi
eval $finish; exit $res
‹ ¯¸\íksÛ62_Í_øÚ”²%Eò#‘OÓ<Z·›q“67½ÄCQÄEjHÊkİß~»€x”íÌ%¹´æ´–,‹Åb_X¥{ÿÎz½Ş×»»Œ>ˆÏŞÖø”ëoïì>èoí~½³Ízı­Ş×ı;l÷ÎGx–yd@Êy”\,ã¨À&“Õ‹Äu”ŸŸÉÓ½?¢¤.tÿìì4îÿ4Úû¿½»ûß»İÿşü#JÂx9æl=-£¼èÎÖ½²uo³îlßh‰Ò¼Èx07Û %J¦ûçEIÁP¢üûİcğÜ¿ÏƒdœÎY²œxÆ¦<áYP¤Y›-sÎŠhÎı£W‡‡-ä,ç|Ì&iÆæiÆY&ø,8ÒLá{Ãò£IĞå1/x6XCVåˆÌßÚÚm©I¼ëÙ¡™Úq	{Èú½aù>ÎOb~Êch‡w?N§~Òji€E–‚QGÅ€ìö$®¼aº,ööØúc`Z\b	?c?Kf¯3è"0ŒcPõm°ş>s€oLÕÖ„)êa¡/9ºH—P–ó¬`“eQšÜ­Òt@uD C}\Zô†ğ±ÇøØÜT‹ØÙóøQ›E­¡ê"˜KA• [€Œ?ò‹Ü¯¥v%ãU´>ƒş:J‘ÈwùtúšƒGé˜o08ÛS^œ$ğ ‚œÈ‡rÿIcIßµèóoåO¢v1AÆçé)—$Q»Àéc·jÊx±ÌØ
ïÒûŸêÿçÁ;>‰bşéôok«¢ÿ·vnõÿÇx¾~zôèùS8¨µ½Ÿ¾ıágù½›²\#ù•¬Cêy_¿˜0’éæ&¾=;|ôë€x?77ûô5Fáh`u¦¬óSu~âşòó"XgÁÇAúÚ;|bà<|r”1üM_Å”ë¾ÍÁşûÂ—+kyşÎ°×ØòÖ¾ğŸ´Ô+Ã7š³Å:©5ZòbÀ”£¤Ù2Ól™!B`bRi•C<O³r ÇÛÈj1˜°‹Ø…ZaYA‡	ëyaÌƒdà­u²9ëLØF×ZğÛçoôtï›²ñ)ôÿÖÖöÖ¶£ÿwvz·şÿGyîolxlƒ}ƒ@©&N¦Ñ)Šú¿xĞfÔR:99´Ó°`YÌĞÇŞ`ìQ6ö2ø÷(ßQËi6Ø‹ ‹röŒg€¿àŒ= è¼Šçy8Kx4–}’$âìÇho÷A—×‡'¤ú	ŸË¸`!PTdË°ÈY1ã¥¯ÜE õ,;“€^Şf<gà<FEã‚¥6ãÑtV°>Í­¥ë­<_í^ÎÀêœ:¶ú­ªÅuPF(:ûHÔÉ"O“gùo½7İ$Œ¡±ÊQ…¯5‹ŒŸ$!²‘
·øàèåÉóƒ£¡ÙsÄKN½gâ6<zmÍê@¯İÓÁ4\^_ûã1O¦ÅìÄ7B—&U",ê2prË]~¬wŒÏdQdt3ÚpšÄwo·iSÂÚ69è1TößY‡ñ*d-¦|6¬É”X±¤k,§H°…¤	W’LÒİfg³¥;×Gƒ5¿ í)¹1£]Íß“7mz‰/„ËâWC¨*¹(£F/ÆÊØÑæÓâÂ=ŞáT	LhóZòiœæí=–ÂğLÍj_´X[ó§À¾–xÁ36ç äÀ»Ä|ÅèTX”A´Œ»äy4Mæ@İC–.DšCwšFc¦i¤	VÓ§tf'Œ£hµÔŸ@}úaW¾›I‰y°Ø+T[ëª}&5Ëó`!é÷ßpŞ7åü’Ã])g4uË‹t±Œ’1^†©QÙ¦ñXá†mMI9ªw"&É'¼wÅ¤fêAÍÌÄÔ$(ŠİÀ©¥`.E•´’\N|Éz9iÙcîJı@lmÔåuèÔ–Ö “]R¬ìrMŒ‘ğëÃDTœaÌõ^§ÍõIšù`óSÖõâôú~·VºPÍØÑöfè Jƒfb›xù|òêŒ<!F£¥~æ[.„ª§€#Û;~A-@‰¥ŒÜ†Ÿ`ÎòğÁ_ø/`BÏ•:Jœ­	0%ÒpàWŒÏ}©T]gˆ)©(wYÛ[‘œ¬s&ºyôp7@}õ¥XÈ}Vèšö®ô>Ø½{r‚}°çæ¤\)€¿¡	!HÉÅ°ÎC€ÉE‰§åÈîtlÁa‚¤=Öc0„2¼Â&—Âx¬r°,¼µ¦¼"$Sqriûn
-’@*$%O3´ÁàóLÙ»¶²Ü°K«M4û5‚SœñE„œ€„Sˆü'ğ$*à c&ä‚ñsÀ×™•­­±İ®Äàl!§fQn¥M•r9˜”Ş“¶©Iï¸ZTüä³¡•Ô¤c–¹˜ÉÌ!S˜Gİ8@©“¥A]OI ’gŠ¾kO•>í£/ìàæ¦™êçg”ú-óûôùº£pyûVÎ®Î*›§²AÒäÁÔìäçd01Ä(:~À „é|ŞEÉ
«¤S&ĞÅAhT¿Là[úrùÒ8÷Åæš m‡)­JÚ¿VÍ,–ùìc?™õB4û-ÃşÖ0W“çY¸?Jae7Z‡ë³ QQwj“Üàô’³ÒÎ˜CÏÔHË/Ñ.o‰¥bµD³g^8IÊÍÎÚû*Á (ñí™Ú5ì4DíÒa_åD‹í+ Œ:ÊÔIAõWDW”.óZÇÂ]Ñ^5(PGÛàº´B®](!ÜÍpf)ãcµş¡ƒæìzX¤÷R¶ë©à¨b´!²Ô`÷™ßNŠ–ƒÊ]70şH1TÃZPèàñ$]NgŸ+—È\7ì±‰råá«Øj)ËJmJy®SC¦K )×Õ eÚ=ˆ2íÊF:jîÖ–îI6ßd³*X”Ÿ­Ú‡õÔ4‰t¹U‘vPÕˆô$åz"ıq©F¤M“Ó¸™Ô«Š´ákâu¸pDj–\@íVJwPyd(×ÂmEïTNd1aš€M°@!™Óc	q ùiNÅ2›óHªÓˆ/X{–“[t®ğ¬È‡¹¡ÏŠpè#©mÒ÷G/ìiG‚ôItÎ~:zª| «~ gş<¸‰Öƒ–B£0§ÃÆ|´œÒ(ŠÿJÒ§¢û’mµğ˜b´#éîŞ±ğñäˆ£ò8cÊ1fø –WÙSk?i/3ÑmÍñE—­æç±ËP9õ}Où,á\*J ;5&Æ—L&÷w¯ JNlÅÒqò8evp"Êş³?ş`eÈgj¹@»t|(œÖ&ª‘©íÁn-ß°ÙáÏÀ³ÜÂÿ9±+mÈJTLmªa£qŸ›¦Ù¯Ÿ¥²¹’·Fş«¢Œ®¹‚n‘ª­‰‰Å."ó(u‚±®Ê:¢«Eæ I1l8‰®Ê†Ù	ÊkfG:NndU"ïÆy‘ëI^Õÿ­¬
—±ù×L¶\iÃVdÜ’'+%E‰Ê1•AåÚ$•É­'Y:wl@WdKZ`¾Cç“%Şé‰Âªq[,bÀ_¡©Fi'°‰ƒó8N“¯0§§g4+‚^“c_'Ê£êË-“7h¨³Ì–ƒ£–«¶ˆ¨J`*§R¨[Ë5’¼’)VÉ'ò£0­2Ny]ä(•êfÔ¥FUÓ&˜ƒSÆœ¸¢ÓÉÀÉl1û=‹¬ôİ0!|A«°Ñw¬dìxº·)rÏô›G	gË3}´Ü2ÑSˆ\‹QzxÃáÛgªImTiã”¯&3i¹™èA· `§<”5´è²¥	ˆ»¤ĞáøFÎ§ÀM/¯DMgJ$Ğ!DÕÖy}|øêÉÁÑw"y©„]d#éQbA İƒ)÷ó¤ò$åi–ë*µ^w!QÉ #$ô‘>.7»(švÏÄ9éS£´iqÄU-*S|TSëBÂ>B_„â…ƒ»#>Åê!6İ•m=Ó!ÛÜŒ
“e¥)–—úØ‰5§lİ’;Ê(Buî=A“©ëL$¶é†õOãJÜ“·©10[êÜß*‘Ê³îÚQ1¾æÒCä k¬=+uÌĞ°:™‘C°heeã•éYïkíKÓˆéƒ+s´p¨°Ğ]äºtĞƒœ¼VN•÷¯¿ñ‡¸ †.<‚YŒby
#ã"|0p“×åU;i”2'(ï‰%«Œ¨§ß?fÏ*ph¡›ãëÑF‚ã¤åF;¾tSM„É-afLEW³À)/	Îwâ›òûò¶€ñ=ëÿfŸ¨ş{kg÷[ÿ×Ûİ¾­ÿû˜õ¸|Æ¦K–ÏÒe<Ft¶5ã<GĞuxÁ°ÑûÇ"¦ó bÈÀ½ ¦Dó}01º9k¥æ‘Â8šGE~Õo–æÁÂ|¿5²Ôˆíß>©ß9éaÉ÷BEQĞ½n¸wòú5£jŸ0rYyE_u,2[â(x–3+lî°ÚvE[Ãûş·ÍnÅ-aRõT
ğO“jí•Y£î•¥R›J¢Œ±ä74ßamÀêowŒ@Ê
úÌ šC3´:êï‡mWÖJlˆ+bÅEzOƒB¦~jjMëf“%¢6•VA‹M¿4”f£iğímì‡^ÃJk«WšØrp%Ä±±VÓ}ƒ\¢Â–
å¬:­+jò`ñ—ğÿ_Õş«_˜|šßíô+öûÖşÿÿÛÇÆ¯65µúAy`éVƒ”…PF®lD­K‚…Í˜Á¡Ô¹§œSŒ…é,ûB”‹j{°ª—ºªOé	³~—ò.Eğç"ÁbVi`$æ”‘;4™SëÂS”\ˆ¤pyÛ kª–‡+â(7Ev³²šÆkú{Ó´d­*‰—÷Tõ²]¯#V+Ê,Ö,:•‹nkA%˜Õêdhò7¼Àš5ú:ñ×Á°/Ç¬Óa¿à4øò¯d½ÍÌêó¿eèhèÿOÿõ ÓÿúnõÿçªÿkÃ-(a(ø,ÍÎ‚lÌÆB¼L#’ÊjH
JDLtÇ"bÆªbdÍH:p”Wƒ)?æ‹iZãáÓ_â—¡0÷:ªö°ÊŞt:ûÌ$lßtÀÖMôo: §»K<¡¸¢v€ù¼}«ÕöÛ·NJ­¨;e º¶fşfÍxsMiğªÎ}ƒ¹p#»ò`X[³â2kk¥uÖUÆš÷mƒˆ?)ƒ¹ªbV¿ÔyÍc¶È["ÑTZT6 Pñˆ´	Hşs&¿_:°ò¶y7UâH,k¾\³x¨h6ªÜ³~6T¦´…wVÒtZyl$SâÈ-<®İfIoŸÛçö¹}şzÏäiù P  