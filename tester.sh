#!/bin/bash

echo "compile std"
c++ -Wall -Wextra -Werror -std=c++98 test.cpp && ./a.out > std_vector.out
echo "compile ft"
c++ -Wall -Wextra -Werror -std=c++98 -D NAME_SPACE="FT" test.cpp && ./a.out > ft_vector.out
sleep 1
diff std_vector.out ft_vector.out
rm *.out