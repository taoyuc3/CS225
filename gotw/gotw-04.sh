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
� ��\�ks�62_�_��ڔ�%E�#��O�<Z���q�67��CQ��EjHʏk��~��x����%��洖,��b_X�{��z��׻��>���֎���o��>�o�~���z�����;l��Gx�yd@�y�\,��&�Ջ�u����ӽ?��.t���4��4������߻����#J�x9�l=-����ֽ�uo��l�h�Ҽ�x07۠%J����EI�P����c�ܿώ�d��Y���xƦ<�YP�Y�-sΊh���W��-�,�|�&i��i�Y&��,8��L�{���I��1/x6�XCV�����m�I��١��q	{���a�>�Ob~�ch�w?N�~�ji�E���QG����$��a�,����c`Z\b	?c?Kf�3�"0��c�P�m��>s�oL�ք)�a�/9�H�P��`�eQ�ܭ�t@uD C}\Z������T�����Q�E���"�KA� [��?�ܯ�v%�U�>��:J��w��t���G�o08�S^�$� ��ȇr�IcIߵ��o�O��v1A���)�$Q���c�j�x���
��������;>�b���ok����vn���x��~z���S8�������g����\�#���C�y�_��0���&�=;|��x?77��5�F�h`��u���S�u~����"Xg��A��;|b�<|r�1�M_��������+ky��ΰ���־����+�7���:�5Z�b�����2�l�!B`bRi�C<O�r����j1���؅��ZaYA�	�yãd�u�9�L�F�Z���o�t�)�����ֶ��wvz���Gy�olxl�}�@�&N��)����x�f�R:99�Ӱ`Y����`�Q6�2��(�Q�i6�؋ �r��g����= 輊�y8Kx4�}��$���ho�A�ׇ'���	�˸`!PTd˰�Y1㥯�E��,;����^�f<g�<FEゥ6��tV�>ͭ���<_�^���:�����uPF(:�H��"O�g�o�7�$����Q��5����$!��
������󃣡�s�KN��g�6<zm��@����4\^_��1O���ā7B�&U",�2pr�]~�w��dQdt3�p���wo�iS��69�1T��Y��*d-�|6�ɔX��k,��H���	W�L��fg��;�G��5� �)�1�]�ߓ7mz�/���WC�*�(�F/��������=��T	Lh�Z�i���=���L�j_�X[�����x�36�����|��TX�A����y4M�@�C�.D�C�w�Fc�i�	Vӧtf'��h�ԟ@}�aW��I�y��+T[�}&5��`!����p�7�����])g4uˋt���1^��Q٦�X�mMI9�w"&�'�wŤf�A����$(��������`.E���\N|�z9i�c�J�@lm��u�Ԗ֠�]�R��rM�����DT�a��^���I��`�S�����~�V�P����f� J�fb�x�|�ꎌ<!F��~�[.�����#�;~A-@���܆�`����_�/`Bϕ:J��	0%�p�W��}�T]g�)�(wY�[���s&�y�p7@}��X�}V����>ؽ{r�}����\)����	!H�Ű�C��E�����tl�a��=�c0��2��&��x�r�,����"$Sqri�n
�-�@*$%O3����L����ܰK�M4�5�S��E����S��'�$*�c&��s��י����ݮ��l!�fQn�M�r9������I�ZT�䳡�Ԥc�����!S�G��8@����A]OI �g��kO�>�/��榙��g��-�������p�y�Vή�*���A�������d�01�(:~� ���|�E�
��S�&��AhT�L�[��r��8��� m�)�JڿV�,���c?��B4�-���0W��Y�?Jae7Z�볠QQwj��������ΘC��H�/�.o��b�D�g^8I�����*��(���5�4D��a_�D��+ �:��IA�WDW�.�Z��]�^5(PG�ິB�](!��pf)�c������zX��R���b�!��`�����N����]70�H1T�ZP���$]Ng�+��\7챉r���j)�JmJy�SC�K )�� e�=��2��F:j�֖��I6�d�*X���ڇ��4�t�U�vPՈ�$�z"�q�F�M�Ӹ�ԫ���k�u�pDj�\@�VJwPyd(��mE�TNd1a���M�@!��c	�q �iN�2��H�ӈ/X{��[t�����ȇ��ϊp�#�m��G/�i�G��It�~:z�| �~ g�<��փ�B�0���|���(��J�ҧ����m��b�#��ޱ��䎈��8c�1f���W�Sk?i/3�m��E�����P9�}O�,�\*J ;5&ƗL&��w� JNl��q�8evp"���?�`e�gj�@��t|(��&�����n-��ُ��������9�+m�JTLm��a�q���ٯ������F�������n������."�(u����:��E�I1l8��ʆ�	�kfG:NndU"��y��I^����
����L�\i�Vd��'+%E��1�A��$���'Y:wl�@WdKZ`�C��%��ªq[,b�_��Fi'����8N��0��g4+�^�c_'ʣ��-�7h��̖�������J`*�R��[��5���)V��'�0�2Ny�]�(��fԥFU�&��SƜ������l1�=����0!|A����w�d�x���)rώ��G	g�3}��2�S�\�Qzx���g�ImTi㔯&3i���A� `�<�5�貥	������FΧ�M/�DMgJ$��!D��y}|�����w"y��]d#�QbA�݃)����$�i��*�^w!Q� #$��>.7�(�v��9�S��iq�U�-*S|TS�B�>B_�⅃�#>��!6ݕm=�!�܌
�e�)���؉5�lݒ;�(Bu�=A���L$���O�Jܓ��10[���*��ʳ��Q1���C�k�=+�u��а:��C�he�e��Y�k�Kӈ�+s�p���]亍t�Ѓ���VN����� �.<�Y�by
#�"|0p���U;i�2'(�%�����?f�*ph�����F���F;�t�SM��-afLEW��)/	�w�����=��f���{kg��[���ݾ�������|��K���e<F�t�5�<G�ux�����"�� bȍ�� ��D�}01�9k�揑�8�GE~�o����|�5�����>��9�a���BEQнn�w��5�j�0rYyE_u�,2[��(x�3+l��vE[�����n��-aR�T
�O�j�Y�R�J����74�am��ow�@�
�� �C3�:��mW�Jl�+�b�EzO�B�~jjM�f�%�6�VA�M�4�f�i��m�^�Jk�W��rp%ı�V�}�\��
�:�+j�`���_���_�|����+��������Ư6�5��Ay`�V���PF��lD�K��͘��Թ��S���,�B��j{�����O�	�~��.E���"�bVi`$攑;4�S��S�\��py� k���+�(7Ev����k�{Ӵd�*���T��]�#V+�,�,:���nkA%���dh��7���5�:����/Ǭ�a��4��d�����e�h��O���Ӎ��n����k�-(a(�,�΂l��B�L#��jH
JDLt�"bƪbd�H:p�W�)?��iZ���_���0�:���ʍ�t:��$l�t��M�o:���K<���v���}���۷NJ��;e ��f�f�xsM�i��}��p#��`X[��2kk�u�Uƚ�m��?)���bV��y�c��["�TZT6 P񏈴	H�s&�_:��y7U�H,k�\�x��h6�ܳ~6T���wV�tZyl$S��-<��fIo�����}�z��i�� P  