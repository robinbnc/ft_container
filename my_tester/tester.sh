#!/bin/bash

#grep -v "Baeldung"
for filename in ./map/*.cpp; do

	c++ -Wall -Wextra -Werror -std=c++98 $filename && ./a.out | grep -v "max_size" > std_vector.out
	c++ -Wall -Wextra -Werror -std=c++98 -D NAME_SPACE="ft" $filename && ./a.out | grep -v "max_size" > ft_vector.out
	echo $filename | rev | cut -d '/' -f 1 | rev | sed "s/.cpp//g" | sed "s/_/ /g" | tr '\n' ' ';
	echo -ne "\t\t\t:\t";
	diff std_vector.out ft_vector.out > /dev/null
	if (($? == 0))
	then
		echo "✅";
	else
		echo "❌";
	fi
	rm *.out
done


# echo "compile std"
# c++ -Wall -Wextra -Werror -std=c++98 test.cpp && ./a.out > std_vector.out
# echo "compile ft"
# c++ -Wall -Wextra -Werror -std=c++98 -D NAME_SPACE="FT" test.cpp && ./a.out > ft_vector.out
# sleep 1
# diff std_vector.out ft_vector.out
# rm *.out