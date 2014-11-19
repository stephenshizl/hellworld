#!/bin/bash

FN="$2"
if [ -f $FN ];then
	echo -e "==== modify u-boot custom configs ===="
	for line in `cat "$FN"`
	do
		head=`expr substr "$line" 1 1`
		if [ "$head" = "#" ]; then
			continue
		fi

		config_head=`expr substr "$line" 1 6`
		if [ "$config_head" = "U-BOOT" ]; then
			echo "config u-boot" >/dev/null
		else
		#not u-boot config,by pass it
			continue
		fi
		line=${line:7}
		value=${line#*=}
		tag=${line%%=*}
		config=$tag
		echo -e $tag"="$value
		value_l=`tr '[A-Z]' '[a-z]' <<<"$value"` #value little
		#is yes or no
		if [ "$value_l" = "y" ]; then
			echo -e "is y"
			echo "#define $config" >> $1
			continue
		else
			if [ "$value_l" = "yes" ]; then
				echo -e "is yes"
				echo "#define $config" >> $1
				continue
			fi
		fi
		if [ "$value_l" = "n" ]; then
			echo -e "is n"
			echo "#undef $config" >> $1
			continue
		else
			if [ "$value_l" = "no" ]; then
				echo -e "is no"
				echo "#undef $config" >> $1
				continue
			fi
		fi

		#is str
		value_f=`expr substr "$value" 1 1`  #value first
		len=${#value}
		value_l=`expr substr "$value" $len 1` #value last
		if [ "$value_f" = "\"" ]; then
			if [ "$value_l" = "\"" ]; then
				echo "is str"
				echo "#define $config $value" >> $1
				continue
			fi
			#str may be error,bybass it,config next
			continue
		fi

		echo "is integer"
		echo "#define $config $value" >> $1
	done
fi
