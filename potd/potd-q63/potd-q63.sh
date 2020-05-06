#!/bin/sh
# This script was generated using Makeself 2.3.0

ORIG_UMASK=`umask`
if test "n" = n; then
    umask 077
fi

CRCsum="1727256821"
MD5="983922f8e11d740de6c12f3cd3c60fd0"
TMPROOT=${TMPDIR:=/tmp}
USER_PWD="$PWD"; export USER_PWD

label="Extracting potd-q63"
script="echo"
scriptargs="The initial files can be found in the newly created directory: potd-q63"
licensetxt=""
helpheader=''
targetdir="potd-q63"
filesizes="2362"
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
	echo Uncompressed size: 20 KB
	echo Compression: gzip
	echo Date of packaging: Tue Apr 30 07:30:52 CDT 2019
	echo Built with Makeself version 2.3.0 on darwin16
	echo Build command was: "./makeself/makeself.sh \\
    \"--notemp\" \\
    \"../../questions/potd3_063_final_boss/potd-q63\" \\
    \"../../questions/potd3_063_final_boss/clientFilesQuestion/potd-q63.sh\" \\
    \"Extracting potd-q63\" \\
    \"echo\" \\
    \"The initial files can be found in the newly created directory: potd-q63\""
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
	echo archdirname=\"potd-q63\"
	echo KEEP=y
	echo NOOVERWRITE=n
	echo COMPRESS=gzip
	echo filesizes=\"$filesizes\"
	echo CRCsum=\"$CRCsum\"
	echo MD5sum=\"$MD5\"
	echo OLDUSIZE=20
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
	MS_Printf "About to extract 20 KB in $tmpdir ... Proceed ? [Y/n] "
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
        if test "$leftspace" -lt 20; then
            echo
            echo "Not enough space left in "`dirname $tmpdir`" ($leftspace KB) to decompress $0 (20 KB)" >&2
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
‹ ü?È\íYëoÛFÏ×ò¯û‚”²%Y~¨;mN\4i.Åá. È•´ÅUù¢¾¿ıföA.)Êé‡³¯v A|ÌÎÎÎó·ËşŞ“§Á`ğüøäÿ‰ú©M°xtr08|ş|p ƒıƒÁÉá8~òTdy¢*Ÿy²*b¾‘ÙÆãûIë(ÿÿ"Ôßó$ú8YÖçó‡òÿÉÑÑFÿ4üt|4xçÿ§¿ñ$Œ‹ˆÁÙo+Ø…W=˜ó¯ºß¤Á|JA²íyEÆ“	$ÁŒeó dåÑ©çå«9‹ØpäÙ±.Œ„ˆ/ ŒY²èu0G®½ïg–iyZ0àcX‰¦Á‚fAÎ"È§(&»0âL2á£ (’2£˜A(Öy¬X
3t&L8
*æŞ›Ûw×Cx¥¤Ó¸\X²à^è‰¬iğ*H$ßâÃtµ¿â %cYZÑt“€'0€ëÏ¿<ã9ƒSŠßÃ\ğ$Ï¶<ï»y32Hz7åHóA(’%dÀ,]åS2#)˜0ZµÀÉÑ)®XàŸD*’=áG†ëHYÆ#–•ÊËñrézU"A˜Ugy*p–ˆb2õvö<òPÒcıH«g¤j¤ËÊÉ:ğÅ#å+ß™ËSù\Æ‹rójş¬ÑúF¼•*¨wjå/ºÆx Ç{{ğîöêv/E‹¥\[(f3†•fG…y6ÅçhÉq‘„9ÉV9ö2Š rÄhI>™Dš‘9Ñ{é¦Hñ.§<fş–V·Ïfó|åwÌRµ´S~¢[¢†)‹Ù\¤h_²0WÒQÆú¤İ’'-áUÎRŠˆ|š’ÙÑúl¶’kÏ0|s“hò¨ï²‹3ÆLÙ"a5‰¿Ì#b¥ájoiı(ÇzımfÂdåEøç2Î„ NY­¼M0‘Y(D‘o+GwA¤ÄŠ÷d,´8¥ê”iÛ*”JŠäº+Ši›ˆå”Â=fãœæŸ=ê´Ø]ÊZi=J(ã)-UµFÖ‘SïÎ{â¨ÖÿË²şøïş¿po¿ÑÿOÿ¹şÿ˜ıŸÌ(Ìl€O0Ÿì',€"½Ø„ p@æ²ÒéšŠÏ‡C5Ê´„²0jšA\˜v€}&,ÇÁ’I>õí­ó9ÓïNk•cgzM€MÔLö#‹çØ®¡'ûm$°jåUÅÌ˜,EcÙÓhÒ.¦}eTöc¦øR¶7øƒ™ ¼Â2l~z2éKu¥²ÎPÍ_tº¥=üox&›»¬yx›sôÒ{Õıóît£PÙ`ôUá£‚¥d)c(Îï)5ßiŸ¿³E¶Œ´§¬—SŠ95^‘ŸûÒÖ·=~H;úvM¦\(œŸ+¶¾º}öÌê å»FìZq§0m†ƒ§ô|ç6Ò¬CŒ	Œ
íM©«jÖ—’=ğ23_Á£À<³q˜´ÑØ'Ô»0³:sï¢–6öX¢Æàİó{GŸÖÆ68%|Ôà³´»[—V¸¿zqŒ ş—6NİµKVÛèó”/M+ëPüÖÊBik;Şk=’J?^&Dˆ’ãlÁEHJªÒnKÚ,PÒ¢p³ÈgŒĞDB9ÉkÜ¼<ËPÖKYç00¡ô¨ì®ªÖr uSˆağS	%Û²Ğğ<x5¶¶d2	¹Ú«„EŠkÎõ½åBÛÉmFq‰¬ÜÖ(»´*!í‘Ù¶)Hmz†[&¥µN£qfÈèÚìmç-9U1ÂÖ¹¥y3}i+=í7°Nèi[B×Z{.£Bï¢-ÿ+MÖr×2èy¹S¯ÆS“_–ß¦$•YveöµçŒ¬Âqc~*mn3¬¾û“tä_ÿHGa±Q{+<ÆıQqj×¸µ¬ud™5~ÙĞï=»µ}î[D˜:ì†5Ã—º²¦~dY[ÊD#Ù•¡kÑ˜J§¥ÿ(em±T±üŒÿÎ>æÀeÂ¿35KŸc]¾»ÛqÊ˜/¹şÉÿÕÙàu™h¸ëhRŒ,»ëEY^OAğÍÁˆB¼ÄÔim­¹¥s>µAh{­ NZzêB ’Äf£é*6-§wQ6üş¼È¦G˜¬¾m±G&éÚØµ¬Î:\©/ú«vúß.QF@P` ¥éØù[Ö>bPDÔX·ZyY59×ÃHéhxpÒ›ÿ´QÕÀß©X‘7Z/ã÷BŒFAó6£Û;KU@Ël­¦Óãì\^ñè'“×l}p•ó­C“üg&®¬‘è1İÚd?ªlm4³Ä ¹’¾€ıº½îƒXVf­tüj)…Í˜lÂ†rÁë–lÀde§†¸*şUºĞœïƒx­dµ›m=vJë•‚&LjZ³õ;:âÒøAêDûhyr´¡à7¿ÜÜØ¢²^«~Ë.{ašP"W*³`¯UìµB¯–ˆ6ØY`i—y–t¾lõsÇkñó¿Ğƒÿ}íûßşÁÁqóüïxßÿ=òù_ˆ5„‹Ú¿Ú§ámÏ£òAáR¶$úT@G*r)’½ ®ÃNÕg	„mq‹'ùv°İ…ÃÍZ~ü²Ù"d;îÊrÔÑmÁLc/k-³…«’:B©û?ÂJ57s–Ñ´rj‹=ñ«B‹n“¾ÌÒ¨Î†aËÒÍ²ş",_—½äò³)n¤IÍ­
vŒE‘D—IdmË…“.X‹*OvC:(9;ƒmbRä>İ|3Â6½&ñA<Ÿt³6>“Â9Æ®‡<rı|bc³ÿ[ıÕêÿ¾¬ÿ®ş?
]¸~sùú3
»wûıßßêë¾ğ¼>à]Édw—î^Ş\ş@=Ì×ópwwğz!ô&Ğ»@ïA{7WÖ›«õ‡lCxêë¹;W]ÓsR¢ã}óÔ¿¹êÀÓ]H1è	xúç)ı†`°”1¡Ö³HjRÎ@^)1G‡²ÉĞû¦—Î 7†¾°õqeÁ‘#G9räÈ‘#G9räÈ‘#G9räÈ‘#G9räÈ‘#G9rô'¦ÿÎ P  