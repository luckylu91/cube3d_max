list=`find . -name '*.c'`
list=`sed "s/^\.\///" <<< "$list"`
list=`grep -E -v 'libft|ft_printf|test|render3d|ray_march3d|minilibx-linux' <<< "$list"`
list=`grep -E -v "^_" <<< "$list"`
list=`awk '{print "SRCS +=\t\t\t" $0}' <<< "$list"`
echo "$list" | pbcopy
